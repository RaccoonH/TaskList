#ifndef TASK_WIDGET_H
#define TASK_WIDGET_H

#include <QLabel>
#include "task_menu.h"

class TaskWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TaskWidget(Task task,TaskMenu *parent = nullptr);

private:
    QPalette _pall;
    Task _task;

private slots:
    void onTaskWidgetClicked();

signals:
    void clicked(Task);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // TASK_WIDGET_H
