import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {

    id: dashboardPage

    title: "Dashboard"

    background: Rectangle {
        color: "#1E1E2F"
    }

    ColumnLayout {

        anchors.fill: parent
        anchors.margins: 20
        spacing: 40

        Label {
            text: "Smart Home Dashboard"
            color: "white"

            font.pixelSize: 42
            font.bold: true

            Layout.alignment: Qt.AlignHCenter
        }

        ScrollView {

            Layout.fillWidth: true
            Layout.fillHeight: true

            Column {

                width: parent.width
                spacing: 45

                //=====LIVING ROOM LIGHT=====

                Rectangle {

                    width: parent.width
                    height: 240

                    radius: 15
                    color: "#2D3250"

                    RowLayout {

                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 35

                        Image {
                            source: "qrc:/qt/qml/Smart_Home/Images/Light-bulb.png"

                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 100

                            fillMode: Image.PreserveAspectFit

                            sourceSize.width: 100
                            sourceSize.height: 100
                        }

                        ColumnLayout {

                            spacing: 10

                            Label {
                                text: "Living Room Light"
                                color: "white"
                                font.pixelSize: 28
                                font.bold: true
                            }

                            Label {
                                text: "Status : " + Math.round(lightProgress.value * 100) + "%"
                                color: "lightgray"
                                font.pixelSize: 18
                            }

                            ProgressBar {
                                id: lightProgress
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
                            lightProgress.value = 1.0
                            console.log("Living Room Light: ON")
                                                        }
                             else {
                            lightProgress.value = 0.0
                            console.log("Living Room Light: OFF")
                            }

                            }

                        }

                    }


                }

                //=====BEDROOM LIGHT=====


                Rectangle {

                    width: parent.width
                    height: 240

                    radius: 15
                    color: "#2D3250"

                    RowLayout {

                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 35

                        Image {
                            source: "qrc:/qt/qml/Smart_Home/Images/light_bed.png"

                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 100

                            fillMode: Image.PreserveAspectFit

                            sourceSize.width: 100
                            sourceSize.height: 100
                        }

                        ColumnLayout {

                            spacing: 10

                            Label {
                                text: "Bedroom Light"
                                color: "white"
                                font.pixelSize: 28
                                font.bold: true
                            }

                            Label {
                                text: "Status : " + Math.round(bedroomProgress.value * 100) + "%"
                                color: "lightgray"
                                font.pixelSize: 18
                            }

                            ProgressBar {
                                id: bedroomProgress
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
                                    bedroomProgress.value = 1.0
                                    console.log("Bedroom Light: ON")
                                } else {
                                    bedroomProgress.value = 0.0
                                    console.log("Bedroom Light: OFF")
                                }

                            }

                        }

                    }

                }

                //=====AIR CONDITIONER=====


                Rectangle {

                    width: parent.width
                    height: 240

                    radius: 15
                    color: "#2D3250"

                    RowLayout {

                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 35

                        Image {
                            source: "qrc:/qt/qml/Smart_Home/Images/images.png"

                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 100

                            fillMode: Image.PreserveAspectFit

                            sourceSize.width: 100
                            sourceSize.height: 100
                        }

                        ColumnLayout {

                            spacing: 10

                            Label {
                                text: "Air Conditioner"
                                color: "white"
                                font.pixelSize: 28
                                font.bold: true
                            }

                            Label {
                                text: "Status : " + Math.round(acProgress.value * 100) + "%"
                                color: "lightgray"
                                font.pixelSize: 18
                            }

                            ProgressBar {
                                id: acProgress
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
                                    acProgress.value = 1.0
                                    console.log("Air Conditioner: ON")
                                } else {
                                    acProgress.value = 0.0
                                    console.log("Air Conditioner: OFF")
                                }

                            }

                        }

                    }

                }

                //=====FAN=====


                Rectangle {

                    width: parent.width
                    height: 240

                    radius: 15
                    color: "#2D3250"

                    RowLayout {

                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 35

                        Image {
                            source: "qrc:/qt/qml/Smart_Home/Images/fan_2.jpeg"

                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 100

                            fillMode: Image.PreserveAspectFit

                            sourceSize.width: 100
                            sourceSize.height: 100
                        }

                        ColumnLayout {

                            spacing: 10

                            Label {
                                text: "Fan"
                                color: "white"
                                font.pixelSize: 28
                                font.bold: true
                            }

                            Label {
                                text: "Status : " + Math.round(fanProgress.value * 100) + "%"
                                color: "lightgray"
                                font.pixelSize: 18
                            }

                            ProgressBar {
                                id: fanProgress
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
                                    fanProgress.value = 1.0
                                    console.log("Fan: ON")
                                } else {
                                    fanProgress.value = 0.0
                                    console.log("Fan: OFF")
                                }

                            }

                        }

                    }

                }

                //=====GARAGE=====


                Rectangle {

                    width: parent.width
                    height: 240

                    radius: 15
                    color: "#2D3250"

                    RowLayout {

                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 35

                        Image {
                            source: "qrc:/qt/qml/Smart_Home/Images/garage_2.jpeg"

                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 100

                            fillMode: Image.PreserveAspectFit

                            sourceSize.width: 100
                            sourceSize.height: 100
                        }

                        ColumnLayout {

                            spacing: 10

                            Label {
                                text: "Garage Door"
                                color: "white"
                                font.pixelSize: 28
                                font.bold: true
                            }

                            Label {
                                text: "Status : " + Math.round(garageProgress.value * 100) + "%"
                                color: "lightgray"
                                font.pixelSize: 18
                            }

                            ProgressBar {
                                id: garageProgress
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
                                    garageProgress.value = 1.0
                                    console.log("Garage Door: OPEN")
                                } else {
                                    garageProgress.value = 0.0
                                    console.log("Garage Door: CLOSED")
                                }

                            }

                        }

                    }

                }

            }


        }

        Button {

            text: "Settings"

            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                dashboardPage.StackView.view.push("settingsPage.qml")
            }
        }


    }

}