#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_btn_chupai_clicked()
{
    CardCombine mine;
    for(int i=0;i<C.size();i++){
        if(C[i]->isSelected&&C[i]->isVisible()){
            mine._list.push_back(C[i]);
        }
    }
    if(mine.compareTo(last)==CardCombine::CompareRes::Larger){
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        sendDataToClientB("chupai");
        sendDataToClientA("chupai");
        sendDataToClientB(QString::number(mine._list.size()));
        sendDataToClientA(QString::number(mine._list.size()));
        last.clear();
        for(int i=0;i<mine._list.size();i++){
            Card *t=new Card(2,i,mine._list[i]->toString(),this);
            last._list.push_back(t);
            t->setVisible(true);
            t->update();
            mine._list[i]->setVisible(false);
            sendDataToClientB(mine._list[i]->toString());
            sendDataToClientA(mine._list[i]->toString());
        }
        paiquan=3;
        Cnum-=mine._list.size();
        updatePaishu();
        ifGameover();
        ui->btn_buchu->setVisible(false);
        ui->btn_chupai->setVisible(false);
    }
    else{
        QMessageBox::warning(this,"Not allowed","Your cards are not allowed!");
    }


}

void MainWindow::on_btn_buchu_clicked()
{
    sendDataToClientB("buchu");
    sendDataToClientA("buchu");
    ui->label_6->setText("不出");
    ui->label_6->setVisible(true);
    ui->btn_buchu->setVisible(false);
    ui->btn_chupai->setVisible(false);
}

void MainWindow::ifGameover()
{
    if(Cnum==0){
        QMessageBox::information(this,"Result","You win!");
        Gameover();
    }
    else if(Bnum==0&&dizhu==2){
        QMessageBox::information(this,"Result","You lose!");
        Gameover();
    }
    else if(Anum==0&&dizhu==1){
        QMessageBox::information(this,"Result","You lose!");
        Gameover();
    }
    else if(Anum==0||Bnum==0){
        QMessageBox::information(this,"Result","You win!");
        Gameover();
    }
}

void MainWindow::ifChupai()
{
    ui->btn_chupai->setVisible(true);
    ui->btn_buchu->setVisible(true);
    if(paiquan==3){
        ui->btn_buchu->setEnabled(false);
    }
    else{
        ui->btn_buchu->setEnabled(true);
    }
}

void MainWindow::updatePaishu()
{
    if(dizhu==1){
        ui->label_1->setText("地主:"+QString::number(Anum)+"张牌");
        ui->label_2->setText("农民:"+QString::number(Bnum)+"张牌");
        ui->label_3->setText("农民:"+QString::number(Cnum)+"张牌");

    }
    else if(dizhu==2){
        ui->label_2->setText("地主:"+QString::number(Bnum)+"张牌");
        ui->label_1->setText("农民:"+QString::number(Anum)+"张牌");
        ui->label_3->setText("农民:"+QString::number(Cnum)+"张牌");

    }
    else if(dizhu==3){
        ui->label_3->setText("地主:"+QString::number(Cnum)+"张牌");
        ui->label_2->setText("农民:"+QString::number(Bnum)+"张牌");
        ui->label_1->setText("农民:"+QString::number(Anum)+"张牌");

    }
}

void MainWindow::Gameover()
{
    ui->btn_chupai->setVisible(false);
    ui->btn_buchu->setVisible(false);
    ui->btn_exit->setVisible(true);
    ui->btn_again->setVisible(true);
}


void MainWindow::on_btn_exit_clicked()
{
    qApp->quit();
}

void MainWindow::on_btn_again_clicked()
{
    dizhu=0;


    for(int i=0;i<C.size();i++){
        C[i]->setVisible(false);
    }
    for(int i=0;i<dizhupoker.size();i++){
        dizhupoker[i]->setVisible(false);
    }

    C.clear();
    dizhupoker.clear();
    last.clear();
    Anum=17;
    Bnum=17;
    Cnum=17;
    paiquan=0;
    sendDataToClientA("begin");
    ui->btn_jiao->setVisible(false);
    ui->btn_bujiao->setVisible(false);
    ui->btn_chupai->setVisible(false);
    ui->btn_buchu->setVisible(false);
    ui->btn_exit->setVisible(false);
    ui->btn_again->setVisible(false);
    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
}

