#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "player.h"

class VideoPlayer : public Player
{
public:
    explicit VideoPlayer(QObject *parent = nullptr);
};

#endif // VIDEOPLAYER_H
