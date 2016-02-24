import QtQuick 2.2

Rectangle {
    id: root;
    width: 300;
    height: 200;
    Text {
        text: "simple demo";
    }
    Rectangle {
        anchors.bottom: parent.bottom;
        color: "red";
        width: 50;
        height: 30;
    }

    Component.onCompleted: {
        console.log("%1 visual children: ".arg(children.length));
        for(var i = 0; i < children.length; i++)
        {
            console.log(children[i]);
        }
    }
}
