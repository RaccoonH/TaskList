#include "task_widget.h"

TaskWidget::TaskWidget(QWidget *parent) : QLabel(parent)
{
    setText("task");
    setMinimumSize(200,100);
    setMaximumSize(200,100);
    setFrameShape(QFrame::Box);

    connect(this,SIGNAL(clicked()),this,SLOT(onTaskWidgetClicked()));
}

void TaskWidget::onTaskWidgetClicked()
{
    pall.setColor(QPalette::Window,Qt::gray);
    setPalette(pall);
    setAutoFillBackground(true);
}

void TaskWidget::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
