import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Dialogs

Window {
    id: root
    width: 800
    height: 480
    visible: true
    title: qsTr("Audio Player")
    color : "#0f172a"
    Material.accent : "cyan"

    //size constrainsts:
    readonly property real iconSize: root.width*0.2
    readonly property real buttonSize: root.width *0.06
    readonly property real muteIconSize: root.width *0.035
    readonly property real spacingVolume: root.width *0.05
    readonly property real spacingMediaBtns: root.width*0.05

    //Big container for all UI elements
    /*
      * App Title
      * App icon +audio metadata
      * duration + audio slider + remaining
      *audio src selection + media contreols +mute + volume

      **/

    ColumnLayout {
        id: bigContainer
        anchors.fill: parent
        Text {
            id: appTitle
            text: qsTr ("Media Player")
            font.bold : true
            font.pixelSize: 30
            color: "white"
            Layout.alignment:  Qt.AlignHCenter
            Layout.topMargin: 15
        }

        // App icon + audio metadata
        RowLayout {
            id: app_iconMetaData
            Layout.alignment: Qt.AlignHCenter
            // icon image:
            Image {
                id: app_Icon
                source: "qrc:/new/prefix1/images/icon.jpg"
                Layout.preferredWidth: root.iconSize
                Layout.preferredHeight: Layout.preferredWidth
            }

            ColumnLayout {
                id: audioMetaData
                Text {
                    id: audioTitle
                    text: qsTr ("Surah Yassin")
                    font.bold: true
                    color: "white"
                    font.pixelSize: 20
                    wrapMode: Text.Wrap

                }
                Text {
                    id: audioAuthorId
                    text: qsTr ("El-Hussary")
                    font.bold: false
                    font.pixelSize: 18
                    color: "white"
                    wrapMode: Text.Wrap

                }
                Text {
                    id: audioTypeId
                    text: qsTr ("El-Hussary")
                    font.bold: false
                    font.pixelSize: 18
                    color: "white"
                    wrapMode: Text.Wrap

                }
            }

        }

        //Elapsed time + audio slider + remaining
        RowLayout {
            id: durationAudioSlider
            Layout.rightMargin: 20
            Layout.leftMargin: 20
            Text {
                id: elapsedTimeId
                text: qsTr ("00:00")
                font.pixelSize: 15
                color: "white"

            }
            Slider {
                id: audioProgressId
                enabled: true
                Layout.fillWidth: true
                from : 0
                to: 100 // durationAudioSlider
                value: 0
                onMoved: {

                }
            }

            Text {
                id: remainingTimeId
                text: qsTr ("00:00")
                font.pixelSize: 15
                color: "white"

            }
        }

        //audio src+ media buttons + volume

        RowLayout {
            id: controlBtnsId
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            spacing: root.spacingMediaBtns

            FolderDialog {
                id:folderDialogId
                onAccepted:  {

                }
            }

            //audio sources
            Image {
                id:folderSelector
                Layout.preferredWidth: root.buttonSize
                Layout.preferredHeight: Layout.preferredWidth
                source: ""
                Layout.leftMargin: 20
                MouseArea {
                    anchors.fill: parent
                    onClicked : {
                        folderDialogId.open()
                    }
                }
            }
            Image {
                            id: radioSrcId
                            Layout.preferredWidth: root.buttonSize
                            Layout.preferredHeight: Layout.preferredWidth
                            source: ""
                            MouseArea {
                                anchors.fill: parent
                                onClicked : {

                                }
                            }
                        }

            //spacer
            Item {
                id: spacer1
                implicitWidth: root.spacing
            }
            Image {
                id: prevBtnId
                source: ""
                Layout.preferredWidth: root.buttonSize
                Layout.preferredHeight: Layout.preferredWidth
                MouseArea {
                    id: prevBtn
                    anchors.fill: parent
                    onClicked : {

                    }
                    }
            }
            Image {
                id: playPauseBtnId
                source: ""
                Layout.preferredWidth: root.buttonSize
                Layout.preferredHeight: Layout.preferredWidth
                MouseArea {
                    id: playPauseBtn
                    anchors.fill: parent
                    onClicked : {

                    }
                    }
            }
            Image {
                id: stopButtonId
                source: ""
                Layout.preferredWidth: root.buttonSize
                Layout.preferredHeight: Layout.preferredWidth
                MouseArea {
                    id: stopButton
                    anchors.fill: parent
                    onClicked : {

                    }
                    }
            }

            Image {
                id: nextBtnId
                source: ""
                Layout.preferredWidth: root.buttonSize
                Layout.preferredHeight: Layout.preferredWidth
                MouseArea {
                    id: nextBtn
                    anchors.fill: parent
                    onClicked : {

                    }
                    }
            }

            Item {
                id: spacer2
                implicitWidth: root.spacing
            }

            RowLayout {
                id: volumeControlId
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Image {
                    id: muteBtnId
                    source: ""
                    Layout.preferredWidth: root.muteIconSize
                    Layout.preferredHeight: Layout.preferredWidth
                    MouseArea {
                        id: muteBtn
                        anchors.fill: parent
                        onClicked : {

                        }
                    }
                }

                Slider {
                    id:volumeBar
                    Layout.fillWidth: true
                    Layout.minimumWidth: 100
                    Layout.maximumWidth: 400

                    from: 0
                    to: 1
                    value: 0.5
                    onMoved: {

                    }

                }

                Text {
                    id: volumeLevelId
                    text: qsTr ("50%")
                    font.pixelSize: 14
                    color: "white"
                }
            }
        }

    }


}
