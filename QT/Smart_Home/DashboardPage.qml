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
        spacing: 24

        RowLayout {
            Layout.fillWidth: true

            Label {
                text: "Smart Home Dashboard"
                color: "white"
                font.pixelSize: 42
                font.bold: true
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "Settings"
                onClicked: dashboardPage.goToSettings()
            }
        }

        ScrollView {
            id: deviceScrollView

            Layout.fillWidth: true
            Layout.fillHeight: true

            GridLayout {
                id: deviceGrid

                width: deviceScrollView.availableWidth
                columns: width >= 1100 ? 2 : 1
                columnSpacing: 32
                rowSpacing: 32

                DeviceCard {
                    deviceName: "Living Room Light"
                    roomName: "Living room"
                    accentColor: "#F6B93B"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/Light-bulb.png"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

                DeviceCard {
                    deviceName: "Bedroom Light"
                    roomName: "Bedroom"
                    accentColor: "#F6B93B"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/light_bed.png"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

                DeviceCard {
                    deviceName: "Air Conditioner"
                    roomName: "Living room"
                    accentColor: "#47B5FF"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/images.png"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

                DeviceCard {
                    deviceName: "Fan"
                    roomName: "Bedroom"
                    accentColor: "#B084F5"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/fan_2.jpeg"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

                DeviceCard {
                    deviceName: "Garage Door"
                    roomName: "Garage"
                    accentColor: "#5ED7A5"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/garage_2.jpeg"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

            }

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
