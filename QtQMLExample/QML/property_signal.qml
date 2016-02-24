import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle {
    width: 320;
    height: 240;
    color: "gray";

    Text {
        id: hello;
        anchors.centerIn: parent;
        text: "Hello World";
        color: "blue";
        font.pixelSize: 32;
        onTextChanged: {
            console.log(text);
        }
    }

    Button {
        anchors.top: hello.bottom;
        anchors.topMargin: 10;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "Changed";
        onClicked: {
            hello.text = "My Change";
        }
    }
}
