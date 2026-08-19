#include "mediacontroller.h"


MediaController::MediaController(QObject *parent)
    : QObject{parent}
    , m_audioPlayer(new Player(this))
    , m_videoPlayer(new VideoPlayer(this))
    , m_radioPlayer(new Player(this))
    , m_localMedia(new LocalMedia(this))
    , m_radioStations(new RadioStations(this))
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
    m_audioPlayer,
    &Player::metadataChanged,
    this,
    &MediaController::metadataChanged
);

connect(
    m_audioPlayer,
    &Player::currentIndexChanged,
    this,
    &MediaController::currentTrackIndexChanged
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

connect(
    m_videoPlayer,
    &VideoPlayer::metadataChanged,
    this,
    &MediaController::metadataChanged
);

connect(
    m_videoPlayer,
    &VideoPlayer::currentIndexChanged,
    this,
    &MediaController::currentTrackIndexChanged
);

connect(
    m_radioPlayer,
    &Player::positionChanged,
    this,
    &MediaController::positionChanged
);

connect(
    m_radioPlayer,
    &Player::durationChanged,
    this,
    &MediaController::durationChanged
);

connect(
    m_radioPlayer,
    &Player::volumeChanged,
    this,
    &MediaController::volumeChanged
);

connect(
    m_radioPlayer,
    &Player::mutedChanged,
    this,
    &MediaController::mutedChanged
);

connect(
    m_radioPlayer,
    &Player::playbackStateChanged,
    this,
    &MediaController::playbackStateChanged
);

connect(
    m_radioPlayer,
    &Player::errorOccurred,
    this,
    &MediaController::errorOccurred
);

connect(
    m_radioPlayer,
    &Player::metadataChanged,
    this,
    &MediaController::metadataChanged
);

connect(
    m_radioPlayer,
    &Player::currentIndexChanged,
    this,
    &MediaController::currentTrackIndexChanged
);

    // * ================= LOCAL MEDIA =================

    connect(
        m_localMedia,
        &LocalMedia::playlistChanged,
        this,
        [this]()
        {
            // ? Whatever triggered the rescan - a manual folder pick or an
            // ? automatically detected USB drive - give the fresh playlists
            // ? to both players here, in one place
            m_audioPlayer->setPlaylist(m_localMedia->getAudioPlaylist());
            m_videoPlayer->setPlaylist(m_localMedia->getVideoPlaylist());

            emit playlistChanged();
        }
    );

    connect(
        m_localMedia,
        &LocalMedia::errorOccurred,
        this,
        &MediaController::errorOccurred
    );

    connect(
        m_localMedia,
        &LocalMedia::usbDeviceConnected,
        this,
        &MediaController::usbConnected
    );

    connect(
        m_localMedia,
        &LocalMedia::usbDeviceDisconnected,
        this,
        &MediaController::usbDisconnected
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

    // ? Only one media type may play at a time - stop whatever was active
    // ? before switching, otherwise it just keeps playing in the background
    activePlayer()->stop();

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
    emit metadataChanged();

    // ? Audio and video have separate playlists/positions - switching between
    // ? them changes which one is "active", so refresh those too
    emit playlistChanged();
    emit currentTrackIndexChanged();
}

MediaController::MediaType MediaController::mediaType() const
{
    return m_currentMediaType;
}

void MediaController::setVideoOutput(QObject *videoOutput)
{
    m_videoPlayer->setVideoOutput(videoOutput);
}

Player* MediaController::activePlayer() const
{
    switch (m_currentMediaType) {
    case MediaType::Audio:
        return m_audioPlayer;
    case MediaType::Video:
        return m_videoPlayer;
    case MediaType::Radio:
        return m_radioPlayer;
    }

    return m_audioPlayer;
}

// * ================= PLAYBACK =================

void MediaController::play()
{
    activePlayer()->play();
}


void MediaController::pause()
{
    activePlayer()->pause();
}


void MediaController::stop()
{
    activePlayer()->stop();
}


void MediaController::next()
{
    activePlayer()->next();
}


void MediaController::previous()
{
    activePlayer()->previous();
}


void MediaController::playAt(int index)
{
    activePlayer()->playAt(index);
}


void MediaController::seek(qint64 position)
{
    activePlayer()->setPosition(position);
}

void MediaController::setVolume(int volume)
{
    activePlayer()->setVolume(volume);
}


void MediaController::setMuted(bool muted)
{
    activePlayer()->setMuted(muted);
}

// * ================= LOCAL MEDIA =================

void MediaController::setMediaFolder(const QUrl &folderUrl)
{
    m_localMedia->setFolder(folderUrl.toLocalFile());
}


void MediaController::setUsbFolder(const QUrl &folderUrl)
{
    m_localMedia->setUsbFolder(folderUrl.toLocalFile());
}


QList<QUrl> MediaController::getAudioPlaylist() const
{
    return m_localMedia->getAudioPlaylist();
}


QList<QUrl> MediaController::getVideoPlaylist() const
{
    return m_localMedia->getVideoPlaylist();
}

// * ================= RADIO =================

void MediaController::setRadioStations(const QList<QUrl> &stations)
{
    m_radioPlayer->setPlaylist(stations);
}

QVariantList MediaController::radioStations() const
{
    return m_radioStations->stations();
}

// * ================= PLAYER PROPERTIES =================

qint64 MediaController::position() const
{
    return activePlayer()->position();
}

qint64 MediaController::duration() const
{
    return activePlayer()->duration();
}

int MediaController::volume() const
{
    return activePlayer()->volume();
}

bool MediaController::isMuted() const
{
    return activePlayer()->isMuted();
}

bool MediaController::isPlaying() const
{
    return activePlayer()->isPlaying();
}

QString MediaController::trackTitle() const
{
    return activePlayer()->title();
}

QString MediaController::trackArtist() const
{
    return activePlayer()->artist();
}

QString MediaController::trackGenre() const
{
    return activePlayer()->genre();
}

QList<QUrl> MediaController::playlist() const
{
    return m_currentMediaType == MediaType::Video
        ? m_localMedia->getVideoPlaylist()
        : m_localMedia->getAudioPlaylist();
}

int MediaController::currentTrackIndex() const
{
    return activePlayer()->currentIndex();
}

