import QtQuick
import QtQuick.Dialogs

import Graduation_Project

MediaBrowserPage {
    id: localPage
    pageTitle: qsTr("Local Media")

    // ? Make sure this page always controls the local audio/video players,
    // ? not whatever player another page (e.g. Radio) left active
    Component.onCompleted: MediaController.setMediaType(MediaController.Audio)

    onFolderRequested: folderDialog.open()

    FolderDialog {
        id: folderDialog
        title: qsTr("Choose a folder")
        onAccepted: MediaController.setMediaFolder(selectedFolder)
    }
}
