#include "task_widget.h"

TaskWidget::TaskWidget(Task task, TaskMenu *parent) : QLabel(parent)
{
    _task = task;
    setText(task.getName());
    setMinimumSize(200,100);
    setMaximumSize(200,100);
    setFrameShape(QFrame::Box);

    if(task.isDone())
    {
        _pall.setColor(QPalette::Window,Qt::green);
        setPalette(_pall);
        setAutoFillBackground(true);
    }
    connect(this, &TaskWidget::clicked, parent, &TaskMenu::displayTaskInfo);
}

//color change not working yet
void TaskWidget::onTaskWidgetClicked()
{
    _pall.setColor(QPalette::Window,Qt::gray);
    setPalette(_pall);
    setAutoFillBackground(true);
}

void TaskWidget::mousePressEvent(QMouseEvent* event)
{
    emit clicked(_task);
}
