#ifndef UREDIPORUDZBINU_H
#define UREDIPORUDZBINU_H

#include <QWidget>

namespace Ui {
class urediporudzbinu;
}

class urediporudzbinu : public QWidget
{
    Q_OBJECT

public:
    explicit urediporudzbinu(QWidget *parent = nullptr);
    ~urediporudzbinu();

private:
    Ui::urediporudzbinu *ui;
};

#endif // UREDIPORUDZBINU_H
