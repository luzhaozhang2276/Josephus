#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

#include "josephus.h"
#include "josephusthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showLCD(int);

signals:
    void sendmsg(int, int);

private slots:
    // 槽函数
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

    void on_MainWindow_toolButtonStyleChanged(const Qt::ToolButtonStyle &toolButtonStyle);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked(bool checked);

    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

    void paintEvent(QPaintEvent*);

    void on_pushButton_3_clicked();


private:
    Ui::MainWindow *ui;
    QAction *openAction;
    Josephus jose;
    JosephusThread *josethread;
};
#endif // MAINWINDOW_H
