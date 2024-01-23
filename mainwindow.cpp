#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(AppState& appState, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_appState(appState)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Select Folder"), "C://");

    if (!folderPath.isEmpty()) {

        ui->FilePath->setText(folderPath);
        m_appState.setFilePath(folderPath);

        qDebug() << "Selected folder path: " << folderPath;
    } else {
        qDebug() << "Operation canceled or no folder selected";
    }
}

void MainWindow::on_MainFIle_clicked(bool checked)
{
    m_appState.setGenerateMain(checked);
    qDebug() <<"Main: " << checked;
}

void MainWindow::on_CMakeFile_clicked(bool checked)
{
    m_appState.setGenerateCMake(checked);
    qDebug() <<"CMake: " << checked;
}

void MainWindow::on_ConanFile_clicked(bool checked)
{
    m_appState.setGenerateConan(checked);
    qDebug() <<"Conan: " << checked;
}


void MainWindow::on_RunnerFile_clicked(bool checked)
{
    m_appState.setGenerateRunner(checked);
    qDebug() <<"Runner: " << checked;
}


void MainWindow::on_ClangFormatFile_clicked(bool checked)
{
    m_appState.setGenerateClangFormat(checked);
    qDebug() <<"ClangFormat: " << checked;
}


void MainWindow::on_pushButton_clicked()
{
    m_appState.generateFiles();
}

