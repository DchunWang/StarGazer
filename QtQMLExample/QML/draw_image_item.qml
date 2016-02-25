import QtQuick 2.2

Canvas {
    width: 1000;
    height: 800;
    id: root;
    Image {
        id: poster;
        source:
            "http://img9.bcyimg.com/drawer/4390/post/177q4/d71a1f60d77f11e5b360870999c03b5e.jpg/w650";
        visible: false;
        onStatusChanged: {
            if(status == Image.Ready){
                root.requestPaint();
            }
        }
    }

    onPaint: {
        var ctx = getContext("2d");
        ctx.drawImage(poster, 50, 0);
    }
}
