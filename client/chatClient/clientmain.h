#ifndef CLIENTMAIN_H
#define CLIENTMAIN_H

#include <QMainWindow>

namespace Ui {
    class clientMain;
}

class clientMain : public QMainWindow {
    Q_OBJECT
public:
    clientMain(QWidget *parent = 0);
    ~clientMain();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::clientMain *ui;
};

#endif // CLIENTMAIN_H
