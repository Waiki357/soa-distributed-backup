#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <QMainWindow>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QHostAddress>

#include "socketthread.h"

class Server_Connection : public QTcpServer
{
    Q_OBJECT

    public:
        Server_Connection(QHostAddress host, quint16 port, QString path, QObject *parent = 0);

    public slots:
        void start();

    protected:
        void incomingConnection(qintptr socketDescriptor);

    private:
        QHostAddress m_host;
        quint16 m_port;
        QString m_path;
};

#endif // SERVER_CONNECTION_H
