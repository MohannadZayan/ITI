import QtQuick

// ? A small auto-dismissing banner for transient status messages (e.g. USB
// ? connected/disconnected) - call show(text) to display it; it slides in
// ? from the top and fades back out on its own after a few seconds.
Item {
    id: root

    property alias accentColor: banner.border.color

    // ? Reserves layout space only while a message is visible, so it doesn't
    // ? leave a gap in the parent's top anchor when hidden
    implicitHeight: visible ? banner.height + banner.anchors.topMargin : 0
    visible: opacity > 0
    opacity: 0

    accentColor: "#20c1e3"

    function show(text) {
        messageText.text = text
        root.opacity = 1
        hideTimer.restart()
    }

    Behavior on opacity { NumberAnimation { duration: 200; easing.type: Easing.OutQuad } }

    Timer {
        id: hideTimer
        interval: 2500
        onTriggered: root.opacity = 0
    }

    Rectangle {
        id: banner
        anchors.top: parent.top
        anchors.topMargin: 16
        anchors.horizontalCenter: parent.horizontalCenter
        width: messageText.implicitWidth + 40
        height: messageText.implicitHeight + 20
        radius: 10
        color: "#0a1a24"
        border.color: root.accentColor
        border.width: 2

        Text {
            id: messageText
            anchors.centerIn: parent
            color: "white"
            font.bold: true
            font.pixelSize: 16
        }
    }
}
