import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {

    id: dashboardPage

    title: "Dashboard"

    background: Rectangle {
        color: "#1E1E2F"
    }

    ColumnLayout {

        anchors.fill: parent
        anchors.margins: 20
        spacing: 40

        Label {
            text: "Smart Home Dashboard"
            color: "white"
            font.pixelSize: 42
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        ScrollView {

            Layout.fillWidth: true
            Layout.fillHeight: true

            Column {

                width: parent.width
                spacing: 45

                DeviceCard {
                    deviceName: "Living Room Light"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/Light-bulb.png"
                    popup: notificationPopup
                }

                DeviceCard {
                    deviceName: "Bedroom Light"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/light_bed.png"
                    popup: notificationPopup
                }

                DeviceCard {
                    deviceName: "Air Conditioner"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/images.png"
                    popup: notificationPopup
                }

                DeviceCard {
                    deviceName: "Fan"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/fan_2.jpeg"
                    popup: notificationPopup
                }

                DeviceCard {
                    deviceName: "Garage Door"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/garage_2.jpeg"
                    popup: notificationPopup
                }

            }

        }

        Button {
            text: "Settings"
            Layout.alignment: Qt.AlignHCenter

            onClicked: dashboardPage.goToSettings()
        }

    }

    function goToSettings() {
        StackView.view.push("settingsPage.qml")
    }

    Popup {

        id: notificationPopup

        x: (parent.width - width) / 2
        y: 20

        width: 320
        height: 60

        modal: false
        focus: false

        background: Rectangle {
            color: "#34495E"
            radius: 12
            border.color: "#5DADE2"
            border.width: 2
        }

        Label {
            id: popupText
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 18
            font.bold: true
        }

        Timer {
            id: popupTimer
            interval: 1500
            repeat: false
            onTriggered: notificationPopup.close()
        }

        function showMessage(message) {
            popupText.text = message
            notificationPopup.open()
            popupTimer.restart()
        }
    }
}