#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::createDizhu()
{
    srand((unsigned)time(0));
    dizhu=rand()%3+1;
    switch(dizhu){
    case 1:
        decideifDizhu();
        break;
    case 2:
        sendDataToClientB("ifDizhu");
        break;
    case 3:
        sendDataToClientC("ifDizhu");
        break;
    }

}

void MainWindow::createPoker()
{
    int i,data[54],random;
    srand(unsigned(time(NULL)));
    for(i=0;i<54;++i)
    {
        data[i]=i;
    }
    for(i=0;i<54;++i)
    {
        random=i+rand()%(54-i);
        std::swap(data[i],data[random]);
    }
    for(i=0;i<17;i++){
        for(int j=0;j<16;j++){
            if(data[j]>data[j+1]){
                std::swap(data[j],data[j+1]);
            }
            if(data[j+17]>data[j+18]){
                std::swap(data[j+17],data[j+18]);
            }
            if(data[j+34]>data[j+35]){
                std::swap(data[j+34],data[j+35]);
            }
        }
    }
    for(i=0;i<17;i++){
        Card* temp=new Card(i,data[i],this);
        A.push_back(temp);
    }
    for(i=17;i<34;i++){
        Card* temp=new Card(i-17,data[i],this);
        B.push_back(temp);
    }
    for(i=34;i<51;i++){
        Card* temp=new Card(i-34,data[i],this);
        C.push_back(temp);
    }
    for(i=51;i<54;i++){
        Card* temp=new Card(i-34,data[i],this);
        dizhupoker.push_back(temp);
    }
    for(i=51;i<54;i++){
        Card* temp=new Card(i-31,data[i],this);
        dizhupoker.push_back(temp);
        temp->setVisible(true);
    }
    for(i=0;i<17;i++){
        A[i]->setVisible(true);
    }
    sendDataToClientB("BPoker");
    for(i=17;i<34;i++){
        QString s;
        s.fill('0', 2);
        s.push_back(QString::number(data[i]));
        s=s.right(2);
        sendDataToClientB(s);
    }
    for(i=51;i<54;i++){
        QString s;
        s.fill('0', 2);
        s.push_back(QString::number(data[i]));
        s=s.right(2);
        sendDataToClientB(s);
    }
    sendDataToClientC("CPoker");
    for(i=34;i<51;i++){
        QString s;
        s.fill('0', 2);
        s.push_back(QString::number(data[i]));
        s=s.right(2);
        sendDataToClientC(s);
    }
    for(i=51;i<54;i++){
        QString s;
        s.fill('0', 2);
        s.push_back(QString::number(data[i]));
        s=s.right(2);
        sendDataToClientC(s);
    }
}




void MainWindow::sendDataToClientB(QString _currentData)
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
    this->readWriteSocketB->write(ba);

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

void MainWindow::recvMessageB()
{
    while(!readWriteSocketB->atEnd()){
        int len=QString(readWriteSocketB->read(2)).toInt();
        QString message=QString(this->readWriteSocketB->read(len));
        if(message=="begin"){
            connect_BC=true;
            emit tryIfbegin();
        }
        else if(message=="dizhuyes"){
            ifBdecided=true;
            ifByes=true;
            ui->label_2->setText("叫");
            ui->label_2->setVisible(true);
            if(!ifCdecided){
                sendDataToClientC("ifDizhu");
            }
            else{
                dizhu=2;
                sendDataToClientB("Dizhu2");
                sendDataToClientC("Dizhu2");
                startGame();
            }
        }
        else if(message=="dizhuno"){
            ifBdecided=true;
            ifByes=false;
            ui->label_2->setText("不叫");
            ui->label_2->setVisible(true);
            if(!ifCdecided){
                sendDataToClientC("ifDizhu");
            }
            else{
                if(ifAyes){
                    dizhu=1;
                    sendDataToClientB("Dizhu1");
                    sendDataToClientC("Dizhu1");
                    startGame();
                }
                else{
                    dizhu=3;
                    sendDataToClientB("Dizhu3");
                    sendDataToClientC("Dizhu3");
                    startGame();
                }
            }
        }
        else if(message=="chupai"){
            int len2=QString(readWriteSocketB->read(2)).toInt();
            len2=this->readWriteSocketB->read(len2).toInt();
            Bnum-=len2;
            updatePaishu();
            ifGameover();
            last.clear();
            paiquan=2;
            for(int i=0;i<len2;i++){
                readChupai(2,i);
            }
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->label_6->setVisible(false);


        }
        else if (message=="buchu") {
            ui->label_5->setText("不出");
            ui->label_5->setVisible(true);
        }
        else if(message=="clear"){
            last.clear();
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->label_6->setVisible(false);
        }
    }
}

