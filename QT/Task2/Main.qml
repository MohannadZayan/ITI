import QtQuick
import QtQuick.Controls.Basic

ApplicationWindow {
    id: window

    width: 900
    height: 700
    visible: true
    title: qsTr("Car Gallery")

    CarModel {
        id: carsModel
    }

    Rectangle {
        anchors.fill: parent
        color: "#1B1D22"

        GridView {
            id: grid

            anchors.fill: parent
            anchors.margins: 24
            clip: true

            cellWidth: 460
            cellHeight: 460

            model: carsModel
            delegate: CarDelegate {}

            currentIndex: -1

            ScrollBar.vertical: ScrollBar {}

            // How each card animates in when the gallery first appears.
            populate: Transition {
                NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 300 }
                NumberAnimation { property: "scale"; from: 0.8; to: 1; duration: 300; easing.type: Easing.OutBack }
            }
        }
    }
}