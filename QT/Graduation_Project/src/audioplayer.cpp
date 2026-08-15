#include "audioplayer.h"

AudioPlayer::AudioPlayer(QObject *parent)
    : Player{parent} // ? Initialize Player
    , m_player(new QMediaPlayer(this)) // ? Create QMediaPlayer
    , m_audioOutput(new QAudioOutput(this)) // ? Create QAudioOutput
    , m_currentIndex(-1)
{
    m_player->setAudioOutput(m_audioOutput);

    connect(
        m_player,                                 // ? Listen to this object
        &QMediaPlayer::playbackStateChanged,      // ? Listen for this signal
        this,                                     // ? On this AudioPlayer
        &AudioPlayer::playbackStateChanged        // ? Emit this signal
    );

    connect(
        m_player,
        &QMediaPlayer::positionChanged,
        this,
        &AudioPlayer::positionChanged
    );

    connect(
        m_player,
        &QMediaPlayer::durationChanged,
        this,
        &AudioPlayer::durationChanged
    );

    connect(
        m_audioOutput,
        &QAudioOutput::volumeChanged,
        this,
        &AudioPlayer::volumeChanged
    );

    connect(
        m_audioOutput,
        &QAudioOutput::mutedChanged,
        this,
        &AudioPlayer::mutedChanged
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

void AudioPlayer::play()
{
    m_player->play();
}

void AudioPlayer::pause()
{
    m_player->pause();
}

void AudioPlayer::next()
{
    if (m_playlist.isEmpty()) {
        emit errorOccurred("Cannot play next track: playlist is empty.");
        return;
    }

    m_currentIndex = (m_currentIndex + 1) % m_playlist.size();

    m_player->setSource(m_playlist[m_currentIndex]);
    m_player->play();
}

void AudioPlayer::previous()
{
    if (m_playlist.isEmpty()) {
        emit errorOccurred("Cannot play previous track: playlist is empty.");
        return;
    }

    if (m_currentIndex <= 0)
        m_currentIndex = m_playlist.size() - 1;
    else
        --m_currentIndex;

    m_player->setSource(m_playlist[m_currentIndex]);
    m_player->play();
}

void AudioPlayer::setMuted(bool muted)
{
    m_audioOutput->setMuted(muted);
}

void AudioPlayer::setVolume(int volume)
{
    volume = qBound(0, volume, 100);
    m_audioOutput->setVolume(volume / 100.0f);
}

void AudioPlayer::setPlaylist(const QList<QUrl>& playlist)
{
    m_playlist = playlist;
    m_currentIndex = -1;
}