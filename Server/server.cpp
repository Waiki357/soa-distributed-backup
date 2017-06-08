#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->IP_text->setEnabled(false);
    ui->Conectar_btn->setEnabled(false);

}

Server::~Server()
{
    delete ui;
}

void Server::on_Conectar_btn_clicked()
{
    ui->Conectar_btn->setEnabled(false);
    Server_ = new Server_Connection(QHostAddress(ui->IP_text->text()),ui->Puerto_text->text().toInt(), ui->path->text(),this);
    Server_->start();

    connect(Server_,SIGNAL(on_Finished_Conection()),this,SLOT(on_Client_Start()));
}

void Server::on_Carpeta_btn_clicked()
{

    QString fileName = QFileDialog::getExistingDirectory(this, tr("Abrir Directorio"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (fileName != "") {
        ui->path->setText(fileName);
        ui->Conectar_btn->setEnabled(true);
    }
    else {
        qDebug() << "No se puede abrir la carpeta";
    }

}

void Server::on_Client_Start(){

        qDebug()<<"F_C";
        QStringList Lista_archivos;
        QDirIterator it(ui->path->text(), QStringList() << "*", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()){
            Lista_archivos.push_back(it.next());
        }

        Client = new Send_Files(ui->path->text(),Lista_archivos,QHostAddress(ui->IP_text_2->text()),ui->Puerto_text_2->text().toInt());
        Client->start();
}
