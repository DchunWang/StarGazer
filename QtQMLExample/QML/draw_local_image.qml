import QtQuick 2.2

Canvas {
    id: root;

    property var dartlikeWeapon: "bigImage.png";

    width: 1200;
    height: 700;

    onPaint: {
        var ctx = getContext("2d");
        ctx.drawImage(dartlikeWeapon, 0, 0);
    }

    Component.onCompleted: loadImage(dartlikeWeapon);
    onImageLoaded: requestPaint();
}
