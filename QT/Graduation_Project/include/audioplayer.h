#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "player.h"

class AudioPlayer : public Player
{
public:
    explicit AudioPlayer(QObject *parent = nullptr);
};

#endif // AUDIOPLAYER_H
