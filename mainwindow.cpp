#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QCoreApplication>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>
#include <QInputDialog>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QFileDialog>
#include <QFile>

// todo: 4.可视化箭头;5.存档与读档

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();

    josethread = new JosephusThread(this);
    connect(josethread, &JosephusThread::sendValue, this, &MainWindow::showJosephus);
    connect(josethread, &JosephusThread::isDone, this, &MainWindow::on_pushButton_quit_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    ui->lineEdit_initial_value->setValidator(new QIntValidator(0,99,this));
    ui->lineEdit_circulate_value->setValidator(new QIntValidator(0,99,this));
    ui->lineEdit_start_value->setValidator(new QIntValidator(0,99,this));
    /********************** title ****************************/
    setWindowTitle(tr("Main Window"));

    /********************** statusbar ****************************/
    //    ui->statusbar->setSizeGripEnabled(false);
    //    QLabel *normal = new QLabel("输入参数",this);
    //    ui->statusbar->addWidget(normal);
    ui->statusbar->showMessage(tr("输入参数"), 5000);
    QLabel *version = new QLabel(this);
    version->setText( tr("<a href=\"https://github.com/luzhaozhang2276/Josephus\">github </a>"));
    version->setOpenExternalLinks(true);
    ui->statusbar->addPermanentWidget(version);

    /********************** statusbar ****************************/
    //    QToolBar *toolBar = addToolBar("工具栏");
    //    toolBar->addAction(paction);
    //    QMenuBar *pmenuBar = menuBar();
    //    QMenu *pmenu = pmenuBar->addMenu("参数");
    //    QAction *inital_action = pmenu->addAction("人数");
    //    QAction *circul_action = pmenu->addAction("循环");

    //    connect(inital_action, &QAction::triggered,
    //            [=]()
    //    {
    //        QInputDialog input(this);
    //        input.setWindowTitle("参数");
    //        input.setLabelText("输入人数:");
    //        input.setInputMode(QInputDialog::IntInput);
    //        if (input.exec() == QInputDialog::Accepted)
    //        {
    //            josethread->setInitialValue(input.intValue());
    //            qDebug() << josethread->getInitialValue();
    //        }
    //    }
    //    );

    //    connect(circul_action, &QAction::triggered,
    //            [=]()
    //    {
    //        QInputDialog input(this);
    //        input.setWindowTitle("参数");
    //        input.setLabelText("循环参数:");
    //        input.setInputMode(QInputDialog::IntInput);
    //        if (input.exec() == QInputDialog::Accepted)
    //        {
    //            josethread->setInitialValue(input.intValue());
    //            qDebug() << josethread->getInitialValue();
    //        }
    //    }
    //    );
}


void MainWindow::on_lineEdit_initial_value_editingFinished()
{
    QString i = ui->lineEdit_initial_value->text();
    initial_value_main_ = i.toInt();
}

void MainWindow::on_lineEdit_circulate_value_editingFinished()
{
    QString i = ui->lineEdit_circulate_value->text();
    circulate_value_main_ = i.toInt();
}

void MainWindow::on_lineEdit_start_value_editingFinished()
{
    QString i = ui->lineEdit_start_value->text();
    start_value_main_ = i.toInt();
}

void MainWindow::on_pushButton_configuration_clicked()
{
    drawVector.clear();
    josethread->setInitialValue(initial_value_main_);
    josethread->setCirculaValue(circulate_value_main_);
    josethread->setStartValue(start_value_main_);
    qDebug() << "人数: " << josethread->getInitialValue();
    qDebug() << "参数: " << josethread->getCircluaValue();
    qDebug() << "起点: " << josethread->getStartValue();
    MainWindow::repaint();
}

void MainWindow::on_pushButton_start_clicked()
{
    runflag = true;
    if (loadflag)
        loadflag = false;
    else
        drawVector.clear();
    josethread->start();
    josethread->setStatus(true);
    josethread->setStop(false);
    MainWindow::repaint();
}

void MainWindow::on_pushButton_pause_clicked()
{
    QString final;
    for (std::vector<int>::size_type i=0;i<drawVector.size();i++)
        final += " " + QString::number(drawVector.at(i));
    ui->label_final->setText(final);

    bool flag = !josethread->getStatus();
    qDebug() << "取反" << flag;
    josethread->setStatus(flag);
}

void MainWindow::on_pushButton_quit_clicked()
{
    QString final;
    for (std::vector<int>::size_type i=0;i<drawVector.size();i++)
        final += " " + QString::number(drawVector.at(i));
    ui->label_final->setText(final);

    josethread->setRemainValue(0);
    josethread->setStatus(true);
    josethread->setStop(true);
    QMessageBox::information(this,"保存结果","请保存结果");
    savefile();
    stopThread();
    drawVector.clear();
}

