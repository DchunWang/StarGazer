import QtQuick 2.2

Rectangle {
    width: 500;
    height: 500;

    Rectangle {
        id: rect1;
        anchors.left: parent.left;
        anchors.leftMargin: 20;
        anchors.top: parent.top;
        anchors.topMargin: 20;
        width: 180;
        height: 180;
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#202020";}
            GradientStop { position: 1.0; color: "#A0A0A0";}
        }
    }

    Rectangle {
        id: rect2;
        anchors.left: rect1.right;
        anchors.leftMargin: 20;
        anchors.top: parent.top;
        anchors.topMargin: 20;
        width: 180;
        height: 180;
        rotation: 90;
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#202020";}
            GradientStop { position: 1.0; color: "#A0A0A0";}
        }
    }

}

