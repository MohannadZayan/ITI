import QtQuick
import QtQuick.Controls.Basic

// ? A styled button used across the app - Basic style ships with no visual
// ? styling of its own, so this gives every button a consistent look plus
// ? hover/press feedback (accent color change + a small scale "pop")
Button {
    id: control

    property color accentColor: "#c0392b"
    property color hoverColor: "#e74c3c"

    // ? Persistent highlight for "this is the active choice" - e.g. the
    // ? currently selected Audio/Video toggle - independent of hover state
    property bool selected: false

    hoverEnabled: true

    contentItem: Text {
        text: control.text
        // ? Sized relative to the button's own height so it stays
        // ? proportionate whether this is a small toggle or a big home button
        font.pixelSize: Math.max(12, control.height * 0.32)
        font.bold: true
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        radius: 8
        color: control.pressed
            ? Qt.darker(control.accentColor, 1.3)
            : (control.hovered || control.selected)
                ? control.hoverColor
                : Qt.rgba(1, 1, 1, 0.08)
        border.width: 2
        border.color: (control.hovered || control.selected) ? control.hoverColor : Qt.rgba(1, 1, 1, 0.3)

        Behavior on color { ColorAnimation { duration: 150 } }
        Behavior on border.color { ColorAnimation { duration: 150 } }
    }

    scale: control.pressed ? 0.96 : control.hovered ? 1.04 : 1.0
    Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutQuad } }
}
