#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("斗地主 玩家A");
    this->setWindowIcon(QIcon(":/pic/dizhu.png"));
    this->setFixedSize(1400,800);
    ui->pushButton->setGeometry(600,580,200,100);
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
    ui->label_1->setGeometry(650,400,200,100);
    ui->label_2->setGeometry(200,200,200,100);
    ui->label_3->setGeometry(1100,200,200,100);

    ui->label_4->setGeometry(650,450,200,100);
    ui->label_5->setGeometry(200,250,200,100);
    ui->label_6->setGeometry(1100,250,200,100);

    ui->label_1->setStyleSheet("color:white");
    ui->label_2->setStyleSheet("color:white");
    ui->label_3->setStyleSheet("color:white");
    ui->label_4->setStyleSheet("color:white");
    ui->label_5->setStyleSheet("color:white");
    ui->label_6->setStyleSheet("color:white");

    setFocusPolicy(Qt::StrongFocus);
    connect(this,SIGNAL(tryIfbegin()),SLOT(ifBegin()));
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

void MainWindow::initServerA()
{
    this->listenSocketB =new QTcpServer;
    this->listenSocketB->listen(QHostAddress::Any,8888);
    QObject::connect(this->listenSocketB,SIGNAL(newConnection()),this,SLOT(acceptConnectionB()));
    this->listenSocketC =new QTcpServer;
    this->listenSocketC->listen(QHostAddress::Any,8889);
    QObject::connect(this->listenSocketC,SIGNAL(newConnection()),this,SLOT(acceptConnectionC()));
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

void MainWindow::acceptConnectionB()
{
    this->readWriteSocketB =this->listenSocketB->nextPendingConnection();
    connect(this->readWriteSocketB,SIGNAL(readyRead()),this,SLOT(recvMessageB()));
    connect_AB=true;
    emit tryIfbegin();
}



void MainWindow::acceptConnectionC()
{
    this->readWriteSocketC =this->listenSocketC->nextPendingConnection();
    connect(this->readWriteSocketC,SIGNAL(readyRead()),this,SLOT(recvMessageC()));
    connect_AC=true;
    emit tryIfbegin();
}





void MainWindow::ifBegin()
{
    if(connect_AB&&connect_AC&&connect_BC){
        sendDataToClientB("begin");
        sendDataToClientC("begin");

        startJiaodizhu();
    }
}

void MainWindow::startJiaodizhu()
{
    ui->btn_jiao->setVisible(false);
    ui->btn_bujiao->setVisible(false);

    ifstart=true;
    update();
    ui->pushButton->setVisible(false);
    createPoker();
    createDizhu();


}




void MainWindow::on_pushButton_clicked()
{
    this->initServerA();
    ui->pushButton->setEnabled(false);
}







