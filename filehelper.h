#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>
/*
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>


class JsonHelper {
public:
    static QJsonObject readJsonFile(const QString& filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Cannot open JSON file:" << filePath;
            return QJsonObject();
        }

        QTextStream in(&file);
        QString jsonString = in.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        return jsonDoc.object();
    }

    static bool writeJsonFile(const QString& filePath, const QJsonObject& jsonObject) {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Cannot open JSON file for writing:" << filePath;
            return false;
        }

        QJsonDocument jsonDoc(jsonObject);
        QTextStream out(&file);
        out << jsonDoc.toJson(QJsonDocument::Indented);
        file.close();

        return true;
    }
};
*/

struct GenerateFile {
    QString fileName;
    bool generateFile;
    //Json j w konstruktorze niech pobiera odrazu
    GenerateFile(const QString& defaultFileName, bool shouldGenerate = false)
        : fileName(defaultFileName), generateFile(shouldGenerate) {}
/*
    GenerateFile(const QString& defaultFileName, const QJsonObject& json)
        : fileName(defaultFileName), generateFile(json["generateFile"].toBool()) {}



    QJsonObject toJson() const {
        QJsonObject json;
        json["fileName"] = fileName;
        json["generateFile"] = generateFile;
        return json;
    }*/

};

struct MainFile : public GenerateFile {
    MainFile() : GenerateFile("main.cpp") {}
    QString includes{"include <iostream>\n"};
    //Może nawet std::pair<QString, QString> bedzie include i cos do testu tego, prosta funkcjonalnosc pokazujaca ze to dziala jakas funkcja czy cos w stylu Funkcja i wywołanie

    /*
    MainFile(const QJsonObject& json) : GenerateFile("main.cpp", json) {
        includes = json["includes"].toString();
    }

    QJsonObject toJson() const {
        QJsonObject json = GenerateFile::toJson();
        json["includes"] = includes;
        return json;
    }
    */
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

