#include "bluetoothmanager.h"

#include <QDBusAbstractAdaptor>
#include <QDBusObjectPath>


// ? ================= GET BLUETOOTH DEVICE PATH =================
// ? Converts a Bluetooth device address into the D-Bus path used by BlueZ

static QString getBluezDevicePath(const QBluetoothDeviceInfo &device)
{
    // ? Get the Bluetooth device address
    QString address = device.address().toString();

    // ? BlueZ uses underscores instead of colons in device paths
    address.replace(':', '_');

    // ? Return the D-Bus path of the Bluetooth device
    return "/org/bluez/hci0/dev_" + address;
}


// ? ================= BLUEZ PAIRING AGENT =================
// ? BlueZ requires a pairing agent to be registered before it will let a
// ? remote device (e.g. a phone) pair with this adapter on its own initiative.
// ? "NoInputNoOutput" tells BlueZ we have no PIN/passkey UI, which makes it
// ? fall back to "just works" pairing for devices that support it (most phones do).
// ? Every slot here simply returns success by not raising a D-Bus error.

class BluetoothPairingAgent : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.bluez.Agent1")

public:
    explicit BluetoothPairingAgent(QObject *parent)
        : QDBusAbstractAdaptor(parent)
    {}

public slots:
    void Release() {}
    void RequestConfirmation(const QDBusObjectPath &, uint) {}
    void RequestAuthorization(const QDBusObjectPath &) {}
    void AuthorizeService(const QDBusObjectPath &, const QString &) {}
    void Cancel() {}
};


// ? ================= CONSTRUCTOR =================

