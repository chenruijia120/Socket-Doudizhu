#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_btn_chupai_clicked()
{
    CardCombine mine;
    for(int i=0;i<B.size();i++){
        if(B[i]->isSelected&&B[i]->isVisible()){
            mine._list.push_back(B[i]);
        }
    }
    if(mine.compareTo(last)==CardCombine::CompareRes::Larger){
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        sendDataToClientA("chupai");
        sendDataToClientC("chupai");
        sendDataToClientA(QString::number(mine._list.size()));
        sendDataToClientC(QString::number(mine._list.size()));
        last.clear();
        for(int i=0;i<mine._list.size();i++){
            Card *t=new Card(2,i,mine._list[i]->toString(),this);
            last._list.push_back(t);
            t->setVisible(true);
            t->update();
            mine._list[i]->setVisible(false);
            sendDataToClientA(mine._list[i]->toString());
            sendDataToClientC(mine._list[i]->toString());
        }
        paiquan=2;
        Bnum-=mine._list.size();
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
    sendDataToClientA("buchu");
    sendDataToClientC("buchu");
    ui->label_5->setText("不出");
    ui->label_5->setVisible(true);
    ui->btn_buchu->setVisible(false);
    ui->btn_chupai->setVisible(false);
}

void MainWindow::ifGameover()
{
    if(Bnum==0){
        QMessageBox::information(this,"Result","You win!");
        Gameover();
    }
    else if(Anum==0&&dizhu==1){
        QMessageBox::information(this,"Result","You lose!");
        Gameover();
    }
    else if(Cnum==0&&dizhu==3){
        QMessageBox::information(this,"Result","You lose!");
        Gameover();
    }
    else if(Anum==0||Cnum==0){
        QMessageBox::information(this,"Result","You win!");
        Gameover();
    }
}

void MainWindow::ifChupai()
{
    ui->btn_chupai->setVisible(true);
    ui->btn_buchu->setVisible(true);
    if(paiquan==2){
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


    for(int i=0;i<B.size();i++){
        B[i]->setVisible(false);
    }
    for(int i=0;i<dizhupoker.size();i++){
        dizhupoker[i]->setVisible(false);
    }

    B.clear();
    dizhupoker.clear();
    last.clear();
    Anum=17;
    Bnum=17;
    Cnum=17;
    paiquan=0;
    sendDataToClientA("begin");
    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);

    ui->btn_jiao->setVisible(false);
    ui->btn_bujiao->setVisible(false);
    ui->btn_chupai->setVisible(false);
    ui->btn_buchu->setVisible(false);
    ui->btn_exit->setVisible(false);
    ui->btn_again->setVisible(false);
}


