#ifndef CONTENTCREATORHELPER_H
#define CONTENTCREATORHELPER_H
#include <QString>

namespace contentCreator{
QString mainFileCreator(const std::optional<std::pair<QString,QString>>& libraryContent ={});
QString conanFileCreator(const std::optional<QString>& requires ={});
}

#endif // CONTENTCREATORHELPER_H
