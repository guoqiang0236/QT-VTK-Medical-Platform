import QtQuick
import QtQuick.Controls

/*
1 核心控件和窗口布局和登录事件处理
    文本说明：登录系统
    用户名：username
    密码: password
    登录按钮: submit
    登录事件处理
        onClicked
*/
ApplicationWindow//窗口
{
    width:1280
    height:800
    visible:true//默认窗口不显示
    title:"login UI"
    id:root
    Rectangle
    {
         Text  //文本说明：登录系统
        {
            x: 530
            y: 130
            width: 120
            height: 30
            font.pixelSize: 24
            text: qsTr("登录系统")
        }

        //用户名：username
        TextField
        {
            id:username
            x: 440
            y: 200
            width: 300
            height: 50
            font.pixelSize: 20
        }

        //密码: password
        TextField
        {
            id:password
            x: username.x
            y: username.y + username.height + 10
            width: username.width
            height: username.height
            font.pixelSize: username.font.pixelSize
            echoMode: TextInput.Password
        }

        //登录按钮: submit
        Button
        {
            x: username.x
            y: password.y + password.height + 10
            width: username.width
            height: username.height
            text: qsTr("登录")
            font.pixelSize: 20
            onClicked: 
            {
                print("登录：" + username.text + " : " + password.text)
            }
        }
    }
}