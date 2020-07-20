#include "tienda.h"
#include "ui_tienda.h"


#include <QDebug>
#include <QLineEdit>
#include <QIntValidator>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <iostream>
#include <QFileDialog>
#include <QObject>
#include <QFont>

using namespace std;


Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    inicializarDatos();
    Tienda::m_subtotal=0;

    ui->inCedula->setValidator(new QIntValidator);
    ui->inTelefono->setValidator(new QIntValidator);
}

Tienda::~Tienda()
{
    delete ui;
}

void Tienda::mostrarPrecio(int index)
{
    //Obtener el precio del producto seleccionado
    float precio = m_productos.at(index)->precio();
    //Colocar el precio en la etiqueta correspondiente
    ui->outPrecio->setText("$"+QString::number(precio));

}

void Tienda::agregarProducto()
{
    int index=ui->inProducto->currentIndex();
    Producto *p=m_productos.at(index);
    int cantidad=ui->inCantidad->value();
    //Calcular subtotal
    float subtotal = cantidad*p->precio();

    //Buscar productos repetidos
    if(!buscar(p,cantidad)){

    //Agregar datos a la tabla

    int posicion = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(posicion);
    ui->outDetalle->setItem(posicion,0,new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(posicion,1,new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(posicion,2,new QTableWidgetItem(QString::number(subtotal)));

    }



    //limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();


    //Calcular valores y mostrar
    calcular(subtotal);

    ingresarCliente();

}

void Tienda::calcular(float subtotal)
{
    m_subtotal+=subtotal;
    float iva=m_subtotal*0.12;
    float total=m_subtotal+iva;

    ui->outSubTotal->setText(QString::number(m_subtotal));
    ui->outIVA->setText(QString::number(iva));
    ui->outTotal->setText(QString::number(total));


}

bool Tienda::buscar(Producto *producto, int cantidad)
{
    //Obtener numero de filas
    int numFilas = ui->outDetalle->rowCount();
    //Recorrer la tabla
    for(int i=0 ; i<numFilas;i++){
        //Obtener el item en la fila y la columa 1
        QTableWidgetItem *item = ui->outDetalle->item(i,1);
        //Obtener el texto
        QString dato = item->data(Qt::DisplayRole).toString();
        //Comparar el producto

        if(dato==producto->nombre()){
            QTableWidgetItem *item = ui->outDetalle->item(i,0);
            int cantidadActual = item->data(Qt::DisplayRole).toInt();
            //sumar cantidad
            int cantidadNueva = cantidadActual+cantidad;
            //Calcular nuevo sub total
            float subtotal=cantidadNueva*producto->precio();
            //Actualizar en la tabla
            ui->outDetalle->setItem(i,0,new QTableWidgetItem(QString::number(cantidadNueva)));

            ui->outDetalle->setItem(i,2,new QTableWidgetItem(QString::number(subtotal)));
            return true;
        }

    }
    return false;
}

void Tienda::validarCedula()
{

   QString numeroCedula =ui->inCedula->text();
   int cedula = numeroCedula.toInt();
   //Probando...
   //qDebug()<<cedula;
   //qDebug()<<numeroCedula;

   if(numeroCedula.length()<10){
       ui->inCedula->setStyleSheet("QLineEdit { background-color: red }");
   }else{




   //CODIGO VALIDACION
   int pares,impares,total,dec=0;
           int a,b,c,d,e,f,g,h,i,j;


           a=cedula/1000000000;
           cedula=cedula-(a*1000000000);
           b=cedula/100000000;
           cedula=cedula-(b*100000000);
           c=cedula/10000000;
           cedula=cedula-(c*10000000);
           d=cedula/1000000;
           cedula=cedula-(d*1000000);
           e=cedula/100000;
           cedula=cedula-(e*100000);
           f=cedula/10000;
           cedula=cedula-(f*10000);
           g=cedula/1000;
           cedula=cedula-(g*1000);
           h=cedula/100;
           cedula=cedula-(h*100);
           i=cedula/10;
           cedula=cedula-(i*10);
           j=cedula/1;
           cedula=cedula-(j*1);

           double valor=2400000000;
           if (cedula>valor){

                   ui->inCedula->setStyleSheet("QLineEdit { background-color: red }");

           }else{

                   pares=b+d+f+h;

                   a=a*2;
                   if (a>9){
                           a=a%10+a/10;
                   }

                   c=c*2;
                   if (c>9){
                           c=c%10+c/10;
                   }

                   e=e*2;
                   if (e>9){
                           e=e%10+e/10;
                   }

                   g=g*2;
                   if (g>9){
                           g=g%10+g/10;
                   }

                   i=i*2;
                   if (i>9){
                           i=i%10+i/10;
                   }

                   impares=a+c+e+g+i;

                   total=pares+impares;



                   while (dec-total!=j && dec<total+10){
                           dec=dec+10;
                   }

                   if (dec-total==j){
                           ui->inCedula->setStyleSheet("QLineEdit { background-color: white }");
                   }else {
                           ui->inCedula->setStyleSheet("QLineEdit { background-color: red }");
                   }




           }
           }

}

void Tienda::crearFactura()
{
    QString nombre;
    QString cedula;
    QString telefono;
    QString correo;
    QString direccion;

    QString subtotal;
    QString IVA;
    QString Total;

    nombre= ui->inNombre->text();
    cedula= ui->inCedula->text();
    telefono= ui->inTelefono->text();
    correo= ui->inMail->text();
    direccion= ui->inDireccion->toPlainText();

    subtotal= ui->outSubTotal->text();
    IVA= ui->outIVA->text();
    Total= ui->outTotal->text();

    QString factura;

    factura="Nombre: "+nombre+"\n"+
            "Cedula: "+cedula+"\n"+
            "Telefono: "+telefono+"\n"+
            "Correo: "+correo+"\n"+
            "Direccion: "+direccion+"\n\n"+

            "Subtotal: "+subtotal+"\n"+
            "IVA: "+IVA+"\n"+
            "TOTAL A PAGAR: "+Total+"\n";

    ui->outFactura->appendPlainText(factura);


}

void Tienda::ingresarCliente()
{


  //qDebug("Estamos en Beta");


}

void Tienda::inicializarDatos()
{
    //Abrir archivo de productos

    QFile archivo("productos.csv");

    if(archivo.open(QFile::ReadOnly)){

        QTextStream in(&archivo);
        while(!in.atEnd()){

            QStringList datos = in.readLine().split(";");
            //QStringList datos=linea.split(";");
            int codigo = datos[0].toInt();
            QString producto=datos[1];
            float precio = datos[2].toFloat();
            //Crear productos
            m_productos.append(new Producto(codigo,producto,precio));


        }


    }else{
        qDebug()<<"Error al abrir";

    }
    archivo.close();


    //Invocar al metodo para inicializar los widgets

    inicializarWidgets();

}

void Tienda::inicializarWidgets()
{
    //SIZE DE TEXTO TOTAL
    QFont font = ui->outTotal->font();
    font.setPointSize(16);
    font.setBold(true);
    ui->outTotal->setFont(font);

    ui->btmFinalizar->setFont(font);


    for (int i = 0; i < m_productos.length(); ++i) {
        ui->inProducto->addItem(m_productos.at(i)->nombre());
    }

    //Inicializar cedula por defecto
    ui->inCedula->setText("9999999999");
    //Colocar cabecera en la plata
    QStringList cabecera={"Cantidad","Producto","Sub Total"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    //Eventos
    connect(ui->inProducto, SIGNAL(currentIndexChanged(int)),this,SLOT(mostrarPrecio(int)));
    connect(ui->btmAgregar, SIGNAL(clicked(bool)),this,SLOT(agregarProducto()));
    connect(ui->btmFinalizar, SIGNAL(clicked(bool)),this,SLOT(ingresarCliente()));
    connect(ui->inCedula, SIGNAL(editingFinished()),this,SLOT(validarCedula()));
    connect(ui->btmFinalizar, SIGNAL(clicked(bool)),this,SLOT(crearFactura()));

    validarCedula();


    //Mostrar el precio del primer producto
    mostrarPrecio(0);
}



void Tienda::on_btmFinalizar_clicked()
{


}

void Tienda::on_actionGuardar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar datos",QDir::home().absolutePath(),"Archivo de Texto(*.txt)");
    QFile data(fileName);
    if(data.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream salida(&data);
        salida<<ui->outFactura->toPlainText();
        ui->statusbar->showMessage("Datos almacenados");
    }
    data.close();
}

void Tienda::on_actionAcerca_de_triggered()
{
    AcercaDe info;
    info.setModal(true);
    info.exec();
}

void Tienda::on_actionAgregar_Producto_triggered()
{
    AgregarP nuevo;
    nuevo.setModal(true);
    nuevo.exec();


}
