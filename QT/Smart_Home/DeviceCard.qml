import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {

    property string deviceName: ""
    property string imageSource: ""
    property var popup

    width: parent.width
    height: 240

    radius: 15
    color: "#2D3250"

    RowLayout {

        anchors.fill: parent
        anchors.margins: 20
        spacing: 35

        Image {

            source: imageSource

            Layout.preferredWidth: 100
            Layout.preferredHeight: 100

            fillMode: Image.PreserveAspectFit

            sourceSize.width: 100
            sourceSize.height: 100
        }

        ColumnLayout {

            spacing: 10

            Label {

                text: deviceName

                color: "white"

                font.pixelSize: 28
                font.bold: true
            }

            Label {

                text: "Status : " + Math.round(progress.value * 100) + "%"

                color: "lightgray"

                font.pixelSize: 18
            }

            ProgressBar {

                id: progress

                value: 0.0

                Layout.preferredWidth: 320
                Layout.preferredHeight: 15

                Behavior on value {

                    NumberAnimation {
                        duration: 500
                    }

                }

            }

        }

        Item {

            Layout.fillWidth: true

        }

        Switch {

            scale: 1.5

            onCheckedChanged: {

                if (checked) {

                    progress.value = 1.0

                    popup.showMessage (deviceName + " ON" )

                }
                else {

                    progress.value = 0.0

                    popup.showMessage(deviceName + " OFF")

                }

            }

        }

    }

}