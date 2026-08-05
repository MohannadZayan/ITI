import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: loginPage

    function goToDashboard() {
        StackView.view.push ("DashboardPage.qml")
    }

    property bool loggingIn: false

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20



        Image {
            source: "qrc:/qt/qml/Smart_Home/Images/logo.png"

            width: 120
            height: 120

            fillMode: Image.PreserveAspectFit
            Layout.alignment: Qt.AlignHCenter
        }


        Label {
            text: "Smart Home Login"
            font.pixelSize: 35
            Layout.alignment: Qt.AlignHCenter
        }

        TextField {
            id: usernameField
            placeholderText: "Username"
            Layout.preferredWidth: 350
            Layout.preferredHeight: 45
            Layout.alignment: Qt.AlignHCenter
        }

        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
            Layout.preferredWidth: 350
            Layout.preferredHeight: 45
            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            id: errorLabel
            text: "Please enter username and password."
            color: "red"
            visible: false
            Layout.alignment: Qt.AlignHCenter
        }

        BusyIndicator {
            running: loginPage.loggingIn
            visible: loginPage.loggingIn
            Layout.alignment: Qt.AlignHCenter
        }

        Button {
            text: "Login"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 50
            Layout.preferredWidth: 200

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