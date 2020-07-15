#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QMainWindow>

namespace Ui {
class introduction;
}

class introduction : public QMainWindow
{
    Q_OBJECT

public:
    explicit introduction(QWidget *parent = nullptr);
    ~introduction();
public slots:
    void back();
private:
    Ui::introduction *ui;
};

#endif // INTRODUCTION_H
