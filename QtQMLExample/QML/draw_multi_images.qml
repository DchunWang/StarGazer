import QtQuick 2.2

Canvas {
    width: 1300;
    height: 700;
    id: root;
    property var bigImage: "mid.jpg";
    property var netImage:
        "http://img9.bcyimg.com/drawer/4390/post/177q4/d71a1f60d77f11e5b360870999c03b5e.jpg/w650";

    onPaint: {
        var ctx = getContext("2d");
        ctx.drawImage(netImage, 600, 0);
        ctx.drawImage(bigImage, 0, 0);
    }

    Component.onCompleted: {
        loadImage(bigImage);
        loadImage(netImage);
    }
    onImageLoaded: requestPaint();
}
