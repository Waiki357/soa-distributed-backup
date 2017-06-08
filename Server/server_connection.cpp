#include "server_connection.h"

Server_Connection::Server_Connection(QHostAddress host, quint16 port, QString path, QObject *parent):
    m_host(host),
    m_port(port),
    QTcpServer(parent),
    m_path(path)
{}

void Server_Connection::start()
{
    if ( this->listen(m_host, m_port) )
        qDebug() << "Server started at " << m_host.toString() << ":" << m_port;
    else
        qDebug() << "Can't start server";
}

void Server_Connection::incomingConnection(qintptr socketDescriptor){

    SocketThread *thread = new SocketThread(socketDescriptor, m_path, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    connect(thread,SIGNAL(onFinishRecieved()),this,SLOT(Finished_Conection()));
}

void Server_Connection::Finished_Conection(){
    qDebug()<<"Server_Connection";
    emit on_Finished_Conection();
}
