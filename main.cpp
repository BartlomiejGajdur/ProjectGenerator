#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
<<<<<<< HEAD
    AppState appState;
    MainWindow w(appState);
    w.show();
    return a.exec();
=======
	AppState appState;
	MainWindow w(appState);
	w.show();
	return a.exec();
>>>>>>> 6b30556809882f6ef8fa51503c67328a4eef15d2
}
