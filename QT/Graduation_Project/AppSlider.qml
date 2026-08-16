import QtQuick
import QtQuick.Controls.Basic

// ? A styled slider used across the app - Basic style ships with no visual
// ? styling of its own. Used for both the playback progress bar and the
// ? volume slider so they share one look instead of two hand-rolled copies.
Slider {
    id: control

    property color accentColor: "#20c1e3"
    property real trackHeight: 6
    property real handleSize: 16

    background: Rectangle {
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        width: control.availableWidth
        height: control.trackHeight
        radius: height / 2
        color: Qt.rgba(1, 1, 1, 0.2)

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            radius: height / 2
            color: control.enabled ? control.accentColor : Qt.rgba(1, 1, 1, 0.35)
        }
    }

    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + control.availableHeight / 2 - height / 2
        width: control.handleSize
        height: control.handleSize
        radius: width / 2
        color: "white"
        border.color: control.enabled ? control.accentColor : Qt.rgba(1, 1, 1, 0.35)
        border.width: 2
        opacity: control.enabled ? 1.0 : 0.6
    }
}
