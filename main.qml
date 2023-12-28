import QtQuick 2.15
import QtQuick.Window 2.15
import SimpleTimeline
import FluentUI

FluWindow {
    id: main
    title: "SimpleTimeline"
    width: 1280
    height: 720

    appBar: FluAppBar {
        id: title_bar
        title: main.title
        showDark: true
        icon: main.windowIcon
    }

//    Connections{
//        target: FluTheme
//        function onDarkModeChanged(){
//            SettingsHelper.saveDarkMode(FluTheme.darkMode)
//        }
//    }

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            stimeline.begin()
//            stimeline.doSomething("stimeline")
//            stimeline.animationFinished()
//            stime2.begin()
//            stime2.doSomething("stime2")
//            stime2.animationFinished()

//            stimeline.start()
//        }
//    }

    STimeline {
        id: stimeline
        onBegin: console.log("stimeline onBegin")
        onAnimationFinished: console.log("stimeline onAnimationFinished")
        xnum: recAni.x
//        onRecordstateChanged: {
//            if (stimeline.recordstate == 1){
//                myt.mystart();
//                console.log("state == 1,start record")
//                onXnumChanged: {
//                    console.log("x changed.")
//                    myt.mystop();
//                    stimeline.addFrameButton(recAni, "x", "rxani", recAni.x,  1,  myt.myelapsed());
//                    console.log("add time:",myt.myelapsed());
//                    myt.mystart();
//                }
//                onYChanged: {
//                    console.log("y changed.")
//                    stimeline.addFrameButton(recAni, "y", "ryani", recAni.y,  1,  timlineEditor.frameNow)
//                }
//            }else{
//                console.log("state == 0,end record");
//            }
//        }
//        onXnumChanged: {
//            console.log("x changed.")
//            myt.mystop();
//            stimeline.addFrameButton(recAni, "x", "rxani", recAni.x,  1,  myt.myelapsed());
//            console.log("add time:",myt.myelapsed());
//            myt.mystart();
//        }
    }

    TimelineEditorFluentUI {
        id: timlineEditor
        width: parent.width
        height: parent.height - parent.height / 1.4
        anchors {
            bottom: parent.bottom
            bottomMargin: 0
        }
        onAddTimeline: {
            console.log("add Timeline")
            FluApp.navigate("/addTimeline")
        }
        onEditTimeline: {
            console.log("edit Timeline")
            FluApp.navigate("/editTimeline")
        }
        onStartTimeline: {
            console.log("start Timeline")
            stimeline.start()
        }
        onStopTimeline: {
            console.log("stop Timeline")
            stimeline.stop()
        }
        onFrameNowChanged: {
//            console.log(frameNow)
        }
        onAddframe: {
            stimeline.addFrameButton(recAni, "x", "rxani", recAni.x,  1,  frameNow)
            stimeline.addFrameButton(recAni, "y", "ryani", recAni.y,  1,  frameNow)
            console.log(frameNow)
        }
        onRecordframe: {
            if (stimeline.recordstate == 0){
                stimeline.recordstate = 1;
            }else{
                stimeline.recordstate = 0;
            }
        }
        frameLine {
            onPositionChanged: {
                console.log(stimeline.preview("rxani", frameNow))
            }
        }



    }

    STimeline {
        id: stime2
        onBegin: console.log("stime2 onBegin")
        onAnimationFinished: console.log("stimeline onAnimationFinished")
    }

//    Rectangle {
//        id: rectangle
//        x: 220
//        y: 140
//        width: 200
//        height: 200
//        color: "#ff0000"
//    }

    Rectangle {
        id: recAni
        x: 1000
        y: 200
        width: 100
        height: 100
        color: "#ff0000"

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: recAni
        }

//        onXChanged: {
//            console.log("x changed.==============j");
//        }
    }

    Component.onCompleted: {
        stimeline.createAnimate("rxani")
        stimeline.createAnimate("ryani")
    }

}
