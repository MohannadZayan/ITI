import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtMultimedia

import Graduation_Project

// ? Reusable layout for any "browse a folder of media" page - used by the
// ? Local, USB, and Radio pages, which differ only in title, whether the
// ? audio/video toggle applies, and what the folder icon opens.
Item {
    id: root

    // ? Everything below is sized relative to this instead of fixed pixel
    // ? values, so the page scales up properly on a large/fullscreen window
    // ? instead of staying a small cluster in the middle of empty space
    readonly property real scaleUnit: Math.min(width, height)

    // ? Matches the accent color already baked into the playback icon assets
    readonly property color accentColor: "#20c1e3"

    property string pageTitle: qsTr("Media")

    // ? Radio has no audio/video distinction and no seekable duration -
    // ? these let RadioPage.qml reuse this same layout with those bits adjusted
    property bool showModeToggle: true
    property bool isLive: false

    // ? Shown in place of the title when the player reports no metadata -
    // ? RadioPage overrides this with the selected station's name, since a
    // ? live recitation stream has no per-track title to show otherwise
    property string fallbackTitle: qsTr("Unknown")

    // ? Emitted when the folder icon is clicked - LocalPage/UsbPage open a
    // ? folder dialog, RadioPage opens a station picker instead
    signal folderRequested()

    // ? mm:ss formatting for the elapsed/remaining time labels
    function formatTime(ms) {
        if (!ms || ms <= 0)
            return "0:00"

        var totalSeconds = Math.floor(ms / 1000)
        var minutes = Math.floor(totalSeconds / 60)
        var seconds = totalSeconds % 60

        return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
    }

    // ? The background zoom animation can overflow its own bounds - clip so it never spills past the window
    clip: true

    // ? Animated background - declared first, so everything else draws on top of it
    AnimatedBackground {
        anchors.fill: parent
    }

    // ? Top bar - back navigation and page title
    RowLayout {
        id: topBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: root.scaleUnit * 0.02
        spacing: root.scaleUnit * 0.02

        AppButton {
            id: homeButton
            text: qsTr("← Home")
            Layout.preferredWidth: root.scaleUnit * 0.14
            Layout.preferredHeight: root.scaleUnit * 0.055
            onClicked: root.StackView.view.pop()
        }

        Text {
            text: root.pageTitle
            font.pixelSize: root.scaleUnit * 0.04
            font.bold: true
            color: "white"
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
        }

        // ? Balances the back button so the title stays visually centered
        Item {
            Layout.preferredWidth: homeButton.Layout.preferredWidth
        }
    }

    ColumnLayout {
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 24
        spacing: root.scaleUnit * 0.05

        Item { Layout.fillHeight: true; Layout.preferredHeight: 1 }

        // ? Artwork and metadata side by side, centered as one unit across the full page width
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: root.scaleUnit * 0.08

            // ? Shows the video picture when playing video; falls back to the
            // ? placeholder artwork for audio/radio, where there's nothing to
            // ? render. Grows much larger during video, since the metadata
            // ? panel next to it hides and isn't competing for space.
            Item {
                readonly property bool showingVideo: MediaController.mediaType === MediaController.Video

                Layout.preferredWidth: showingVideo ? root.scaleUnit * 0.85 : root.scaleUnit * 0.32
                Layout.preferredHeight: showingVideo ? root.scaleUnit * 0.55 : root.scaleUnit * 0.32

                Behavior on Layout.preferredWidth { NumberAnimation { duration: 200; easing.type: Easing.OutQuad } }
                Behavior on Layout.preferredHeight { NumberAnimation { duration: 200; easing.type: Easing.OutQuad } }

                VideoOutput {
                    id: videoOutput
                    anchors.fill: parent
                    visible: MediaController.mediaType === MediaController.Video
                    fillMode: VideoOutput.PreserveAspectFit

                    Component.onCompleted: MediaController.setVideoOutput(videoOutput)
                }

                Image {
                    anchors.fill: parent
                    source: "assets/images/Icon.png"
                    fillMode: Image.PreserveAspectFit
                    visible: MediaController.mediaType !== MediaController.Video
                }
            }

            // ? Not relevant while a video is on screen - hidden so the video above can take over this space
            ColumnLayout {
                visible: MediaController.mediaType !== MediaController.Video
                spacing: root.scaleUnit * 0.02

                Text {
                    text: qsTr("Now Playing")
                    font.pixelSize: root.scaleUnit * 0.045
                    font.bold: true
                    color: "white"
                }

                Text {
                    text: qsTr("Title: ") + (MediaController.trackTitle.length > 0 ? MediaController.trackTitle : root.fallbackTitle)
                    color: "white"
                    font.pixelSize: root.scaleUnit * 0.032
                }
                Text {
                    text: qsTr("Artist: ") + (MediaController.trackArtist.length > 0 ? MediaController.trackArtist : "—")
                    color: "white"
                    font.pixelSize: root.scaleUnit * 0.032
                }
                Text {
                    text: qsTr("Genre: ") + (MediaController.trackGenre.length > 0 ? MediaController.trackGenre : "—")
                    color: "white"
                    font.pixelSize: root.scaleUnit * 0.032
                }
            }
        }

        // ? Audio / Video mode toggle
        RowLayout {
            visible: root.showModeToggle
            Layout.alignment: Qt.AlignHCenter
            spacing: root.scaleUnit * 0.02

            AppButton {
                text: qsTr("Audio")
                selected: MediaController.mediaType === MediaController.Audio
                Layout.preferredWidth: root.scaleUnit * 0.18
                Layout.preferredHeight: root.scaleUnit * 0.065
                onClicked: MediaController.setMediaType(MediaController.Audio)
            }

            AppButton {
                text: qsTr("Video")
                selected: MediaController.mediaType === MediaController.Video
                Layout.preferredWidth: root.scaleUnit * 0.18
                Layout.preferredHeight: root.scaleUnit * 0.065
                onClicked: MediaController.setMediaType(MediaController.Video)
            }
        }

        // ? Playback progress - elapsed time, seek bar, remaining time
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: root.scaleUnit * 0.9
            spacing: root.scaleUnit * 0.02

            Text {
                text: root.formatTime(MediaController.position)
                color: "white"
                font.pixelSize: root.scaleUnit * 0.026
            }

            AppSlider {
                id: progressSlider
                Layout.fillWidth: true
                from: 0
                to: Math.max(MediaController.duration, 1)
                value: MediaController.position
                accentColor: root.accentColor
                trackHeight: root.scaleUnit * 0.008
                handleSize: root.scaleUnit * 0.02

                // ? A live stream can't be seeked - disable (not just hide) the
                // ? slider so it's visibly grayed out and doesn't respond to input
                enabled: !root.isLive

                onMoved: MediaController.seek(value)
            }

            // ? A fixed duration doesn't apply to a live stream - show a LIVE badge instead
            Text {
                visible: !root.isLive
                text: "-" + root.formatTime(Math.max(MediaController.duration - MediaController.position, 0))
                color: "white"
                font.pixelSize: root.scaleUnit * 0.026
            }

            RowLayout {
                visible: root.isLive
                spacing: root.scaleUnit * 0.01

                Rectangle {
                    width: root.scaleUnit * 0.018
                    height: width
                    radius: width / 2
                    color: "#2979ff"
                }

                Text {
                    text: qsTr("LIVE")
                    color: "#2979ff"
                    font.bold: true
                    font.pixelSize: root.scaleUnit * 0.026
                }
            }
        }

        // ? All icon controls in a single row, folder icon first
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: root.scaleUnit * 0.06

            IconButton {
                source: "assets/images/folder.jpg"
                Layout.preferredWidth: root.scaleUnit * 0.08
                Layout.preferredHeight: root.scaleUnit * 0.08
                onClicked: root.folderRequested()
            }

            IconButton {
                source: "assets/images/Back.png"
                Layout.preferredWidth: root.scaleUnit * 0.065
                Layout.preferredHeight: root.scaleUnit * 0.065
                onClicked: MediaController.previous()
            }

            IconButton {
                source: MediaController.playing ? "assets/images/Pause.png" : "assets/images/Play.png"
                Layout.preferredWidth: root.scaleUnit * 0.085
                Layout.preferredHeight: root.scaleUnit * 0.085
                onClicked: MediaController.playing ? MediaController.pause() : MediaController.play()
            }

            IconButton {
                source: "assets/images/Stop.png"
                Layout.preferredWidth: root.scaleUnit * 0.065
                Layout.preferredHeight: root.scaleUnit * 0.065
                onClicked: MediaController.stop()
            }

            IconButton {
                source: "assets/images/Next.png"
                Layout.preferredWidth: root.scaleUnit * 0.065
                Layout.preferredHeight: root.scaleUnit * 0.065
                onClicked: MediaController.next()
            }

            IconButton {
                source: {
                    if (MediaController.muted)
                        return "assets/images/Mute.png"
                    if (MediaController.volume < 33)
                        return "assets/images/SmallVolume.png"
                    if (MediaController.volume < 66)
                        return "assets/images/MidVolume.png"
                    return "assets/images/FullVolume.png"
                }
                Layout.preferredWidth: root.scaleUnit * 0.055
                Layout.preferredHeight: root.scaleUnit * 0.055
                onClicked: MediaController.setMuted(!MediaController.muted)
            }

            AppSlider {
                id: volumeSlider
                Layout.preferredWidth: root.scaleUnit * 0.15
                from: 0
                to: 100
                value: MediaController.volume
                enabled: !MediaController.muted
                accentColor: root.accentColor
                trackHeight: root.scaleUnit * 0.006
                handleSize: root.scaleUnit * 0.016

                onMoved: MediaController.setVolume(value)
            }
        }

        Item { Layout.fillHeight: true; Layout.preferredHeight: 1 }
    }
}
