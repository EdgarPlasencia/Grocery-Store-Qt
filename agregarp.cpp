#include "agregarp.h"
#include "ui_agregarp.h"
#include <QIntValidator>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QList>
#include <QTextStream>

AgregarP::AgregarP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarP)
{
    ui->setupUi(this);
      ui->inNuevoCodigo->setValidator(new QIntValidator);
}

AgregarP::~AgregarP()
{
    delete ui;
}

void AgregarP::on_bmtAgregarNuevo_accepted()
{
    QString codigP;
    QString nombreP;
    QString precioP;

    codigP=ui->inNuevoCodigo->text();
    nombreP=ui->inNuevoProducto->text();
    precioP=ui->inNuevoPrecio->text();

    //LINEA PARA INGRESAR
    QString ingresarP;
    ingresarP=codigP+";"+nombreP+";"+precioP;
    //qDebug()<<ingresarP;



    QFile fileIn("productos.csv"), fileOut("textOut.csv");

    fileIn.open(QFile::ReadOnly); // check result
    fileOut.open(QFile::WriteOnly); // check result

    QTextStream streamIn(&fileIn), streamOut(&fileOut);
    const QChar delimeter = ';';

    while (!streamIn.atEnd())
    {
        QStringList list = streamIn.readLine().split(delimeter);

        streamOut<< list.join(delimeter)<< "\r\n";

        if (streamIn.atEnd()){

            streamOut <<ingresarP << "\r\n"; // or endl
        }
    }

    fileIn.close();
    fileOut.close();

    fileIn.remove(); // check result
    fileOut.rename(QFileInfo(fileIn).absoluteFilePath()); // check result

    //ui->statusbar->showMessage()

}
