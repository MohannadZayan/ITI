#include "include/mediamode.h"

MediaMode::MediaMode(QObject *parent) : QObject{parent}, m_currentMode(Mode::LocalAudio) //? Setting the default mode to local audio
 {

 }

 MediaMode::Mode MediaMode::getMode() const
 {
     return m_currentMode;
 }

 void MediaMode::setMode(Mode mode) {
    if (m_currentMode == mode)           //? If the mode is the same, do nothing
    return;

    m_currentMode = mode;
    emit modeChanged();
 }
