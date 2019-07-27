#include "task_menu.h"
#include "task_widget.h"
#include <QAction>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>

TaskMenu::TaskMenu(QWidget *parent) : QWidget(parent)
{
    _taskMenuLayout = new QGridLayout(this);
    setLayout(_taskMenuLayout);
    _taskMenuLayout->setMargin(0);

    _taskMenuLayout->addWidget(new QPushButton("add new task(test)",this),0,0);

    _taskMenuLayout->addWidget(createTaskList(),1,0);
    _taskMenuLayout->addWidget(createTaskInfoMenu(),0,1,2,1);
}

QScrollArea* TaskMenu::createTaskList()
{
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *taskListWidget = new QWidget(scrollArea);
    QVBoxLayout *taskListLayout = new QVBoxLayout(taskListWidget);

    taskListLayout->setAlignment(Qt::AlignTop);
    taskListLayout->setSpacing(2);
    taskListLayout->setMargin(0);
    taskListLayout->setSizeConstraint(QLayout::SetFixedSize);

    taskListWidget->setMaximumWidth(225);
    taskListWidget->setMinimumWidth(225);
    scrollArea->setMaximumWidth(225);
    scrollArea->setMinimumWidth(225);
    scrollArea->setWidget(taskListWidget);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //test code delete later
    for(int i = 0; i < 10; i++)
    {
        TaskWidget *task = new TaskWidget(this);
        taskListLayout->addWidget(task);
    }

    return scrollArea;
}

QWidget* TaskMenu::createTaskInfoMenu()
{
    QWidget *taskInfoWidget = new QWidget(this);
    QVBoxLayout *taskInfoLayout = new QVBoxLayout(taskInfoWidget);

    taskInfoLayout->setAlignment(Qt::AlignTop);
    taskInfoLayout->setMargin(0);

    QLineEdit *nameLineEdit = new QLineEdit(taskInfoWidget);
    taskInfoLayout->addWidget(nameLineEdit);

    QTextEdit *descriptionTextEdit = new QTextEdit(taskInfoWidget);
    taskInfoLayout->addWidget(descriptionTextEdit);

    QLabel *leadTimeLabel = new QLabel("Время выполнения: test",taskInfoWidget);
    taskInfoLayout->addWidget(leadTimeLabel);

    QLabel *statusLabel = new QLabel("Статус: test", taskInfoWidget);
    taskInfoLayout->addWidget(statusLabel);

    QPushButton *performTaskButton = new QPushButton("Выполнить задачу", taskInfoWidget);
    taskInfoLayout->addWidget(performTaskButton);

    QPushButton *deleteTaskButton = new QPushButton("Удалить задачу", taskInfoWidget);
    taskInfoLayout->addWidget(deleteTaskButton);

    return taskInfoWidget;
}

TaskMenu::~TaskMenu()
{

}
