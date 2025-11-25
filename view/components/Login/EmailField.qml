import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

TextField {
    id: textField

    property var allowedDomains: ["gruzowiki.ru", "driver.gruzowiki.ru"]

    property bool ok: emailFormatValid && emailDomainValid

    // Флаг валидности
    property bool emailFormatValid: false
    property bool emailDomainValid: false

    placeholderText: "name.surname@gruzowiki.ru"
    font.pointSize: theme.font_size
    echoMode: TextInput.Normal
    inputMethodHints: Qt.ImhEmailCharactersOnly
    selectByMouse: true

    // Обрезаем пробелы и приводим к нижнему регистру при потере фокуса
    onEditingFinished: text = text.trim().toLowerCase()

    onTextChanged: {
        // базовая проверка формата e-mail
        // регулярное выражение рассчитано на стандартный формат локальной@домен
        var re = /^[a-zA-Z0-9._%+\-]+@[a-zA-Z0-9.\-]+\.[a-zA-Z]{2,}$/;
        emailFormatValid = re.test(text);

        // проверка корпоративного домена — допускает поддомены
        if (emailFormatValid) {
            emailDomainValid = false;
            for (var i = 0; i < allowedDomains.length; ++i) {
                var d = allowedDomains[i].toLowerCase();
                if (text.endsWith("@" + d) || text.endsWith("." + d)) {
                    // строгое совпадение с доменом (например user@company.com)
                    // или поддомен (user@dept.company.com) — при желании убрать вторую проверку
                    emailDomainValid = text.endsWith("@" + d) || text.indexOf("@" + d + ".") !== -1;
                }
            }
        } else {
            emailDomainValid = false;
        }
    }
    Text {
        id: errorText
        text: emailFormatValid ? (emailDomainValid ? "" : "Invalid domain") : "Invalid email format"
        color: (errorText.text === "" || textField.text === "") ? "transparent" : theme.error
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
        anchors.topMargin: 2
    }
}
