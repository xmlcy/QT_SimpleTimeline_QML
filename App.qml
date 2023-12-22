import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI

Item {
    id: app

    Component.onCompleted: {
        FluApp.init(app)
        FluApp.windowIcon = "qrc:/"
        FluTheme.enableAnimation = true
        FluApp.routes = {
            "/":"qrc:/main.qml",
            "/login":"qrc:/Login.qml",
            "/addTimeline":"qrc:/AddTimeline.qml",
            "/editTimeline":"qrc:/EditTimeline.qml"
        }
        FluApp.initialRoute = "/login"
        FluApp.run()
    }
}
