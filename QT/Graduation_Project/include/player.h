#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QUrl>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioDevice>

class Player : public QObject
{
    Q_OBJECT

public:
    // ? Used directly for audio playback; VideoPlayer subclasses it to add setVideoOutput()
    explicit Player(QObject *parent = nullptr);

    void play();
    void pause();
    void stop();
    void next();
    void previous();

    // ? Jumps directly to a specific playlist item, e.g. picking a radio station from a list
    void playAt(int index);

    void setMuted(bool muted);
    void setVolume(int volume);
    void setPosition(qint64 position);
    void setPlaylist(const QList<QUrl>& playlist);
    void setAudioDevice(const QAudioDevice &device);

    qint64 position() const;
    qint64 duration() const;
    int volume() const;
    bool isMuted() const;
    bool isPlaying() const;

    QString title() const;
    QString artist() const;
    QString genre() const;

signals:
    void positionChanged();
    void durationChanged();
    void volumeChanged();
    void mutedChanged();
    void playbackStateChanged();
    void metadataChanged();
    void errorOccurred(const QString &message);

protected:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;

private:
    QList<QUrl> m_playlist;
    int m_currentIndex;
};

#endif // PLAYER_H
