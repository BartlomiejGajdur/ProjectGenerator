#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QStyleFactory>

#include "appstate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
void setApplicationStyle(QApplication& a);
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(AppState& appState, QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_toolButton_clicked();

	void on_CMakeFile_clicked(bool checked);

	void on_MainFIle_clicked(bool checked);

	void on_ConanFile_clicked(bool checked);

	void on_RunnerFile_clicked(bool checked);

	void on_ClangFormatFile_clicked(bool checked);

	void on_pushButton_clicked();

	void on_ConanLibraryComboBox_currentIndexChanged(int index);

	void on_GitignoreFile_clicked(bool checked);

	void on_helpButton_clicked();

private:
	void validateDirectoryPath();
	void setContentFromConanLibraryComboBox();
	Ui::MainWindow *ui;
	AppState m_appState;
};
#endif // MAINWINDOW_H
