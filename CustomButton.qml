import QtQuick 2.0

Rectangle {
    id: root
    width: 200
    height: 50
    color: "#007BFF"  // Default button color
    radius: 10

    property string text: "Click Me"
    signal clicked

    Text {
        anchors.centerIn: parent
        color: "white"
        text: root.text
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
