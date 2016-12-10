import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: page
    width: 320; height: 350
    color: "lightgray"

    Rectangle {
		anchors.fill: parent
		anchors.margins: 10

		TextField {
			id: txtImageUrl
			placeholderText: qsTr("Image url")
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.top: parent.top
			anchors.margins: 10
		}

		ComboBox {
			id: cbImageFormat
			anchors.left: parent.left
			anchors.top: txtImageUrl.bottom
			anchors.topMargin: 10
			anchors.leftMargin: 10
			model: ["PNG", "JPEG"]
		}

		Button {
			id: btnConvert
			text: "Do some magic"
			anchors.left: cbImageFormat.right
			anchors.top: txtImageUrl.bottom
			anchors.right: parent.right
			anchors.leftMargin: 10
			anchors.rightMargin: 10
			anchors.topMargin: 10
			onClicked: {
				_mainWindow.convert(txtImageUrl.text, cbImageFormat.currentText);
			}
		}
	}
}
