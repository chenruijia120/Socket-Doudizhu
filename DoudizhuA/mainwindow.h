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
    void initServerA();
    void paintEvent(QPaintEvent *e);

public slots:
    void acceptConnectionB();
    void recvMessageB();
    void acceptConnectionC();
    void recvMessageC();
    void sendDataToClientB(QString _currentData);
    void sendDataToClientC(QString _currentData);
    void ifBegin();
    void startJiaodizhu();

    void decideifDizhu();
    void startGame();
    void createDizhu();
    void createPoker();
    void ifGameover();
    void ifChupai();
    void updatePaishu();
    void Gameover();
    void readChupai(int who, int i);
signals:
    void tryIfbegin();

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
    QTcpServer  *listenSocketB;
    QTcpServer  *listenSocketC;
    QTcpSocket  *readWriteSocketB;
    QTcpSocket  *readWriteSocketC;
    bool connect_AB=false;
    bool connect_AC=false;
    bool connect_BC=false;

    int dizhu=0;
    bool ifAdecided=false;
    bool ifBdecided=false;
    bool ifCdecided=false;

    bool ifAyes=false;
    bool ifByes=false;
    bool ifCyes=false;

    bool ifstart=false;

    QVector<Card*> A;
    QVector<Card*> B;
    QVector<Card*> C;
    QVector<Card*> dizhupoker;
    CardCombine last;
    int Anum=17;
    int Bnum=17;
    int Cnum=17;
    int paiquan=0;
};

#endif // MAINWINDOW_H
