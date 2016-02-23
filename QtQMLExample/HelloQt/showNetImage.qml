import QtQuick 2.2
import QtQuick.Controls 1.2


Rectangle {
    width: 1000;
    height: 750;
    color: "#121212";

    BusyIndicator {
        id: busy;
        running: true;
        anchors.centerIn: parent;
        z: 2;
    }

    Text {
        id: stateLabel;
        visible: false;
        anchors.centerIn: parent;
        z: 3;
    }

    Image {
        id: imageViewer;
        asynchronous: true;
        cache: false;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit;
        onStatusChanged: {
            if(imageViewer.status === Image.Loading)
            {
                busy.running = true;
                stateLabel.visible = false;
            }
            else if(imageViewer.status === Image.Ready)
            {
                busy.running = false;
            }
            else if(imageViewer.status === Image.Error)
            {
                busy.running = false;
                stateLabel.visible = true;
                stateLabel.text = "Error";
            }
        }
    }

    Component.onCompleted: {
        imageViewer.source = "http://bcy.net/image/full?type=coser&id=453102&url=http://img9.bcyimg.com/coser/56442/post/177q2/53718660d61e11e584acd18a8c7b407c.jpg";
    }
}

