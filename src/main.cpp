#include "main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("haven"); // got this far
    a.setOrganizationName("not_sure"); // i dunno
    a.setOrganizationDomain("drewol.me"); // i guess

    MainWindow w;
    w.show();

    return a.exec();
}
