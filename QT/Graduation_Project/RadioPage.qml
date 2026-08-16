import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import Graduation_Project

// ? Radio has no audio/video toggle and no seekable duration, and instead
// ? of a folder picker it opens a list of built-in stations - everything
// ? else is the same shared layout as Local/USB.
MediaBrowserPage {
    id: radioPage

    pageTitle: qsTr("Radio")
    showModeToggle: false
    isLive: true

    // ? Built-in Quran radio stations - stream URLs verified to be live before adding
    readonly property var stations: [
        { name: qsTr("Quran Radio — Makkah (Saudi Arabia)"), url: "http://stream.radiojar.com/0tpy1h0kxtzuv" },
        { name: qsTr("Quran Radio — Cairo (Egypt)"), url: "https://stream.radiojar.com/8s5u5tpdtwzuv" },
        { name: qsTr("Quran Radio — Sharjah (UAE)"), url: "https://l3.itworkscdn.net/smcquranlive/quranradiolive/icecast.audio" }
    ]

    // ? These streams don't provide any per-track title metadata (it's
    // ? continuous recitation, not songs) - show the station's own name
    // ? instead of a bare "Unknown" once one has been picked
    property int currentStationIndex: -1
    fallbackTitle: currentStationIndex >= 0 ? stations[currentStationIndex].name : qsTr("No station selected")

    // ? Radio always controls the dedicated radio player, and the built-in
    // ? station list only needs to be handed to the backend once
    Component.onCompleted: {
        MediaController.setMediaType(MediaController.Radio)
        MediaController.setRadioStations(radioPage.stations.map(function(station) { return station.url }))
    }

    onFolderRequested: stationPopup.open()

    Popup {
        id: stationPopup
        modal: true
        focus: true
        anchors.centerIn: parent
        width: radioPage.width * 0.5
        height: radioPage.height * 0.55
        padding: 0

        background: Rectangle {
            color: "#0a1a24"
            radius: 12
            border.color: radioPage.accentColor
            border.width: 2
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: radioPage.scaleUnit * 0.03
            spacing: radioPage.scaleUnit * 0.02

            Text {
                text: qsTr("Choose a Radio Station")
                font.pixelSize: radioPage.scaleUnit * 0.032
                font.bold: true
                color: "white"
            }

            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: radioPage.scaleUnit * 0.012
                model: radioPage.stations

                delegate: Rectangle {
                    width: ListView.view.width
                    height: radioPage.scaleUnit * 0.075
                    radius: 8
                    color: stationMouseArea.containsMouse ? radioPage.accentColor : Qt.rgba(1, 1, 1, 0.06)

                    Behavior on color { ColorAnimation { duration: 120 } }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: radioPage.scaleUnit * 0.02
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.name
                        color: "white"
                        font.pixelSize: radioPage.scaleUnit * 0.022
                    }

                    MouseArea {
                        id: stationMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            MediaController.playAt(index)
                            radioPage.currentStationIndex = index
                            stationPopup.close()
                        }
                    }
                }
            }
        }
    }
}
