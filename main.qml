import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12

import Qt.labs.settings 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Tür Kamera")

    MediaPlayer {
        id: player
        objectName: "player"
        autoPlay: false
    }

    VideoOutput {
        id: videoOutput
        source: player
        anchors.fill: parent
    }

}
