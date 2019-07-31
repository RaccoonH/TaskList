#include "task.h"

Task::Task()
{

}

Task::Task(int id, QString name, QString description, int leadTime, int priority)
{
    _id = id;
    _name = name;
    _description = description;
    _leadTime = leadTime;
    _priority = priority;
    _status = false;
}

void Task::setName(QString name)
{
    _name = name;
}

void Task::setDescription(QString description)
{
    _description = description;
}

void Task::setLeadTime(int time)
{
    _leadTime = time;
}

void Task::setPriority(int priority)
{
    _priority = priority;
}

void Task::setStatus(bool status)
{
    _status = status;
}

QString Task::getName()
{
    return _name;
}

QString Task::getDescription()
{
    return _description;
}

int Task::getLeadTime()
{
    return _leadTime;
}

int Task::getPriority()
{
    return _priority;
}

bool Task::isDone()
{
    return _status;
}

int Task::getId()
{
    return _id;
}

void Task::setId(int id)
{
    _id = id;
}
