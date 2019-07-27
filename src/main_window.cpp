#include "main_window.h"
#include "task_menu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(900,600);

    TaskMenu *taskMenu = new TaskMenu(this);
    setCentralWidget(taskMenu);


}

MainWindow::~MainWindow()
{

}
