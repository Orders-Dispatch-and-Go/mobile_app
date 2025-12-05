import QtQuick 2.15
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

Item {
    id: root
    height: 100

    property int radius: 10

    property var pointA: {
        "lat": 54,
        "lon": 37
    }       // Первая точка линии
    property var pointB: {
        "lat": 60,
        "lon": 40
    }       // Вторая точка линии
    property var existingStart: {
        "lat": 54,
        "lon": 37
    } // Начало существующей линии
    property var existingEnd: {
        "lat": 30,
        "lon": 30
    }   // Конец существующей линии

    property bool nearStart: root.near(existingStart, pointA)
    property bool nearFinish: root.near(existingEnd, pointB)

    property var usualColor: "#FAAD14"
    property var activeColor: "#ADFA14"

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            const colorA = root.nearStart ? root.activeColor : root.usualColor;
            const colorB = root.nearFinish ? root.activeColor : root.usualColor;
            const x1 = root.radius + 2 * Kirigami.Units.largeSpacing;
            const x2 = width - root.radius - 2 * Kirigami.Units.largeSpacing;
            const y = height / 2 + 2 * root.radius;

            ctx.beginPath();
            console.log(colorA, colorB);
            const gradient = ctx.createLinearGradient(x1, y, x2, y);
            gradient.addColorStop(0, colorA);
            gradient.addColorStop(1, colorB);
            ctx.strokeStyle = gradient;
            ctx.lineWidth = root.radius / 2;
            ctx.moveTo(x1, y);
            ctx.lineTo(x2, y);
            ctx.stroke();
            ctx.beginPath();
            ctx.moveTo(x1, y);
            ctx.arc(x1, y, root.radius, 0, Math.PI * 2);
            ctx.fillStyle = colorA;
            ctx.fill();
            ctx.beginPath();
            ctx.moveTo(x2, y);
            ctx.arc(x2, y, root.radius, 0, Math.PI * 2);
            ctx.fillStyle = colorB;
            ctx.fill();
        }
    }
    Component.onCompleted: canvas.requestPaint()

    function dist(a, b) {
        return Math.sqrt(Math.pow(a.lat - b.lat, 2) + Math.pow(a.lon - b.lon, 2));
    }
    function near(a, b) {
        return dist(a, b) < 10;
    }
}
