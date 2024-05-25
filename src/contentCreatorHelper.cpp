#include "../include/contentCreatorHelper.h"

#include <QDebug>

namespace contentCreator
{
QString mainFileCreator( const std::optional< libraryContent >& content )
{

	libraryContent mainContent{ "#include <iostream>\n", "int main(){\n" };

	if( content.has_value() )
	{
		mainContent.first += content.value().first;
		mainContent.second += content.value().second;
	}

	QString endMainFunction{ R"(

std::cout << "Press Enter to exit...";
getchar();
return 0;
}
)" };

	return mainContent.first + mainContent.second + endMainFunction;
}

QString conanFileCreator( const std::optional< QString >& requires )
{
	if( !requires.has_value() )
	{
		return "[requires]\n\n[generators]\nCMakeDeps\nCMakeToolchain";
	}
	return "[requires]\n" +
		requires
		.value() + "\n[generators]\nCMakeDeps\nCMakeToolchain";
}

QString runnerFileCreator( const std::optional< QString >& preset )
{

	QString presetToSet{};
	// qDebug()<<preset.value();
	if( preset.has_value() )
		presetToSet = "-G \"" + preset.value() + "\" ";

	return QString( R"(@ECHO ON
set BASEDIR=%~dp0
PUSHD %BASEDIR%
RMDIR /Q /S build
conan install . --output-folder=build --build=missing
cd build
cmake .. )" )
		+ presetToSet + R"(-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=RELEASE
make

echo If build is successful, start build/ProjectGenerator.exe

pause
)";
}

QString cmakeFileCreator( const std::optional< QString >& libraryContent )
{
	QString cmakeContent{
		R"(cmake_minimum_required(VERSION 3.15)
project(ProjectGenerator)

add_executable(${PROJECT_NAME} main.cpp)

	)"
	};

	if( libraryContent.has_value() )
		cmakeContent += libraryContent.value();

	return cmakeContent;
}

QString clangFormatFileCreator()
{
	QString clangFormatContent{
		R"(Language:        Cpp
BasedOnStyle: LLVM
IndentWidth: 4
UseTab: Never
MaxEmptyLinesToKeep: 1
ColumnLimit: 80
)"
	};

	return clangFormatContent;
}

QString gitignoreFormatFileCreator()
{
	QString gitignoreFormatContent{
		R"(
#build
build
# Prerequisites
*.d

# Compiled Object files
*.slo
*.lo
*.o
*.obj

# Precompiled Headers
*.gch
*.pch

# Compiled Dynamic libraries
*.so
*.dylib
*.dll

# Fortran module files
*.mod
*.smod

# Compiled Static libraries
*.lai
*.la
*.a
*.lib

# Executables
*.exe
*.out
*.app
)"
	};

	return gitignoreFormatContent;
}

void fmt::fillData()
{
	this->conanRequires = "fmt/10.2.1";
	this->cmakeContent =
		R"(
	find_package(fmt REQUIRED)
	target_link_libraries(${PROJECT_NAME} fmt::fmt)
	)";

	this->mainContent.first	 = "#include <fmt/chrono.h>\n\n";
	this->mainContent.second = "\n auto now = std::chrono::system_clock::now();";
	this->mainContent.second += "\n fmt::print(\"Date and time: {}\\n\", now);";
	this->mainContent.second += "\n fmt::print(\"Time: {:%H:%M}\\n\", now);\n";
}

void nlohmann_json::fillData()
{
	this->conanRequires = "nlohmann_json/3.11.3";
	this->cmakeContent =
		R"(
			find_package(nlohmann_json REQUIRED)
			target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
			)";

	this->mainContent.first = "#include <nlohmann/json.hpp>\n\n";

	this->mainContent.second = R"(

nlohmann::json myJson = {
		{"Name", "John"},
		{"Age", 30},
		{"City", "New York"}
	};

	// Wyświetl JSON
	std::cout << myJson.dump(4) << std::endl;
)";
}

void zlib::fillData()
{
	this->conanRequires = "zlib/1.3.1";
	this->cmakeContent =
		R"(
	find_package(ZLIB REQUIRED)
	target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)
)";

	this->mainContent.first	 = "#include <zlib.h>\n";
	this->mainContent.second = R"(
if (ZLIB_VERNUM >= 0x1280) {
		std::cout << "Zlib is installed and the version is compatible." << std::endl;
	} else {
		std::cout << "Zlib is either not installed or the version is not compatible." << std::endl;
	}
)";
}

void sfml::fillData()
{
	this->conanRequires =
		R"(sfml/2.6.1
freetype/2.13.2
stb/cci.20230920
flac/1.4.3
openal-soft/1.22.2
vorbis/1.3.7
minimp3/cci.20211201
)";

	this->cmakeContent =
		R"(
# Wyszukaj i załaduj SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Dołącz katalogi nagłówkowe SFML
target_include_directories(ProjectGenerator PRIVATE ${SFML_INCLUDE_DIRS})

# Podłącz biblioteki SFML
target_link_libraries(ProjectGenerator PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
)";

	this->mainContent.first	 = "#include <SFML/Graphics.hpp>\n\n";
	this->mainContent.second = R"(
 // Utwórz okno SFML
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Example");

	// Główna pętla programu
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Wyczyszczenie okna
		window.clear();

		// Tu dodaj swoje elementy graficzne, animacje itp.

		// Wyświetlenie zawartości okna
		window.display();
	}
)";
}

} // namespace contentCreator
