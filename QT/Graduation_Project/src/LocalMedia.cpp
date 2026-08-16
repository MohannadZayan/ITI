#include "LocalMedia.h"

LocalMedia::LocalMedia(QObject *parent)
    : QObject{parent}
    , m_usbPollTimer(new QTimer(this))
{
    // ? Seed the baseline with whatever is already mounted when the app
    // ? starts, so only drives plugged in afterwards count as "new"
    const QList<QStorageInfo> volumes = QStorageInfo::mountedVolumes();

    for (const QStorageInfo &storage : volumes) {
        if (storage.isValid() && storage.isReady() && !storage.isRoot())
            m_knownMountPaths.append(storage.rootPath());
    }

    connect(m_usbPollTimer, &QTimer::timeout, this, &LocalMedia::checkForUsbDevices);

    // ? Poll every 2 seconds - simple and good enough for detecting a USB insert
    m_usbPollTimer->start(2000);
}


// * ================= CHECK FOR USB DEVICES =================
// ? Compares the currently mounted volumes against the ones we already knew
// ? about, and automatically scans any newly-appeared removable drive

void LocalMedia::checkForUsbDevices()
{
    const QList<QStorageInfo> volumes = QStorageInfo::mountedVolumes();

    QStringList currentMountPaths;

    for (const QStorageInfo &storage : volumes) {

        // ? Skip the root filesystem and anything not actually mounted/ready
        if (!storage.isValid() || !storage.isReady() || storage.isRoot())
            continue;

        currentMountPaths.append(storage.rootPath());

        // ? A volume that wasn't there last time we checked just appeared
        if (!m_knownMountPaths.contains(storage.rootPath())) {
            emit usbDeviceConnected(storage.rootPath());
            setUsbFolder(storage.rootPath());
        }
    }

    m_knownMountPaths = currentMountPaths;
}


// * ================= SET FOLDER =================
// ? Stores the folder selected by the user and scans it for audio files

void LocalMedia::setFolder(const QString &folderPath)
{
    QDir directory(folderPath);

    // ? Checking if the provided path actually exists
    if (!directory.exists()) {
        emit errorOccurred("The selected folder does not exist.");
        return;
    }

    // ? Store the valid folder path
    m_folderPath = folderPath;

    // ? Scan the folder and build the playlist
    scanFolder();
}

void LocalMedia::setUsbFolder(const QString &folderPath)
{
    QStorageInfo storage(folderPath);

    // ? Checking if the selected path belongs to a valid mounted storage volume
    if (!storage.isValid() || !storage.isReady()) {
        emit errorOccurred("The selected USB storage is not available.");
        return;
    }

    // ? Store the selected USB folder
    m_folderPath = folderPath;

    // ? Scan the USB folder for audio files
    scanFolder();
}


// * ================= SCAN FOLDER =================
// ? Searches the selected folder for supported audio files and builds the playlist

void LocalMedia::scanFolder()
{
    // ? Making sure a folder has actually been selected
    if (m_folderPath.isEmpty()) {
        emit errorOccurred("No folder has been selected.");
        return;
    }

    QDir directory(m_folderPath);

    // ? Making sure the selected folder still exists
    if (!directory.exists()) {
        emit errorOccurred("The selected folder no longer exists.");
        return;
    }

    // ? Supported audio file extensions
    QStringList audioExtensions = {
        "*.mp3",
        "*.wav",
        "*.flac",
        "*.aac",
        "*.ogg",
        "*.m4a",
        "*.wma"
    };

    // ? Supported video file extensions
    QStringList videoExtensions = {
        "*.mp4",
        "*.mkv",
        "*.avi",
        "*.mov",
        "*.webm",
        "*.wmv",
        "*.flv"
    };

    // ? Get all supported media files from the selected folder in one pass
    //? Built-in function that gives info about the files inside the directory
    QFileInfoList mediaFiles = directory.entryInfoList(
        audioExtensions + videoExtensions,
        // ? Only return files that are readable (bit-wise OR)
        QDir::Files | QDir::Readable,
        // ? Sort the files by name
        QDir::Name
    );

    // ? Clear the old playlists before creating the new ones
    m_audioPlaylist.clear();
    m_videoPlaylist.clear();

    // ? Sort every discovered file into the audio or video playlist
    for (const QFileInfo &file : mediaFiles) {

        // ? Convert the local file path into a QUrl
        QUrl fileUrl = QUrl::fromLocalFile(file.absoluteFilePath());

        // ? Route the file based on its extension
        QString suffix = "*." + file.suffix().toLower();

        if (audioExtensions.contains(suffix))
            m_audioPlaylist.append(fileUrl);
        else
            m_videoPlaylist.append(fileUrl);
    }

    // ? Check if no supported media files were found
    if (m_audioPlaylist.isEmpty() && m_videoPlaylist.isEmpty()) {
        emit errorOccurred("No supported audio or video files were found in the selected folder.");
        return;
    }

    // ? Tell the rest of the backend that the playlists have changed
    emit playlistChanged();
}


// * ================= GET PLAYLISTS =================
// ? Returns the current audio and video playlists

QList<QUrl> LocalMedia::getAudioPlaylist() const
{
    return m_audioPlaylist;
}

QList<QUrl> LocalMedia::getVideoPlaylist() const
{
    return m_videoPlaylist;
}