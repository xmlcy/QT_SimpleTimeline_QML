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
            stimeline.addFrame(recAni, "x", "rxani", recAni.x,  1,  frameNow)
            stimeline.addFrame(recAni, "y", "ryani", recAni.y,  1,  frameNow)
            console.log(frameNow)
        }

    }

    STimeline {
        id: stime2
        onBegin: console.log("stime2 onBegin")
        onAnimationFinished: console.log("stimeline onAnimationFinished")
    }

    Rectangle {
        id: rectangle
        x: 220
        y: 140
        width: 200
        height: 200
        color: "#ff0000"
    }

    Rectangle {
        id: recAni
        x: 1000
        y: 200
        width: 100
        height: 100
        color: "#ffff00"

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: recAni
        }
    }

    Component.onCompleted: {
        console.log("Component.onCompleted")
        //        stimeline.createAnimate(rectangle, "x", "xani", 1000)
        //        stimeline.addFrame("xani", 0, 0, 220)
        //        stimeline.addFrame("xani", 0, 0.2, 100)
        //        stimeline.addFrame("xani", 0, 0.5, 0)
        //        stimeline.addFrame("xani", 0, 1, 220)
        //        stimeline.createAnimate(rectangle, "y", "xani", 1000)
        //        stimeline.addFrame("xani", 0, 0, 140)
        //        stimeline.addFrame("xani", 0, 0.2, 100)
        //        stimeline.addFrame("xani", 0, 0.5, 0)
        //        stimeline.addFrame("xani", 0, 1, 140)
        stimeline.createAnimate(rectangle, "xani")
        //        stimeline.addFrame(rectangle, "x", "xani", 220,  1,    0)
        stimeline.addFrame(rectangle, "x", "xani", 100,  1,  200)
        stimeline.addFrame(rectangle, "x", "xani",   0,  1,  500)
        stimeline.addFrame(rectangle, "x", "xani", 400,  1,  700)
        stimeline.addFrame(rectangle, "x", "xani", 220,  1, 1000)
        stimeline.updateFrame("xani", 100, 1, 1000)
        stimeline.deleteFrame("xani", 700)
        stimeline.createAnimate(rectangle, "yani")
        //        stimeline.addFrame(rectangle, "y", "yani", 140,  1,    0)
        stimeline.addFrame(rectangle, "y", "yani", 100,  1,  200)
        stimeline.addFrame(rectangle, "y", "yani",   0,  1,  500)
        stimeline.addFrame(rectangle, "y", "yani", 300,  1,  700)
        stimeline.addFrame(rectangle, "y", "yani", 140,  1, 1000)
        stimeline.updateFrame("yani", 100, 1, 1000)
        stimeline.deleteFrame("yani", 700)

        stimeline.createAnimate(recAni, "rxani")
        stimeline.createAnimate(recAni, "ryani")
    }

}
