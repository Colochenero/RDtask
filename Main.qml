import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "File Encryptor/Decryptor"

    Column {
        spacing: 20
        anchors.centerIn: parent

        CustomTextInput {
            id: filePathInput
            placeholderText: "File path will appear here after selection..."
            //readonly: true  // Make the input read-only
        }

        CustomButton {
            text: "Choose File"
            onClicked: fileHandler.setFileInfo()
        }

        CustomButton {
            text: "Encrypt File"
            onClicked: fileHandler.encryptFile()
        }

        CustomButton {
            text: "Decrypt File"
            onClicked: fileHandler.decryptFile()
        }

        Label {
            id: filePathLabel
            text: "File Path: "
        }

        Label {
            id: fileSizeLabel
            text: "File Size: "
        }

        Label {
            id: fileExtensionLabel
            text: "File Extension: "
        }
    }

    Connections {
        target: fileHandler
        function onFilePathChanged(filePath) {
            console.log("Received filePathChanged:", filePath)
            filePathLabel.text = "File Path: " + filePath
            filePathInput.text = filePath
        }
        function onFileSizeChanged(fileSize) {
            console.log("Received fileSizeChanged:", fileSize)
            fileSizeLabel.text = "File Size: " + fileSize + " bytes"
        }
        function onFileExtensionChanged(fileExtension) {
            console.log("Received fileExtensionChanged:", fileExtension)
            fileExtensionLabel.text = "File Extension: " + fileExtension
        }
    }
}
