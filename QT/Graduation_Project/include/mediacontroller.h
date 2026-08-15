// ? ================= THIS IS A SINGLETON CLASS RESPONSIBLE FOR GIVING THE FRONT END ACCESS TO ALL BACKEND FUNCTIONALITY =================

#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <QObject>
#include <QList>
#include <QUrl>
#include <QString>
#include <QQmlEngine>

#include "player.h"
#include "videoplayer.h"
#include "LocalMedia.h"

class MediaController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(int volume READ volume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ isMuted NOTIFY mutedChanged)
    Q_PROPERTY(MediaType mediaType READ mediaType NOTIFY mediaTypeChanged)

public:

    // ? Returns the single instance of the MediaController
    static MediaController* instance();

    // ? Called by the QML engine to obtain the singleton instance
    static MediaController* create(QQmlEngine *engine, QJSEngine *scriptEngine);


    // ? Determines which media type is currently being controlled
    enum class MediaType {
        Audio,
        Video
    };
    Q_ENUM(MediaType)


    // * ================= MEDIA TYPE =================

    Q_INVOKABLE void setMediaType(MediaType type);
    MediaType mediaType() const;


    // * ================= PLAYBACK =================

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();


    // * ================= AUDIO =================

    Q_INVOKABLE void setVolume(int volume);
    Q_INVOKABLE void setMuted(bool muted);


    // * ================= LOCAL MEDIA =================

    // ? Selects a normal local folder and scans it for media
    Q_INVOKABLE void setMediaFolder(const QString &folderPath);

    // ? Selects a folder located on a USB storage device
    Q_INVOKABLE void setUsbFolder(const QString &folderPath);


    // ? Returns the audio and video playlists generated from the selected folder
    Q_INVOKABLE QList<QUrl> getAudioPlaylist() const;
    Q_INVOKABLE QList<QUrl> getVideoPlaylist() const;


    // * ================= PLAYER PROPERTIES =================

    qint64 position() const;
    qint64 duration() const;
    int volume() const;
    bool isMuted() const;


signals:

    // * ================= PLAYER SIGNALS =================

    void positionChanged();
    void durationChanged();
    void volumeChanged();
    void mutedChanged();
    void playbackStateChanged();
    void mediaTypeChanged();


    // * ================= LOCAL MEDIA SIGNALS =================

    // ? Tells the frontend that the playlist has changed
    void playlistChanged();


    // * ================= GENERAL ERROR =================

    // ? Reports errors from any backend component to the frontend
    void errorOccurred(const QString &message);


private:

    // ? The constructor is private to prevent the frontend from creating multiple instances of this class
    explicit MediaController(QObject *parent = nullptr);

    // ? Making a copy of this class is not allowed
    MediaController(const MediaController&) = delete;
    MediaController& operator=(const MediaController&) = delete;


    // ? Handles audio playback
    Player *m_audioPlayer;

    // ? Handles video playback
    VideoPlayer *m_videoPlayer;

    // ? Handles local and USB media files
    LocalMedia *m_localMedia;

    // ? Stores which player the controller is currently controlling
    MediaType m_currentMediaType;
};

#endif // MEDIACONTROLLER_H