import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: loginPage

    property bool loggingIn: false

    function goToDashboard() {
        StackView.view.push("DashboardPage.qml")
    }

    background: Item {
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "#161827"
        }

        Image {
            anchors.fill: parent
            source: "qrc:/qt/qml/Smart_Home/Images/logo.png"
            fillMode: Image.PreserveAspectCrop
            opacity: 0.14
        }

        Rectangle {
            anchors.fill: parent
            color: "#161827"
            opacity: 0.55
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        width: Math.min(loginPage.width - 48, 460)
        spacing: 18

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 470
            radius: 22
            color: "#2A304B"
            border.width: 1
            border.color: "#414A6B"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 36
                spacing: 14

                Label {
                    text: "Welcome back"
                    color: "white"
                    font.pixelSize: 30
                    font.bold: true
                }

                Label {
                    text: "Sign in to manage your smart home."
                    color: "#AAB2CC"
                    font.pixelSize: 15
                    Layout.bottomMargin: 12
                }

                Label {
                    text: "Username"
                    color: "#D7DCF0"
                    font.pixelSize: 14
                    font.bold: true
                }

                TextField {
                    id: usernameField
                    placeholderText: "Enter your username"
                    placeholderTextColor: "#7F89A8"
                    color: "white"
                    font.pixelSize: 16
                    Layout.fillWidth: true
                    Layout.preferredHeight: 52

                    background: Rectangle {
                        radius: 12
                        color: "#1D2237"
                        border.width: usernameField.activeFocus ? 2 : 1
                        border.color: usernameField.activeFocus ? "#47B5FF" : "#4A5373"

                        Behavior on border.color { ColorAnimation { duration: 150 } }
                    }
                }

                Label {
                    text: "Password"
                    color: "#D7DCF0"
                    font.pixelSize: 14
                    font.bold: true
                    Layout.topMargin: 6
                }

                TextField {
                    id: passwordField
                    placeholderText: "Enter your password"
                    placeholderTextColor: "#7F89A8"
                    echoMode: TextInput.Password
                    color: "white"
                    font.pixelSize: 16
                    rightPadding: 62
                    Layout.fillWidth: true
                    Layout.preferredHeight: 52

                    background: Rectangle {
                        radius: 12
                        color: "#1D2237"
                        border.width: passwordField.activeFocus ? 2 : 1
                        border.color: passwordField.activeFocus ? "#47B5FF" : "#4A5373"

                        Behavior on border.color { ColorAnimation { duration: 150 } }
                    }

                    Button {
                        anchors.right: parent.right
                        anchors.rightMargin: 8
                        anchors.verticalCenter: parent.verticalCenter
                        text: passwordField.echoMode === TextInput.Password ? "Show" : "Hide"

                        onClicked: {
                            passwordField.echoMode = passwordField.echoMode === TextInput.Password
                                                     ? TextInput.Normal
                                                     : TextInput.Password
                        }
                    }
                }

                Label {
                    id: errorLabel
                    text: "Please enter both a username and password."
                    color: "#FF8B9B"
                    font.pixelSize: 13
                    visible: false
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                }

                Item {
                    Layout.fillHeight: true
                }

                Button {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 54
                    enabled: !loginPage.loggingIn

                    background: Rectangle {
                        radius: 14
                        color: parent.down ? "#268FD0" : "#47B5FF"

                        Behavior on color { ColorAnimation { duration: 120 } }
                    }

                    contentItem: RowLayout {
                        anchors.centerIn: parent
                        spacing: 10

                        BusyIndicator {
                            running: loginPage.loggingIn
                            visible: loginPage.loggingIn
                            Layout.preferredWidth: visible ? 20 : 0
                            Layout.preferredHeight: visible ? 20 : 0
                        }

                        Label {
                            text: loginPage.loggingIn ? "Signing in..." : "Sign in"
                            color: "#10223A"
                            font.pixelSize: 16
                            font.bold: true
                        }
                    }

                    onClicked: {
                        if (usernameField.text !== "" && passwordField.text !== "") {
                            errorLabel.visible = false
                            loginPage.loggingIn = true
                            loginTimer.start()
                        } else {
                            errorLabel.visible = true
                        }
                    }
                }
            }
        }
    }

    Timer {
        id: loginTimer
        interval: 2000
        repeat: false

        onTriggered: {
            loginPage.loggingIn = false
            console.log("Login Successful")
            loginPage.goToDashboard()
        }
    }
}
