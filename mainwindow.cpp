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
	if(!checked)
	{
		m_appState.setGenerateConan(checked);
		ui->ConanFile->setCheckState(Qt::CheckState::Unchecked);
		qDebug() <<"Conan tez zmieniam: " << checked;
	}
    qDebug() <<"CMake: " << checked;
}

void MainWindow::on_ConanFile_clicked(bool checked)
{
    m_appState.setGenerateConan(checked);
	if(checked)
	{
		m_appState.setGenerateCMake(checked);
		ui->CMakeFile->setCheckState(Qt::CheckState::Checked);
		qDebug() <<"CMake tez zmieniam: " << checked;
	}
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

void MainWindow::setContentFromConanLibraryComboBox(){
	const int currentIndex{ui->ConanLibraryComboBox->currentIndex()};
	if(currentIndex == 0)
	{
		const contentCreator::fmt fmt{};
		m_appState.setConanFileContent(contentCreator::conanFileCreator(fmt.conanRequires));

		m_appState.setMainFileContent(contentCreator::mainFileCreator(fmt.mainContent));

		m_appState.setCMakeFileContent(contentCreator::cmakeFileCreator(fmt.cmakeContent));
	}

	if(currentIndex == 1)
	{
		const contentCreator::nlohmann_json nlohmann_json{};
		m_appState.setConanFileContent(contentCreator::conanFileCreator(nlohmann_json.conanRequires));

		m_appState.setMainFileContent(contentCreator::mainFileCreator(nlohmann_json.mainContent));

		m_appState.setCMakeFileContent(contentCreator::cmakeFileCreator(nlohmann_json.cmakeContent));
	}

	qDebug()<<"Current Index: "<< currentIndex;
}

void MainWindow::on_pushButton_clicked(){

	try{

		validateDirectoryPath();

	}catch(const std::runtime_error& e)
	{
		QMessageBox::warning(nullptr, "Błąd", e.what());
	}

	//----------------------
	setContentFromConanLibraryComboBox();
	m_appState.generateFiles();
	//----------------------
}

void MainWindow::on_ConanLibraryComboBox_currentIndexChanged(int index)
{
	qDebug()<<"[CHANGED] Current Index: "<< index;
}


