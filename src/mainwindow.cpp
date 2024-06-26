#include "../include/mainwindow.h"
#include "../include/ui_mainwindow.h"
#include "../include/contentCreatorHelper.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextEdit>
#include <QIcon>

MainWindow::MainWindow( AppState& appState, QWidget* parent )
	: QMainWindow( parent ), ui( new Ui::MainWindow ), m_appState( appState )
{
	ui->setupUi( this );
	QIcon icon{ ":/ProjectGenerator.jpg" };
	this->setWindowIcon( icon );
}

MainWindow::~MainWindow()
{
	delete ui;
}

void Ui::setApplicationStyle( QApplication& a )
{
	a.setStyle( QStyleFactory::create( "Fusion" ) );

	QFont defaultFont = QApplication::font();
	defaultFont.setPointSize( defaultFont.pointSize() + 2 );
	a.setFont( defaultFont );

	QPalette darkPalette;
	darkPalette.setColor( QPalette::Window, QColor( 53, 53, 53 ) );
	darkPalette.setColor( QPalette::WindowText, Qt::white );
	darkPalette.setColor( QPalette::Disabled, QPalette::WindowText, QColor( 127, 127, 127 ) );
	darkPalette.setColor( QPalette::Base, QColor( 42, 42, 42 ) );
	darkPalette.setColor( QPalette::AlternateBase, QColor( 66, 66, 66 ) );
	darkPalette.setColor( QPalette::ToolTipBase, Qt::white );
	darkPalette.setColor( QPalette::ToolTipText, Qt::white );
	darkPalette.setColor( QPalette::Text, Qt::white );
	darkPalette.setColor( QPalette::Disabled, QPalette::Text, QColor( 127, 127, 127 ) );
	darkPalette.setColor( QPalette::Dark, QColor( 35, 35, 35 ) );
	darkPalette.setColor( QPalette::Shadow, QColor( 20, 20, 20 ) );
	darkPalette.setColor( QPalette::Button, QColor( 53, 53, 53 ) );
	darkPalette.setColor( QPalette::ButtonText, Qt::white );
	darkPalette.setColor( QPalette::Disabled, QPalette::ButtonText, QColor( 127, 127, 127 ) );
	darkPalette.setColor( QPalette::BrightText, Qt::red );
	darkPalette.setColor( QPalette::Link, QColor( 42, 130, 218 ) );
	darkPalette.setColor( QPalette::Highlight, QColor( 42, 130, 218 ) );
	darkPalette.setColor( QPalette::Disabled, QPalette::Highlight, QColor( 80, 80, 80 ) );
	darkPalette.setColor( QPalette::HighlightedText, Qt::white );
	darkPalette.setColor( QPalette::Disabled, QPalette::HighlightedText, QColor( 127, 127, 127 ) );

	a.setPalette( darkPalette );
}

void MainWindow::on_toolButton_clicked()
{
	const QString folderPath = QFileDialog::getExistingDirectory( this, tr( "Select Folder" ), "C://" );

	if( !folderPath.isEmpty() )
	{
		ui->FilePath->setText( folderPath );
		m_appState.setFilePath( folderPath );
	}
}

void MainWindow::on_MainFIle_clicked( bool checked )
{
	m_appState.setGenerateMain( checked );
}

void MainWindow::on_CMakeFile_clicked( bool checked )
{
	m_appState.setGenerateCMake( checked );
	if( !checked )
	{
		m_appState.setGenerateConan( checked );
		ui->ConanFile->setCheckState( Qt::CheckState::Unchecked );
	}
}

void MainWindow::on_ConanFile_clicked( bool checked )
{
	m_appState.setGenerateConan( checked );
	if( checked )
	{
		m_appState.setGenerateCMake( checked );
		ui->CMakeFile->setCheckState( Qt::CheckState::Checked );
	}
}

void MainWindow::on_RunnerFile_clicked( bool checked )
{
	m_appState.setGenerateRunner( checked );
}

void MainWindow::on_ClangFormatFile_clicked( bool checked )
{
	m_appState.setGenerateClangFormat( checked );
}

