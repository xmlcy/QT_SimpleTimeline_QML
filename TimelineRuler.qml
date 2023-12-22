import QtQuick 2.15

Rectangle {
    width: 400
    height: 100

    property int startYear: 0
    property int endYear: 20

    Canvas {
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            var w = width;
            var h = height;

            // 绘制背景
            ctx.fillStyle = "#f8f8f8";
            ctx.fillRect(0, 0, w, h);

            // 绘制时间轴
            ctx.strokeStyle = "#aaa";
            ctx.lineWidth = 2;
            ctx.beginPath();
            ctx.moveTo(0, h-5);
            ctx.lineTo(w, h-5);
            ctx.stroke();

            // 绘制刻度线
            var yearCount = endYear - startYear;
            var tickSpacing = w / yearCount;
            for (var i = 0; i <= yearCount; i++) {
                var x = i * tickSpacing;
                ctx.beginPath();
                ctx.moveTo(x, h - 20);
                ctx.lineTo(x, h - 5);
                ctx.stroke();

                // 绘制年份标签
                var year = startYear + i;
                ctx.fillStyle = "#666";
                ctx.font = "12px sans-serif";
                ctx.textAlign = "center";
                ctx.fillText(year.toString(), x, h/2-5);
            }
        }
    }
}

