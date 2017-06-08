#include "send_files.h"

Send_Files::Send_Files(QString root, QStringList F, QHostAddress Host, quint16 Port):
Files(F),
Dir_actual(root),
m_port(Port),
m_host(Host)
{
    qDebug()<<"objeto creado";
}

void Send_Files::disconnect()
{
    qDebug() << "disconnected!";
}

void Send_Files::run(){

    qDebug()<<"Empezar envio";
    QTcpSocket *socket = new QTcpSocket;

    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));

    socket->connectToHost(m_host, m_port);
    socket->waitForConnected();

    if (socket->state() != QAbstractSocket::ConnectedState) {
            qDebug() << "Socket no conectado";
            delete socket;
            return;
     }

    QListIterator<QString> itr (Files);
        while (itr.hasNext()) {
            QString current = itr.next();

            m_file = new QFile(current);
            if(!(m_file->open(QIODevice::ReadOnly))){
                   qDebug("Archivo no abierto");
                   exit(0);
            }

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_8);

            //Nombre archivo
            current.remove(0,Dir_actual.size());
            out << (quint64)0 << current;
            qDebug()<< current;

            //Tamaño archivo
            out.device()->seek(0);
            out << (quint64)(m_file->size());

            qDebug()<<(quint64)(m_file->size());
            qint64 x = 0;
            while (x < block.size()) {
                qint64 y = socket->write(block);
                x += y;
                socket->waitForBytesWritten();
            }
            socket->waitForReadyRead(-1);
            socket->flush();

            QByteArray read;
            while(1)
            {
                read.clear();
                read = m_file->read(32768*8);
                qDebug() << "Read : " << read.size();
                if(read.size()==0)
                    break;

                qDebug() << "Written : " << socket->write(read);
                socket->waitForBytesWritten(-1);
                read.clear();
            }
            m_file->close();
            delete m_file;
            socket->waitForReadyRead(-1);
            socket->flush();
        }

        socket->disconnectFromHost();
}
