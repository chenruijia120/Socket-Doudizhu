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
    void paintEvent(QPaintEvent *e);

public slots:
    void recvMessageA();
    void recvMessageB();
    void sendDataToClientA(QString _currentData);
    void sendDataToClientB(QString _currentData);
    void decideifDizhu();
    void startGame();
    void connectHostA();
    void connectHostB();
    void startJiaodizhu();
    Card* readPoker(int num);
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
    QTcpSocket  *readWriteSocketA;
    QTcpSocket  *readWriteSocketB;

    int dizhu;
    bool ifstart=false;

    QVector<Card*> C;
    QVector<Card*> dizhupoker;

    CardCombine last;
    int Anum=17;
    int Bnum=17;
    int Cnum=17;
    int paiquan=0;
};

#endif // MAINWINDOW_H
