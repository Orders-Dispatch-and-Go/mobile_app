import QtQuick 2.15

Item {
    id: root
    width: 160
    height: 160

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
    property int padding: 12

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            var dpr = canvas.devicePixelRatio || 1;
            ctx.reset();
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            ctx.save();
            ctx.scale(dpr, dpr);

            var w = canvas.width / dpr;
            var h = canvas.height / dpr;
            var pad = root.padding;

            // ► НОРМАЛИЗАЦИЯ: максимальный габарит всегда = 100 px
            var maxDim = Math.max(root.boxWidth, root.boxHeight, root.boxDepth);
            var normScale = root.maximumSize / Math.max(1, maxDim);   // основной масштаб

            // визуальные размеры
            var visW = root.boxWidth * normScale;
            var visH = root.boxHeight * normScale;
            var depthOffsetX = root.boxDepth * normScale * 0.6;
            var depthOffsetY = -root.boxDepth * normScale * 0.35;

            // центрируем фигуру
            var totalW = visW + Math.max(0, depthOffsetX) + pad * 2;
            var totalH = visH + Math.max(0, -depthOffsetY) + pad * 2;

            var fx = (w - totalW) / 2 + pad + Math.max(0, depthOffsetX) * 0;
            var fy = (h - totalH) / 2 + pad + Math.max(0, -depthOffsetY);

            var fx2 = fx + visW;
            var fy2 = fy + visH;

            var bx = fx + depthOffsetX;
            var by = fy + depthOffsetY;
            var bx2 = fx2 + depthOffsetX;
            var by2 = fy2 + depthOffsetY;
            // рисуем заднюю грань (тонко, пунктир), затем переднюю
            ctx.lineWidth = root.strokeWidth;
            ctx.strokeStyle = root.strokeColor;
            ctx.fillStyle = root.fillColor;

            // задняя грань (полупрозрачная)
            ctx.setLineDash([6, 6]);
            ctx.globalAlpha = 0.6;
            ctx.beginPath();
            ctx.moveTo(bx, by);
            ctx.lineTo(bx2, by);
            ctx.lineTo(bx2, by2);
            ctx.lineTo(bx, by2);
            ctx.closePath();
            ctx.stroke();

            // соединяющие ребра (задняя->передняя)
            ctx.beginPath();
            ctx.moveTo(bx, by);
            ctx.lineTo(fx, fy);
            ctx.moveTo(bx2, by);
            ctx.lineTo(fx2, fy);
            ctx.moveTo(bx2, by2);
            ctx.lineTo(fx2, fy2);
            ctx.stroke();

            // передняя грань (сплошная)
            ctx.setLineDash([]);
            ctx.globalAlpha = 1.0;
            ctx.beginPath();
            ctx.rect(fx, fy, visW, visH);
            ctx.stroke();

            // заливка (если задана)
            if (root.fillColor !== "transparent") {
                ctx.globalAlpha = 0.12;
                ctx.fillStyle = root.fillColor;
                ctx.fillRect(fx, fy, visW, visH);
                ctx.globalAlpha = 1.0;
            }

            // подписываем размеры: width (понизу, по центру), height (слева по центру), depth (рядом со смещением)
            ctx.fillStyle = root.textColor;
            var fontSize = Math.max(10, Math.min(18, 12 * scale)); // адаптивный размер шрифта
            ctx.font = fontSize + "px sans-serif";
            ctx.textBaseline = "middle";
            ctx.textAlign = "center";

            // width label (цифра и линия измерения)
            var midBottomX = (fx + fx2) / 2;
            var bottomY = fy2 + 18;
            // dimension line
            ctx.beginPath();
            ctx.moveTo(fx, fy2 + 6);
            ctx.lineTo(fx, fy2 + 12);
            ctx.moveTo(fx2, fy2 + 6);
            ctx.lineTo(fx2, fy2 + 12);
            ctx.moveTo(fx, fy2 + 9);
            ctx.lineTo(fx2, fy2 + 9);
            ctx.stroke();
            ctx.fillText(String(root.boxWidth) + " cm", midBottomX, bottomY);

            // height label (слева, вертикально)
            ctx.save();
            ctx.translate(fx - 14, (fy + fy2) / 2);
            ctx.rotate(-Math.PI / 2);
            ctx.textAlign = "center";
            ctx.fillText(String(root.boxHeight) + " cm", 0, 0);
            ctx.restore();

            // depth label (на диагонали/вверху между передней и задней гранью)
            // вычислим середину диагонали от верх-right передней до верх-right задней
            var diagMidX = (fx2 + bx2) / 2;
            var diagMidY = (fy + by) / 2 - 8;
            ctx.save();
            // повернём текст вдоль диагонали
            var angle = Math.atan2(by - fy, bx - fx); // угол смещения
            ctx.translate(diagMidX, diagMidY);
            ctx.rotate(angle);
            ctx.textAlign = "center";
            ctx.fillText(String(root.boxDepth) + " cm", 0, 0);
            ctx.restore();

            ctx.restore();
        }

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
}
