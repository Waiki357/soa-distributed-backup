#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDataStream>
#include <QThread>
#include <QString>
#include <QFile>
#include <QDir>

class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread(qintptr socketDescriptor, QString path, QObject *parent = 0);
    ~SocketThread();

protected:
    void run() Q_DECL_OVERRIDE;

signals:
    void onFinishRecieved();
    void error(QTcpSocket::SocketError socketError);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    qintptr     m_socketDescriptor;
    QTcpSocket *m_socket;
    qint32      m_blockSize;
    qint64      m_filesize;
    QString     m_path;
};

#endif // SOCKETTHREAD_H
