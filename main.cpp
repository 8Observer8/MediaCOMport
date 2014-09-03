
#include "MainWindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if ( !QSystemTrayIcon::isSystemTrayAvailable() ) {
        QMessageBox::information( 0, QObject::tr( "System Tray" ),
                                  QObject::tr( "Unable detect any system tray"
                                               " on this system." ) );
    }

    MainWindow w;
    w.show();

    return a.exec();
}