void MainWindow::readChupai(int who,int i)
{
    int len;
    QString message;
    Card* t;
    if(who==2){
        len=QString(readWriteSocketB->read(2)).toInt();
        message=QString(this->readWriteSocketB->read(len));
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

void MainWindow::recvMessageC()
{
    while(!readWriteSocketC->atEnd()){
        int len=QString(readWriteSocketC->read(2)).toInt();
        QString message=QString(this->readWriteSocketC->read(len));
        if(message=="begin"){
            connect_AC=true;
            emit tryIfbegin();
        }
        else if(message=="dizhuyes"){
            ifCdecided=true;
            ifCyes=true;
            ui->label_3->setText("叫");
            ui->label_3->setVisible(true);
            if(ifAdecided==false){
                decideifDizhu();
            }
            else{
                dizhu=3;
                sendDataToClientB("Dizhu3");
                sendDataToClientC("Dizhu3");
                startGame();
            }
        }
        else if(message=="dizhuno"){
            ifCdecided=true;
            ifCyes=false;
            ui->label_3->setText("不叫");
            ui->label_3->setVisible(true);
            if(!ifAdecided){
                decideifDizhu();
            }
            else{
                if(ifByes){
                    dizhu=2;
                    sendDataToClientB("Dizhu2");
                    sendDataToClientC("Dizhu2");
                    startGame();
                }
                else{
                    dizhu=1;
                    sendDataToClientB("Dizhu1");
                    sendDataToClientC("Dizhu1");
                    startGame();
                }
            }
        }
        else if(message=="chupai"){
            int len2=QString(readWriteSocketC->read(2)).toInt();
            len2=this->readWriteSocketC->read(len2).toInt();
            Cnum-=len2;
            updatePaishu();
            ifGameover();
            last.clear();
            paiquan=3;
            for(int i=0;i<len2;i++){
                readChupai(3,i);
            }
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->label_6->setVisible(false);

            ifChupai();

        }
        else if (message=="buchu") {
            ui->label_6->setText("不出");
            ui->label_6->setVisible(true);
            if(paiquan==1){
                last.clear();
                sendDataToClientB("clear");
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
    }
}

void MainWindow::decideifDizhu()
{
    ui->btn_jiao->setVisible(true);
    ui->btn_bujiao->setVisible(true);
}

void MainWindow::startGame()
{
    if(dizhu==1){
        for(int i=0;i<3;i++){
            A.push_back(dizhupoker[i]);
            dizhupoker[i]->setVisible(true);
        }

        Anum+=3;
        paiquan=1;
        updatePaishu();
        ifChupai();
    }
    else if(dizhu==2){
        Bnum+=3;
        paiquan=2;
        updatePaishu();
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
    ifAdecided=true;
    ifAyes=true;
    ui->label_1->setText("叫");
    ui->label_1->setVisible(true);
    sendDataToClientB("dizhuyes");
    sendDataToClientC("dizhuyes");

    if(ifBdecided==false){
        sendDataToClientB("ifDizhu");
    }
    else {
        dizhu=1;
        sendDataToClientB("Dizhu1");
        sendDataToClientC("Dizhu1");
        startGame();
    }
    ui->btn_jiao->setVisible(false);
    ui->btn_bujiao->setVisible(false);

}

void MainWindow::on_btn_bujiao_clicked()
{
    ifAdecided=true;
    ifAyes=false;
    ui->label_1->setText("不叫");
    ui->label_1->setVisible(true);
    sendDataToClientB("dizhuno");
    sendDataToClientC("dizhuno");

    if(ifBdecided==false){
        sendDataToClientB("ifDizhu");
    }
    else {
        if(ifCyes==true){
            dizhu=3;
            sendDataToClientB("Dizhu3");
            sendDataToClientC("Dizhu3");
            startGame();
        }
        else {
            dizhu=2;
            sendDataToClientB("Dizhu2");
            sendDataToClientC("Dizhu2");
            startGame();
        }
    }
    ui->btn_jiao->setVisible(false);
    ui->btn_bujiao->setVisible(false);
    ui->btn_chupai->setVisible(false);
    ui->btn_buchu->setVisible(false);
    ui->btn_exit->setVisible(false);
    ui->btn_again->setVisible(false);
}
