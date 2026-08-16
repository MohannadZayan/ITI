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
}
