#ifndef MONEY_H
#define MONEY_H

#include <QWidget>

namespace Ui {
class Money;
}

class Money : public QWidget
{
    Q_OBJECT

public:
    explicit Money(QWidget *parent = nullptr);
    ~Money();

private:
    Ui::Money *ui;
};

#endif // MONEY_H
