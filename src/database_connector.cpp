#include "database_connector.h"
#include <QFile>
#include <QDebug>

DataBaseConnector::DataBaseConnector()
{

}

DataBaseConnector * DataBaseConnector::_singleton = nullptr;

void DataBaseConnector::init()
{
//    DataBaseConnector *test = new DataBaseConnector();
//    qDebug() << test;
//    test->~DataBaseConnector();
//    qDebug() << test;

    _singleton = new DataBaseConnector();
    _singleton->connectToDataBase();
}

void DataBaseConnector::deinit()
{
    delete _singleton;
}

int DataBaseConnector::getCountOfTasks()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM TaskList_Table");
    query.exec();

    query.next();
    qDebug() << query.value(0).toInt();
    return query.value(0).toInt();
}

QVector<Task> DataBaseConnector::getTaskList()
{
    QVector<Task> vec;
    QSqlQuery query;
    query.prepare("SELECT * FROM TaskList_Table ORDER BY priority DESC");
    query.exec();

    while(query.next())
    {
        Task task;
        task.setId(query.value(0).toInt());
        task.setName(query.value(1).toString());
        task.setDescription(query.value(2).toString());
        task.setLeadTime(query.value(3).toInt());
        task.setPriority(query.value(4).toInt());
        task.setStatus(query.value(5).toBool());
        vec.push_back(task);
    }

    return vec;
}

void DataBaseConnector::addNewTask(Task task)
{
    QSqlQuery query;
    query.prepare("INSERT INTO TaskList_Table (name, description, leadTime, priority, status) VALUES (:name, :description, :leadTime, :priority, :status)");
    query.bindValue(":name", task.getName());
    query.bindValue(":description", task.getDescription());
    query.bindValue(":leadTime", task.getLeadTime());
    query.bindValue(":priority", task.getPriority());
    query.bindValue(":status", task.isDone());
    query.exec();
}

void DataBaseConnector::completeTask(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE TaskList_Table set status = '1' WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

void DataBaseConnector::completeTaskAgain(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE TaskList_Table set status = '0' WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

void DataBaseConnector::deleteTask(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM TaskList_Table WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

void DataBaseConnector::changeTask(int id, QString name, QString desc)
{
    QSqlQuery query;
    query.prepare("UPDATE TaskList_Table SET name = :name, description = :desc WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":desc", desc);
    query.exec();
}

void DataBaseConnector::connectToDataBase()
{
    _dataBase = QSqlDatabase::addDatabase("QSQLITE");
    if(QFile("TaskList_Base.db").exists())
    {
        _dataBase.setDatabaseName("TaskList_Base.db");
        _dataBase.open();
    }
    else
    {
        _dataBase.setDatabaseName("TaskList_Base.db");
        _dataBase.open();
        QSqlQuery query;
        query.exec("CREATE TABLE TaskList_Table (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name STRING, description STRING, leadTime INTEGER, priority INTEGER, status BOOLEAN);");
        _dataBase.open();
    }
}

DataBaseConnector * DataBaseConnector::dataBase()
{
    return _singleton;
}
