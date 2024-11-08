#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QTcpSocket>
#include <QThread>

class ServerConnection : public QThread {
    Q_OBJECT

public:
    explicit ServerConnection(QObject *parent = nullptr) : QThread(parent) {}

    void run() override {
        QTcpSocket socket;
        socket.connectToHost("192.168.214.236", 600);
        //while (socket.waitForReadyRead(-1)) {
            //QByteArray data = socket.readAll();
            //emit dataReceived(data);
        //}
    }

signals:
    void error(QTcpSocket::SocketError socketError);
    void dataReceived(QByteArray &data);

};

#endif // SERVERCONNECTION_H
