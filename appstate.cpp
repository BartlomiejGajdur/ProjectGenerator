#include "appstate.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

AppState::AppState()
{

}

void AppState::generateFiles()
{
    try
    {
        generateMainFile();
        generateCmakeFile();
        generateConanFile();
        generateRunnerFile();
        generateClangFormatFile();
    }
	catch (const std::runtime_error& errMsg)
	{
		QMessageBox::warning(nullptr, "Błąd", errMsg.what());
	}
}

void AppState::generateFile(const QString& fileName, const QString& content)
{
    QString filePath = m_filePath + "/" + fileName;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << content;
        file.close();
    }
    else
	{
		QString errorMsg{"Failed to create file: "};
		errorMsg+= fileName;
		throw std::runtime_error(errorMsg.toStdString());
    }
}

void AppState::generateMainFile()
{
    if (mainFile.generateFile)
    {
		generateFile(mainFile.fileName, mainFile.content);
    }
}

void AppState::generateCmakeFile()
{
    if (cmakeFile.generateFile)
    {
		generateFile(cmakeFile.fileName, cmakeFile.content);
    }
}

void AppState::generateConanFile()
{
    if (conanFile.generateFile)
    {
		generateFile(conanFile.fileName, conanFile.content);
    }
}

void AppState::generateRunnerFile()
{
    if (runnerFile.generateFile)
    {
		generateFile(runnerFile.fileName, runnerFile.content);
    }
}

void AppState::generateClangFormatFile()
{
    if (clangFormatFile.generateFile)
    {
		generateFile(clangFormatFile.fileName, clangFormatFile.content);
    }
}
