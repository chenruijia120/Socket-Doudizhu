#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QByteArray>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QVector>
#include <QtAlgorithms>
#include <QMessageBox>

#include "card.h"
#include "cardcombine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initServerB();
    void paintEvent(QPaintEvent *e);


public slots:
    void recvMessageA();
    Card* readPoker(int num);
    void acceptConnectionC();
    void recvMessageC();
    void sendDataToClientA(QString _currentData);
    void sendDataToClientC(QString _currentData);
    void decideifDizhu();
    void startGame();
    void connectHostA();
    void startJiaodizhu();
    void ifGameover();
    void ifChupai();
    void updatePaishu();
    void Gameover();
    void readChupai(int who, int i);
private slots:
    void on_pushButton_clicked();
    
    void on_btn_jiao_clicked();

    void on_btn_bujiao_clicked();

    void on_btn_chupai_clicked();

    void on_btn_buchu_clicked();

    void on_btn_exit_clicked();

    void on_btn_again_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer  *listenSocketC;
    QTcpSocket  *readWriteSocketA;
    QTcpSocket  *readWriteSocketC;

    int dizhu;
    bool ifstart=false;

    QVector<Card*> B;
    QVector<Card*> dizhupoker;
    CardCombine last;
    int Anum=17;
    int Bnum=17;
    int Cnum=17;
    int paiquan=0;
};

#endif // MAINWINDOW_H
