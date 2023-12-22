import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import FluentUI

FluWindow {

    id:window
    title:"登录"
    width: 400
    height: 400
    fixSize: true

    onInitArgument:
        (argument)=>{
            textbox_uesrname.updateText("User")
            textbox_password.focus =  true
        }

    ColumnLayout{
        anchors{
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        FluAutoSuggestBox{
            id:textbox_uesrname
            items:[{title:"Admin"},{title:"User"}]
            placeholderText: "请输入账号"
            Layout.preferredWidth: 260
            Layout.alignment: Qt.AlignHCenter
        }

        FluTextBox{
            id:textbox_password
            Layout.topMargin: 20
            Layout.preferredWidth: 260
            placeholderText: "请输入密码"
            echoMode:TextInput.Password
            Layout.alignment: Qt.AlignHCenter
        }

        FluFilledButton{
            text:"登录"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            onClicked:{
                if (textbox_password.text === "") {
                    showWarning("请输入密码")
                    return
                } else if (textbox_password.text === "123456") {
//                    showSuccess("登录成功") // 无法提示
                    FluApp.navigate("/")
                    onResult({password:textbox_password.text})
                    window.close()
                } else {
                    showError("密码错误")
                    return
                }
            }
        }

    }



}