BluetoothManager::BluetoothManager(QObject *parent)
    : QObject{parent}
    , m_agent(new QBluetoothDeviceDiscoveryAgent(this)) // ? BluetoothManager owns the discovery agent
    , m_device(new QBluetoothLocalDevice(this))         // ? Represents our computer's Bluetooth adapter
    , m_mediaDevices(new QMediaDevices(this))           // ? Monitors the system's available audio devices
    , m_connectionState(ConnectionState::Disconnected)
{
    // ! ================= PAIRING AGENT =================
    // ? Register ourselves with BlueZ as the pairing agent so that a phone
    // ? initiating pairing with us (rather than us initiating it) can succeed.

    new BluetoothPairingAgent(this);

    QDBusConnection::systemBus().registerObject(
        "/org/graduationproject/agent",
        this
    );

    QDBusInterface agentManager(
        "org.bluez",
        "/org/bluez",
        "org.bluez.AgentManager1",
        QDBusConnection::systemBus()
    );

    agentManager.call(
        "RegisterAgent",
        QVariant::fromValue(QDBusObjectPath("/org/graduationproject/agent")),
        QStringLiteral("NoInputNoOutput")
    );

    agentManager.call(
        "RequestDefaultAgent",
        QVariant::fromValue(QDBusObjectPath("/org/graduationproject/agent"))
    );


    // ! ================= DEVICE DISCOVERY =================

    connect(
        m_agent,
        &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
        this,
        [this](const QBluetoothDeviceInfo &device)
        {
            m_devices.append(device);      // ? Store the discovered Bluetooth device
            emit deviceDiscovered(device); // ? Tell the rest of the backend that a device was discovered
        }
    );


    connect(
        m_agent,
        &QBluetoothDeviceDiscoveryAgent::finished,
        this,
        &BluetoothManager::scanFinished
    );


    connect(
        m_agent,
        &QBluetoothDeviceDiscoveryAgent::errorOccurred,
        this,
        [this](QBluetoothDeviceDiscoveryAgent::Error)
        {
            emit errorOccurred(
                m_agent->errorString()
            ); // ? Forward Qt's Bluetooth discovery error
        }
    );


    // ? ================= AUDIO OUTPUT CHANGES =================
    // ? This fires when Linux/Qt detects a change in the available audio outputs.
    // ? A Bluetooth speaker/headset can appear here after BlueZ connects it.

    connect(
        m_mediaDevices,
        &QMediaDevices::audioOutputsChanged,
        this,
        [this]()
        {
            // ? We only care about audio outputs while connecting to a Bluetooth device
            if (m_connectionState != ConnectionState::Connecting)
                return;

            // ? Make sure we have a Bluetooth device selected
            if (!m_connectedDevice.isValid())
                return;

            // ? Get all audio outputs currently available to the system
            const QList<QAudioDevice> audioOutputs =
                QMediaDevices::audioOutputs();


            // ? Search for the audio output belonging to our Bluetooth device
            for (const QAudioDevice &audioDevice : audioOutputs) {

                // ? Compare the Bluetooth device name with the audio output description
                if (audioDevice.description() == m_connectedDevice.name()) {

                    // ? Store the Bluetooth audio output
                    m_audioDevice = audioDevice;

                    // ? The Bluetooth device is now usable as an audio output
                    m_connectionState = ConnectionState::Connected;

                    emit connectionStateChanged(m_connectionState);

                    // ? Give the rest of the backend the audio device
                    emit audioDeviceChanged(m_audioDevice);

                    return;
                }
            }
        }
    );


    // ! ================= PAIRING =================

    connect(
        m_device,
        &QBluetoothLocalDevice::pairingFinished,
        this,
        [this](
            const QBluetoothAddress &address,
            QBluetoothLocalDevice::Pairing pairing
        )
        {
            // ? Ignore pairing results for a device other than the one we are
            // ? already tracking - but don't ignore pairing that a remote
            // ? device (e.g. a phone) initiated on its own, since in that
            // ? case we won't have a device tracked yet
            if (m_connectedDevice.isValid() && address != m_connectedDevice.address())
                return;


            // ? Check if pairing failed
            if (pairing == QBluetoothLocalDevice::Unpaired) {

                m_connectionState = ConnectionState::Disconnected;

                emit connectionStateChanged(m_connectionState);

                emit errorOccurred(
                    "Bluetooth pairing failed."
                );

                return;
            }


            // ? Pairing succeeded. If it was initiated by the remote device
            // ? rather than by us, adopt it as the device we are tracking.
            if (!m_connectedDevice.isValid() || m_connectedDevice.address() != address)
                m_connectedDevice = QBluetoothDeviceInfo(address, QString(), 0);

            // ? Now attempt to establish the actual Bluetooth connection
            connectToDevice(m_connectedDevice);
        }
    );


    // ! ================= BLUETOOTH DEVICE CONNECTION =================

    connect(
        m_device,
        &QBluetoothLocalDevice::deviceConnected,
        this,
        [this](const QBluetoothAddress &address)
        {
            // ? Adopt this device as the one we are tracking if we are not
            // ? already tracking a different one - covers connections that a
            // ? phone initiates on its own, not just ones we started
            if (!m_connectedDevice.isValid() || m_connectedDevice.address() != address)
                m_connectedDevice = QBluetoothDeviceInfo(address, QString(), 0);

            // ? The Bluetooth device itself is now connected
            // ? We still wait for QMediaDevices to expose its audio output
            m_connectionState = ConnectionState::Connecting;

            emit connectionStateChanged(m_connectionState);
        }
    );


    connect(
        m_device,
        &QBluetoothLocalDevice::deviceDisconnected,
        this,
        [this](const QBluetoothAddress &address)
        {
            // ? Ignore disconnection events for a device other than the one
            // ? we are currently tracking
            if (m_connectedDevice.isValid() && address != m_connectedDevice.address())
                return;

            // ? The Bluetooth device has disconnected
            m_connectionState = ConnectionState::Disconnected;
            m_connectedDevice = QBluetoothDeviceInfo();

            // ? Clear the selected audio device
            m_audioDevice = QAudioDevice();

            emit connectionStateChanged(m_connectionState);
            emit audioDeviceChanged(m_audioDevice);
        }
    );


    // ! ================= BLUETOOTH ERRORS =================

    connect(
        m_device,
        &QBluetoothLocalDevice::errorOccurred,
        this,
        [this](QBluetoothLocalDevice::Error)
        {
            // ? Bluetooth adapter reported an error
            m_connectionState = ConnectionState::Disconnected;

            emit connectionStateChanged(m_connectionState);

            emit errorOccurred(
                "A Bluetooth adapter error occurred."
            );
        }
    );
}


// * ================= SCAN FOR BLUETOOTH DEVICES =================

void BluetoothManager::startScanning()
{
    // ? Clear the previous list of discovered devices
    m_devices.clear();

    // ? Start scanning for nearby Bluetooth devices
    m_agent->start();
}


void BluetoothManager::stopScanning()
{
    // ? Stop the current Bluetooth scan
    m_agent->stop();
}


// * ================= DISCOVERABILITY =================

void BluetoothManager::setDiscoverable(bool discoverable)
{
    // ? HostDiscoverable also implies connectable, so a phone can both see
    // ? this adapter and pair/connect to it. HostConnectable keeps pairing
    // ? possible for already-paired devices without advertising us to everyone.
    m_device->setHostMode(
        discoverable
            ? QBluetoothLocalDevice::HostDiscoverable
            : QBluetoothLocalDevice::HostConnectable
    );
}


