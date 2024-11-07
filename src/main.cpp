#include "browser.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    browser w;
    w.show();
    return a.exec();
}