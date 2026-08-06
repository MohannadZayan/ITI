import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Calculator

ApplicationWindow {
    id: window
    width: 320
    height: 480
    minimumWidth: 280
    minimumHeight: 420
    visible: true
    title: qsTr("Calculator")
    color: "#101010"

    // one reusable button style, so we don't repeat the same background/animation code 17 times
    component CalcButton: Button {
        id: control
        property color baseColor: "#2a2a2a"

        hoverEnabled: true
        Layout.fillWidth: true
        Layout.fillHeight: true

        // grows slightly on hover, shrinks slightly while pressed, animated smoothly
        scale: control.pressed ? 0.95 : (control.hovered ? 1.05 : 1.0)
        Behavior on scale {
            NumberAnimation { duration: 100; easing.type: Easing.OutQuad }
        }

        background: Rectangle {
            radius: 14
            color: control.hovered ? Qt.lighter(control.baseColor, 1.3) : control.baseColor
            Behavior on color {
                ColorAnimation { duration: 150 }
            }
        }

        contentItem: Text {
            text: control.text
            color: "white"
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Calculator {
        id: calc
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            radius: 14
            color: "#181818"

            Label {
                id: display
                text: calc.display
                anchors.fill: parent
                anchors.margins: 12
                color: "#e0e0e0"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 32
                font.bold: true
            }
        }

        GridLayout {
            id: buttonGrid
            columns: 4
            rowSpacing: 8
            columnSpacing: 8
            Layout.fillWidth: true
            Layout.fillHeight: true

            CalcButton { text: "sin"; onClicked: calc.calculateTrig("sin") }
            CalcButton { text: "cos"; onClicked: calc.calculateTrig("cos") }
            CalcButton { text: "tan"; onClicked: calc.calculateTrig("tan") }
            CalcButton { text: "^";   onClicked: calc.inputOperator("^") }

            CalcButton { text: "C";   onClicked: calc.clear() }
            CalcButton { text: "7";   onClicked: calc.inputDigit(7) }
            CalcButton { text: "8";   onClicked: calc.inputDigit(8) }
            CalcButton { text: "9";   onClicked: calc.inputDigit(9) }

            CalcButton { text: "/";   onClicked: calc.inputOperator("/") }
            CalcButton { text: "4";   onClicked: calc.inputDigit(4) }
            CalcButton { text: "5";   onClicked: calc.inputDigit(5) }
            CalcButton { text: "6";   onClicked: calc.inputDigit(6) }

            CalcButton { text: "*";   onClicked: calc.inputOperator("*") }
            CalcButton { text: "1";   onClicked: calc.inputDigit(1) }
            CalcButton { text: "2";   onClicked: calc.inputDigit(2) }
            CalcButton { text: "3";   onClicked: calc.inputDigit(3) }

            CalcButton { text: "-";   onClicked: calc.inputOperator("-") }
            CalcButton { text: "0";   onClicked: calc.inputDigit(0) }
            CalcButton { text: ".";   onClicked: calc.inputDecimal() }
            CalcButton { text: "+";   onClicked: calc.inputOperator("+") }

            CalcButton {
                text: "="
                baseColor: "#3b82f6"
                Layout.columnSpan: 4
                onClicked: calc.equals()
            }
        }
    }
}
