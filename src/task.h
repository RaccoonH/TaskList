#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
public:
    Task();
    Task(int, QString, QString, int, int);

private:
    int _id;
    QString _name;
    QString _description;
    int _leadTime;
    int _priority;
    bool _status;

public:
    QString getName();
    void setName(QString name);
    QString getDescription();
    void setDescription(QString description);
    int getLeadTime();
    void setLeadTime(int time);
    int getPriority();
    void setPriority(int priority);
    bool isDone();
    void setStatus(bool status);
    int getId();
    void setId(int);
};

#endif // TASK_H
