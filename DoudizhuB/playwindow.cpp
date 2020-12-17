#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::sendDataToClientA(QString _currentData)
{
    //获取待发送数据转码为utf8后的长度
    QString length = QString::number(_currentData.toUtf8().length());
    //构造一个2位的字符串来存储length
    QString m_len;
    m_len.fill('0', 2);
    m_len.push_back(length);
    m_len = m_len.right(2);
    //合并字符串
    _currentData = m_len + _currentData;
    QByteArray ba = _currentData.toUtf8();
    this->readWriteSocketA->write(ba);
}

void MainWindow::sendDataToClientC(QString _currentData)
{
    //获取待发送数据转码为utf8后的长度
    QString length = QString::number(_currentData.toUtf8().length());
    //构造一个2位的字符串来存储length
    QString m_len;
    m_len.fill('0', 2);
    m_len.push_back(length);
    m_len = m_len.right(2);
    //合并字符串
    _currentData = m_len + _currentData;
    QByteArray ba = _currentData.toUtf8();
    this->readWriteSocketC->write(ba);
}

void MainWindow::recvMessageA()
{
    while(!readWriteSocketA->atEnd()){
        int len=QString(readWriteSocketA->read(2)).toInt();
        QString message=QString(this->readWriteSocketA->read(len));
        if(message=="begin"){
            startJiaodizhu();
        }
        else if(message=="ifDizhu"){
            decideifDizhu();
        }
        else if(message=="Dizhu1"){
            dizhu=1;
            startGame();
        }
        else if(message=="Dizhu2"){
            dizhu=2;
            startGame();
        }
        else if(message=="Dizhu3"){
            dizhu=3;
            startGame();
        }
        else if (message=="BPoker") {
            for(int i=0;i<17;i++){
                Card* temp=readPoker(i);
                B.push_back(temp);
                temp->setVisible(true);
            }
            for(int i=17;i<20;i++){
                Card* temp=readPoker(i);
                dizhupoker.push_back(temp);

            }
            for(int i=17;i<20;i++){
                Card* temp2=new Card(i+3,dizhupoker[i-17]->getValue(),this);
                dizhupoker.push_back(temp2);
                temp2->setVisible(true);
            }
        }
        else if(message=="chupai"){
            int len2=QString(readWriteSocketA->read(2)).toInt();
            len2=this->readWriteSocketA->read(len2).toInt();
            Anum-=len2;
            updatePaishu();
            last.clear();
            paiquan=1;
            for(int i=0;i<len2;i++){
                readChupai(1,i);
            }
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->label_6->setVisible(false);

            ifChupai();
            ifGameover();
        }
        else if (message=="buchu") {
            ui->label_4->setText("不出");
            ui->label_4->setVisible(true);
            if(paiquan==2){
                last.clear();
                sendDataToClientA("clear");
                sendDataToClientC("clear");
                ui->label_4->setVisible(false);
                ui->label_5->setVisible(false);
                ui->label_6->setVisible(false);
            }

            ifChupai();
        }
        else if (message=="clear") {
            last.clear();
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->label_6->setVisible(false);
        }
        else if(message=="dizhuyes"){
            ui->label_1->setText("叫");
            ui->label_1->setVisible(true);
        }
        else if(message=="dizhuno"){
            ui->label_1->setText("不叫");
            ui->label_1->setVisible(true);
        }
    }
}

Card *MainWindow::readPoker(int num)
{
    int len=QString(readWriteSocketA->read(2)).toInt();
    QString message=QString(this->readWriteSocketA->read(len));
    int data=message.toInt();
    Card* t=new Card(num,data,this);
    return t;
}

void MainWindow::recvMessageC()
{
    while(!readWriteSocketC->atEnd()){
    int len=QString(readWriteSocketC->read(2)).toInt();
    QString message=QString(this->readWriteSocketC->read(len));
    if(message=="chupai"){
        int len2=QString(readWriteSocketC->read(2)).toInt();
        len2=this->readWriteSocketC->read(len2).toInt();
        Cnum-=len2;
        updatePaishu();
        last.clear();
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);

        paiquan=3;
        for(int i=0;i<len2;i++){
            readChupai(3,i);
        }
        ifGameover();
    }
    else if (message=="buchu") {
        ui->label_6->setText("不出");
        ui->label_6->setVisible(true);
    }
    else if (message=="clear") {
        last.clear();
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
    }
    else if(message=="dizhuyes"){
        ui->label_3->setText("叫");
        ui->label_3->setVisible(true);
    }
    else if(message=="dizhuno"){
        ui->label_3->setText("不叫");
        ui->label_3->setVisible(true);
    }
    }
}


void MainWindow::readChupai(int who, int i)
{
    int len;
    QString message;
    Card* t;
    if(who==1){
        len=QString(readWriteSocketA->read(2)).toInt();
        message=QString(this->readWriteSocketA->read(len));
        t=new Card(1,i,message,this);
    }
    else if (who==3) {
        len=QString(readWriteSocketC->read(2)).toInt();
        message=QString(this->readWriteSocketC->read(len));
        t=new Card(3,i,message,this);
    }
    t->setVisible(true);
    t->update();
    last._list.push_back(t);
}


void MainWindow::decideifDizhu()
{
    ui->btn_jiao->setVisible(true);
    ui->btn_bujiao->setVisible(true);
}

void MainWindow::startGame()
{
    if(dizhu==1){
        Anum+=3;
        paiquan=1;
        updatePaishu();
    }
    else if(dizhu==2){
        Bnum+=3;
        paiquan=2;
        updatePaishu();
        for(int i=0;i<3;i++){
            B.push_back(dizhupoker[i]);
            dizhupoker[i]->setVisible(true);
        }
        ifChupai();
    }
    else if(dizhu==3){
        Cnum+=3;
        paiquan=3;
        updatePaishu();
    }
    ui->label_1->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);

    for(int i=3;i<6;i++){
        dizhupoker[i]->isShow=true;
        dizhupoker[i]->update();
    }
}




void MainWindow::on_btn_jiao_clicked()
{
    sendDataToClientA("dizhuyes");
    sendDataToClientC("dizhuyes");
    ui->label_2->setText("叫");
    ui->label_2->setVisible(true);
    ui->btn_jiao->setVisible(false);
    ui->btn_bujiao->setVisible(false);
}

void MainWindow::on_btn_bujiao_clicked()
{
    sendDataToClientA("dizhuno");
    sendDataToClientC("dizhuno");
    ui->label_2->setText("不叫");
    ui->label_2->setVisible(true);
    ui->btn_jiao->setVisible(false);
    ui->btn_bujiao->setVisible(false);
}
