#include "mainwindow.h"

#include <QApplication>
#include "filehelper.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AppState appState;
	MainWindow w(appState);
	w.show();
	return a.exec();
}
