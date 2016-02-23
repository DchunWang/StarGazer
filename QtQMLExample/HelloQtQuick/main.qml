import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.1

Window {
    visible: true
    width: 400
    height: 400

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello, my future!")
        anchors.centerIn: parent
    }

    Button {
        text: "Quit";
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 70;
                implicitHeight: 25;
                border.width: control.activeFocus ? 2 : 1;
            }
        }
    }
}

