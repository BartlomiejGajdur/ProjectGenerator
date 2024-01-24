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
        QString content = "cmake_minimum_required(VERSION 3.0)\n"
                          "project(MyProject)\n"
                          "// Your CMake configuration here\n";
        generateFile(cmakeFile.fileName, content);
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
        QString content = "@echo on\n"
                          "pause // Your runner script here\n";
        generateFile(runnerFile.fileName, content);
    }
}

void AppState::generateClangFormatFile()
{
    if (clangFormatFile.generateFile)
    {
        QString content = "Language: Cpp\n"
                          "BasedOnStyle: Google\n"
                          "// Your ClangFormat configuration here\n";
        generateFile(clangFormatFile.fileName, content);
    }
}
