import QtQuick 2.15
import QtQuick.Controls 2.15
import FluentUI

FluRectangle {
    id: root

    width: 1280
    height: 220

    signal addAni
    signal editTimeline

    FluRectangle {
        id: menuRec
        x: 0
        y: 0
        width: parent.width
        height: 30
//        color: "#8a8a8a"

        FluText {
            id: menuTitle
            x: 4
            y: 5
            text: qsTr("Timeline")
            font.pixelSize: 15
        }
    }

    FluRectangle {
        id: setRec
        x: 0
        y: 30
        width: parent.width
        height: 30
        color: "#c9c9c9"

        FluIconButton {
            id: buttonAdd
            x: 210
            y: 3
            width: 24
            height: 24
            iconSource:FluentIcons.Add
            iconSize: 8
            onClicked: {
                root.addAni()
            }
        }

        FluIconButton {
            id: buttonSetting
            x: 240
            y: 3
            width: 24
            height: 24
            iconSource:FluentIcons.Settings
            iconSize: 8
            onClicked: {
                root.editTimeline()
            }
        }

        Text {
            id: timelineDuration
            x: 320
            y: 9
            text: qsTr("1000")
            font.pixelSize: 10
        }

        FluComboBox{
            id: comboBox
            x: 8
            y: 2
            width: 180
            height: 25
            font.pixelSize: 12
            model: ListModel {
                id: model
                ListElement { text: "Ani" }
                ListElement { text: "动画1" }
                ListElement { text: "动画2" }
            }
            onAccepted: {
                if (find(editText) === -1)
                    model.append({text: editText})
            }
        }
    }

    FluRectangle {
        id: frameView
        x: 0
        y: 60
        width: parent.width
        height: parent.height-y
        color: "#ffffff"

        ScrollView {
            id: scrollView
            x: 200
            y: 40
            width: parent.width-x
            height: parent.height-y
            clip: true // 确保内容在边界内显示
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            //            contentWidth: 2000
            //            contentHeight: 500
            //            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
            //            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            Flickable {
                id: flickableScrollView
                contentWidth: item1.width+200
                contentHeight: item1.height+100

                // 双向绑定之后动画会很奇怪，暂时只用单向
                //                contentY: flickableScrollView1.contentY
                //                contentX: flickableScrollView2.contentX
                //                onContentYChanged: {
                //                    // 当 ScrollView 1 滚动时，同步 ScrollView 2 的滚动位置
                //                    flickableScrollView1.contentY = contentY;
                //                }
            }

            Item {
                id: item1
                width: childrenRect.width
                height: childrenRect.height

                FluRectangle {
                    id: recAni1
                    x: 0
                    y: 0
                    width: 3000
                    height: 30
                    color: "#8a8a8a"

                    FluRectangle {
                        id: recFrame1
                        x: 279
                        y: 1
                        width: 200
                        height: 28
                        color: "#404040"
//                        border.color: "#ffffff"
//                        border.width: 2
                    }

                    FluRectangle {
                        id: recFrame2
                        x: 558
                        y: 1
                        width: 344
                        height: 28
                        color: "#404040"
//                        border.color: "#ffffff"
//                        border.width: 2
                    }
                }

                FluRectangle {
                    id: recAni2
                    x: 0
                    y: 30
                    width: parent.width
                    height: 30
                    color: "#c9c9c9"
                }

                FluRectangle {
                    id: recAni3
                    x: 0
                    y: 60
                    width: parent.width
                    height: 30
                    color: "#8a8a8a"
                }

                FluRectangle {
                    id: recAni4
                    x: 0
                    y: 90
                    width: parent.width
                    height: 30
                    color: "#c9c9c9"
                }

                FluRectangle {
                    id: recAni5
                    x: 0
                    y: 120
                    width: parent.width
                    height: 30
                    color: "#8a8a8a"
                }

                FluRectangle {
                    id: recAni6
                    x: 0
                    y: 150
                    width: parent.width
                    height: 30
                    color: "#c9c9c9"
                }
            }
        }

        ScrollView {
            id: scrollView1
            x: 0
            y: 40
            width: 200
            height: parent.height-y
            clip: true // 确保内容在边界内显示
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            Flickable {
                id: flickableScrollView1
                contentWidth: 0
                contentHeight: 0
                interactive: false // 禁用鼠标滑动
                contentY: flickableScrollView.contentY

                //                onContentYChanged: {
                //                    // 当 ScrollView 2 滚动时，同步 ScrollView 1 的滚动位置
                //                    flickableScrollView.contentY = contentY;
                //                }

            }


            FluRectangle {
                id: rectangle1
                x: 0
                y: 0
                width: 200
                height: 30
                color: "#404040"
            }

            FluRectangle {
                id: rectangle2
                x: 0
                y: 30
                width: 200
                height: 30
                color: "#616161"
            }

            FluRectangle {
                id: rectangle3
                x: 0
                y: 60
                width: 200
                height: 30
                color: "#404040"
            }

            FluRectangle {
                id: rectangle4
                x: 0
                y: 90
                width: 200
                height: 30
                color: "#616161"
            }

            FluRectangle {
                id: rectangle5
                x: 0
                y: 120
                width: 200
                height: 30
                color: "#404040"
            }

            FluRectangle {
                id: rectangle6
                x: 0
                y: 150
                width: 200
                height: 30
                color: "#616161"
            }
        }

        ScrollView {
            id: scrollView2
            x: 200
            y: 0
            width: parent.width-x
            height: 40
            clip: true // 确保内容在边界内显示
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            Flickable {
                id: flickableScrollView2
                contentWidth: 0
                contentHeight: 0
                interactive: false // 禁用鼠标滑动
                contentX: flickableScrollView.contentX

                //                onContentYChanged: {
                //                    // 当 ScrollView 2 滚动时，同步 ScrollView 1 的滚动位置
                //                    flickableScrollView.contentY = contentY;
                //                }

            }

            FluRectangle {
                id: recTimeruler
                x: 0
                y: 0
                width: parent.width
                height: 40
                color: "#aeaeae"

                Text {
                    id: text1
                    x: 605
                    y: 8
                    text: qsTr("100")
                    font.pixelSize: 20
                }
            }
        }

        FluRectangle {
            id: recTimerulerMenu
            x: 0
            y: 0
            width: 200
            height: 40
            color: "#aeaeae"
//            border.width: 1
        }
    }

}


