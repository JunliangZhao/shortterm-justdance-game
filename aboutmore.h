#ifndef ABOUTMORE_H
#define ABOUTMORE_H

#include <QMainWindow>

namespace Ui {
class aboutmore;
}

class aboutmore : public QMainWindow
{
    Q_OBJECT

public:
    explicit aboutmore(QWidget *parent = nullptr);
    ~aboutmore();
public slots:
    void back();
private:
    Ui::aboutmore *ui;
};

#endif // ABOUTMORE_H
