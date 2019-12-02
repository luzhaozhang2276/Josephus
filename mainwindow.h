#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>

//#include "josephus.h"
#include "josephusthread.h"

#define CENTER_POINT_X 400
#define CENTER_POINT_Y 400
#define RADIUS 200
#define RADIUS_NODE 20

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initWindow();

    void showLCD(int);
    void showJosephus();

signals:
    void sendmsg(int, int);

private slots:
    // 槽函数
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);
    void on_MainWindow_toolButtonStyleChanged(const Qt::ToolButtonStyle &toolButtonStyle);

    void on_pushButton_2_clicked();
    void on_pushButton_clicked(bool checked);
    void on_pushButton_3_clicked();

    void on_lineEdit_initial_value_returnPressed();
    void on_lineEdit_circulate_value_returnPressed();
    void on_lineEdit_start_value_returnPressed();

    void paintEvent(QPaintEvent*);

    void on_pushButton_configuration_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_pause_clicked();
    void on_pushButton_quit_clicked();

private:
    Ui::MainWindow *ui;
    QAction *openAction;
//    Josephus jose;
    JosephusThread *josethread;
    int paintflag;
    std::vector<int> *pVector;
    int draw_count;
};
#endif // MAINWINDOW_H
