#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>

struct GenerateFile {
    QString fileName;
    bool generateFile;

    GenerateFile(const QString& defaultFileName, bool shouldGenerate = false)
        : fileName(defaultFileName), generateFile(shouldGenerate) {}

};

struct MainFile : public GenerateFile {
    MainFile() : GenerateFile("main.cpp") {}
    QString includes{"include <iostream>\n"};

};

struct CMakeFile : public GenerateFile {
    CMakeFile() : GenerateFile("CMakeLists.txt") {}
    QString projectName{};
    QString dependencies{}; //Jakies zliby nlohmany fmt itd...
};

struct ConanFile : public GenerateFile {
    ConanFile() : GenerateFile("conanfile.txt") {}
    QString dependencies{};
};

struct RunnerFile : public GenerateFile {
    RunnerFile() : GenerateFile("runner_windows.bat") {}
    //Tutaj chyba nie potrzeba za wiele
};

struct ClangFormatFile : public GenerateFile {
    ClangFormatFile() : GenerateFile(".clang-format") {}
    //Tu też nic chyba
};

//----------------------------------------------------------

#endif // FILEHELPER_H

