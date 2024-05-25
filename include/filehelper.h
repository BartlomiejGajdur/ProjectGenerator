#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>

#include "contentCreatorHelper.h"

struct GenerateFile
{
	QString fileName{};
	QString content{};
	bool generateFile;

	GenerateFile( const QString& defaultFileName, bool shouldGenerate = false )
		: fileName( defaultFileName ), generateFile( shouldGenerate )
	{
	}
};

struct MainFile : public GenerateFile
{
	MainFile() : GenerateFile( "main.cpp" )
	{
		content = contentCreator::mainFileCreator();
	}
};

struct CMakeFile : public GenerateFile
{
	CMakeFile() : GenerateFile( "CMakeLists.txt" )
	{
		content = contentCreator::cmakeFileCreator();
	}
};

struct ConanFile : public GenerateFile
{
	ConanFile() : GenerateFile( "conanfile.txt" )
	{
		content = contentCreator::conanFileCreator();
	}
};

struct RunnerFile : public GenerateFile
{
	RunnerFile() : GenerateFile( "runner_windows.bat" )
	{
		content = contentCreator::runnerFileCreator();
	}
};

struct ClangFormatFile : public GenerateFile
{
	ClangFormatFile() : GenerateFile( ".clang-format" )
	{
		content = contentCreator::clangFormatFileCreator();
	}
};

struct GitignoreFile : public GenerateFile
{
	GitignoreFile() : GenerateFile( ".gitignore" )
	{
		content = contentCreator::gitignoreFormatFileCreator();
	}
};

//----------------------------------------------------------

#endif // FILEHELPER_H
