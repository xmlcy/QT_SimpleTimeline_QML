import QtQuick 2.15
import QtQuick.Window 2.15
import SimpleTimeline

Window {
    id: main
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    MouseArea {
        anchors.fill: parent
        onClicked: {
            stimeline.begin()
            stimeline.doSomething("stimeline")
            stimeline.animationFinished()
            stime2.begin()
            stime2.doSomething("stime2")
            stime2.animationFinished()

            stimeline.start()
        }
    }

    STimeline {
        id: stimeline
        onBegin: console.log("stimeline onBegin")
        onAnimationFinished: console.log("stimeline onAnimationFinished")
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
        stimeline.addFrame(rectangle, "x", "xani", 220,  1,    0)
        stimeline.addFrame(rectangle, "x", "xani", 100,  1,  200)
        stimeline.addFrame(rectangle, "x", "xani",   0,  1,  500)
        stimeline.addFrame(rectangle, "x", "xani", 220,  1, 1000)
        stimeline.createAnimate(rectangle, "yani")
        stimeline.addFrame(rectangle, "y", "yani", 140,  1,    0)
        stimeline.addFrame(rectangle, "y", "yani", 100,  1,  200)
        stimeline.addFrame(rectangle, "y", "yani",   0,  1,  500)
        stimeline.addFrame(rectangle, "y", "yani", 140,  1, 1000)
    }

}