// * ================= GETTERS =================

BluetoothManager::ConnectionState
BluetoothManager::getConnectionState() const
{
    return m_connectionState;
}


QAudioDevice BluetoothManager::getAudioDevice() const
{
    return m_audioDevice;
}


// * ================= CONNECT TO BLUETOOTH DEVICE =================

void BluetoothManager::connectToDevice(
    const QBluetoothDeviceInfo &device
)
{
    // ? Make sure our computer actually has a Bluetooth adapter
    if (!m_device->isValid()) {

        emit errorOccurred(
            "Bluetooth adapter is not available."
        );

        return;
    }


    // ? Remember which Bluetooth device the user selected
    m_connectedDevice = device;


    // ? Tell the rest of the backend that we are attempting to connect
    m_connectionState = ConnectionState::Connecting;

    emit connectionStateChanged(m_connectionState);


    // ? Check whether the selected device is already paired
    QBluetoothLocalDevice::Pairing pairingStatus =
        m_device->pairingStatus(
            device.address()
        );


    // ? If the device is not paired, pair it first
    if (pairingStatus == QBluetoothLocalDevice::Unpaired) {

        m_device->requestPairing(
            device.address(),
            QBluetoothLocalDevice::Paired
        );

        return;
    }


    // ? The device is already paired
    // ? Now ask BlueZ to establish the actual Bluetooth connection

    QString devicePath = getBluezDevicePath(device);


    // ? Create a D-Bus interface for this Bluetooth device
    QDBusInterface bluezDevice(
        "org.bluez",                         // ? BlueZ D-Bus service
        devicePath,                          // ? Selected Bluetooth device path
        "org.bluez.Device1",                 // ? BlueZ Bluetooth device interface
        QDBusConnection::systemBus()         // ? BlueZ runs on the system D-Bus
    );


    // ? Make sure we successfully created the BlueZ interface
    if (!bluezDevice.isValid()) {

        m_connectionState = ConnectionState::Disconnected;

        emit connectionStateChanged(m_connectionState);

        emit errorOccurred(
            "Could not communicate with the BlueZ Bluetooth service."
        );

        return;
    }


    // ? Ask BlueZ to connect the Bluetooth device
    QDBusMessage reply = bluezDevice.call("Connect");


    // ? Check whether BlueZ returned an error
    if (reply.type() == QDBusMessage::ErrorMessage) {

        m_connectionState = ConnectionState::Disconnected;

        emit connectionStateChanged(m_connectionState);

        emit errorOccurred(
            reply.errorMessage()
        );

        return;
    }


    // ? BlueZ accepted the connection request
    // ? We now wait for QMediaDevices::audioOutputsChanged()
    // ? to detect the Bluetooth audio output
}


// * ================= DISCONNECT FROM BLUETOOTH DEVICE =================

void BluetoothManager::disconnect()
{
    // ? Make sure a Bluetooth device is currently selected
    if (!m_connectedDevice.isValid()) {

        emit errorOccurred(
            "No Bluetooth device is currently connected."
        );

        return;
    }


    // ? Get the BlueZ D-Bus path of the selected device
    QString devicePath =
        getBluezDevicePath(m_connectedDevice);


    // ? Create a D-Bus interface for the selected Bluetooth device
    QDBusInterface bluezDevice(
        "org.bluez",
        devicePath,
        "org.bluez.Device1",
        QDBusConnection::systemBus()
    );


    // ? Make sure we can communicate with BlueZ
    if (!bluezDevice.isValid()) {

        emit errorOccurred(
            "Could not communicate with the BlueZ Bluetooth service."
        );

        return;
    }


    // ? Ask BlueZ to disconnect the device
    QDBusMessage reply =
        bluezDevice.call("Disconnect");


    // ? Check whether BlueZ returned an error
    if (reply.type() == QDBusMessage::ErrorMessage) {

        emit errorOccurred(
            reply.errorMessage()
        );

        return;
    }


    // ? Clear the selected audio device
    m_audioDevice = QAudioDevice();

    // ? Clear the selected Bluetooth device
    m_connectedDevice = QBluetoothDeviceInfo();

    // ? Update our connection state
    m_connectionState = ConnectionState::Disconnected;

    emit connectionStateChanged(m_connectionState);
    emit audioDeviceChanged(m_audioDevice);
}

#include "bluetoothmanager.moc"