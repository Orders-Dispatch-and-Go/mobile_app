import QtQuick 2.15
import QtQuick.Controls 2.15

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

Item {
    id: root

    property alias text: passwordField.text

    property bool ok: validLength && validDigit && validLetter
    property bool validLength: false
    property bool validDigit: false
    property bool validLetter: false

    property int minLength: 8

    RowLayout {
        id: row
        spacing: 6
        width: parent.width

        TextField {
            id: passwordField
            Layout.fillWidth: true
            placeholderText: "Пароль"
            echoMode: isVisible ? TextInput.Normal : TextInput.Password

            property bool isVisible: false

            onEditingFinished: text = text.trim()
            onTextChanged: {
                validLength = text.length >= minLength;
                validDigit = /[0-9]/.test(text);
                validLetter = /[a-zA-Z]/.test(text);
            }
        }

        ToolButton {
            icon.name: passwordField.isVisible ? "visibility" : "visibility-off"
            onClicked: passwordField.isVisible = !passwordField.isVisible
        }
    }
    Text {
        id: errorText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: row.bottom
        anchors.topMargin: 15
        color: (errorText.text === "" || passwordField.text === "") ? "transparent" : theme.error

        text: {
            if (passwordField.text === "")
                return "";
            if (!root.validLength)
                return "Минимум " + root.minLength + " символов";
            if (!root.validDigit)
                return "Нужна хотя бы одна цифра";
            if (!root.validLetter)
                return "Нужна хотя бы одна буква";
            return "";
        }
    }
}
