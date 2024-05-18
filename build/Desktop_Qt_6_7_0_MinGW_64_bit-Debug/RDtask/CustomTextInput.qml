import QtQuick 2.0

Rectangle {
    id: root
    width: 300
    height: 40
    border.color: "gray"
    border.width: 1
    radius: 5

    property alias text: input.text
    property alias placeholderText: placeholder.text

    Text {
        id: placeholder
        text: root.placeholderText
        color: "gray"
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 10
        visible: input.text.length === 0
    }

    TextInput {
        id: input
        anchors.fill: parent
        anchors.margins: 8
        font.pixelSize: 16
        color: "black"
    }
}
