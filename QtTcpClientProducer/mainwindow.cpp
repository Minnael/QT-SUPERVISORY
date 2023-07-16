#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimerEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(ui->start, SIGNAL(clicked(bool)), this, SLOT(startTemp()));
    connect(ui->stop, SIGNAL(clicked(bool)), this, SLOT(stopTemp()));
    connect(ui->connect, SIGNAL(clicked(bool)), this, SLOT(on_connect_clicked()));
    connect(ui->disconnect, SIGNAL(clicked(bool)), this, SLOT(on_disconnect_clicked()));
}

void MainWindow::tcpConnect(){
    socket->connectToHost(ui->lineEdit->text(), 1234);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
        ui->onoff->setText("Conectado");
    }
    else{
        qDebug() << "Disconnected";
        ui->onoff->setText("Desconectado");
    }
}

void MainWindow::putData(){
    QDateTime datetime;
    QString str;
    qint64 msecdate;

    int minimo = ui->display_min->value();
    int maximo = ui->display_max->value();

    if(socket->state()== QAbstractSocket::ConnectedState){

        msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
        str = "set "+ QString::number(msecdate) + " " + QString::number(minimo+(rand()%(maximo-minimo)))+"\r\n";

        qDebug() << str;
        qDebug() << socket->write(str.toStdString().c_str())<< " bytes written";

        if(socket->waitForBytesWritten(3000)){
            qDebug() << "wrote";
        }
        ui->textBrowser->append(str);
    }
    qDebug()<<"xxxx";
}

void MainWindow::on_connect_clicked(){
    tcpConnect();
}

void MainWindow::on_disconnect_clicked(){
    socket -> disconnectFromHost();
    ui->onoff->setText("Desconectado");
}

void MainWindow::timerEvent(QTimerEvent *event){
    putData();
}

void MainWindow::startTemp(){
    int time = 1000*ui->time->value();
    timer = startTimer(time);
    qDebug()<<"amdiwwjqdnqpdoq";
}

void MainWindow::stopTemp(){
    killTimer(timer);
}

void MainWindow::on_min_valueChanged(int value){
    ui->display_min->display(value);
}

void MainWindow::on_max_valueChanged(int value){
    ui->display_max->display(value);
}

void MainWindow::on_time_valueChanged(int value){
    ui->display_time->display(value);
}

MainWindow::~MainWindow(){
    delete socket;
    delete ui;
}
