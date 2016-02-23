import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle{
    width: 400;
    height: 300;
    Button {
        text: "Quit";
        anchors.centerIn: parent;
        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100;
                implicitHeight: 100;
                color: control.pressed ? "yellow" : "blue";
                border.width: control.pressed ? 3 : 1;
                border.color: (control.hovered || control.pressed) ?
                                  "green" : "red";

            }
        }

        //onClicked: Qt.quit();
    }
}
