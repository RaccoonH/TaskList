#include "task_menu.h"
#include "task_widget.h"
#include <QAction>
#include <QTextEdit>
#include <QLineEdit>
#include <QDebug>
#include "new_task_window.h"

TaskMenu::TaskMenu(QWidget *parent) : QWidget(parent)
{
    _taskMenuLayout = new QGridLayout(this);
    setLayout(_taskMenuLayout);
    _taskMenuLayout->setMargin(0);

    _addNewTaskButton = new QPushButton("Добавить задачу", this);
    _taskMenuLayout->addWidget(_addNewTaskButton);
    connect(_addNewTaskButton,&QPushButton::clicked, this, &TaskMenu::onNewTaskButtonClicked);

    _taskMenuLayout->addWidget(createTaskList(),1,0);
    _taskMenuLayout->addWidget(createTaskInfoMenu(),0,1,2,1);
}

QScrollArea* TaskMenu::createTaskList()
{
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *taskListWidget = new QWidget(scrollArea);
    _taskListLayout = new QVBoxLayout(taskListWidget);

    _taskListLayout->setAlignment(Qt::AlignTop);
    _taskListLayout->setSpacing(2);
    _taskListLayout->setMargin(0);
    _taskListLayout->setSizeConstraint(QLayout::SetFixedSize);

    taskListWidget->setMaximumWidth(225);
    taskListWidget->setMinimumWidth(225);
    scrollArea->setMaximumWidth(225);
    scrollArea->setMinimumWidth(225);
    scrollArea->setWidget(taskListWidget);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //test code delete later
    Task task("test", "description", 30, 5);
    TaskWidget *taskWidget = new TaskWidget(task, this);
    _taskListLayout->addWidget(taskWidget);

    return scrollArea;
}

QWidget* TaskMenu::createTaskInfoMenu()
{
    QWidget *taskInfoWidget = new QWidget(this);
    QVBoxLayout *taskInfoLayout = new QVBoxLayout(taskInfoWidget);

    taskInfoLayout->setAlignment(Qt::AlignTop);
    taskInfoLayout->setMargin(0);

    _nameLineEdit = new QLineEdit(taskInfoWidget);
    taskInfoLayout->addWidget(_nameLineEdit);

    _descriptionTextEdit = new QTextEdit(taskInfoWidget);
    taskInfoLayout->addWidget(_descriptionTextEdit);

    _leadTimeLabel = new QLabel("Время выполнения: test",taskInfoWidget);
    taskInfoLayout->addWidget(_leadTimeLabel);

    _statusLabel = new QLabel("Статус: test", taskInfoWidget);
    taskInfoLayout->addWidget(_statusLabel);

    //this button must be perform and performAgain if task is already done
    QPushButton *performTaskButton = new QPushButton("Выполнить задачу", taskInfoWidget);
    taskInfoLayout->addWidget(performTaskButton);

    QPushButton *deleteTaskButton = new QPushButton("Удалить задачу", taskInfoWidget);
    taskInfoLayout->addWidget(deleteTaskButton);

    return taskInfoWidget;
}

void TaskMenu::displayTaskInfo(Task task)
{
    _nameLineEdit->setText(task.getName());
    _descriptionTextEdit->setText(task.getDescription());
    _leadTimeLabel->setText("Время выполнения: " + QString::number(task.getLeadTime()));
    if(task.isDone())
    {
        _statusLabel->setText("Статус: Выполнено");
    }
    else
    {
        _statusLabel->setText("Статус: Не выполнено");
    }
}

void TaskMenu::onNewTaskCreated(Task task)
{
    TaskWidget *taskWidget = new TaskWidget(task, this);
    _taskListLayout->addWidget(taskWidget);
}

void TaskMenu::onDeleteTaskClicked()
{

}

void TaskMenu::onNewTaskButtonClicked()
{
    NewTaskWindow newTaskWindow(this);
    newTaskWindow.exec();
}

TaskMenu::~TaskMenu()
{

}
