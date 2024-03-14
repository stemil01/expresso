#ifndef TABLEOPTIONS_H
#define TABLEOPTIONS_H

#include <QDialog>
#include "sto.h"

namespace Ui {
class TableOptions;
}

class TableOptions : public QDialog
{
    Q_OBJECT

public:
    explicit TableOptions(QWidget *parent = nullptr,Sto* sto = nullptr);
    ~TableOptions();



private slots:
    void onOkClicked();
    void onRound();
    void onDefaultClicked();
    void onHSliderWidthChanged();
    void onHSliderHeightChanged();
    void onApplyClicked();
    void restoreValues();

private:
    void refresh();
    void connectSlots();
    Ui::TableOptions *ui;
    Sto* m_sto;
    qreal m_oldWidth;
    qreal m_oldHeight;
    bool m_rounded;
    QColor m_oldColor;
    qint32 m_oldDegree;
    Sto::Status m_oldStatus;
};

#endif // TABLEOPTIONS_H
