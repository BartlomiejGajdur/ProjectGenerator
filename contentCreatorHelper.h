#ifndef CONTENTCREATORHELPER_H
#define CONTENTCREATORHELPER_H
#include <QString>

namespace contentCreator{
using libraryContent = std::pair<QString, QString>;

QString mainFileCreator(const std::optional<libraryContent>& libraryContent ={});
QString conanFileCreator(const std::optional<QString>& requires ={});
QString runnerFileCreator(const std::optional<QString>& preset ={});
QString cmakeFileCreator(const std::optional<QString>& libraryContent ={});
QString clangFormatFileCreator();
QString gitignoreFormatFileCreator();

struct library{
	virtual void fillData() = 0;

	QString conanRequires;
	QString cmakeContent;
	libraryContent mainContent;
};

struct fmt : public library{
	fmt(){fillData();}

	void fillData() override;
};

struct nlohmann_json : public library{
	nlohmann_json(){fillData();}

	void fillData() override;
};

struct zlib : public library{
	zlib(){fillData();}

	void fillData() override;
};

struct sfml : public library{
	sfml(){fillData();}

	void fillData() override;
};

}

#endif // CONTENTCREATORHELPER_H
