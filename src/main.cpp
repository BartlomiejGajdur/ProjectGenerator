#include "../include/mainwindow.h"
#include "../include/appstate.h"
#include <QApplication>

int main( int argc, char* argv[] )
{
	QApplication a( argc, argv );
	Ui::setApplicationStyle( a );
	AppState appState;
	MainWindow w( appState );
	w.show();
	return a.exec();
}
