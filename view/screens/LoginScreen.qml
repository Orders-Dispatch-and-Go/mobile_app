import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import org.kde.kirigami as Kirigami

Kirigami.Page {
    id: root

    property bool loginClicked: false

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Kirigami.Units.smallSpacing
        anchors.topMargin: Kirigami.Units.largeSpacing
        Layout.fillHeight: true
        spacing: Kirigami.Units.largeSpacing
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
        BusyIndicator {
            visible: root.loginClicked
            Layout.fillWidth: true
        }
        Button {
            text: "Login"
            visible: !root.loginClicked
            Layout.fillWidth: true
            onClicked: {
                if (emailField.ok && passwordField.text.length > 0) {
                    root.loginClicked = true;
                    backend.login(emailField.text, passwordField.text);
                }
            }
        }
    }

    Kirigami.PromptDialog {
        id: errorDialog

        width: parent.width * 0.8
        height: parent.height * 0.8

        title: qsTr("Error")
        subtitle: qsTr("Invalid login")
        standardButtons: Dialog.Ok
    }

    Connections {
        target: backend

        function onUserLoggedId() {
            root.loginClicked = false;
        }

        function onUserLoginFailed() {
            root.loginClicked = false;
            errorDialog.open();
        }
    }
}
