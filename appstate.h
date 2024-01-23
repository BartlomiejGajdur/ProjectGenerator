#ifndef APPSTATE_H
#define APPSTATE_H

#include <QString>

#include "filehelper.h"

class AppState
{
public:
    AppState();

    //--------------------
    void setFilePath(const QString &filePath) { m_filePath = filePath; }
    QString getFilePath() const { return m_filePath; }

    //--------------------
    bool isGenerateMain() const { return mainFile.generateFile; }
    void setGenerateMain(bool value) { mainFile.generateFile = value; }

    // Getter i Setter dla generateCMake
    bool isGenerateCMake() const { return cmakeFile.generateFile; }
    void setGenerateCMake(bool value) { cmakeFile.generateFile = value; }

    // Getter i Setter dla generateConan
    bool isGenerateConan() const { return conanFile.generateFile; }
    void setGenerateConan(bool value) { conanFile.generateFile = value; }

    // Getter i Setter dla generateRunner
    bool isGenerateRunner() const { return runnerFile.generateFile; }
    void setGenerateRunner(bool value) { runnerFile.generateFile = value; }

    // Getter i Setter dla generateClangFormat
    bool isGenerateClangFormat() const { return clangFormatFile.generateFile; }
    void setGenerateClangFormat(bool value) { clangFormatFile.generateFile = value; }


    void generateFiles();

private:
    QString m_filePath{};

    MainFile mainFile;
    CMakeFile cmakeFile;
    ConanFile conanFile;
    RunnerFile runnerFile;
    ClangFormatFile clangFormatFile;

private:
    void generateFile(const QString& fileName, const QString& content);
    void generateMainFile();
    void generateCmakeFile();
    void generateConanFile();
    void generateRunnerFile();
    void generateClangFormatFile();
};

#endif // APPSTATE_H
