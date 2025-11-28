import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    palette.buttonText: theme.background
    height: 40
    highlighted: true

    background: Rectangle {
        id: bg
        color: theme.primary
        radius: 5

        // Область для наведения и нажатия
        MouseArea {
            id: area
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            hoverEnabled: true
        }

        states: [
            State {
                name: "hovered"
                when: area.containsMouse && !area.pressed
                PropertyChanges {
                    target: bg
                    color: theme.primary_light
                }
            },
            State {
                name: "pressed"
                when: area.pressed
                PropertyChanges {
                    target: bg
                    color: theme.primary_light
                }
            }
        ]

        // Плавная анимация смены цвета
        Behavior on color {
            ColorAnimation {
                duration: 120
            }
        }
    }
}
