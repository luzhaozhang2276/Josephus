#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    setWindowTitle(tr("Main Window"));

    ui->statusbar->setSizeGripEnabled(false);

    QLabel *normal = new QLabel("正常信息",this);
    ui->statusbar->addWidget(normal);
    //    ui->statusbar->showMessage(tr("临时信息"), 2000);

    QLabel *version = new QLabel(this);
    //    version->setFrameStyle(QFrame::Box | QFrame::Sunken);
    version->setText( tr("<a href=\"https://github.com/luzhaozhang2276\">github主页</a>"));
    //    version->setText("永久信息");
    version->setOpenExternalLinks(true);
    ui->statusbar->addPermanentWidget(version);

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
            jose.SetInitialValue(input.intValue());
            qDebug() << jose.GetInitialValue();
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
            jose.SetInitialValue(input.intValue());
            qDebug() << jose.GetInitialValue();
        }
    }
    );

    josethread = new JosephusThread(this);
    connect(this, SIGNAL(sendmsg(int, int)), josethread, SLOT(getValue(int, int)));
    connect(josethread, &JosephusThread::changeValue, this, &MainWindow::showLCD);
    josethread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_lineEdit_returnPressed()
{
    QString i = ui->lineEdit->text();
    int number = i.toInt();
    jose.SetInitialValue(number);
    qDebug() << "人数: " << jose.GetInitialValue();
}

void MainWindow::on_lineEdit_2_returnPressed()
{
    QString i = ui->lineEdit_2->text();
    int number = i.toInt();
    jose.SetCirculaValue(number);
    qDebug() << "参数: " << jose.GetCirculaValue();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);

    // 设置画刷颜色   (255, 160, 90)
//    painter.setBrush(QColor(255, 255, 255));

    // 绘制圆
    int count = 4;
    painter.drawEllipse(QPointF(300, 300), 50, 50);

    painter.setBrush(QColor(255, 255, 255));
    for (int i=0;i<count;++i) {
        QPointF insertPoint(QPointF(50*qCos(2*M_PI/count*i)+300, 50*qSin(2*M_PI/count*i)+300));
//        QEllipse ff();
        painter.drawEllipse(insertPoint, 10, 10);
        painter.drawText(insertPoint.x()-4,insertPoint.y()+5, QString::number(i+1,10));
    }
//    Qt::AlignCenter;
//    painter.drawPoint(350,300);
//    painter.drawText(350,300,tr("1"));
//    qDebug() << "*****************************************";
    painter.setBrush(QColor(255, 160, 90));
//    painter.drawEllipse(QPointF(50+300, 300), 10, 10);

    painter.end();
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
