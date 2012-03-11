#include "clientmain.h"
#include "ui_clientmain.h"

clientMain::clientMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientMain)
{
    ui->setupUi(this);
}

clientMain::~clientMain()
{
    delete ui;
}

void clientMain::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
