#ifndef TASK_MENU_H
#define TASK_MENU_H

#include <QWidget>
#include <QLayout>
#include <QScrollArea>

class TaskMenu : public QWidget
{
    Q_OBJECT
public:
    explicit TaskMenu(QWidget *parent = nullptr);
    ~TaskMenu();

private:
    QGridLayout *_taskMenuLayout;
//    QVBoxLayout *_taskListLayout;
//    QWidget *_taskListWidget;
//    QVBoxLayout *_taskInfoLayout;
//    QWidget *_taskInfoWidget;
//    QScrollArea *_scrollArea;

private:
    QScrollArea* createTaskList();
    QWidget* createTaskInfoMenu();

signals:

public slots:
};

#endif // TASK_MENU_H
