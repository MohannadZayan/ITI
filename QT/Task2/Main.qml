import QtQuick
import QtQuick.Controls.Basic

ApplicationWindow {
    id: window

    width: 900
    height: 700
    visible: true
    title: qsTr("Car Gallery")

    // Properties
    property bool showInfo: false

    property string carModel: ""
    property string engine: ""
    property string horsepower: ""
    property string topSpeed: ""

    Rectangle {
        anchors.fill: parent
        color: "#F0F0F0"

        Row {
            id: imageRow

            spacing: 20

            anchors {
                top: parent.top
                topMargin: 40
                horizontalCenter: parent.horizontalCenter
            }

            //================ BMW M4 =================
            Image {
                source: "qrc:/qt/qml/Task2/bmw_m4.jpg"

                width: 220
                height: 150
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        window.showInfo = true
                        window.carModel = "BMW M4 Competition"
                        window.engine = "3.0L Twin Turbo I6"
                        window.horsepower = "503 HP"
                        window.topSpeed = "290 km/h"
                    }
                }
            }

            //================ BMW M3 =================
            Image {
                source: "qrc:/qt/qml/Task2/bmw_m3.jpeg"

                width: 220
                height: 150
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        window.showInfo = true
                        window.carModel = "BMW M3 Competition"
                        window.engine = "3.0L Twin Turbo I6"
                        window.horsepower = "473 HP"
                        window.topSpeed = "250 km/h"
                    }
                }
            }

            //================ SEAT =================
            Image {
                source: "qrc:/qt/qml/Task2/SEAT_Leon.jpg"

                width: 220
                height: 150
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        window.showInfo = true
                        window.carModel = "SEAT Leon "
                        window.engine = "1.4L Turbo"
                        window.horsepower = "150HP"
                        window.topSpeed = "250 km/h"
                    }
                }
            }
        }

        Column {
            visible: window.showInfo

            spacing: 10

            anchors {
                top: imageRow.bottom
                topMargin: 40
                horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "Model: " + window.carModel
                font.pixelSize: 24
            }

            Text {
                text: "Engine: " + window.engine
                font.pixelSize: 24
            }

            Text {
                text: "Horsepower: " + window.horsepower
                font.pixelSize: 24
            }

            Text {
                text: "Top Speed: " + window.topSpeed
                font.pixelSize: 24
            }
        }
    }
}