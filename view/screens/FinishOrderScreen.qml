import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.20 as Kirigami

Kirigami.Page {
    id: root
    title: qsTr("Finish order #") + backend.orderToFinish

    property int pinLength: 8
    property string pin: ""

    property var shapes: ["●", "▲", "◆", "★", "⬢", "⬣", "■"]

    ListModel {
        id: digitsModel
        ListElement {
            value: "0"
        }
        ListElement {
            value: "1"
        }
        ListElement {
            value: "2"
        }
        ListElement {
            value: "3"
        }
        ListElement {
            value: "4"
        }
        ListElement {
            value: "5"
        }
        ListElement {
            value: "6"
        }
        ListElement {
            value: "7"
        }
        ListElement {
            value: "8"
        }
        ListElement {
            value: "9"
        }
    }

    function shuffleDigits() {
        // Fisher–Yates с ListModel
        for (let i = digitsModel.count - 1; i > 0; i--) {
            let j = Math.floor(Math.random() * (i + 1));

            // swap values[i] <-> values[j]
            let vi = digitsModel.get(i).value;
            let vj = digitsModel.get(j).value;

            digitsModel.set(i, {
                value: vj
            });
            digitsModel.set(j, {
                value: vi
            });
        }
    }

    function maskedPin() {
        let r = "";

        for (let i = 0; i < pin.length; i++) {
            r += shapes[i % shapes.length];
        }
        const placeholder = "\u2015";
        for (let i = pin.length; i < pinLength; i++) {
            r += placeholder;
        }
        return r;
    }

    Component.onCompleted: shuffleDigits()

    signal pinAccepted(string value)

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        Label {
            text: qsTr("Введите PIN-код")
            font.pointSize: 18
            color: Kirigami.Theme.textColor
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            width: parent.width
            height: 60
            radius: 10
            border.width: 1

            Text {
                anchors.centerIn: parent
                color: Kirigami.Theme.textColor
                text: maskedPin()
                font.pointSize: 26
            }
        }

        GridLayout {
            id: keypad
            columns: 3
            rowSpacing: 10
            columnSpacing: 10
            Layout.alignment: Qt.AlignHCenter

            Repeater {
                model: digitsModel
                Button {
                    text: model.value
                    implicitWidth: 90
                    implicitHeight: 70
                    onClicked: {
                        if (pin.length < pinLength)
                            pin += text;
                    }
                }
            }

            Button {
                text: qsTr("Очистить")
                implicitWidth: 90
                implicitHeight: 70
                onClicked: pin = ""
            }

            Button {
                text: qsTr("OK")
                implicitWidth: 90
                implicitHeight: 70
                onClicked: {
                    pinAccepted(pin);
                    pin = "";
                    shuffleDigits();
                }
            }
        }
    }

    Connections {
        target: root
        onPinAccepted: {
            console.log("PIN accepted:", value);
        }
    }
}
