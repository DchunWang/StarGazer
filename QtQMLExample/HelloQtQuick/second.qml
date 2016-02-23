import QtQuick 2.2
import QtQuick.Controls 1.1


Rectangle {
    width: 400;
    height: 400;
    color: "blue"

    Text {
        text: "Test!";
        color: "blue";
        font.pixelSize: 32;
        anchors.centerIn: parent;
    }

    Button {
        id: openFile;
        text: "打开";
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.top: parent.top;
        anchors.topMargin: 5;
    }

    Button {
        id: quit;
        text: "退出";
        anchors.left: openFile.right;
        anchors.leftMargin: 3;
        anchors.bottom: openFile.bottom;

    }
}


