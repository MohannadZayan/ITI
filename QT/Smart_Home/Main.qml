import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


ApplicationWindow {
    id: window

    width: 640
    height: 480

    visible: true
    title: "Smart Home Dashboard"

    StackView {
        id: stackView

        anchors.fill: parent

        initialItem: LoginPage {} // Shows this as the first page
    }

}
