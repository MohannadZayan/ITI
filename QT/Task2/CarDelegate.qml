import QtQuick

Flipable {
    id: card

    // "model" is filled in automatically by the GridView with the
    // data (name, image, engine...) of the car this card represents.
    property string carName: model.name
    property string carImage: model.image
    property string carEngine: model.engine
    property string carHorsepower: model.horsepower
    property string carTopSpeed: model.topSpeed
    property string carDescription: model.description

    // True once the card has been tapped, showing its back side.
    property bool flipped: false

    width: GridView.view.cellWidth - 20
    height: GridView.view.cellHeight - 20

    // Tilt and grow a bit while the mouse is hovering over the card
    // (only while it's showing its front, so it doesn't fight the flip).
    scale: (hoverArea.containsMouse && !flipped) ? 1.05 : 1.0
    rotation: (hoverArea.containsMouse && !flipped) ? 10 : 0

    Behavior on scale {
        NumberAnimation { duration: 200; easing.type: Easing.OutBack }
    }
    Behavior on rotation {
        NumberAnimation { duration: 200; easing.type: Easing.OutBack }
    }

    // ---- front side: big photo + name ----
    front: Rectangle {
        anchors.fill: parent
        radius: 12
        color: "#22252B"
        border.width: card.flipped ? 3 : 1
        border.color: card.flipped ? "#4C8DFF" : "#33363D"

        Behavior on border.color {
            ColorAnimation { duration: 150 }
        }
        Behavior on border.width {
            NumberAnimation { duration: 150 }
        }

        Column {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 14

            Image {
                width: parent.width
                height: width * 0.72
                source: card.carImage
                fillMode: Image.PreserveAspectFit
            }

            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: card.carName
                font.pixelSize: 24
                font.bold: true
                color: "#F2F3F5"
                elide: Text.ElideRight
            }

            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: "Tap for details"
                font.pixelSize: 12
                color: "#6E7480"
            }
        }
    }

    // ---- back side: description + specs ----
    back: Rectangle {
        anchors.fill: parent
        radius: 12
        color: "#22252B"
        border.width: 3
        border.color: "#4C8DFF"

        Column {
            anchors.fill: parent
            anchors.margins: 22
            spacing: 16

            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: card.carName
                font.pixelSize: 20
                font.bold: true
                color: "#F2F3F5"
                elide: Text.ElideRight
            }

            Text {
                width: parent.width
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                text: card.carDescription
                font.pixelSize: 14
                color: "#C6CAD1"
            }

            Column {
                width: parent.width
                spacing: 6

                Text {
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    text: "Engine: " + card.carEngine
                    font.pixelSize: 13
                    color: "#9BA1AC"
                }

                Text {
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    text: "Horsepower: " + card.carHorsepower
                    font.pixelSize: 13
                    color: "#9BA1AC"
                }

                Text {
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    text: "Top Speed: " + card.carTopSpeed
                    font.pixelSize: 13
                    color: "#9BA1AC"
                }
            }
        }
    }

    // Rotating the card around its vertical (Y) axis is what makes it
    // look like it's flipping over, like a physical playing card.
    transform: Rotation {
        id: flipRotation
        origin.x: card.width / 2
        origin.y: card.height / 2
        axis { x: 0; y: 1; z: 0 }
        angle: 0
    }

    states: State {
        name: "flippedState"
        when: card.flipped
        PropertyChanges { target: flipRotation; angle: 180 }
    }

    transitions: Transition {
        NumberAnimation { target: flipRotation; property: "angle"; duration: 400; easing.type: Easing.InOutQuad }
    }

    MouseArea {
        id: hoverArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: card.flipped = !card.flipped
    }
}
