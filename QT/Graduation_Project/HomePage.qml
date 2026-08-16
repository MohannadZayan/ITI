import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Item {
    id: homePage

    // ? Everything below is sized relative to this instead of fixed pixel
    // ? values, so the page scales up properly on a large/fullscreen window
    readonly property real scaleUnit: Math.min(width, height)

    // ? The background image is animated (slow zoom) and can overflow its
    // ? own bounds while doing so - clip here so it never spills past the window
    clip: true

    // ? Animated background - declared first, so everything else draws on top of it
    AnimatedBackground {
        anchors.fill: parent
    }

    // ? ITI watermark - top-right corner, partially transparent
    Image {
        id: itiWatermark
        source: "assets/images/iti.png"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 16
        width: 64
        fillMode: Image.PreserveAspectFit
        opacity: 0.7
    }

    // ? Main content - title and the 3 mode buttons, centered over the background
    ColumnLayout {
        anchors.centerIn: parent
        spacing: homePage.scaleUnit * 0.04

        Text {
            text: qsTr("Choose Your Media Source")
            font.pixelSize: homePage.scaleUnit * 0.05
            font.bold: true
            color: "white"
            Layout.alignment: Qt.AlignHCenter
        }

        ColumnLayout {
            spacing: homePage.scaleUnit * 0.02
            Layout.alignment: Qt.AlignHCenter

            AppButton {
                text: qsTr("Local")
                Layout.preferredWidth: homePage.scaleUnit * 0.35
                Layout.preferredHeight: homePage.scaleUnit * 0.08
                onClicked: homePage.StackView.view.push("LocalPage.qml")
            }

            AppButton {
                text: qsTr("USB")
                Layout.preferredWidth: homePage.scaleUnit * 0.35
                Layout.preferredHeight: homePage.scaleUnit * 0.08
                onClicked: homePage.StackView.view.push("UsbPage.qml")
            }

            AppButton {
                text: qsTr("Radio")
                Layout.preferredWidth: homePage.scaleUnit * 0.35
                Layout.preferredHeight: homePage.scaleUnit * 0.08
                onClicked: homePage.StackView.view.push("RadioPage.qml")
            }
        }
    }
}
