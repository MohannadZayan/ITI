#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "player.h"
#include <QMediaPlayer> // ? Responsible for loading media files, playing,pausing,seeking,emitting useful playback signals
#include <QAudioOutput> // ? Responsible for where the audio gets output, volume, mute, etc.
#include <QList>
#include <QUrl>

class AudioPlayer : public Player
{
    Q_OBJECT

    private: 
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QList<QUrl> m_playlist;
    int m_currentIndex;

public:
    explicit AudioPlayer(QObject *parent = nullptr);

    void play() override;
    void pause() override;
    void next() override;
    void previous() override;
    void setMuted(bool muted) override;
    void setVolume(int volume) override;

    void setPlaylist(const QList<QUrl>& playlist);

};

#endif // AUDIOPLAYER_H
