#ifndef CHOOSE_H
#define CHOOSE_H

#include <QMainWindow>

namespace Ui {
class choose;
}

class choose : public QMainWindow
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = 0);
    ~choose();

private:
    Ui::choose *ui;
};

#endif // CHOOSE_H
