#include "appstate.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

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
    catch (const QString& errMsg)
    {
        qDebug() << "Error during file generation: " << errMsg;
        // Obsługa błędu, na przykład wyświetlenie komunikatu dla użytkownika
    }
}

// Funkcja pomocnicza do generowania pliku o podanej nazwie i zawartości
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
        throw QString("Failed to create file: ") + fileName;
    }
}

void AppState::generateMainFile()
{
    if (mainFile.generateFile)
    {
        QString content = "int main() {\n"
                          "    // Your code here\n"
                          "}\n";
        mainFile.fileName = "gej.cpp";
        generateFile(mainFile.fileName, content);
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
        QString content = "[requires]\n"
                          "// Your Conan requirements here\n";
        generateFile(conanFile.fileName, content);
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
