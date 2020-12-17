#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("斗地主 玩家C");
    this->setWindowIcon(QIcon(":/pic/dizhu.png"));
    this->setFixedSize(1400,800);
    ui->pushButton->setGeometry(600,580,200,100);
    setFocusPolicy(Qt::StrongFocus);
    ui->btn_jiao->setVisible(false);
    ui->btn_bujiao->setVisible(false);
    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);

    ui->btn_jiao->setGeometry(200,300,200,100);
    ui->btn_bujiao->setGeometry(1000,300,200,100);
    ui->label_3->setGeometry(650,400,200,100);
    ui->label_1->setGeometry(200,200,200,100);
    ui->label_2->setGeometry(1100,200,200,100);
    ui->label_6->setGeometry(650,450,200,100);
    ui->label_4->setGeometry(200,250,200,100);
    ui->label_5->setGeometry(1100,250,200,100);

    ui->label_1->setStyleSheet("color:white");
    ui->label_2->setStyleSheet("color:white");
    ui->label_3->setStyleSheet("color:white");
    ui->label_4->setStyleSheet("color:white");
    ui->label_5->setStyleSheet("color:white");
    ui->label_6->setStyleSheet("color:white");

    ui->btn_chupai->setGeometry(200,420,200,100);
    ui->btn_buchu->setGeometry(1000,420,200,100);
    ui->btn_chupai->setVisible(false);
    ui->btn_buchu->setVisible(false);
    ui->btn_exit->setVisible(false);
    ui->btn_again->setVisible(false);
    ui->btn_again->setGeometry(200,420,200,100);
    ui->btn_exit->setGeometry(1000,420,200,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectHostA()
{
    this->readWriteSocketA = new QTcpSocket;
    this->readWriteSocketA->connectToHost(QHostAddress("127.0.0.1"),8889);
    connect(this->readWriteSocketA,SIGNAL(readyRead()),this,SLOT(recvMessageA()));
}

void MainWindow::connectHostB()
{
    this->readWriteSocketB = new QTcpSocket;
    this->readWriteSocketB->connectToHost(QHostAddress("127.0.0.1"),8890);
    connect(this->readWriteSocketB,SIGNAL(readyRead()),this,SLOT(recvMessageB()));
}

void MainWindow::startJiaodizhu()
{
    ifstart=true;
    update();
    ui->pushButton->setVisible(false);
}



void MainWindow::paintEvent(QPaintEvent *e)
{
    if(ifstart==false){
        QPainter painter(this);
        //创建QPixmap对象
        QPixmap pix;
        //加载图片
        pix.load(":/pic/background.png");
        //绘制背景图
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
    }
    else{
        QPainter painter(this);
        //创建QPixmap对象
        QPixmap pix;
        //加载图片
        pix.load(":/pic/play2.png");
        //绘制背景图
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
    }
}





void MainWindow::on_pushButton_clicked()
{
    this->connectHostA();
    this->connectHostB();
    ui->pushButton->setEnabled(false);
}






