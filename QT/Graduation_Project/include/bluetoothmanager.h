// ? ================= THIS CLASS IS RESPONSIBLE FOR HANDLING BLUETOOTH =================

// ! The four responsibilities of this class are:
// ! 1. Scanning for nearby Bluetooth devices
// ! 2. Connecting to a Bluetooth device
// ! 3. Disconnecting from a Bluetooth device
// ! 4. Reporting Bluetooth errors and/or state changes

#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>
#include <QList>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceInfo>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QQmlEngine>

class BluetoothManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("BluetoothManager is owned by MediaController and cannot be created from QML")

public:

    enum class ConnectionState {
        Disconnected,
        Connecting,
        Connected
    };
    Q_ENUM(ConnectionState)

    explicit BluetoothManager(QObject *parent = nullptr);

    void startScanning();
    void stopScanning();

    // ? Makes this adapter visible/connectable so a phone can find and pair with it
    void setDiscoverable(bool discoverable);

    // ? Reconnects to a device that is already paired
    void connectToDevice(const QBluetoothDeviceInfo &device);
    void disconnect();

    ConnectionState getConnectionState() const;
    QAudioDevice getAudioDevice() const;

private:
    QBluetoothDeviceDiscoveryAgent *m_agent; // ? Responsible for scanning and discovering nearby Bluetooth devices
    QBluetoothLocalDevice *m_device;         // ? Represents our computer's local Bluetooth adapter
    QMediaDevices *m_mediaDevices;           // ? Provides information about the system's available audio devices

    QList<QBluetoothDeviceInfo> m_devices;   // ? Stores the Bluetooth devices discovered during scanning

    ConnectionState m_connectionState;      // ? Stores the current Bluetooth connection state
    QAudioDevice m_audioDevice;              // ? Stores the currently selected Bluetooth audio output device
    QBluetoothDeviceInfo m_connectedDevice; // ? Stores the Bluetooth device we are currently connecting to

signals:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void scanFinished();
    void connectionStateChanged(ConnectionState state);
    void audioDeviceChanged(const QAudioDevice &device);
    void errorOccurred(const QString &message);
};

#endif // BLUETOOTHMANAGER_H