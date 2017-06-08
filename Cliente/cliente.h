#ifndef CLIENTE_H
#define CLIENTE_H

#include <QMainWindow>
#include <QFile>
#include <QTcpSocket>
#include <QDebug>
#include <QNetworkInterface>
#include <QFileDialog>
#include <QProcess>
#include <QThread>
#include <QDir>
#include <QDirIterator>

#include "send_files.h"
#include "server_connection.h"

namespace Ui {
class Cliente;
}

class Cliente : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Cliente(QWidget *parent = 0);
        ~Cliente();

    private slots:
        void on_Open_clicked();
        void on_Send_bnt_clicked();
        void on_Open_2_clicked();

        void on_Send_bnt_2_clicked();

private:
        Ui::Cliente *ui;
        QString fileName;
        QStringList Lista_archivos;
        Send_Files *Pepe;
        Server_Connection *Server_;
};

#endif // CLIENTE_H
