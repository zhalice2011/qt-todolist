#include "todolist.h"

TodoList::TodoList(QObject *parent) : QObject(parent)
{
    mItems.append({ true, QStringLiteral("1") });
    mItems.append({ false, QStringLiteral("2") });
}

QVector<TodoItem> TodoList::items() const
{
    return mItems;
}

bool TodoList::setItemAt(int index, const TodoItem &item)
{
    if (index < 0 || index >= mItems.size()) {
        return false;
    }

    const TodoItem & oldItem = mItems.at(index);
    if (item.done == oldItem.done && item.description == oldItem.description) { // 添加一个存在的项目 返回false
        return false;
    }

    mItems[index] = item;
    return true;
}

void TodoList::appendItem()
{
    emit preItemAppended();

    TodoItem item;
    item.done = false;
    mItems.append((item));

    emit postItemAppended();
}

void TodoList::removeCompletedItems()
{

    for (int i = 0; i < mItems.size();) {
        if (mItems.at(i).done) {
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        } else {
            i++;
        }
    }

}
