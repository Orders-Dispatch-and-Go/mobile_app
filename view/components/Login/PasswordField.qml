import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: passwordField

    property int minLength: 8
    property bool needDigit: true
    property bool needLetter: true

    property bool validLength: false
    property bool validDigit: false
    property bool validLetter: false
    property bool ok: validLength && validDigit && validLetter

    placeholderText: "Введите пароль"
    font.pointSize: theme.font_size
    echoMode: showPassword ? TextInput.Normal : TextInput.Password
    inputMethodHints: Qt.ImhHiddenText | Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase
    selectByMouse: true

    property bool showPassword: false

    onEditingFinished: text = text.trim()

    onTextChanged: {
        validLength = text.length >= minLength;
        validDigit = needDigit ? /[0-9]/.test(text) : true;
        validLetter = needLetter ? /[a-zA-Z]/.test(text) : true;
    }

    // Кнопка с изображением
    Rectangle {
        id: showBtn
        width: parent.height
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top
        color: theme.paper
        radius: 4
        z: 100

        Image {
            fillMode: Image.PreserveAspectFit
            source: showPassword ? "qrc:/pass_shown" : "qrc:/pass_hidden"
            anchors.centerIn: parent
            anchors.fill: parent
            anchors.margins: 5
        }
        MouseArea {
            anchors.fill: parent
            onClicked: mouse => {
                passwordField.showPassword = !passwordField.showPassword;
                mouse.accepted = false;
            }
        }
    }

    // Отступ, чтобы текст не перекрывался иконкой
    rightPadding: showBtn.width + 10

    Text {
        id: errorText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
        anchors.topMargin: 2
        color: (errorText.text === "" || passwordField.text === "") ? "transparent" : theme.error

        text: {
            if (passwordField.text === "")
                return "";
            if (!validLength)
                return "Минимум " + passwordField.minLength + " символов";
            if (!validDigit)
                return "Нужна хотя бы одна цифра";
            if (!validLetter)
                return "Нужна хотя бы одна буква";
            return "";
        }
    }
}
