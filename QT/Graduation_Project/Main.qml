import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import QtQuick.VirtualKeyboard

import Graduation_Project

ApplicationWindow {
    id: window
    width: 640
    height: 480
    minimumWidth: 200
    minimumHeight: 250
    visible: true
    title: qsTr("Hello World")

    Column {
        anchors.centerIn: parent
        spacing: 8

        Text {
            text: "MediaController reachable — position: " + MediaController.position + ", muted: " + MediaController.muted
        }

        Button {
            text: "Toggle mute (invokable call test)"
            onClicked: MediaController.setMuted(!MediaController.muted)
        }
    }
}
