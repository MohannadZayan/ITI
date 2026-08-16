import QtQuick

// ? A clickable icon with hover feedback (scale pop) and a disabled state
// ? (dimmed, no pointer cursor) - used for every playback control icon
Image {
    id: root

    signal clicked()

    fillMode: Image.PreserveAspectFit
    opacity: enabled ? 1.0 : 0.4

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: root.enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
        onClicked: if (root.enabled) root.clicked()
    }

    scale: (mouseArea.containsMouse && root.enabled) ? 1.1 : 1.0
    Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutQuad } }
}
