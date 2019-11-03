import QtQuick 2.0
import QtQuick.Window 2.0
import QtMultimedia 5.0


Window {
    id: window
    visible: true
//    width: 640
//    height: 480
    title: qsTr("Tür Kamera")

    MediaPlayer {
        id: player
        objectName: "player"
        autoPlay: true
    }

    VideoOutput {
        id: videoOutput
        source: player
        anchors.fill: parent
    }

}
