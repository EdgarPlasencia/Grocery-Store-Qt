#ifndef AGREGARP_H
#define AGREGARP_H

#include <QDialog>


namespace Ui {
class AgregarP;
}

class AgregarP : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarP(QWidget *parent = nullptr);
    ~AgregarP();

private slots:
    void on_bmtAgregarNuevo_accepted();

private:
    Ui::AgregarP *ui;

};

#endif // AGREGARP_H
