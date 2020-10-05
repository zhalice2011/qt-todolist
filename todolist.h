#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include<QVector>

struct TodoItem {
    bool done;
    QString description;
};

class TodoList : public QObject
{
    Q_OBJECT
public:
    explicit TodoList(QObject *parent = nullptr);

    QVector<TodoItem> items() const;

    bool setItemAt(int index, const TodoItem &item);

signals:  // 前置和后置信号, 在数据即将发生改变前后得到通知
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeCompletedItems();
private:
    QVector<TodoItem> mItems;

};

#endif // TODOLIST_H
