#ifndef NARUCI_H
#define NARUCI_H

#include <QDialog>

namespace Ui {
class Naruci;
}

class Naruci : public QDialog
{
    Q_OBJECT

public:
    explicit Naruci(QWidget *parent = nullptr);
    ~Naruci();

private:
    Ui::Naruci *ui;
};

#endif // NARUCI_H
