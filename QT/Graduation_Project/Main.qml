import QtQuick
import QtQuick.Controls.Basic

import Graduation_Project

ApplicationWindow {
    id: window
    width: 640
    height: 480
    minimumWidth: 200
    minimumHeight: 250
    visible: true
    title: qsTr("Media Player")

    // ? Hosts whichever page is currently active, and handles navigation
    // ? between pages (push forward, pop back)
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: HomePage {}
    }

    // ? Instantiated on demand when a USB is plugged in, rather than eagerly,
    // ? so it doesn't scan/set up media state before it's actually needed
    Component {
        id: usbPageComponent
        UsbPage {}
    }

    // ? USB status is shown here (not on a specific page) since detection
    // ? runs continuously in the backend regardless of which page is active
    Toast {
        id: usbToast
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        z: 100
    }

    Connections {
        target: MediaController

        function onUsbConnected() {
            usbToast.show(qsTr("USB Connected"))

            // ? Jump straight to the USB page so the freshly-scanned
            // ? playlist is visible, unless we're already there
            if (!stackView.currentItem || !stackView.currentItem.isUsbPage)
                stackView.push(usbPageComponent)
        }

        function onUsbDisconnected() {
            usbToast.show(qsTr("USB Disconnected"))
        }
    }
}
