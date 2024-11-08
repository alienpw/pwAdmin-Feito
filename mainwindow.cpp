#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Worker.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*connect(socket, &QTcpSocket::connected, [&]{
        qDebug() << "Conectado!";
    });
    connect(socket, &QTcpSocket::disconnected, [&]{
        qDebug() << "Desconectado!";
    });*/
   /* connect(socket, &QTcpSocket::readyRead, [&]{
        qDebug() << socket->readAll();
    });*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    socket->connectToHost("192.168.214.236", 600);
    if (socket->waitForConnected())
        qDebug() << "C";
}

