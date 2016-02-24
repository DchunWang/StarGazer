import QtQuick 2.2

Rectangle {
    id: root;
    Component.onCompleted : {
        console.log(root);
        var array = new Array(10, 12, 8, "Anna");
        console.debug("Print array:", array);
    }
}
