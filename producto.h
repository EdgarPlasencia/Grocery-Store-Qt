#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QObject>

class Producto : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int codigo READ codigo)
    Q_PROPERTY(float precio READ precio WRITE setPrecio)
    Q_PROPERTY(QString nombre READ nombre)

    Q_PROPERTY(QString cliente READ cliente WRITE setCliente)

public:
    explicit Producto(QObject *parent = nullptr);

    Producto(int codigo, QString nombre, float precio);
    //Geters
    int codigo() const;
    float precio() const;
    QString nombre() const;
    //Setters
    void setPrecio(float precio);


    QString cliente();
    void setCliente(QString cliente);

signals:

private:
    int m_codigo;
    float m_precio;
    QString m_nombre;

    QString m_cliente="";
    /* QString m_cedula;
    QString direccion;
    QString telefono;
    QString correo;
    */
};

#endif // PRODUCTO_H
