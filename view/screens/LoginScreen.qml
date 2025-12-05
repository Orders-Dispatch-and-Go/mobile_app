import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import org.kde.kirigami as Kirigami

Kirigami.Page {
    id: root
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        anchors.topMargin: 20
        Layout.fillHeight: true
        spacing: 30
        EmailField {
            id: emailField
            text: "test@gruzowiki.ru"
            Layout.fillWidth: true
        }
        PasswordField {
            id: passwordField
            Layout.fillWidth: true
        }
        Rectangle {
            color: "transparent"
            Layout.fillHeight: true
        }
        Button {
            text: "Login"
            Layout.fillWidth: true
            onClicked: {
                if (emailField.ok && passwordField.text.length > 0) {
                    backend.login(emailField.text, passwordField.text);
                }
            }
        }
    }
}
