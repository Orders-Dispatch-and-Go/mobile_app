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
    }
    property var pointB: {
        "lat": 60,
        "lon": 40
    }
    property var existingStart: {
        "lat": 54,
        "lon": 37
    }
    property var existingEnd: {
        "lat": 30,
        "lon": 30
    }

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

            // Линия с градиентом
            ctx.beginPath();
            const gradient = ctx.createLinearGradient(x1, y, x2, y);
            gradient.addColorStop(0, colorA);
            gradient.addColorStop(1, colorB);
            ctx.strokeStyle = gradient;
            ctx.lineWidth = root.radius / 2;
            ctx.moveTo(x1, y);
            ctx.lineTo(x2, y);
            ctx.stroke();

            // Круги на концах линии
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

            // Текст над точками
            ctx.fillStyle = Kirigami.Theme.textColor;
            ctx.font = "12px sans-serif";
            ctx.textAlign = "center";
            ctx.textBaseline = "bottom";
            ctx.fillText(root.pointA.lat + ", " + root.pointA.lon, x1, y - root.radius - 4);
            ctx.fillText(root.pointB.lat + ", " + root.pointB.lon, x2, y - root.radius - 4);
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
