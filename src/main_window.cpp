#include "main_window.h"
#include "task_menu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(900,600);

    TaskMenu *taskW = new TaskMenu(this);
    setCentralWidget(taskW);


}

MainWindow::~MainWindow()
{

}
