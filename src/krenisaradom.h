#ifndef KRENISARADOM_H
#define KRENISARADOM_H

#include <QDialog>

namespace Ui {
class krenisaradom;
}

class krenisaradom : public QDialog
{
    Q_OBJECT

public:
    explicit krenisaradom(QWidget *parent = nullptr);
    ~krenisaradom();

private:
    Ui::krenisaradom *ui;
};

#endif // KRENISARADOM_H
