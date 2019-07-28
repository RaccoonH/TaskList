#include "new_task_window.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

NewTaskWindow::NewTaskWindow(TaskMenu *parent) : QDialog(parent)
{
    resize(500,350);
    setWindowTitle("Добавить новую задачу");

    QGridLayout *layout = new QGridLayout(this);

    _nameLineEdit = new QLineEdit(this);
    _descriptionTextEdit = new QTextEdit(this);

    QLabel *leadTimeLabel = new QLabel("Время выполнения: ",this);
    _leadTimeNum = new QSpinBox(this);
    _leadTimeNum->setMinimum(1);

    QLabel *priorityLabel = new QLabel("Приоритет: ",this);
    _priorityNum = new QSpinBox(this);
    _priorityNum->setRange(1,10);

    QPushButton *applyButton = new QPushButton("Принять",this);
    connect(applyButton, &QPushButton::clicked, this, &NewTaskWindow::onApplyClicked);

    QPushButton *cancelButton = new QPushButton("Отмена",this);
    connect(cancelButton,&QPushButton::clicked, this, &NewTaskWindow::onCancelClicked);

    layout->addWidget(_nameLineEdit,1,1,1,2);
    layout->addWidget(_descriptionTextEdit,2,1,1,2);
    layout->addWidget(leadTimeLabel,3,1);
    layout->addWidget(_leadTimeNum,3,2);
    layout->addWidget(priorityLabel,4,1);
    layout->addWidget(_priorityNum,4,2);
    layout->addWidget(applyButton,5,1);
    layout->addWidget(cancelButton,5,2);

    connect(this, &NewTaskWindow::newTaskCreated, parent, &TaskMenu::onNewTaskCreated);
}

void NewTaskWindow::onApplyClicked()
{
    Task task;
    task.setName(_nameLineEdit->text());
    task.setDescription(_descriptionTextEdit->toPlainText());
    task.setLeadTime(_leadTimeNum->value());
    task.setPriority(_priorityNum->value());
    task.setStatus(false);

    emit newTaskCreated(task);

    this->close();
}

void NewTaskWindow::onCancelClicked()
{
    this->close();
}

NewTaskWindow::~NewTaskWindow()
{
    this->close();
}
