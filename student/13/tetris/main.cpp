/* This program is a modified version of a tetris game. Further instructions in
 * the "instructions"-folder.
* Name: Eetu Jokinen
* Student number: 273281
* UserID: teekkart ( Necessary due to gitlab folder naming. )
* eetu.jokinen@tuni.fi
* */

#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
