#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void tcpConnect();
public slots:
  void putData();
private slots:
    void on_connect_clicked();
    void on_disconnect_clicked();

    void on_horizontalSlider_3_actionTriggered(int action);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_timer_2_valueChanged(int value);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
