#ifndef TASK_MENU_H
#define TASK_MENU_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include "task.h"
#include "database_connector.h"

class TaskMenu : public QWidget
{
    Q_OBJECT
public:
    explicit TaskMenu(QWidget *parent = nullptr);
    ~TaskMenu();

private:
    QGridLayout *_taskMenuLayout;
    QPushButton *_addNewTaskButton;
    QVBoxLayout *_taskListLayout;

    QLineEdit *_nameLineEdit;
    QTextEdit *_descriptionTextEdit;
    QLabel *_leadTimeLabel;
    QLabel *_statusLabel;

    int _idOfCurrentTask;

private:
    QScrollArea* createTaskList();
    QWidget* createTaskInfoMenu();

signals:

public slots:
    void onNewTaskButtonClicked();
    void displayTaskInfo(Task task);
    void onNewTaskCreated();
    void onCompleteTaskClicked();
    void onDeleteTaskClicked();
    void updateTaskList();
};

#endif // TASK_MENU_H
