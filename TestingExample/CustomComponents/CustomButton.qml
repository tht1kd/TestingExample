///////////////////////////////////////////////////////////////////////////////
// Copyright Deere & Company. For more information,
// please see COPYRIGHT file in root of source repository.
///////////////////////////////////////////////////////////////////////////////
import QtQuick 2.15
import QtQuick.Templates 2.15 as T

T.Button {
    id: root

    //////////////////////////////////////////////////////
    // Properties
    //////////////////////////////////////////////////////
    property alias source: icon.source

    //////////////////////////////////////////////////////
    // Sizing
    //////////////////////////////////////////////////////
    implicitHeight: Math.max(word.implicitHeight, icon.implicitHeight) + topPadding + bottomPadding
    implicitWidth: icon.implicitWidth + word.implicitWidth + leftPadding + rightPadding + row.spacing

    //////////////////////////////////////////////////////
    // Creation
    //////////////////////////////////////////////////////
    enabled: !root.locked
    bottomInset: 4
    leftInset: 4
    rightInset: 4
    topInset: 4
    horizontalPadding: 4
    verticalPadding: 4
    state: "primary"

    contentItem: Item {

        Row {
            id: row
            spacing: 6

            Image {
                id: icon
                source: "qrc:/assests/salute.jpg"
                sourceSize: Qt.size(40,40)
            }
            Text {
                id: word
                objectName: "JDButtonWord"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                height: Math.min(parent.height, implicitHeight)
                font.pointSize: 22
                text: root.text
                width: parent.width >= implicitWidth ? implicitWidth : parent.width
            }
        }
    }

    background: Rectangle {
        id: background
        objectName: "ButtonBackground"
        border.width: 1
        border.color: "Green"
        radius: 4
    }
}
