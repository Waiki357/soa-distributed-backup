#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QFileDialog>
#include <QHostAddress>

#include "server_connection.h"
#include "send_files.h"

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Server(QWidget *parent = 0);
        ~Server();

    private slots:
        void on_Conectar_btn_clicked();
        void on_Carpeta_btn_clicked();

    public slots:
        void on_Client_Start();

    private:
            Ui::Server *ui;
            Server_Connection *Server_;
            Send_Files *Client;

};

#endif // SERVER_H
