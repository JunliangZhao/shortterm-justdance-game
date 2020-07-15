#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QMainWindow>

namespace Ui {
class gameover;
}

class gameover : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameover(QWidget *parent = 0);
    ~gameover();

public slots:
    void ClickButton();
private:
    Ui::gameover *ui;
};

#endif // GAMEOVER_H
