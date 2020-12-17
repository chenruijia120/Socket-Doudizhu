#include "card.h"

Card::Card(int _num, int _value, QWidget *parent) : QWidget(parent)
{

    this->setVisible(false);
    x=x+_num*65;
    num=_num;
    int tmpS=_value%4;
    int tmpP=_value/4;
    Suit _suit;
    switch(tmpS){
    case 0:{_suit=Suit::Spade;break;}
    case 1:{_suit=Suit::Heart;break;}
    case 2:{_suit=Suit::Club;break;}
    case 3:{_suit=Suit::Diamond;break;}
    }
    Point _point;
    switch(tmpP){
    case 0:{_point=Point::Card_A;break;}
    case 1:{_point=Point::Card_2;break;}
    case 2:{_point=Point::Card_3;break;}
    case 3:{_point=Point::Card_4;break;}
    case 4:{_point=Point::Card_5;break;}
    case 5:{_point=Point::Card_6;break;}
    case 6:{_point=Point::Card_7;break;}
    case 7:{_point=Point::Card_8;break;}
    case 8:{_point=Point::Card_9;break;}
    case 9:{_point=Point::Card_10;break;}
    case 10:{_point=Point::Card_J;break;}
    case 11:{_point=Point::Card_Q;break;}
    case 12:{_point=Point::Card_K;break;}
    case 13:{_point=(_value==53?Point::Card_RK:Point::Card_BK);break;}
    }
    suit=_suit;
    point=_point;
    value=_value;
    if(num>=20){
        x=(num-20)*65+605;
        y=50;
    }
}

Card::Card(int _player, int _num, QString str, QWidget *parent) : QWidget(parent)
{
    num=_num;
    if(str[0]=="S"){
        suit=Spade;
    }
    else if (str[0]=="H") {
        suit=Heart;
    }
    else if (str[0]=="C") {
        suit=Club;
    }
    else if (str[0]=="D") {
        suit=Diamond;
    }
    if(str[1]=="A"){
        point=Point::Card_A;
    }
    else if (str[1]=="2") {
        point=Point::Card_2;
    }
    else if (str[1]=="3") {
        point=Point::Card_3;
    }
    else if (str[1]=="4") {
        point=Point::Card_4;
    }
    else if (str[1]=="5") {
        point=Point::Card_5;
    }
    else if (str[1]=="6") {
        point=Point::Card_6;
    }
    else if (str[1]=="7") {
        point=Point::Card_7;
    }
    else if (str[1]=="8") {
        point=Point::Card_8;
    }
    else if (str[1]=="9") {
        point=Point::Card_9;
    }
    else if (str[1]=="0") {
        point=Point::Card_10;
    }
    else if (str[1]=="J") {
        point=Point::Card_J;
    }
    else if (str[1]=="Q") {
        point=Point::Card_Q;
    }
    else if (str[1]=="K") {
        point=Point::Card_K;
    }

    if(str=="RK"){
        suit=Heart;
        point=Point::Card_RK;
    }
    else if (str=="BK") {
        suit=Spade;
        point=Point::Card_BK;
    }
    value=0;
    player=_player;
    y=280;
    x=50+(player-1)*350+num*65;
    this->setVisible(true);
}




void Card::paintEvent(QPaintEvent *event)
{

        QPainter painter(this);
        QPixmap pix;
        QString str="";
        switch(suit){
        case Suit::Spade:{str.append("S");break;}
        case Suit::Heart:{str.append("H");break;}
        case Suit::Club:{str.append("C");break;}
        case Suit::Diamond:{str.append("D");break;}
        }
        switch(point){
        case Point::Card_A:{str.append("A");break;}
        case Point::Card_2:{str.append("2");break;}
        case Point::Card_3:{str.append("3");break;}
        case Point::Card_4:{str.append("4");break;}
        case Point::Card_5:{str.append("5");break;}
        case Point::Card_6:{str.append("6");break;}
        case Point::Card_7:{str.append("7");break;}
        case Point::Card_8:{str.append("8");break;}
        case Point::Card_9:{str.append("9");break;}
        case Point::Card_10:{str.append("10");break;}
        case Point::Card_J:{str.append("J");break;}
        case Point::Card_Q:{str.append("Q");break;}
        case Point::Card_K:{str.append("K");break;}
        case Point::Card_RK:{str="RED JOKER";break;}
        case Point::Card_BK:{str="BLACK JOKER";break;}
        }
        if((!isShow)&&num>=20){
            str="PADDING";
        }
        pix.load(":/pic/"+str+".png");
        //绘制背景图
        this->setGeometry(x,y,60,120);

        painter.drawPixmap(0,0,60,120,pix);


}

void Card::mousePressEvent(QMouseEvent *e)
{
    setSelected();
}




Suit Card::getSuit()const
{
    return suit;
}

Point Card::getPoint()const
{
    return point;
}

int Card::getValue() const
{
    return value;
}

void Card::setSelected()
{
    isSelected=!isSelected;
    if(isSelected){
        y=y-30;
        update();
    }
    else{
        y=y+30;
        update();
    }
}

int Card::getNum() const
{
    return num;
}

void Card::setNum(int _num)
{
    num=_num;
}



QString Card::toString()const
{
    QString str="";
    switch(suit){
    case Suit::Spade:{str.append("S");break;}
    case Suit::Heart:{str.append("H");break;}
    case Suit::Club:{str.append("C");break;}
    case Suit::Diamond:{str.append("D");break;}
    }
    switch(point){
    case Point::Card_A:{str.append("A");break;}
    case Point::Card_2:{str.append("2");break;}
    case Point::Card_3:{str.append("3");break;}
    case Point::Card_4:{str.append("4");break;}
    case Point::Card_5:{str.append("5");break;}
    case Point::Card_6:{str.append("6");break;}
    case Point::Card_7:{str.append("7");break;}
    case Point::Card_8:{str.append("8");break;}
    case Point::Card_9:{str.append("9");break;}
    case Point::Card_10:{str.append("0");break;}
    case Point::Card_J:{str.append("J");break;}
    case Point::Card_Q:{str.append("Q");break;}
    case Point::Card_K:{str.append("K");break;}
    case Point::Card_RK:{str="RK";break;}
    case Point::Card_BK:{str="BK";break;}
    }
    return str;
}
