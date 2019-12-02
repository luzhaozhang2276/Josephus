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

// todo: 1.状态栏显示静态与动态文本;2.输入检验

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();
    pVector = new std::vector<int>;

    josethread = new JosephusThread(this);
    connect(this, SIGNAL(sendmsg(int, int)), josethread, SLOT(getValue(int, int)));
    connect(josethread, &JosephusThread::changeValue, this, &MainWindow::showLCD);
    paintflag = 0;
    draw_count = 0;
    connect(josethread, &JosephusThread::sendpVector, this, &MainWindow::showJosephus);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    /********************** title ****************************/
    setWindowTitle(tr("Main Window"));

    /********************** statusbar ****************************/
    ui->statusbar->setSizeGripEnabled(false);
    QLabel *normal = new QLabel("正常信息",this);
    ui->statusbar->addWidget(normal);
    //    ui->statusbar->showMessage(tr("临时信息"), 2000);
    QLabel *version = new QLabel(this);
    version->setText( tr("<a href=\"https://github.com/luzhaozhang2276/Josephus\">github主页</a>"));
    version->setOpenExternalLinks(true);
    ui->statusbar->addPermanentWidget(version);

    /********************** statusbar ****************************/
    //    QToolBar *toolBar = addToolBar("工具栏");
    //    toolBar->addAction(paction);
    QMenuBar *pmenuBar = menuBar();
    QMenu *pmenu = pmenuBar->addMenu("参数");
    QAction *inital_action = pmenu->addAction("人数");
    QAction *circul_action = pmenu->addAction("循环");

    connect(inital_action, &QAction::triggered,
            [=]()
    {
        QInputDialog input(this);
        input.setWindowTitle("参数");
        input.setLabelText("输入人数:");
        input.setInputMode(QInputDialog::IntInput);
        if (input.exec() == QInputDialog::Accepted)
        {
            josethread->setInitialValue(input.intValue());
            qDebug() << josethread->getInitialValue();
        }
    }
    );

    connect(circul_action, &QAction::triggered,
            [=]()
    {
        QInputDialog input(this);
        input.setWindowTitle("参数");
        input.setLabelText("循环参数:");
        input.setInputMode(QInputDialog::IntInput);
        if (input.exec() == QInputDialog::Accepted)
        {
            josethread->setInitialValue(input.intValue());
            qDebug() << josethread->getInitialValue();
        }
    }
    );
}

void MainWindow::on_pushButton_2_clicked()
{
    //    QString s = QString::number(11);
    ui->label_2->setText(tr("11"));
    QMessageBox msg;
    msg.setText("Thank you!");
    msg.exec();
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    QString  name;
    if (checked) {
        name="luzhaozhang";
        ui->label->setText(name);
    }
    else
    {
        name="";
        ui->label->setText(name);
    }
}

void MainWindow::on_lineEdit_initial_value_returnPressed()
{
    QString i = ui->lineEdit_initial_value->text();
    int number = i.toInt();
    josethread->setInitialValue(number);
    qDebug() << "人数: " << josethread->getInitialValue();
}

void MainWindow::on_lineEdit_circulate_value_returnPressed()
{
    QString i = ui->lineEdit_circulate_value->text();
    int number = i.toInt();
    josethread->setCirculaValue(number);
    qDebug() << "参数: " << josethread->getCircluaValue();
}

void MainWindow::on_lineEdit_start_value_returnPressed()
{
    QString i = ui->lineEdit_start_value->text();
    int number = i.toInt();
    josethread->setStartValue(number);
    qDebug() << "起点: " << josethread->getStartValue();
}

void MainWindow::on_pushButton_configuration_clicked()
{
    josethread->start();
    josethread->setInitialFlag(true);
    paintflag =1;
    MainWindow::repaint();
//    qDebug() << "paintflag: " << paintflag;
}

void MainWindow::on_pushButton_3_clicked()
{
    int i = 3, j = 4;
    emit sendmsg(i, j);
}

void MainWindow::showLCD(int n)
{
    ui->lcdNumber->display(n);
}

void MainWindow::on_pushButton_start_clicked()
{

}

void MainWindow::on_pushButton_pause_clicked()
{

}

void MainWindow::on_pushButton_quit_clicked()
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (josethread->getInitialFlag())
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
            painter.drawText(insertPoint.x()-4.0,insertPoint.y()+5.0, QString::number(i+1,RADIUS_NODE));
        }

        if (paintflag == 1)
        {
            painter.setBrush(QColor(255, 160, 90));
            int id = 0;
            for (int i=0;i<draw_count;i++) {
                id = pVector->at(i);
                QPointF insertPoint(QPointF(RADIUS*qCos(2*M_PI/count*id)+CENTER_POINT_X, RADIUS*qSin(2*M_PI/count*id)+CENTER_POINT_Y));
                painter.drawEllipse(insertPoint, RADIUS_NODE, RADIUS_NODE);
            }
            paintflag = 0;
        }
        painter.end();
    }
}

void MainWindow::showJosephus()
{
    qDebug() << "showJosephus()";
    size_t size = pVector->size();
    qDebug() << "size: " << size << " , " << pVector->at(0);
    for (size_t i = 0; i < size; ++i)
    {
        draw_count++;
        repaint();
        QTime t;
        t.start();
        while(t.elapsed()<1000)
            QCoreApplication::processEvents();
    }

}
