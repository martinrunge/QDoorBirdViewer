import QtQuick 2.0
import QtQuick.Window 2.0
import QtMultimedia 5.0


Window {
    id: window
    visible: true

    title: qsTr("Tür Kamera")

    //flags: Qt.FramelessWindowHint

    property url videosrc;

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



    Timer {
        id: timer
        interval: 5000; repeat: false
        onTriggered: {
            player.stop()
            player.source = ""
        }
    }

    // when window gets minimized, stop video after 5 seconds
    onWindowStateChanged: {
        console.log("onWindowStateChanged: ", windowState);
        if (windowState === Qt.WindowMinimized) {
            console.log("Minimized");
            timer.start()
        } else {
            console.log("Play Video");
            timer.stop()  // in case timer is running
            if(player.playbackState !== Qt.PlayingState) {
                player.source = videosrc
                player.play()
            }
        }
    }
}
