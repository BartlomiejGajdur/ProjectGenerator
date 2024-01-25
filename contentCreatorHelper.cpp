// contentCreatorHelper.cpp
#include "contentCreatorHelper.h"



namespace contentCreator {
QString mainFileCreator(const std::optional<libraryContent>& content) {

	libraryContent mainContent{"#include <iostream>\n","int main(){\n"};

	if (content.has_value())
	{
		mainContent.first += content.value().first;
		mainContent.second += content.value().second;
	}

	QString endMainFunction
	{R"(

std::cout << "Press Enter to exit...";
getchar();
return 0;
}
)"};

	return mainContent.first + mainContent.second + endMainFunction;
}

QString conanFileCreator(const std::optional<QString>& requires){
	if(!requires.has_value())
	{
		return "[requires]\n\n[generators]\nCMakeDeps\nCMakeToolchain";
	}
	return "[requires]\n"+requires.value()+"\n[generators]\nCMakeDeps\nCMakeToolchain";
}

QString runnerFileCreator(const std::optional<QString>& preset){

	QString presetToSet{"Unix Makefiles"};
	if (preset.has_value())
		presetToSet = preset.value();

	return QString(R"(@ECHO ON
	set BASEDIR=%~dp0
	PUSHD %BASEDIR%
	RMDIR /Q /S build
	conan install . --output-folder=build --build=missing
	cd build
	cmake .. -G)") + " \"" + presetToSet + "\" " + R"(-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=RELEASE
	make
	pause)";

}

QString cmakeFileCreator(const std::optional<QString>& libraryContent)
{
	QString cmakeContent{
	R"(
	cmake_minimum_required(VERSION 3.15)
	project(compressor)

	add_executable(${PROJECT_NAME} main.cpp)

	)"
	};

	if (libraryContent.has_value())
		cmakeContent+=libraryContent.value();

	return cmakeContent;
}

QString clangFormatFileCreator()
{
	QString clangFormatContent{
R"(Language:        Cpp
# BasedOnStyle:  WebKit
AccessModifierOffset: -4
AlignAfterOpenBracket: true
AlignConsecutiveAssignments: true
AlignConsecutiveDeclarations: false
AlignEscapedNewlines: Left
AlignOperands:   false
AlignTrailingComments: true
AllowAllParametersOfDeclarationOnNextLine: true
AllowShortBlocksOnASingleLine: false
AllowShortCaseLabelsOnASingleLine: false
AllowShortFunctionsOnASingleLine: Empty
AllowShortIfStatementsOnASingleLine: false
AllowShortLoopsOnASingleLine: false
AlwaysBreakAfterDefinitionReturnType: None
AlwaysBreakAfterReturnType: None
AlwaysBreakBeforeMultilineStrings: false
AlwaysBreakTemplateDeclarations: true
BinPackArguments: false
BinPackParameters: false
BreakBeforeBraces: Allman
BraceWrapping:
  AfterClass:      true
  AfterControlStatement: true
  AfterEnum:       true
  AfterFunction:   true
  AfterNamespace:  true
  AfterObjCDeclaration: true
  AfterStruct:     true
  AfterUnion:      false
  AfterExternBlock: true
  BeforeCatch:     true
  BeforeElse:      true
  IndentBraces:    false
  SplitEmptyFunction: true
  SplitEmptyRecord: true
  SplitEmptyNamespace: true
BreakBeforeBinaryOperators: All
BreakBeforeInheritanceComma: false
BreakBeforeTernaryOperators: false
BreakConstructorInitializersBeforeComma: false
BreakConstructorInitializers: BeforeColon
BreakAfterJavaFieldAnnotations: false
BreakStringLiterals: true
ColumnLimit:     120
CommentPragmas:  '^ IWYU pragma:'
CompactNamespaces: false
ConstructorInitializerAllOnOneLineOrOnePerLine: true
ConstructorInitializerIndentWidth: 4
ContinuationIndentWidth: 4
Cpp11BracedListStyle: false
DerivePointerAlignment: false
DisableFormat:   false
ExperimentalAutoDetectBinPacking: false
FixNamespaceComments: true
IncludeIsMainRegex: '(Test)?$'
IndentCaseLabels: false
IndentPPDirectives: None
IndentWidth:     4
IndentWrappedFunctionNames: false
JavaScriptQuotes: Leave
JavaScriptWrapImports: true
KeepEmptyLinesAtTheStartOfBlocks: true
MacroBlockBegin: '^[A-Z_]+_(BEGIN|CONTINUE)[A-Z_]*$|^[A-Z_]*(BEGIN|CONTINUE)_[A-Z_]+$|^CPP_INTERFACE(_[1-9]+)?$|^glBegin'
MacroBlockEnd:   '^[A-Z_]+_END[A-Z_]*$|^[A-Z_]*END_[A-Z_]+$|^CPP_INTERFACE_END$|^glEnd'
MaxEmptyLinesToKeep: 1
NamespaceIndentation: None
ObjCBlockIndentWidth: 4
ObjCSpaceAfterProperty: true
ObjCSpaceBeforeProtocolList: true
PenaltyBreakAssignment: 2
PenaltyBreakBeforeFirstCallParameter: 19
PenaltyBreakComment: 300
PenaltyBreakFirstLessLess: 120
PenaltyBreakString: 1000
PenaltyExcessCharacter: 1000000
PenaltyReturnTypeOnItsOwnLine: 600
PointerAlignment: Left
ReflowComments:  true
SortIncludes: false
SpaceAfterCStyleCast: false
SpaceAfterTemplateKeyword: false
SpaceBeforeAssignmentOperators: true
SpaceBeforeParens: Never
SpaceInEmptyParentheses: false
SpacesBeforeTrailingComments: 1
SpacesInAngles:  true
SpacesInContainerLiterals: true
SpacesInCStyleCastParentheses: true
SpacesInParentheses: true
SpacesInSquareBrackets: true
Standard:        Cpp11
TabWidth:        4
UseTab:          Always
)"
	};

	return clangFormatContent;
}

void fmt::fillData(){
	this->conanRequires = "fmt/10.2.1";
	this->cmakeContent =
	R"(
	find_package(fmt REQUIRED)
	target_link_libraries(${PROJECT_NAME} fmt::fmt)
	)";

	this->mainContent.first = "#include <fmt/chrono.h>\n\n";
	this->mainContent.second = "\n auto now = std::chrono::system_clock::now();";
	this->mainContent.second += "\n fmt::print(\"Date and time: {}\\n\", now);";
	this->mainContent.second += "\n fmt::print(\"Time: {:%H:%M}\\n\", now);\n";
}

void nlohmann_json::fillData(){
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

} //contentCreator
