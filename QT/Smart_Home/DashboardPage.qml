import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: dashboardPage

    title: qsTr("Dashboard")
    property int activeDeviceCount: (livingRoomLight.isOn ? 1 : 0)
                                   + (bedroomLight.isOn ? 1 : 0)
                                   + (airConditioner.isOn ? 1 : 0)
                                   + (fan.isOn ? 1 : 0)
                                   + (garageDoor.isOn ? 1 : 0)
    property date currentDateTime: new Date()

    function greetingForCurrentTime() {
        const hour = currentDateTime.getHours()

        if (hour < 12)
            return qsTr("Good morning")
        if (hour < 18)
            return qsTr("Good afternoon")

        return qsTr("Good evening")
    }

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
                text: qsTr("Smart Home Dashboard")
                color: "white"
                font.pixelSize: 42
                font.bold: true
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                id: settingsButton
                text: qsTr("Settings")
                Layout.preferredWidth: 104
                Layout.preferredHeight: 38
                hoverEnabled: true

                contentItem: Label {
                    text: settingsButton.text
                    color: settingsButton.hovered ? "white" : "#C8D0E8"
                    font.pixelSize: 14
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 10
                    color: settingsButton.down ? "#2B4461"
                                              : settingsButton.hovered ? "#263D59" : "transparent"
                    border.width: 1
                    border.color: settingsButton.hovered ? "#47B5FF" : "#59627F"

                    Behavior on color { ColorAnimation { duration: 150 } }
                    Behavior on border.color { ColorAnimation { duration: 150 } }
                }

                onClicked: dashboardPage.goToSettings()
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 112
            radius: 18
            color: "#2A304B"
            border.width: 1
            border.color: "#414A6B"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 22
                spacing: 28

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 4

                    Label {
                        text: dashboardPage.greetingForCurrentTime() + ", Mohannad"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                    }

                    Label {
                        text: Qt.formatDate(dashboardPage.currentDateTime, "dddd, d MMMM")
                              + "  ·  "
                              + Qt.formatTime(dashboardPage.currentDateTime, "h:mm AP")
                        color: "#AAB2CC"
                        font.pixelSize: 14
                    }
                }

                Rectangle {
                    Layout.preferredWidth: 1
                    Layout.preferredHeight: 56
                    color: "#414A6B"
                }

                ColumnLayout {
                    spacing: 3

                    Label {
                        text: qsTr("DEVICES")
                        color: "#9FA9C9"
                        font.pixelSize: 11
                        font.bold: true
                        font.letterSpacing: 1
                    }

                    Label {
                        text: qsTr("5 total")
                        color: "white"
                        font.pixelSize: 19
                        font.bold: true
                    }
                }

                ColumnLayout {
                    spacing: 3

                    Label {
                        text: qsTr("ACTIVE NOW")
                        color: "#9FA9C9"
                        font.pixelSize: 11
                        font.bold: true
                        font.letterSpacing: 1
                    }

                    Label {
                        text: dashboardPage.activeDeviceCount
                        color: "#47B5FF"
                        font.pixelSize: 19
                        font.bold: true
                    }
                }

                ColumnLayout {
                    spacing: 3

                    Label {
                        text: qsTr("SYSTEM")
                        color: "#9FA9C9"
                        font.pixelSize: 11
                        font.bold: true
                        font.letterSpacing: 1
                    }

                    RowLayout {
                        spacing: 6

                        Rectangle {
                            Layout.preferredWidth: 8
                            Layout.preferredHeight: 8
                            radius: 4
                            color: "#5ED7A5"
                        }

                        Label {
                            text: qsTr("Online")
                            color: "#5ED7A5"
                            font.pixelSize: 19
                            font.bold: true
                        }
                    }
                }
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
                    id: livingRoomLight
                    deviceName: qsTr("Living Room Light")
                    roomName: qsTr("Living room")
                    accentColor: "#F6B93B"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/Light-bulb.png"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

                DeviceCard {
                    id: bedroomLight
                    deviceName: qsTr("Bedroom Light")
                    roomName: qsTr("Bedroom")
                    accentColor: "#F6B93B"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/light_bed.png"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

                DeviceCard {
                    id: airConditioner
                    deviceName: qsTr("Air Conditioner")
                    roomName: qsTr("Living room")
                    accentColor: "#47B5FF"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/images.png"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

                DeviceCard {
                    id: fan
                    deviceName: qsTr("Fan")
                    roomName: qsTr("Bedroom")
                    accentColor: "#B084F5"
                    imageSource: "qrc:/qt/qml/Smart_Home/Images/fan_2.jpeg"
                    popup: notificationPopup
                    Layout.preferredWidth: deviceGrid.columns === 2
                                           ? (deviceGrid.width - deviceGrid.columnSpacing) / 2
                                           : deviceGrid.width
                }

                DeviceCard {
                    id: garageDoor
                    deviceName: qsTr("Garage Door")
                    roomName: qsTr("Garage")
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

    Timer {
        interval: 1000
        running: true
        repeat: true

        onTriggered: dashboardPage.currentDateTime = new Date()
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
