// contentCreatorHelper.cpp
#include "contentCreatorHelper.h"

namespace contentCreator {
QString mainFileCreator(const std::optional<std::pair<QString, QString>>& libraryContent) {
	{

		QString defaultInclude{"#include <iostream>\n"};
		QString beginMainFunction{"int main(){\n"};
		QString endMainFunction{"\n\n\treturn 0;\n}"};
		if(!libraryContent.has_value())
		{
			return defaultInclude + "\n\n" + beginMainFunction + endMainFunction;
		}
		return defaultInclude + libraryContent.value().first + "\n\n" + beginMainFunction + libraryContent.value().second + endMainFunction;
	}
}

QString conanFileCreator(const std::optional<QString>& requires){
	if(!requires.has_value())
	{
		return "[requires]\n\n[generators]\nCMakeDeps\nCMakeToolchain";
	}
	return "[requires]\n"+requires.value()+"\n[generators]\nCMakeDeps\nCMakeToolchain";
}
} //contentCreator
