// ? ================= THIS CLASS IS RESPONSIBLE FOR HANDLING LOCAL MEDIA =================

// ! The three responsibilites of this class are:
// ! 1. Validating the folder
// ! 2. Scanning the folder for supported audio and video files
// ! 3. Providing the audio and video playlists

#ifndef LOCALMEDIA_H
#define LOCALMEDIA_H

#include <QObject>
#include <QDir>          // ? Used to work with directories/folders
#include <QFileInfo>     // ? Used to get information about files
#include <QList>
#include <QUrl>          // ? Used to represent media file paths
#include <QStorageInfo>  // ? Used to get information about the storage device connected to our computer
#include <QStringList>
#include <QTimer>        // ? Used to periodically check for newly-inserted USB drives

class LocalMedia : public QObject
{
    Q_OBJECT

public:
    explicit LocalMedia(QObject *parent = nullptr);

    void setFolder(const QString &folderPath);
    void scanFolder();
    void setUsbFolder(const QString &folderPath);

    QList<QUrl> getAudioPlaylist() const;
    QList<QUrl> getVideoPlaylist() const;

signals:
    void playlistChanged();
    void errorOccurred(const QString &message);

    // ? A new removable drive was detected and is being scanned automatically
    void usbDeviceConnected(const QString &path);

private:
    // ? Checks which mounted volumes are new since the last check, and
    // ? automatically scans any that just appeared
    void checkForUsbDevices();

    QString m_folderPath;
    QList<QUrl> m_audioPlaylist;
    QList<QUrl> m_videoPlaylist;

    QTimer *m_usbPollTimer;           // ? Periodically triggers checkForUsbDevices()
    QStringList m_knownMountPaths;    // ? Root paths of volumes we've already seen, so only newly-plugged-in drives trigger a scan
};

#endif // LOCALMEDIA_H