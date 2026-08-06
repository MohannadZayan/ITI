import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


ApplicationWindow {
    id: window

    // Start at a useful desktop size, while keeping the window resizable.
    width: 1280
    height: 800
    minimumWidth: 960
    minimumHeight: 640

    visible: true
    title: "Smart Home Dashboard"

    StackView {
        id: stackView

        anchors.fill: parent

        initialItem: LoginPage {} // Shows this as the first page
    }

}
