import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width: 800;
    height: 500;

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    Rectangle {
        id: re
        width: 50;
        height: 40;
        color: "blue";
        border.color: "#808080";
        border.width: 2;
        radius: 12;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        anchors.left: parent.left;
        anchors.leftMargin: 5;
    }

    Rectangle {
        width: 100;
        height: 40;
        anchors.left: re.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        gradient: Gradient {
            GradientStop {position: 0.0; color: "#101010";}
            GradientStop {position: 0.2; color: "blue";}
            GradientStop {position: 1.0; color: "red";}
        }
    }
}

