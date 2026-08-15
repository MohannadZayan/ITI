#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent)
    : Player{parent}
    , m_player(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
    , m_currentIndex(-1)
{
    m_player->setAudioOutput(m_audioOutput);

    connect(
    m_player,
    &QMediaPlayer::playbackStateChanged,
    this,
    &VideoPlayer::playbackStateChanged
);

connect(
    m_player,
    &QMediaPlayer::positionChanged,
    this,
    &VideoPlayer::positionChanged
);

connect(
    m_player,
    &QMediaPlayer::durationChanged,
    this,
    &VideoPlayer::durationChanged
);

connect(
    m_audioOutput,
    &QAudioOutput::volumeChanged,
    this,
    &VideoPlayer::volumeChanged
);

connect(
    m_audioOutput,
    &QAudioOutput::mutedChanged,
    this,
    &VideoPlayer::mutedChanged
);

connect(
    m_player,
    &QMediaPlayer::errorOccurred,
    this,
    [this](QMediaPlayer::Error, const QString &errorString)
    {
        emit errorOccurred(errorString);
    }
);
}

void VideoPlayer::play()
{
    m_player->play();
}

void VideoPlayer::pause()
{
    m_player->pause();
}

void VideoPlayer::next()
{
    if (m_playlist.isEmpty()) {
        emit errorOccurred("Cannot play next video: playlist is empty.");
        return;
    }

    m_currentIndex = (m_currentIndex + 1) % m_playlist.size();

    m_player->setSource(m_playlist[m_currentIndex]);
    m_player->play();
}

void VideoPlayer::previous()
{
    if (m_playlist.isEmpty()) {
        emit errorOccurred("Cannot play previous video: playlist is empty.");
        return;
    }

    if (m_currentIndex <= 0)
        m_currentIndex = m_playlist.size() - 1;
    else
        --m_currentIndex;

    m_player->setSource(m_playlist[m_currentIndex]);
    m_player->play();
}

void VideoPlayer::setMuted(bool muted)
{
    m_audioOutput->setMuted(muted);
}

void VideoPlayer::setVolume(int volume)
{
    volume = qBound(0, volume, 100);
    m_audioOutput->setVolume(volume / 100.0f);
}

void VideoPlayer::setPlaylist(const QList<QUrl>& playlist)
{
    m_playlist = playlist;
    m_currentIndex = -1;
}

void VideoPlayer::setVideoOutput(QObject *videoOutput)
{
    m_player->setVideoOutput(videoOutput);
}