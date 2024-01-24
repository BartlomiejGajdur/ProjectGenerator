#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "contentCreatorHelper.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

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

void MainWindow::validateDirectoryPath(){
	if(ui->ProjectNameLineEdit->text().isEmpty())
		return;

		QString directoryPath = m_appState.getFilePath() + "/" + ui->ProjectNameLineEdit->text();

		if (!QDir(directoryPath).exists())
		{
			if (!QDir().mkdir(directoryPath))
			{
				throw std::runtime_error("Nie udało się utworzyć katalogu.");
			}
		}
		else
		{
			throw std::runtime_error("Katalog już istnieje.");
		}

		m_appState.setFilePath(directoryPath);
}

void MainWindow::on_pushButton_clicked(){

	try{
		validateDirectoryPath();
		m_appState.generateFiles();
	}catch(const std::runtime_error& e)
	{
		QMessageBox::warning(nullptr, "Błąd", e.what());
	}
}

void MainWindow::on_ConanLibraryComboBox_currentIndexChanged(int index)
{
	if(index == 1)
	{
		QString requires{"fmt/10.2.1"};
		m_appState.setConanFileContent(contentCreator::conanFileCreator(requires));

		std::pair<QString, QString> libraryContent{
			"#include <fmt/chrono.h>\n",
			R"(
			auto now = std::chrono::system_clock::now();
			fmt::print("Date and time: {}\\n", now);
			fmt::print("Time: {:%H:%M}\\n", now);
			)"
		};
		m_appState.setMainFileContent(contentCreator::mainFileCreator(libraryContent));

		//Tu jeszcze do CMAKE trzeba dorzucic do kompilacji
	}

	if(index == 2)
	{

	}
    qDebug()<<"Current Index: "<< index;
}

