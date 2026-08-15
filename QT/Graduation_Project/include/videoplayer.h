#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "player.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QList>
#include <QUrl>

class VideoPlayer : public Player
{
    Q_OBJECT

public:
    explicit VideoPlayer(QObject *parent = nullptr);

    void play() override;
    void pause() override;
    void next() override;
    void previous() override;
    void setMuted(bool muted) override;
    void setVolume(int volume) override;
    
    void setPlaylist(const QList<QUrl>& playlist);
    void setVideoOutput(QObject *videoOutput);

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QList<QUrl> m_playlist;
    int m_currentIndex;
};

#endif // VIDEOPLAYER_H