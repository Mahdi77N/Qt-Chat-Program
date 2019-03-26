#ifndef LOGOUT_H
#define LOGOUT_H

#include <QWidget>

namespace Ui {
class logout;
}

class logout : public QWidget
{
    Q_OBJECT

public:
    explicit logout(QWidget *parent = 0);
    ~logout();

private:
    Ui::logout *ui;
};

#endif // LOGOUT_H
