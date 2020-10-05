
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Todo 1.0

ColumnLayout {
    Frame {
        Layout.fillWidth: true
        ListView {
            // 给listView设置隐式的宽高
            implicitWidth: 250
            implicitHeight: 250
            clip: true // 类似于overflow: hidden
            anchors.fill: parent

            // a. 数据模型  (可以是js或者c++)
    //        model: 100
            // b. 简单列表模型
    //        model: ListModel {
    //            ListElement {
    //                done: false
    //                description: "buy a house"
    //            }
    //            ListElement {
    //                done: true
    //                description: "girl firend"
    //            }
    //        }
            // c. 自定义模型
            model: TodoModel {
                list: todoList
            }

            // 委托是一种视觉模板, 描述了列表的方式
            delegate: RowLayout { // RowLayout表示一项显示一行
    //            width: parent.width

                CheckBox { // 复选框
                    checked: model.done
                    onClicked: model.done = checked
                }
                TextField { // 文字描述
                    text: model.description
                    Layout.fillWidth: true // 类似于flex1
                    onEditingFinished: model.description = text
                }
            }
        }
    }

    RowLayout {
        Button {
            text: qsTr("Add a new Item   ")
            Layout.fillWidth: true
            onClicked: todoList.appendItem()
        }
        Button {
            text: qsTr("remove completed  removeremoveremoveremove ")
            Layout.fillWidth: true
            onClicked: todoList.removeCompletedItems()

        }
    }
}
