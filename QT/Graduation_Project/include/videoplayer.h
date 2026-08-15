// ? ================= THIS CLASS IS RESPONSIBLE FOR HANDLING VIDEO PLAYBACK =================

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "player.h"

class VideoPlayer : public Player
{
    Q_OBJECT

public:
    explicit VideoPlayer(QObject *parent = nullptr);

    void setVideoOutput(QObject *videoOutput);
};

#endif // VIDEOPLAYER_H
