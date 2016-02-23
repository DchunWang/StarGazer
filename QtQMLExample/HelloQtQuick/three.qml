import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    width: 320;
    height: 480;

    Button {
        id: quit;
        text: "退出";
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        onClicked: {
            Qt.quit();
        }
    }
}
