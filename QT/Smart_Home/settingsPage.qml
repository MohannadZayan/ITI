import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: settingsPage
    title: qsTr("Settings")

    function goBack() {
        StackView.view.pop()
    }

    background: Rectangle {
        color: "#1E1E2F"
    }

    ScrollView {
        anchors.fill: parent
        anchors.margins: 24

        ColumnLayout {
            width: settingsPage.width - 48
            spacing: 28

            Label {
                text: qsTr("Smart Home Settings")
                color: "white"
                font.pixelSize: 40
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 250
                radius: 18
                color: "#2A304B"
                border.color: "#414A6B"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 24
                    spacing: 18

                    Label {
                        text: qsTr("General")
                        color: "white"
                        font.pixelSize: 24
                        font.bold: true
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: qsTr("Language")
                            color: "white"
                            font.pixelSize: 18
                            Layout.preferredWidth: 220
                        }

                        ComboBox {
                            id: languageBox
                            Layout.fillWidth: true
                            model: [qsTr("English"), qsTr("Arabic"), qsTr("French")]
                            currentIndex: translationController.currentLanguage === "ar" ? 1 : translationController.currentLanguage === "fr" ? 2 : 0

                            onCurrentIndexChanged: {
                                var selectedLanguage = currentIndex === 1 ? "ar" : currentIndex === 2 ? "fr" : "en"
                                if (translationController.currentLanguage !== selectedLanguage) {
                                    translationController.setLanguage(selectedLanguage)
                                    settingsPopup.showMessage(qsTr("Language changed to %1").arg(currentText))
                                }
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: qsTr("Notifications")
                            color: "white"
                            font.pixelSize: 18
                            Layout.preferredWidth: 220
                        }

                        Switch {
                            checked: true

                            onCheckedChanged:
                                settingsPopup.showMessage(
                                    checked ?
                                    qsTr("Notifications Enabled") :
                                    qsTr("Notifications Disabled"))
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: qsTr("Auto Lock")
                            color: "white"
                            font.pixelSize: 18
                            Layout.preferredWidth: 220
                        }

                        Switch {
                            checked: true

                            onCheckedChanged:
                                settingsPopup.showMessage(
                                    checked ?
                                    qsTr("Auto Lock Enabled") :
                                    qsTr("Auto Lock Disabled"))
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 260
                radius: 18
                color: "#2A304B"
                border.color: "#414A6B"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 24
                    spacing: 24

                    Label {
                        text: qsTr("Environment")
                        color: "white"
                        font.pixelSize: 24
                        font.bold: true
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 10

                        RowLayout {
                            Layout.fillWidth: true

                            Label {
                                text: qsTr("Brightness")
                                color: "white"
                                font.pixelSize: 18
                                Layout.preferredWidth: 220
                            }

                            Label {
                                text: Math.round(brightnessSlider.value) + "%"
                                color: "#47B5FF"
                                font.pixelSize: 18
                                font.bold: true
                            }
                        }

                        Slider {
                            id: brightnessSlider
                            Layout.fillWidth: true
                            from: 0
                            to: 100
                            value: 50
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 10

                        RowLayout {
                            Layout.fillWidth: true

                            Label {
                                text: qsTr("Temperature")
                                color: "white"
                                font.pixelSize: 18
                                Layout.preferredWidth: 220
                            }

                            Label {
                                text: Math.round(tempSlider.value) + "°C"
                                color: "#47B5FF"
                                font.pixelSize: 18
                                font.bold: true
                            }
                        }

                        Slider {
                            id: tempSlider
                            Layout.fillWidth: true
                            from: 16
                            to: 30
                            value: 22
                        }
                    }
                }
            }

            Button {
                id: saveButton
                Layout.fillWidth: true
                Layout.preferredHeight: 60
                text: qsTr("Save Changes")

                contentItem: Label {
                    text: saveButton.text
                    color: "white"
                    font.pixelSize: 18
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 12
                    color: saveButton.down ? "#2380D3"
                                           : saveButton.hovered ? "#3B9EFF"
                                                                : "#47B5FF"

                    Behavior on color {
                        ColorAnimation { duration: 150 }
                    }
                }

                onClicked: settingsPopup.showMessage(qsTr("Settings Saved Successfully"))
            }

            Button {
                text: qsTr("← Dashboard")
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 220
                Layout.preferredHeight: 48

                onClicked: settingsPage.goBack()
            }
        }
    }

    Popup {
        id: settingsPopup

        x: (parent.width - width) / 2
        y: 20

        width: 360
        height: 60

        modal: false
        focus: false

        background: Rectangle {
            color: "#34495E"
            radius: 12
            border.color: "#47B5FF"
            border.width: 2
        }

        Label {
            id: popupLabel
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 17
            font.bold: true
        }

        Timer {
            id: popupTimer
            interval: 1500
            repeat: false
            onTriggered: settingsPopup.close()
        }

        function showMessage(message) {
            popupLabel.text = message
            settingsPopup.open()
            popupTimer.restart()
        }
    }
}