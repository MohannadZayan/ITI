#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent)
    : Player{parent}
{}

void VideoPlayer::setVideoOutput(QObject *videoOutput)
{
    m_player->setVideoOutput(videoOutput);
}
