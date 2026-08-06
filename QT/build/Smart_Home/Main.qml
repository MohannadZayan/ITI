pragma Translator: translationController.currentLanguage
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    id: window

    width: 1280
    height: 800
    minimumWidth: 960
    minimumHeight: 640

    visible: true
    title: qsTr("Smart Home Dashboard")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: LoginPage {}
    }
}
