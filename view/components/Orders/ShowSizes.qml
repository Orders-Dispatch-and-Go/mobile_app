import QtQuick 2.15
import org.kde.kirigami as Kirigami

Item {
    id: root
    width: 140
    height: 140

    // свойства коробки (передавайте нужные числа)
    property real boxWidth: 160
    property real boxHeight: 100
    property real boxDepth: 60

    property real maximumSize: 100

    // стили
    property color strokeColor: "black"
    property color fillColor: "transparent"
    property color textColor: "black"
    property int strokeWidth: 2
    property int padding: 30

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: root.draw(canvas)

        // перерисовка при изменении свойств
        onWidthChanged: canvas.requestPaint()
        onHeightChanged: canvas.requestPaint()
    }

    // следим за изменениями свойств коробки и запрашиваем перерисовку
    onBoxWidthChanged: canvas.requestPaint()
    onBoxHeightChanged: canvas.requestPaint()
    onBoxDepthChanged: canvas.requestPaint()
    onStrokeColorChanged: canvas.requestPaint()
    onFillColorChanged: canvas.requestPaint()
    onTextColorChanged: canvas.requestPaint()
    onStrokeWidthChanged: canvas.requestPaint()
    function draw(canvas) {
        var ctx = canvas.getContext("2d");
        var dpr = canvas.devicePixelRatio || 1;

        ctx.reset();
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.save();
        ctx.scale(dpr, dpr);

        var w = canvas.width / dpr;
        var h = canvas.height / dpr;
        var pad = root.padding;

        /* ---------- 1. БАЗОВЫЕ РАЗМЕРЫ ---------- */
        var baseW = root.boxWidth;
        var baseH = root.boxHeight;
        var baseD = root.boxDepth;

        var depthX = baseD * 0.6;
        var depthY = -baseD * 0.35;

        /* ---------- BOUNDING BOX ---------- */
        var minX = Math.min(0, depthX);
        var maxX = Math.max(baseW, baseW + depthX);
        var minY = Math.min(0, depthY);
        var maxY = Math.max(baseH, baseH + depthY);

        var projW = maxX - minX;
        var projH = maxY - minY;

        /* ---------- ДОСТУПНАЯ ОБЛАСТЬ ---------- */
        var availW = w - pad * 3;
        var availH = h - pad * 3;

        /* ---------- МАСШТАБ ---------- */
        var scale = Math.min(availW / projW, availH / projH);

        /* ---------- ВИЗУАЛЬНЫЕ РАЗМЕРЫ ---------- */
        var visW = baseW * scale;
        var visH = baseH * scale;
        var offX = depthX * scale;
        var offY = depthY * scale;

        /* ---------- ЦЕНТРИРОВАНИЕ ---------- */
        var fx = (w - projW * scale) / 2 - minX * scale;
        var fy = (h - projH * scale) / 2 - minY * scale;

        var fx2 = fx + visW;
        var fy2 = fy + visH;

        var bx = fx + offX;
        var by = fy + offY;
        var bx2 = fx2 + offX;
        var by2 = fy2 + offY;

        /* ---------- КОРОБКА ---------- */
        ctx.lineWidth = root.strokeWidth;
        ctx.strokeStyle = root.strokeColor;
        ctx.fillStyle = root.fillColor;

        // задняя грань
        ctx.setLineDash([6, 6]);
        ctx.globalAlpha = 0.6;
        ctx.strokeRect(bx, by, visW, visH);

        // рёбра
        ctx.beginPath();
        ctx.moveTo(bx, by);
        ctx.lineTo(fx, fy);
        ctx.moveTo(bx2, by);
        ctx.lineTo(fx2, fy);
        ctx.moveTo(bx2, by2);
        ctx.lineTo(fx2, fy2);
        ctx.stroke();

        // передняя грань
        ctx.setLineDash([]);
        ctx.globalAlpha = 1.0;
        ctx.strokeRect(fx, fy, visW, visH);

        /* ---------- ТЕКСТ И ЛЕЙБЛЫ ---------- */

        var fontSize = 11;
        ctx.font = fontSize + "px sans-serif";
        ctx.textBaseline = "middle";
        ctx.textAlign = "center";

        function drawLabel(text, x, y, angle) {
            angle = angle || 0;

            ctx.save();
            ctx.translate(x, y);
            ctx.rotate(angle);

            var paddingX = 6;
            var paddingY = 4;
            var radius = 4;

            var metrics = ctx.measureText(text);
            var textW = metrics.width;
            var textH = fontSize;

            var lw = textW + paddingX * 2;
            var lh = textH + paddingY * 2;

            var rx = -lw / 2;
            var ry = -lh / 2;

            ctx.fillStyle = Kirigami.Theme.disabledTextColor;
            ctx.beginPath();
            ctx.moveTo(rx + radius, ry);
            ctx.lineTo(rx + lw - radius, ry);
            ctx.quadraticCurveTo(rx + lw, ry, rx + lw, ry + radius);
            ctx.lineTo(rx + lw, ry + lh - radius);
            ctx.quadraticCurveTo(rx + lw, ry + lh, rx + lw - radius, ry + lh);
            ctx.lineTo(rx + radius, ry + lh);
            ctx.quadraticCurveTo(rx, ry + lh, rx, ry + lh - radius);
            ctx.lineTo(rx, ry + radius);
            ctx.quadraticCurveTo(rx, ry, rx + radius, ry);
            ctx.closePath();
            ctx.fill();

            ctx.fillStyle = root.textColor;
            ctx.fillText(text, 0, 0);

            ctx.restore();
        }

        // width
        drawLabel(root.boxWidth + " cm", (fx + fx2) / 2, fy2 + fontSize * 1.6);

        // height
        drawLabel(root.boxHeight + " cm", fx - fontSize * 1.6, (fy + fy2) / 2, -Math.PI / 2);

        // depth
        drawLabel(root.boxDepth + " cm", (fx2 + bx2) / 2, (fy + by) / 2, Math.atan2(by - fy, bx - fx));

        ctx.restore();
    }
}
