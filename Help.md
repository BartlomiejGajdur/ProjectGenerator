## Build without Cmake
```python
g++ -std=c++<WersjaCpp-11/14/17/20> <pliki do kompilacji.cpp>
```
Przykład:
```
g++ -std=c++17 main.cpp functions.cpp
```
## Cmake build

```python
mkdir build
cd build
cmake ..
make -j
```
## Cmake build - Error - 'nmake' '?' 

```python
G++ --version
Make --version
set CMAKE_C_COMPILER="gcc"
set CMAKE_CXX_COMPILER="g++"
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make -j
```
## Conan with cmake setup 
Conan to otwarte oprogramowanie do zarządzania zależnościami w projektach programistycznych w języku C++. 

Conan 2.0 - https://docs.conan.io/2/index.html - Dokumentacja

Conan 2.0 INSTALL - https://docs.conan.io/2/installation.html - Jak zainstalować Conana

ConanCenter - https://conan.io/center - Zbiór paczek i bibliotek 

```python
pip install conan
conan profile detect
```
conanfile.txt
```
[requires]
zlib/1.2.11
<XXX/XXX>

[generators]
CMakeDeps
CMakeToolchain
```
CMakeList.txt
```
cmake_minimum_required(VERSION 3.15)
project(<ProjectName>)

find_package(ZLIB REQUIRED)
find_package(XXX REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)
target_link_libraries(${PROJECT_NAME} XXX::XXX)
```
```
conan install . --output-folder=build --build=missing
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=RELEASE
make -j
./<ProjectName>.exe
```

## Mediator
To są skrypty w bashu. Pisze się takie "runnery", które odpalają program w C++ z ustawionymi parametrami. Przykład:
Ten skrypt wsadowy ma na celu usunięcie istniejącego katalogu "build", zainstalowanie zależności Conana, skonfigurowanie projektu za pomocą CMake i zbudowanie projektu przy użyciu narzędzia kompilacyjnego (np. make).

run_example.bat
```bash
@ECHO ON

set BASEDIR=%~dp0
PUSHD %BASEDIR%

RMDIR /Q /S build

conan install . --output-folder=build --build=missing
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=RELEASE
make
pause
```

```
@ECHO ON
```
Włącza tryb wyświetlania poleceń w oknie wiersza poleceń, co oznacza, że każde polecenie będzie wyświetlane przed jego wykonaniem.

```
set BASEDIR=%~dp0
```
Ustawia zmienną środowiskową BASEDIR na katalog, w którym znajduje się plik wsadowy. %~dp0 to specjalny argument w języku wsadowym, który zwraca pełną ścieżkę bieżącego pliku wsadowego.

```
PUSHD %BASEDIR%
```
Zmienia bieżący katalog na ten określony przez zmienną BASEDIR. Polecenie PUSHD umożliwia przechodzenie między katalogami i zachowuje poprzednią lokalizację na stosie, co pozwala na późniejsze łatwe powroty.

```
RMDIR /Q /S build
```
Usuwa katalog "build" (jeśli istnieje) razem z jego zawartością. Opcje /Q i /S oznaczają ciche usunięcie katalogu bez potwierdzania i usuwanie zawartości wraz z podkatalogami.

```
conan install . --output-folder=build --build=missing
```
Uruchamia polecenie conan install, które pobiera i instaluje zależności dla projektu. Opcja --output-folder=build określa katalog docelowy dla zainstalowanych paczek, a --build=missing oznacza, że Conan powinien kompilować tylko te zależności, które nie są dostępne jako paczki binarne.

```
cd build
```
Zmienia bieżący katalog na "build", aby przygotować się do budowy projektu.

```
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=RELEASE
```
Uruchamia polecenie CMake, które generuje pliki projektu na podstawie źródeł. Opcje określają generator projektu ("Unix Makefiles"), plik narzędzia dołączanego przez Conana (conan_toolchain.cmake), i tryb kompilacji (RELEASE).

```
make
```
Uruchamia polecenie make, które kompiluje projekt. To polecenie jest typowe dla systemów opartych na Unix, takich jak Linux. W systemie Windows używa się zazwyczaj polecenia nmake lub innych narzędzi do kompilacji.

```
pause
```
Polecenie pause zatrzymuje działanie pliku wsadowego, pozwalając użytkownikowi zobaczyć wyniki wykonania przed zamknięciem okna wiersza poleceń.

## Clang-Format

ClangDownload - https://github.com/llvm/llvm-project/releases/tag/llvmorg-17.0.6

```
LLVM-17.0.6-win64.exe
```

W VSC zainstalować rozszerzenie:
```
Clang-Format
Xaver Hellauer
```

Settings:
```
Clang-format: Executable
clang-format executable path
e.g. C:\Program Files\LLVM\bin\clang-format

Format on save = true
PPM -> Format Document With -> Clang-Format (default)
```


<details>
  <summary>.clang-format</summary>

<pre>
Language:        Cpp
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
ForEachMacros:
  - foreach
  - Q_FOREACH
  - BOOST_FOREACH
IncludeBlocks:   Preserve
IncludeCategories:
  - Regex:           '^"(llvm|llvm-c|clang|clang-c)/'
    Priority:        2
  - Regex:           '^(<|"(gtest|gmock|isl|json)/)'
    Priority:        3
  - Regex:           '.*'
    Priority:        1
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
</pre>

</details>



