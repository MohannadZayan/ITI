#ifndef MEDIAMODE_H
#define MEDIAMODE_H

#include <QObject>

class MediaMode : public QObject
{
    Q_OBJECT

public:

    enum class Mode {
        LocalAudio,
        UsbAudio,
        Video,
        Bluetooth
    };

    explicit MediaMode(QObject *parent = nullptr);

    Mode getMode() const;
    void setMode(Mode mode);

signals:
    void modeChanged();

private:
    Mode m_currentMode;
};

#endif // MEDIAMODE_H