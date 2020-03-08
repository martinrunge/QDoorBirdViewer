import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.3
import QtMultimedia 5.0


Window {
    id: window
    visible: true
    title: qsTr("Tür Kamera")

    // flags: Qt.FramelessWindowHint

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
        Button {
                id: closeBtn;
                icon.name: "close"
                icon.source: "icons/close-24px.svg"
                icon.height: parent.height / 3;
                icon.color: "#000000"
                width: parent.width / 3;
                height: parent.height / 3;
                anchors.top: parent.Top;
                anchors.right: parent.right;
                background: Rectangle {
                            color: "#88ffffff";
                        }
                onClicked: window.showMinimized();
        }
        Button {
                id: maxBtn;
                icon.name: "fullscreen"
                icon.source: "icons/fullscreen-24px.svg"
                icon.height: parent.height / 3;
                icon.color: "#000000"
                width: parent.width / 3;
                height: parent.height / 3;
                anchors.top: parent.Top;
                anchors.left: parent.left;
                background: Rectangle {
                            color: "#88ffffff";
                        }
                onClicked: window.showMaximized();
        }

    }



    Timer {
        id: timer
        interval: 5000; repeat: false
        onTriggered: {
            player.stop()
            player.source = ""
            console.log("Timer expired, stopping stream");
        }
    }

    // when window gets minimized, stop video after 5 seconds
    onWindowStateChanged: {
        console.log("onWindowStateChanged: ", windowState);
        if (windowState === Qt.WindowMinimized) {
            console.log("Minimized, starting timer");
            timer.start()
        } if (windowState !== Qt.WindowActive && windowState !== Qt.WindowNoState ) {
            console.log("Window not active, starting timer");
            timer.start()
        } else {
            console.log("Play Video, stopping timer");
            timer.stop()  // in case timer is running
            if(player.playbackState !== Qt.PlayingState) {
                player.source = videosrc
                player.play()
            }
            if (windowState === Qt.WindowMaximized || windowState === Qt.WindowFullScreen) {
                maxBtn.visible = false;
            }
            else {
                maxBtn.visible = true;
            }
        }
    }
}
