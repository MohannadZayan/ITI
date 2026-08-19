import QtQuick
import QtQuick.Dialogs

import Graduation_Project

MediaBrowserPage {
    id: usbPage
    pageTitle: qsTr("USB Media")
    isUsbPage: true

    // ? Make sure this page always controls the local audio/video players,
    // ? not whatever player another page (e.g. Radio) left active
    Component.onCompleted: MediaController.setMediaType(MediaController.Audio)

    // ? USB drives are also auto-detected in the background, but this lets
    // ? the user manually point at a folder (e.g. a specific subfolder)
    onFolderRequested: folderDialog.open()

    FolderDialog {
        id: folderDialog
        title: qsTr("Choose a USB folder")
        onAccepted: MediaController.setUsbFolder(selectedFolder)
    }
}
