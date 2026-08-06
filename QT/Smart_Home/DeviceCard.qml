pragma Translator: translationController.currentLanguage
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: card

    property string deviceName: ""
    property string roomName: "Smart device"
    property string imageSource: ""
    property color accentColor: "#47B5FF"
    property var popup
    property alias isOn: deviceSwitch.checked

    implicitWidth: 460
    implicitHeight: 240
    Layout.fillWidth: true
    Layout.preferredHeight: 240

    radius: 18
    color: hoverHandler.hovered ? "#343B5C" : "#2D3250"
    border.width: 1
    border.color: hoverHandler.hovered ? accentColor : "#414865"
    scale: hoverHandler.hovered ? 1.015 : 1

    Behavior on color { ColorAnimation { duration: 160 } }
    Behavior on border.color { ColorAnimation { duration: 160 } }
    Behavior on scale { NumberAnimation { duration: 160; easing.type: Easing.OutCubic } }

    HoverHandler {
        id: hoverHandler
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 26
        spacing: 18

        Rectangle {
            Layout.preferredWidth: 96
            Layout.preferredHeight: 96
            radius: 16
            color: Qt.rgba(card.accentColor.r, card.accentColor.g, card.accentColor.b, 0.18)
            border.width: 1
            border.color: Qt.rgba(card.accentColor.r, card.accentColor.g, card.accentColor.b, 0.45)

            Image {
                anchors.centerIn: parent
                width: 64
                height: 64
                source: card.imageSource
                fillMode: Image.PreserveAspectFit
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            spacing: 8

            Label {
                text: card.roomName.toUpperCase()
                color: "#9FA9C9"
                font.pixelSize: 12
                font.bold: true
                font.letterSpacing: 1.2
            }

            Label {
                text: card.deviceName
                color: "#FFFFFF"
                font.pixelSize: 24
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Rectangle {
                    Layout.preferredWidth: statusText.implicitWidth + 20
                    Layout.preferredHeight: 26
                    radius: 13
                    color: deviceSwitch.checked
                           ? Qt.rgba(card.accentColor.r, card.accentColor.g, card.accentColor.b, 0.22)
                           : "#242A42"

                    Label {
                        id: statusText
                        anchors.centerIn: parent
                        text: deviceSwitch.checked ? qsTr("ON") : qsTr("OFF")
                        color: deviceSwitch.checked ? card.accentColor : "#AAB2CC"
                        font.pixelSize: 11
                        font.bold: true
                    }
                }

                Label {
                    text: deviceSwitch.checked ? qsTr("100%") : qsTr("0%")
                    color: "#D7DCF0"
                    font.pixelSize: 14
                    font.bold: true
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 8
                radius: height / 2
                color: "#1F243B"

                Rectangle {
                    width: parent.width * (deviceSwitch.checked ? 1 : 0)
                    height: parent.height
                    radius: parent.radius
                    color: card.accentColor

                    Behavior on width {
                        NumberAnimation { duration: 350; easing.type: Easing.OutCubic }
                    }
                }
            }
        }

        Switch {
            id: deviceSwitch
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredWidth: 56
            Layout.preferredHeight: 32
            scale: 1.05

            indicator: Rectangle {
                implicitWidth: 54
                implicitHeight: 30
                radius: height / 2
                color: deviceSwitch.checked ? card.accentColor : "#20263D"
                border.width: 1
                border.color: deviceSwitch.checked ? card.accentColor : "#58617D"

                Behavior on color { ColorAnimation { duration: 180 } }

                Rectangle {
                    x: deviceSwitch.checked ? parent.width - width - 4 : 4
                    anchors.verticalCenter: parent.verticalCenter
                    width: 22
                    height: 22
                    radius: width / 2
                    color: "#FFFFFF"

                    Behavior on x {
                        NumberAnimation { duration: 180; easing.type: Easing.OutCubic }
                    }
                }
            }

            contentItem: Item { }

            onToggled: {
                popup.showMessage(card.deviceName + (checked ? qsTr(" ON") : qsTr(" OFF")))
            }
        }
    }
}
