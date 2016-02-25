import QtQuick 2.2

Canvas {
    width: 1200;
    height: 750;
    contextType: "2d";
    property var comicRole:
        "http://img9.bcyimg.com/drawer/22444/post/177q8/a500ee20db0111e584f8fb42156459cb.jpg/w650";

    onPaint: {
        context.lineWidth = 2;
        context.strokeStyle = "blue";
        context.fillStyle = Qt.rgba(0.3, 0.5, 0.7, 0.5);

        context.save();
        context.translate(width/2, height/2);
        context.drawImage(comicRole, -68, -100, 137, 200);
        context.restore();

        context.save();
        context.translate(width/2, 0);
        context.shear(0.6, 0);
        context.drawImage(comicRole, 0, 0, 137, 200);
        context.restore();

        context.save();
        context.translate(width/2, 0);
        context.drawImage(comicRole, -137, 0, 137, 200);
        context.restore();

        context.save();
        context.translate(0, height/2);
        context.shear(0.3, 0);
        context.rotate(Math.PI/3);
        context.drawImage(comicRole, 0, -100, 137, 200);
        context.restore();

        context.save();
        context.translate(width/2, height/2);
        context.rotate(Math.PI/2);
        context.drawImage(comicRole, 120, -40, 137, 200);
        context.restore();

        context.save();
        context.setTransform(1.2, 0.5, 0, 0.7, width-100, height-120);
        context.drawImage(comicRole, 0, 0, 68, 100);
        context.restore();
    }

    Component.onCompleted: loadImage(comicRole);
    onImageLoaded: requestPaint();
}
