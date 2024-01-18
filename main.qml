import QtQuick
import QtQuick.Controls

import an.qt.ColorMaker 1.0

/*
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
}
*/

Rectangle {
    width: 360
    height: 360
    border.color: "red"
    border.width: 5

    Text {
        id: timeLabel
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        font.pixelSize: 26
        text: qsTr("Hello World")
    }


    // 在QML文件中定义对象
    ColorMaker {
        id: colorMaker
        color: "Green"
    }

    Rectangle {
        id: colorRect;
        anchors.centerIn: parent;
        width: 200;
        height: 200;
        color: "blue";
    }

    Button {
        id: start;
        text: "start";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked: {
            colorMaker.Start();
        }
    }

    Button {
        id: stop;
        text: "stop";
        anchors.left: start.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            colorMaker.Stop();
        }
    }

    function changeAlgorithm(button, algorithm) {
        switch(algorithm)
        {
        case 0:
            button.text = "RandomRGB";
            break;
        case 1:
            button.text = "RandomRed";
            break;
        case 2:
            button.text = "RandomGreen";
            break;
        case 3:
            button.text = "RandomBlue";
            break;
        case 4:
            button.text = "LinearIncrease";
            break;
        }
    }

    Button {
      id: colorAlgorithm;
      text: "RandomRGB";
      anchors.left: stop.right;
      anchors.leftMargin: 4;
      anchors.bottom: start.bottom;
      onClicked: {
          var algorithm = (colorMaker.algorithm() + 1) % 5;
          changeAlgorithm(colorAlgorithm, algorithm);
          colorMaker.setAlgorithm(algorithm);
      }
    }

    Button {
        id: quit;
        text: "quit";
        anchors.left: colorAlgorithm.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            // If the event loop is not running, this function does nothing
            //Qt.quit(); 此处直接调用quit无效
            // 调用封装好的函数
            colorMaker.QuitApp();
        }
    }

    Component.onCompleted: {
      colorMaker.color = Qt.rgba(0,180,120, 255);
      colorMaker.setAlgorithm(ColorMaker.LinearIncrease);
      changeAlgorithm(colorAlgorithm, colorMaker.algorithm());
    }

    Connections {
      target: colorMaker;
      onCurrentTime:{
          timeLabel.text = strTime;
          timeLabel.color = colorMaker.timeColor;
      }
    }

    Connections {
      target: colorMaker;
      onColorChanged:{
          colorRect.color = color;
      }
    }
}
