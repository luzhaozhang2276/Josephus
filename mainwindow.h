#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>

#include "josephusthread.h"

#define CENTER_POINT_X 450
#define CENTER_POINT_Y 500
#define RADIUS 300
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

signals:
    void sendmsg(int, int);

private slots:
    // 槽函数
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);
    void on_MainWindow_toolButtonStyleChanged(const Qt::ToolButtonStyle &toolButtonStyle);

    void on_lineEdit_initial_value_editingFinished();
    void on_lineEdit_circulate_value_editingFinished();
    void on_lineEdit_start_value_editingFinished();
    void on_horizontalSlider_sliderReleased();

    void on_pushButton_configuration_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_pause_clicked();
    void on_pushButton_quit_clicked();
    void on_pushButton_savefile_clicked();
    void on_pushButton_loadfile_clicked();

    void paintEvent(QPaintEvent*);
    void showJosephus(int);
    void stopThread();
    void savefile();
    void loadfile();




private:
    Ui::MainWindow *ui;
    QAction *openAction;
    JosephusThread *josethread;
    std::vector<int> drawVector;
    std::vector<int> initVector;
    bool loadflag{false};
    bool runflag{false};
    int initial_value_main_{9};
    int circulate_value_main_{3};
    int start_value_main_{1};
};
#endif // MAINWINDOW_H
