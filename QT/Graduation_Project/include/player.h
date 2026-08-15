#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual void setMuted(bool muted) = 0;
    virtual void setVolume(int volume) = 0;

signals:
    void positionChanged();
    void durationChanged();
    void volumeChanged();
    void mutedChanged();
    void playbackStateChanged();
    void errorOccurred(const QString &message);
};

#endif // PLAYER_H