import QtQuick

// ? Shared animated background - slow "Ken Burns" zoom on the image plus
// ? softly glowing particles drifting upward. Used by every page so they
// ? all match instead of each having its own copy that can drift apart.
Item {
    id: root

    Image {
        id: background
        anchors.fill: parent
        source: "assets/images/background.jpg"
        fillMode: Image.PreserveAspectCrop

        SequentialAnimation on scale {
            loops: Animation.Infinite
            NumberAnimation { to: 1.08; duration: 14000; easing.type: Easing.InOutSine }
            NumberAnimation { to: 1.0; duration: 14000; easing.type: Easing.InOutSine }
        }
    }

    Repeater {
        model: 10

        delegate: Rectangle {
            id: particle

            property real size: 4 + Math.random() * 10
            property real startX: Math.random() * root.width
            property real startY: root.height + size + Math.random() * 200
            property real travel: 200 + Math.random() * 250

            width: size
            height: size
            radius: size / 2
            color: "white"
            opacity: 0
            x: startX
            y: startY

            SequentialAnimation {
                running: true
                loops: Animation.Infinite

                PauseAnimation { duration: Math.random() * 6000 }

                ParallelAnimation {
                    NumberAnimation {
                        target: particle
                        property: "y"
                        to: particle.startY - particle.travel - root.height
                        duration: 9000 + Math.random() * 7000
                        easing.type: Easing.InOutSine
                    }
                    SequentialAnimation {
                        NumberAnimation { target: particle; property: "opacity"; to: 0.35 + Math.random() * 0.25; duration: 2500 }
                        PauseAnimation { duration: 4000 }
                        NumberAnimation { target: particle; property: "opacity"; to: 0; duration: 2500 }
                    }
                }

                // ? Reset to a new random starting position for the next loop
                ScriptAction {
                    script: {
                        particle.startX = Math.random() * root.width
                        particle.startY = root.height + particle.size + Math.random() * 200
                        particle.x = particle.startX
                        particle.y = particle.startY
                    }
                }
            }
        }
    }
}
