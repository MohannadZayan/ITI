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

private:
    QString m_folderPath;
    QList<QUrl> m_audioPlaylist;
    QList<QUrl> m_videoPlaylist;
};

#endif // LOCALMEDIA_H