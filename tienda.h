#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>
#include <QList>
#include "producto.h"
#include "acercade.h"
#include "agregarp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);

    Producto ingresar;
    ~Tienda();
public slots:

    void mostrarPrecio(int);
    void agregarProducto();

    void ingresarCliente();
    void validarCedula();
    void crearFactura();


private slots:
    void on_btmFinalizar_clicked();

    void on_actionGuardar_triggered();

    void on_actionAcerca_de_triggered();

    void on_actionAgregar_Producto_triggered();

private:

    Ui::Tienda *ui;

    //secDialog *sec;

    //cliente ingresarC;


    QList<Producto*>m_productos;

    void inicializarDatos();
    void inicializarWidgets();
    float m_subtotal;


    void calcular(float);
    bool buscar(Producto *producto, int cantidad);



};
#endif // TIENDA_H