void MainWindow::on_pushButton_savefile_clicked()
{
    savefile();
}

void MainWindow::on_pushButton_loadfile_clicked()
{
    loadflag = true;
    initVector.clear();
    loadfile();
    josethread->setRemainValue(initVector.size()-3);
    josethread->setInitialValue(initVector.at(0));
    josethread->setCirculaValue(initVector.at(1));
    josethread->setStartValue(initVector.at(2));

    ui->lineEdit_initial_value->setText(QString::number(josethread->getInitialValue()));
    ui->lineEdit_circulate_value->setText(QString::number(josethread->getCircluaValue()));
    ui->lineEdit_start_value->setText(QString::number(josethread->getStartValue()));

    drawVector.clear();
    for (std::vector<int>::size_type i=3;i<initVector.size();i++) {
        drawVector.emplace_back(initVector.at(i));
    }

    MainWindow::repaint();
    qDebug() << "load success: " << initVector.size();
}

void MainWindow::savefile()
{
    QString filename = QFileDialog::getSaveFileName(
                this, tr("save data"),
                "../", tr("txt (*.txt)"));

    if(filename.isEmpty())
    {
        QMessageBox::information(this,"Error","请选择保存文件路径!");
        return;
    }

    QFile *file = new QFile;
    file->setFileName(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream s_output(file);

    s_output << initial_value_main_ << endl;
    s_output << circulate_value_main_ << endl;
    s_output << start_value_main_ << endl;

    for (std::vector<int>::size_type i=0;i<drawVector.size();i++)
    {
        s_output << drawVector.at(i) << endl;
    }
    qDebug() << "save success!";

    file->close();
    delete(file);
}

void MainWindow::loadfile()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("open data"),
                "../", tr("txt (*.txt)"));

    if (filename.isEmpty())
    {
        QMessageBox::information(this,"Error","Please select a txt");
        return;
    }

    QFile *file = new QFile;
    file->setFileName(filename);
    file->open(QIODevice::ReadOnly);

    //    int config_count = 3;
    while (!file->atEnd())
    {
        QByteArray line = file->readLine();
        QString str(line);
        initVector.emplace_back(str.toInt());

        //        switch (config_count) {
        //        case 1:
        //            qDebug() << "initial_value: " << str.toInt() << endl;
        //            break;
        //        case 2:
        //            qDebug() << "circulate_value: " << str.toInt() << endl;
        //            break;
        //        case 3:
        //            qDebug() << "start_value: " << str.toInt() << endl;
        //            break;
        //        default:
        //            qDebug() << str.toInt();
        //            break;
        //        }
        //        config_count--;
    }

    file->close();
    delete file;

    //    for (auto &p : initVector)
    //        qDebug() << "initVector: " << p;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    // 绘制圆
    int count = josethread->getInitialValue();
    painter.drawEllipse(QPointF(CENTER_POINT_X, CENTER_POINT_Y), RADIUS, RADIUS);
    painter.setBrush(QColor(255, 255, 255));
    for (int i=0;i<count;++i) {
        QPointF insertPoint(QPointF(RADIUS*qCos(2*M_PI/count*i)+CENTER_POINT_X, RADIUS*qSin(2*M_PI/count*i)+CENTER_POINT_Y));
        painter.drawEllipse(insertPoint, RADIUS_NODE, RADIUS_NODE);
        painter.drawText(insertPoint.x()-4.0,insertPoint.y()+5.0, QString::number(i+1));
    }

    if (runflag)
    {
        // 显示当前删除的元素
        painter.setBrush(QColor(255, 160, 90));
        int id = 0;
        for (std::vector<int>::size_type i=0;i<drawVector.size();i++) {
            id = drawVector.at(i);
            //                qDebug() << "draw: " << id;
            id--;
            QPointF insertPoint(QPointF(RADIUS*qCos(2*M_PI/count*id)+CENTER_POINT_X, RADIUS*qSin(2*M_PI/count*id)+CENTER_POINT_Y));
            painter.drawEllipse(insertPoint, RADIUS_NODE, RADIUS_NODE);
        }
    }

    painter.end();
}

void MainWindow::showJosephus(int n)
{
    if (runflag){
        qDebug() << "showJosephus() :" << n;
        drawVector.emplace_back(n);
        repaint();
    }
    else
        repaint();
}

void MainWindow::stopThread()
{
    runflag = false;
    josethread->quit();
    drawVector.clear();
    repaint();
    qDebug() << "thread closed!";
}



void MainWindow::on_horizontalSlider_sliderReleased()
{
    int speed = ui->horizontalSlider->value();
    josethread->setSpeedValue(speed);
}
