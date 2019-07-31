#ifndef NEW_TASK_WINDOW_H
#define NEW_TASK_WINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include "task.h"
#include "task_menu.h"

class NewTaskWindow : public QDialog
{
    Q_OBJECT
public:
    explicit NewTaskWindow(TaskMenu *parent = nullptr);
    ~NewTaskWindow();

private:
    QLineEdit *_nameLineEdit;
    QTextEdit *_descriptionTextEdit;
    QSpinBox *_leadTimeNum;
    QSpinBox *_priorityNum;

signals:
    void newTaskCreated();

public slots:
    void onApplyClicked();
    void onCancelClicked();
};

#endif // NEW_TASK_WINDOW_H
