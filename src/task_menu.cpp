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
    DataBaseConnector::init();

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

    QVector<Task> taskList;
    taskList = DataBaseConnector::dataBase()->getTaskList();
    for(int i = 0; i < taskList.size(); ++i)
    {
        Task task = taskList[i];
        TaskWidget *taskWidget = new TaskWidget(task, this);
        _taskListLayout->addWidget(taskWidget);
    }

    return scrollArea;
}

QWidget* TaskMenu::createTaskInfoMenu()
{
    QWidget *taskInfoWidget = new QWidget(this);
    QVBoxLayout *taskInfoLayout = new QVBoxLayout(taskInfoWidget);

    taskInfoLayout->setAlignment(Qt::AlignTop);
    taskInfoLayout->setMargin(0);

    _nameLineEdit = new QLineEdit(taskInfoWidget);
    _nameLineEdit->setText("Добро пожаловать в TaskList");
    taskInfoLayout->addWidget(_nameLineEdit);

    _descriptionTextEdit = new QTextEdit(taskInfoWidget);
    _descriptionTextEdit->setText("Нажмите на задачу из списка задач в левой части окна, или создайте новую задачу.");
    taskInfoLayout->addWidget(_descriptionTextEdit);

    _leadTimeLabel = new QLabel("",taskInfoWidget);
    taskInfoLayout->addWidget(_leadTimeLabel);

    _statusLabel = new QLabel("", taskInfoWidget);
    taskInfoLayout->addWidget(_statusLabel);

    _completeTaskButton = new QPushButton("Выполнить задачу", taskInfoWidget);
    taskInfoLayout->addWidget(_completeTaskButton);
    connect(_completeTaskButton, &QPushButton::clicked, this, &TaskMenu::onCompleteTaskClicked);

    QPushButton *applyChangesButton = new QPushButton("Принять изменения", taskInfoWidget);
    taskInfoLayout->addWidget(applyChangesButton);
    connect(applyChangesButton, &QPushButton::clicked, this, &TaskMenu::onApplyChangesClicked);

    QPushButton *deleteTaskButton = new QPushButton("Удалить задачу", taskInfoWidget);
    taskInfoLayout->addWidget(deleteTaskButton);
    connect(deleteTaskButton, &QPushButton::clicked, this, &TaskMenu::onDeleteTaskClicked);

    return taskInfoWidget;
}

void TaskMenu::displayTaskInfo(Task task)
{
    _idOfCurrentTask = task.getId();
    _nameLineEdit->setText(task.getName());
    _descriptionTextEdit->setText(task.getDescription());
    _leadTimeLabel->setText("Время выполнения: " + QString::number(task.getLeadTime()));
    if(task.isDone())
    {
        _statusLabel->setText("Статус: Выполнено");
        _completeTaskButton->setText("Выполнить задачу повторно");
    }
    else
    {
        _statusLabel->setText("Статус: Не выполнено");
        _completeTaskButton->setText("Выполнить задачу");
    }
}

void TaskMenu::onNewTaskCreated()
{
    QVector<Task> taskList;
    taskList = DataBaseConnector::dataBase()->getTaskList();
    for(int i = 0; i < taskList.size(); ++i)
    {
        Task task = taskList[i];
        TaskWidget *taskWidget = new TaskWidget(task, this);
        _taskListLayout->addWidget(taskWidget);
    }
}

void TaskMenu::updateTaskList()
{
    QLayoutItem *child;

    while ((child = _taskListLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }
    QVector<Task> taskList;
    taskList = DataBaseConnector::dataBase()->getTaskList();
    for(int i = 0; i < taskList.size(); ++i)
    {
        Task task = taskList[i];
        TaskWidget *taskWidget = new TaskWidget(task, this);
        _taskListLayout->addWidget(taskWidget);
    }
}

void TaskMenu::updateTaskInfoMenu()
{
    QVector<Task> taskList;
    taskList = DataBaseConnector::dataBase()->getTaskList();
    Task task;
    for(int i = 0; i < taskList.size(); ++i)
    {
        task = taskList[i];
        if(task.getId()==_idOfCurrentTask)
        {
            break;
        }
    }
    displayTaskInfo(task);
}

void TaskMenu::onCompleteTaskClicked()
{
    if(_statusLabel->text()=="Статус: Не выполнено")
    {
        DataBaseConnector::dataBase()->completeTask(_idOfCurrentTask);
    }
    else
    {
        DataBaseConnector::dataBase()->completeTaskAgain(_idOfCurrentTask);
    }
    updateTaskList();
    updateTaskInfoMenu();
}

void TaskMenu::onDeleteTaskClicked()
{
    DataBaseConnector::dataBase()->deleteTask(_idOfCurrentTask);
    updateTaskList();
}

void TaskMenu::onNewTaskButtonClicked()
{
    NewTaskWindow newTaskWindow(this);
    newTaskWindow.exec();
}

void TaskMenu::onApplyChangesClicked()
{
    DataBaseConnector::dataBase()->changeTask(_idOfCurrentTask, _nameLineEdit->text(), _descriptionTextEdit->toPlainText());
    updateTaskList();
}

TaskMenu::~TaskMenu()
{
    DataBaseConnector::deinit();
}
