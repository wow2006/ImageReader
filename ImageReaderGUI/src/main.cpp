#include <QApplication>
#include "maindialog.h"

int
main(int argc, char* argv[]){
    QApplication a(argc, argv);
    mainDialog w;
    w.show();
    return a.exec();
}
