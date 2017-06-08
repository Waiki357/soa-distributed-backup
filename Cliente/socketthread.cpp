#include "socketthread.h"

SocketThread::SocketThread(qintptr socketDescriptor, QString path, QObject *parent):
    QThread(parent),
    m_socketDescriptor(socketDescriptor),
    m_blockSize(0),
    m_path(path)
{}

SocketThread::~SocketThread()
{
    delete m_socket;
}

void SocketThread::run()
{
    m_socket = new QTcpSocket;
    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
            emit error(m_socket->error());
            return;
    }

    connect(m_socket, SIGNAL(readyRead()),    this, SLOT(onReadyRead()),    Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);

    exec();
}

void SocketThread::onReadyRead()
{
    qDebug()<<"hola2";
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_5_8);

    in >> m_filesize;
    qDebug()<<m_filesize;

    QString fileName;
    QString path;
    in >> fileName;
    path = fileName;

    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream<<1;
    m_socket->write(byteArray);
    m_socket->waitForBytesWritten(-1);
    m_socket->flush();

    if(fileName.lastIndexOf("/")!=0){
        path.truncate(fileName.lastIndexOf("/"));
        QDir dir(m_path + path);
        if (!dir.exists()){
             dir.mkpath(m_path + path);
        }
    }
    qDebug()<<m_path + fileName;
    QFile files(m_path + fileName);
    if(!(files.open(QIODevice::Append))){
           qDebug("File cannot be opened.");
           exit(0);
    }

    QByteArray read;
    while(m_socket->waitForReadyRead())
    {
        read.clear();
        if(m_socket->bytesAvailable()>(m_filesize-files.size())){
            read = m_socket->read(m_filesize-files.size());
        }
        else{
            read = m_socket->read(m_socket->bytesAvailable());
        }

        qDebug() << "Read    : " << read.size();
        files.write(read);
        qDebug() << "Written : " << files.size();
        if(files.size()==m_filesize){
            qDebug()<<"Cerrado";
            files.close();
            m_filesize=0;
            break;
        }
    }

    m_socket->write(byteArray);
    m_socket->waitForBytesWritten(-1);
    m_socket->flush();

}

void SocketThread::onDisconnected()
{
    m_socket->close();
    qDebug()<<"terminado";
    quit();
}
