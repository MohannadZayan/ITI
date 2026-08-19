// ? ================= THIS IS A SINGLETON CLASS RESPONSIBLE FOR GIVING THE FRONT END ACCESS TO ALL BACKEND FUNCTIONALITY =================

#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <QObject>
#include <QList>
#include <QUrl>
#include <QString>
#include <QVariantList>
#include <QQmlEngine>

#include "player.h"
#include "videoplayer.h"
#include "LocalMedia.h"
#include "RadioStations.h"

class MediaController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(int volume READ volume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ isMuted NOTIFY mutedChanged)
    Q_PROPERTY(bool playing READ isPlaying NOTIFY playbackStateChanged)
    Q_PROPERTY(MediaType mediaType READ mediaType NOTIFY mediaTypeChanged)
    Q_PROPERTY(QString trackTitle READ trackTitle NOTIFY metadataChanged)
    Q_PROPERTY(QString trackArtist READ trackArtist NOTIFY metadataChanged)
    Q_PROPERTY(QString trackGenre READ trackGenre NOTIFY metadataChanged)
    Q_PROPERTY(QList<QUrl> playlist READ playlist NOTIFY playlistChanged)
    Q_PROPERTY(int currentTrackIndex READ currentTrackIndex NOTIFY currentTrackIndexChanged)

public:

    // ? Returns the single instance of the MediaController
    static MediaController* instance();

    // ? Called by the QML engine to obtain the singleton instance
    static MediaController* create(QQmlEngine *engine, QJSEngine *scriptEngine);


    // ? Determines which media type is currently being controlled
    enum class MediaType {
        Audio,
        Video,
        Radio
    };
    Q_ENUM(MediaType)


    // * ================= MEDIA TYPE =================

    Q_INVOKABLE void setMediaType(MediaType type);
    MediaType mediaType() const;

    // ? Hands the video player a QML VideoOutput item to render into
    Q_INVOKABLE void setVideoOutput(QObject *videoOutput);


    // * ================= PLAYBACK =================

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();

    // ? Jumps directly to a specific playlist item, e.g. picking a radio station from a list
    Q_INVOKABLE void playAt(int index);

    // ? Seeks the active player to a position, in milliseconds
    Q_INVOKABLE void seek(qint64 position);


    // * ================= AUDIO =================

    Q_INVOKABLE void setVolume(int volume);
    Q_INVOKABLE void setMuted(bool muted);


    // * ================= LOCAL MEDIA =================

    // ? Selects a normal local folder and scans it for media
    Q_INVOKABLE void setMediaFolder(const QUrl &folderUrl);

    // ? Selects a folder located on a USB storage device
    Q_INVOKABLE void setUsbFolder(const QUrl &folderUrl);


    // ? Returns the audio and video playlists generated from the selected folder
    Q_INVOKABLE QList<QUrl> getAudioPlaylist() const;
    Q_INVOKABLE QList<QUrl> getVideoPlaylist() const;


    // * ================= RADIO =================

    // ? Sets the list of internet radio station stream URLs - use next()/previous() to switch between them
    Q_INVOKABLE void setRadioStations(const QList<QUrl> &stations);

    // ? Returns the stations loaded from the external radio_stations.json config file
    Q_INVOKABLE QVariantList radioStations() const;


    // * ================= PLAYER PROPERTIES =================

    qint64 position() const;
    qint64 duration() const;
    int volume() const;
    bool isMuted() const;
    bool isPlaying() const;

    QString trackTitle() const;
    QString trackArtist() const;
    QString trackGenre() const;

    // ? The playlist and current index for whichever local media type (audio/video) is active
    QList<QUrl> playlist() const;
    int currentTrackIndex() const;


signals:

    // * ================= PLAYER SIGNALS =================

    void positionChanged();
    void durationChanged();
    void volumeChanged();
    void mutedChanged();
    void playbackStateChanged();
    void metadataChanged();
    void mediaTypeChanged();
    void currentTrackIndexChanged();


    // * ================= LOCAL MEDIA SIGNALS =================

    // ? Tells the frontend that the playlist has changed
    void playlistChanged();


    // * ================= USB SIGNALS =================

    // ? A removable drive was plugged in / unplugged
    void usbConnected(const QString &path);
    void usbDisconnected(const QString &path);


    // * ================= GENERAL ERROR =================

    // ? Reports errors from any backend component to the frontend
    void errorOccurred(const QString &message);


private:

    // ? The constructor is private to prevent the frontend from creating multiple instances of this class
    explicit MediaController(QObject *parent = nullptr);

    // ? Making a copy of this class is not allowed
    MediaController(const MediaController&) = delete;
    MediaController& operator=(const MediaController&) = delete;

    // ? Returns whichever player corresponds to the current MediaType
    Player* activePlayer() const;


    // ? Handles audio playback
    Player *m_audioPlayer;

    // ? Handles video playback
    VideoPlayer *m_videoPlayer;

    // ? Handles internet radio streaming
    Player *m_radioPlayer;

    // ? Handles local and USB media files
    LocalMedia *m_localMedia;

    // ? Loads the radio station list from the external config file
    RadioStations *m_radioStations;

    // ? Stores which player the controller is currently controlling
    MediaType m_currentMediaType;
};

#endif // MEDIACONTROLLER_H