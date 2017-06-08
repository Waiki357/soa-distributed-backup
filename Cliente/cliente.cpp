#include "cliente.h"
#include "ui_cliente.h"

Cliente::Cliente(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cliente)
{
    ui->setupUi(this);
    ui->Send_bnt->setEnabled(false);
    ui->Server_IP_text_2->setEnabled(false);

}

Cliente::~Cliente()
{
    delete ui;
}

void Cliente::on_Open_clicked()
{
    fileName = QFileDialog::getExistingDirectory(this, tr("Abrir Directorio"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (fileName != "") {
        ui->Carpeta_text->setText(fileName);

        QDirIterator it(fileName, QStringList() << "*", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()){
            Lista_archivos.push_back(it.next());
        }
        ui->Send_bnt->setEnabled(true);
    }
    else {
        qDebug() << "No se puede abrir la carpeta";
    }
}


void Cliente::on_Send_bnt_clicked()
{
    Pepe = new Send_Files(fileName,Lista_archivos,QHostAddress (ui->Server_IP_text->text()),ui->Server_Puerto_text->text().toInt());
    Pepe->start();
}

void Cliente::on_Open_2_clicked()
{
    QString fileName2 = QFileDialog::getExistingDirectory(this, tr("Abrir Directorio"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (fileName2 != "") {
        ui->Carpeta_text_2->setText(fileName2);
        ui->Send_bnt_2->setEnabled(true);
    }
    else {
        qDebug() << "No se puede abrir la carpeta";
    }

}

void Cliente::on_Send_bnt_2_clicked()
{
    ui->Send_bnt_2->setEnabled(false);
    Server_ = new Server_Connection(QHostAddress(ui->Server_IP_text_2->text()),ui->Server_Puerto_text_2->text().toInt(), ui->Carpeta_text_2->text(),this);
    Server_->start();
}
