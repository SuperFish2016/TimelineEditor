#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>


class TimelineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimelineWidget(QWidget *parent = nullptr);
    ~TimelineWidget();

};

#endif // MAINWINDOW_H
