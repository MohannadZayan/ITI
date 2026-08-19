#include "player.h"

#include <QMediaMetaData>

Player::Player(QObject *parent)
    : QObject{parent}
    , m_player(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
    , m_currentIndex(-1)
{
    m_player->setAudioOutput(m_audioOutput);

    connect(
        m_player,
        &QMediaPlayer::playbackStateChanged,
        this,
        &Player::playbackStateChanged
    );

    connect(
        m_player,
        &QMediaPlayer::positionChanged,
        this,
        &Player::positionChanged
    );

    connect(
        m_player,
        &QMediaPlayer::durationChanged,
        this,
        &Player::durationChanged
    );

    connect(
        m_audioOutput,
        &QAudioOutput::volumeChanged,
        this,
        &Player::volumeChanged
    );

    connect(
        m_audioOutput,
        &QAudioOutput::mutedChanged,
        this,
        &Player::mutedChanged
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

    connect(
        m_player,
        &QMediaPlayer::metaDataChanged,
        this,
        &Player::metadataChanged
    );
}

void Player::play()
{
    // ? Nothing has been loaded from the playlist yet - load the first item
    // ? instead of asking QMediaPlayer to play an empty source
    if (m_currentIndex == -1 && !m_playlist.isEmpty()) {
        m_currentIndex = 0;
        m_player->setSource(m_playlist[m_currentIndex]);
        emit currentIndexChanged();
    }

    m_player->play();
}

void Player::pause()
{
    m_player->pause();
}

void Player::stop()
{
    m_player->stop();
}

void Player::next()
{
    if (m_playlist.isEmpty()) {
        emit errorOccurred("Cannot play next item: playlist is empty.");
        return;
    }

    m_currentIndex = (m_currentIndex + 1) % m_playlist.size();
    emit currentIndexChanged();

    m_player->setSource(m_playlist[m_currentIndex]);
    m_player->play();
}

void Player::previous()
{
    if (m_playlist.isEmpty()) {
        emit errorOccurred("Cannot play previous item: playlist is empty.");
        return;
    }

    if (m_currentIndex <= 0)
        m_currentIndex = m_playlist.size() - 1;
    else
        --m_currentIndex;

    emit currentIndexChanged();

    m_player->setSource(m_playlist[m_currentIndex]);
    m_player->play();
}

void Player::playAt(int index)
{
    if (index < 0 || index >= m_playlist.size()) {
        emit errorOccurred("Cannot play item: index out of range.");
        return;
    }

    m_currentIndex = index;
    emit currentIndexChanged();

    m_player->setSource(m_playlist[m_currentIndex]);
    m_player->play();
}

void Player::setMuted(bool muted)
{
    m_audioOutput->setMuted(muted);
}

void Player::setVolume(int volume)
{
    volume = qBound(0, volume, 100);
    m_audioOutput->setVolume(volume / 100.0f);
}

void Player::setPosition(qint64 position)
{
    m_player->setPosition(position);
}

void Player::setPlaylist(const QList<QUrl>& playlist)
{
    m_playlist = playlist;
    m_currentIndex = -1;
    emit currentIndexChanged();
}

void Player::setAudioDevice(const QAudioDevice &device)
{
    m_audioOutput->setDevice(device);
}

qint64 Player::position() const
{
    return m_player->position();
}

qint64 Player::duration() const
{
    return m_player->duration();
}

int Player::volume() const
{
    return qRound(m_audioOutput->volume() * 100.0f);
}

bool Player::isMuted() const
{
    return m_audioOutput->isMuted();
}

bool Player::isPlaying() const
{
    return m_player->playbackState() == QMediaPlayer::PlayingState;
}

QString Player::title() const
{
    return m_player->metaData().stringValue(QMediaMetaData::Title);
}

QString Player::artist() const
{
    return m_player->metaData().stringValue(QMediaMetaData::ContributingArtist);
}

QString Player::genre() const
{
    return m_player->metaData().stringValue(QMediaMetaData::Genre);
}

int Player::currentIndex() const
{
    return m_currentIndex;
}
