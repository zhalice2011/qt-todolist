#include "todomodel.h"

#include "todolist.h"

TodoModel::TodoModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int TodoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size(); // 返回列表的长度
}

QVariant TodoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const TodoItem item = mList->items().at(index.row());
    switch (role) {
    case DoneRole: {
        return QVariant(item.done);
    }
    case DescriptionRole: {
        return QVariant(item.description);
    }
    }
};

bool TodoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;
    TodoItem item = mList->items().at(index.row());
    switch (role) {
    case DoneRole: {
        item.done = value.toBool();
    }
    case DescriptionRole: {
        item.description = value.toString();
    }
    }
    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TodoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> TodoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";
    return names;
}

TodoList *TodoModel::list() const
{
    return mList;
}

void TodoModel::setList(TodoList *list)
{
    beginResetModel();

    if (mList) {
        mList->disconnect(this);
    }

    mList = list;

    if (mList) {
        connect(mList, &TodoList::preItemAppended, this, [=]() {
           const int index = mList->items().size();
           beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &TodoList::postItemAppended, this, [=]() {
           endInsertRows();
        });
        connect(mList, &TodoList::preItemRemoved, this, [=](int index) {
           beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &TodoList::postItemRemoved, this, [=]() {
           endRemoveRows();
        });

        endResetModel();
    }
}
