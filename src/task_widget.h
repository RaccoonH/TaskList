#ifndef TASK_WIDGET_H
#define TASK_WIDGET_H

#include <QLabel>

class TaskWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TaskWidget(QWidget *parent = nullptr);

private:
    QPalette pall;

private slots:
    void onTaskWidgetClicked();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // TASK_WIDGET_H
