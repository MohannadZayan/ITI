import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    function goBack () {
        StackView.view.pop()
    }

    id: settingsPage

    title: "Settings"

    background: Rectangle {
        color: "#1E1E2F"
    }

    ColumnLayout {

        anchors.centerIn: parent
        spacing: 25

        Label {
            text: "Settings"
            color: "white"
            font.pixelSize: 36
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            text: "Language"
            color: "white"
        }

        ComboBox {

            model: ["English", "Arabic", "French"]

            onCurrentTextChanged: {
                console.log("Language:", currentText)
            }
        }

        Label {
            text: "Brightness"
            color: "white"
        }

        Slider {

            from: 0
            to: 100
            value: 50
            Layout.preferredWidth: 250

            onValueChanged: {
                console.log("Brightness:", value)
            }
        }

        Label {
            text: "Temperature"
            color: "white"
        }

        Dial {

            from: 16
            to: 30
            value: 22

            onValueChanged: {
                console.log("Temperature:", value)
            }
        }

        CheckBox {

            text: "Enable Notifications"

            onCheckedChanged: {
                console.log("Notifications:", checked)
            }
        }

        Button {

            text: "Save Settings"

            onClicked: {
                console.log("Settings Saved")
            }
        }

        Button {

            text: "← Dashboard"

            onClicked: {
                settingsPage.goBack()
            }
        }

    }

}