#include "mainwindow.h"

#include <QApplication>
#include "filehelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Tworzenie przykładowego pliku JSON
    /*
    QJsonObject jsonContent;
    jsonContent["generateFile"] = true;
    jsonContent["includes"] = "#include <iostream>\n";
    jsonContent["additionalField"] = "Dodatkowe pole";

    // Zapisywanie pliku JSON
    JsonHelper::writeJsonFile("content.json", jsonContent);

    // Wczytywanie pliku JSON do struktury MainFile
    QJsonObject jsonFromFile = JsonHelper::readJsonFile("content.json");
    MainFile mainFileFromJson(jsonFromFile);

    // Wyświetlanie danych wczytanych z pliku
    qDebug() << "generateFile: " << mainFileFromJson.generateFile;
    qDebug() << "includes: " << mainFileFromJson.includes;
    */
    AppState appState;
    MainWindow w(appState);
    w.show();
    return a.exec();
}
