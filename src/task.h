#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
public:
    Task();

private:
    QString _name;
    QString _description;
    int _leadTime;
    int _priority;
    bool _status;

private:
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
};

#endif // TASK_H
