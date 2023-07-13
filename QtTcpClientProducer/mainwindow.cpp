#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    socket = new QTcpSocket(this);
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

  if(socket->state()== QAbstractSocket::ConnectedState){

    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " +
        QString::number(rand()%35)+"\r\n";

      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str())
               << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
}

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}

void MainWindow::on_connect_clicked(){
  tcpConnect();
}

void MainWindow::on_disconnect_clicked(){
  socket -> disconnectFromHost();
  ui->onoff->setText("Desconectado");
}


