#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "task.h"

class DataBaseConnector : public QObject
{
    Q_OBJECT
public:
    static DataBaseConnector* dataBase();
    static void init();
    static void deinit();

    void setTask(Task);
    Task getTask(int);
    int getCountOfTasks();
    void addNewTask(Task);
    void completeTask(int);
    void deleteTask(int);
    QVector<Task> getTaskList();

private:
    DataBaseConnector();

    void connectToDataBase();
    void disconnectFromDataBase();

private:
    static DataBaseConnector *_singleton;
    QSqlDatabase _dataBase;

signals:

public slots:
};

#endif // DATABASE_CONNECTOR_H
