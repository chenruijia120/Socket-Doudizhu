#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPoint>

enum Point
{
    Card_Zero,
    Card_3,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A,
    Card_2,
    Card_BK,
    Card_RK

};

enum Suit
{
    Spade,
    Heart,
    Club,
    Diamond,
};


class Card : public QWidget
{
    Q_OBJECT
public:
    Card(int _num,int _value,QWidget *parent = nullptr);
    Card(int _player,int _num,QString str,QWidget *parent = nullptr);
    bool isSelected=false;
    bool isShow=false;
    Suit getSuit()const;
    Point getPoint()const;
    int getValue()const;
    void setSelected();
    int getNum()const;
    void setNum(int _num);
    QString toString()const;
signals:
public slots:
    void paintEvent(QPaintEvent *event);
private:
    Suit suit;
    Point point;
    int value;
    int x=50;
    int y=600;
    int num;
    int player=0;

private slots:
    void mousePressEvent(QMouseEvent *e);
};

#endif // CARD_H