void MainWindow::validateDirectoryPath()
{
	if( ui->ProjectNameLineEdit->text().isEmpty() )
		throw std::runtime_error( "Project name cannot be empty" );

	const QString directoryPath = m_appState.getFilePath() + "/" + ui->ProjectNameLineEdit->text();

	if( QDir( directoryPath ).exists() )
		throw std::runtime_error( "Directory already exists." );

	if( !QDir().mkdir( directoryPath ) )
		throw std::runtime_error( "Failed to create directory." );

	m_appState.setFilePath( directoryPath );
}

void MainWindow::setContentFromConanLibraryComboBox()
{
	const int currentIndex{ ui->ConanLibraryComboBox->currentIndex() };
	if( currentIndex == 0 )
	{
		const contentCreator::fmt fmt{};
		m_appState.setConanFileContent( contentCreator::conanFileCreator( fmt.conanRequires ) );

		m_appState.setMainFileContent( contentCreator::mainFileCreator( fmt.mainContent ) );

		m_appState.setCMakeFileContent( contentCreator::cmakeFileCreator( fmt.cmakeContent ) );
	}

	if( currentIndex == 1 )
	{
		const contentCreator::nlohmann_json nlohmann_json{};
		m_appState.setConanFileContent( contentCreator::conanFileCreator( nlohmann_json.conanRequires ) );

		m_appState.setMainFileContent( contentCreator::mainFileCreator( nlohmann_json.mainContent ) );

		m_appState.setCMakeFileContent( contentCreator::cmakeFileCreator( nlohmann_json.cmakeContent ) );
	}

	if( currentIndex == 2 )
	{
		const contentCreator::zlib zlib{};
		m_appState.setConanFileContent( contentCreator::conanFileCreator( zlib.conanRequires ) );

		m_appState.setMainFileContent( contentCreator::mainFileCreator( zlib.mainContent ) );

		m_appState.setCMakeFileContent( contentCreator::cmakeFileCreator( zlib.cmakeContent ) );
	}

	if( currentIndex == 3 )
	{
		const contentCreator::sfml sfml{};
		m_appState.setConanFileContent( contentCreator::conanFileCreator( sfml.conanRequires ) );

		m_appState.setMainFileContent( contentCreator::mainFileCreator( sfml.mainContent ) );

		m_appState.setCMakeFileContent( contentCreator::cmakeFileCreator( sfml.cmakeContent ) );
	}
}

void MainWindow::on_pushButton_clicked()
{
	try
	{

		validateDirectoryPath();
		//----------------------

		const QString generatorUsed = ui->GeneratorLineEdit->text();
		const std::optional< QString > generatorUsedOpt
			= generatorUsed.isEmpty() ? std::nullopt : std::make_optional( generatorUsed );

		m_appState.setRunnerFileContent( contentCreator::runnerFileCreator( generatorUsedOpt ) );

		//----------------------
		setContentFromConanLibraryComboBox();
		m_appState.generateFiles();
		m_appState.setFilePath( ui->FilePath->text() );
		//----------------------
		QMessageBox msgBox;
		msgBox.setIcon( QMessageBox::Information );
		msgBox.setWindowTitle( "Information" );
		msgBox.setText( "Files generated correctly" );
		msgBox.setWindowIcon( QIcon{ ":/ProjectGenerator.jpg" } );
		msgBox.exec();
	}
	catch( const std::runtime_error& e )
	{
		QMessageBox::warning( nullptr, "Błąd", e.what() );
	}
}

void MainWindow::on_GitignoreFile_clicked( bool checked )
{
	m_appState.setGenerateGitignoreFormat( checked );
}

void MainWindow::on_helpButton_clicked()
{
	QFile file( ":/Help.md" );
	if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
		throw std::runtime_error( "Nie można otworzyć pliku Help.md" );

	QTextStream in( &file );
	QString markdownText = in.readAll();

	QTextEdit* textEdit = new QTextEdit();

	textEdit->setMarkdown( markdownText );
	textEdit->setWindowTitle( "Help" );
	textEdit->setReadOnly( true );
	textEdit->resize( 600, 400 );

	QIcon icon{ ":/ProjectGenerator.jpg" };
	textEdit->setWindowIcon( icon );

	textEdit->show();
}
