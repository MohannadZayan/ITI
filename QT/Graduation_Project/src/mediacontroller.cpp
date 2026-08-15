#include "mediacontroller.h"


MediaController::MediaController(QObject *parent)
    : QObject{parent}
    , m_audioPlayer(new Player(this))
    , m_videoPlayer(new VideoPlayer(this))
    , m_localMedia(new LocalMedia(this))
    , m_bluetoothManager(new BluetoothManager(this))
    , m_currentMediaType(MediaType::Audio)
{

    // * ================= PLAYERS =================

    connect(
    m_audioPlayer,
    &Player::positionChanged,
    this,
    &MediaController::positionChanged
);

connect(
    m_audioPlayer,
    &Player::durationChanged,
    this,
    &MediaController::durationChanged
);

connect(
    m_audioPlayer,
    &Player::volumeChanged,
    this,
    &MediaController::volumeChanged
);

connect(
    m_audioPlayer,
    &Player::mutedChanged,
    this,
    &MediaController::mutedChanged
);

connect(
    m_audioPlayer,
    &Player::playbackStateChanged,
    this,
    &MediaController::playbackStateChanged
);

connect(
    m_audioPlayer,
    &Player::errorOccurred,
    this,
    &MediaController::errorOccurred
);

connect(
    m_videoPlayer,
    &VideoPlayer::positionChanged,
    this,
    &MediaController::positionChanged
);

connect(
    m_videoPlayer,
    &VideoPlayer::durationChanged,
    this,
    &MediaController::durationChanged
);

connect(
    m_videoPlayer,
    &VideoPlayer::volumeChanged,
    this,
    &MediaController::volumeChanged
);

connect(
    m_videoPlayer,
    &VideoPlayer::mutedChanged,
    this,
    &MediaController::mutedChanged
);

connect(
    m_videoPlayer,
    &VideoPlayer::playbackStateChanged,
    this,
    &MediaController::playbackStateChanged
);

connect(
    m_videoPlayer,
    &VideoPlayer::errorOccurred,
    this,
    &MediaController::errorOccurred
);

    // * ================= LOCAL MEDIA =================

    connect(
        m_localMedia,
        &LocalMedia::playlistChanged,
        this,
        &MediaController::playlistChanged
    );

    connect(
        m_localMedia,
        &LocalMedia::errorOccurred,
        this,
        &MediaController::errorOccurred
    );


    // * ================= BLUETOOTH =================

    connect(
        m_bluetoothManager,
        &BluetoothManager::deviceDiscovered,
        this,
        &MediaController::deviceDiscovered
    );

    connect(
        m_bluetoothManager,
        &BluetoothManager::scanFinished,
        this,
        &MediaController::scanFinished
    );

    connect(
        m_bluetoothManager,
        &BluetoothManager::connectionStateChanged,
        this,
        &MediaController::connectionStateChanged
    );

    connect(
        m_bluetoothManager,
        &BluetoothManager::errorOccurred,
        this,
        &MediaController::errorOccurred
    );

    connect(
        m_bluetoothManager,
        &BluetoothManager::audioDeviceChanged,
        this,
        [this](const QAudioDevice &device)
        {
            // ? Give the selected Bluetooth audio device to the active player
            m_audioPlayer->setAudioDevice(device);
        }
    );
}

 // * ================= THE SINGLETON INSTANCE =================

 MediaController* MediaController::instance()
{
    static MediaController controller;

    return &controller;
}

MediaController* MediaController::create(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    // ? The instance is owned by C++ (it is a static local), so QML must not try to delete it
    QQmlEngine::setObjectOwnership(instance(), QQmlEngine::CppOwnership);

    return instance();
}

// * ================= MEDIA TYPE =================

void MediaController::setMediaType(MediaType type)
{
    if (type == m_currentMediaType)
        return;

    m_currentMediaType = type;

    emit mediaTypeChanged();

    // ? The active player just switched, so every property that reads from
    // ? "whichever player is current" now points at different underlying
    // ? state - notify QML so bound values refresh instead of going stale
    emit positionChanged();
    emit durationChanged();
    emit volumeChanged();
    emit mutedChanged();
    emit playbackStateChanged();
}

MediaController::MediaType MediaController::mediaType() const
{
    return m_currentMediaType;
}

// * ================= PLAYBACK =================

void MediaController::play()
{
    if (m_currentMediaType == MediaType::Audio)
        m_audioPlayer->play();
    else
        m_videoPlayer->play();
}


void MediaController::pause()
{
    if (m_currentMediaType == MediaType::Audio)
        m_audioPlayer->pause();
    else
        m_videoPlayer->pause();
}


void MediaController::next()
{
    if (m_currentMediaType == MediaType::Audio)
        m_audioPlayer->next();
    else
        m_videoPlayer->next();
}


void MediaController::previous()
{
    if (m_currentMediaType == MediaType::Audio)
        m_audioPlayer->previous();
    else
        m_videoPlayer->previous();
}

void MediaController::setVolume(int volume)
{
    if (m_currentMediaType == MediaType::Audio)
        m_audioPlayer->setVolume(volume);
    else
        m_videoPlayer->setVolume(volume);
}


void MediaController::setMuted(bool muted)
{
    if (m_currentMediaType == MediaType::Audio)
        m_audioPlayer->setMuted(muted);
    else
        m_videoPlayer->setMuted(muted);
}

// * ================= LOCAL MEDIA =================

void MediaController::setMediaFolder(const QString &folderPath)
{
    m_localMedia->setFolder(folderPath);

    m_audioPlayer->setPlaylist(m_localMedia->getAudioPlaylist());
    m_videoPlayer->setPlaylist(m_localMedia->getVideoPlaylist());
}


void MediaController::setUsbFolder(const QString &folderPath)
{
    m_localMedia->setUsbFolder(folderPath);

    m_audioPlayer->setPlaylist(m_localMedia->getAudioPlaylist());
    m_videoPlayer->setPlaylist(m_localMedia->getVideoPlaylist());
}


QList<QUrl> MediaController::getAudioPlaylist() const
{
    return m_localMedia->getAudioPlaylist();
}


QList<QUrl> MediaController::getVideoPlaylist() const
{
    return m_localMedia->getVideoPlaylist();
}

// * ================= PLAYER PROPERTIES =================

qint64 MediaController::position() const
{
    if (m_currentMediaType == MediaType::Audio)
        return m_audioPlayer->position();
    else
        return m_videoPlayer->position();
}

qint64 MediaController::duration() const
{
    if (m_currentMediaType == MediaType::Audio)
        return m_audioPlayer->duration();
    else
        return m_videoPlayer->duration();
}

int MediaController::volume() const
{
    if (m_currentMediaType == MediaType::Audio)
        return m_audioPlayer->volume();
    else
        return m_videoPlayer->volume();
}

bool MediaController::isMuted() const
{
    if (m_currentMediaType == MediaType::Audio)
        return m_audioPlayer->isMuted();
    else
        return m_videoPlayer->isMuted();
}

// * ================= BLUETOOTH =================

void MediaController::setBluetoothDiscoverable(bool discoverable)
{
    m_bluetoothManager->setDiscoverable(discoverable);
}


void MediaController::startBluetoothScanning()
{
    m_bluetoothManager->startScanning();
}


void MediaController::stopBluetoothScanning()
{
    m_bluetoothManager->stopScanning();
}


void MediaController::connectToBluetoothDevice(
    const QBluetoothDeviceInfo &device
)
{
    m_bluetoothManager->connectToDevice(device);
}


void MediaController::disconnectBluetooth()
{
    m_bluetoothManager->disconnect();
}

