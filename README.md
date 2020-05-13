UE Viewer
=========

UE Viewer is a viewer for visual resources of games made with [Unreal engine](https://www.unrealengine.com/).
Currently all engine versions (from 1 to 4) are supported.

The project was originally named the "Unreal model viewer", however the name
[was changed](https://www.gildor.org/smf/index.php/topic,731.0.html) in 2011 to meet the request from Epic Games.
Please note that "official" project's name is "UE Viewer", and a short unofficial name of the project is "umodel"
(it was left from the older name "**U**nreal **MODEL** viewer").

There's a place where you may discuss the source code:
[gildor.org forums](https://www.gildor.org/smf/index.php?board=37.0).


Getting the source code
-----------------------
The source code is [available at GitHub](https://github.com/gildor2/UModel). You may either checkout it
with use of any Git client, or download it as a [Zip file](https://github.com/gildor2/UModel/archive/master.zip).


Building the source code
------------------------
Мы используем собственную систему сборки для компиляции UE Viewer. Вы можете найти Perl-скрипт в *Tools/genmake*. Этот скрипт
генерирует make-файлы проекта. После этого вы можете собрать сгенерированный make-файл
используя 'nmake' для Visual Studio или 'make' для gcc. Процесс сборки контролируется скриптом *build.sh*.

### build.sh options
Чтобы просмотреть все параметры, запустите `build.sh --help`. Текущие варианты:
- `--64` скомпилировать для Windows 64bit
- `--debug` сделать отладочную версию исполняемого файла
- `--vc <version>` указывает, какую версию Visual Studio следует использовать для компиляции, по умолчанию это самый
  последний компилятор, установленный в вашей системе

Обратите внимание, что `build.sh` - это не просто ярлык для вызова `make -f <makefile>`, он умеет выполнять больше действий.
Дополнительные возможности:
- Создание make-файла для текущей платформы.
- Создание файла `UModelTool/Version.h`, который содержит текущий номер сборки, основанный на количестве коммитов Git.
- Предварительная обработка шейдеров (с выполнением `Unreal/Shaders/make.pl`).
- Он имеет возможность скомпилировать только один файл cpp из проекта (используется с Visual Studio Code Ctrl + клавиша F7).

### Windows 32-bit

UE Viewer компилируется с использованием Visual Studio. Требуется VisualStudio 2013 или новее. Старые компиляторы Visual Studio не подходят, потому что код использует функции C++11.

В настоящее время сборка выполняется с использованием Visual C ++ 2019.

Система сборки использует GNU Tools для сборки, в частности - Bash и Perl. Версии для Windows были упакованы
с использованием инструментов, которые были частью [проекта MinGW/MSYS] (http://www.mingw.org/). Вы можете получить все, что вам нужно
для сборки [здесь](https://github.com/gildor2/BuildTools). Эта страница содержит **BuildTools**. Вам необходимо
скачать проект и распаковать его любое удобное для вас место (нажмите зеленую кнопку «Клонировать или скачать», затем «Загрузить ZIP»). Например, вы извлекли их в *C:\BuildTools*. После этого добавьте *C:\BuildTools\bin* в системную переменную среды *PATH*. В качестве альтернативы можно создать командный файл, который будет временно изменять *PATH*, а затем выполнить скрипт сборки.
Вот пример такого файла:

    @echo off
    set PATH=%PATH%;C:\BuildTools\bin
    bash build.sh

Чтобы запустить процесс сборки без пакета, просто запустите его.

    bash build.sh

### Windows 64-bit
Несмотря на то, что мы предоставляем только 32-битные сборки UE Viewer, его можно скомпилировать для 64-битной платформы. Для этого вам нужно изменить переменную в *build.sh*: *PLATFORM* необходимо изменить с `vc-win32` на `vc-win64`. Также 64-битная сборка может быть запущена с выполнением команды *build.sh --64*.

### Linux
Linux system has the most of dependencies by default. You'll need to install the following development packages if they're
not available on your system: SDL2, zlib, libpng. Of course, you'll also need gcc for compiling the project.
To build UE Viewer, simply execute the following command from terminal

    ./build.sh

When compiling for Linux, project will use system's zlib and libpng libraries. If you want to bundle (statically link) them
into umodel executable, you may find and comment the following line in *common.project*

	USE_SYSTEM_LIBS = 1

In this case, Linux build will be performed in the same way as Windows build, with compiling and bundling mentioned libraries.

### Visual Studio Code
UE Viewer contains project files needed for opening and running it from [Visual Studio Code](https://code.visualstudio.com/).
Just open viewer's folder in VSCode, and you'll get everything. Project already has a build task and launch actions set up.
Of course you'll need a [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) installed.

VSCode project comes with additional build command which could be bound to a key. Just use
```
	{
		"key": "ctrl+f7",
		"command": "workbench.action.tasks.runTask",
		"args": "Compile"
	}
```
and then Ctrl+F7 key will compile a file currently opened in editor. Of course, it won't work for headers and other non-cpp
files.

By default, Visual Studio Code project performs Debug build. If you want something else, change `.vscode/tasks.json` file,
and remove `--debug` option from `build.sh` command.


C runtime library for MSVC
--------------------------
UE Viewer is dynamically linked with CRT library, so it requires CRT DLL files to be installed onto your system. It is possible
to *statically* link with you compiler's CRT by changing a line in *common.project* (with cost of growing executable file size):

    LIBC = shared

to

    LIBC = static

UE Viewer uses custom CRT library for being able to link against MSVCRT.DLL. MSVCRT.DLL is chosen because it allows to
reduce size of UE Viewer distribution without needs to install compiler runtime libraries onto a Windows system - MSVCRT.DLL present on
_any_ Windows installation. You may disable MSVCRT.DLL linking by commenting out the line

    OLDCRT = 1

Previously there were some problems with using msvcrt.dll with Visual Studio compiler 2015 and newer. However all issues has been
solved. For those who interested in details, I've [prepared an article](https://github.com/gildor2/UModel/wiki/Using-MSVCRT.DLL-with-Visual-Studio-compiler).

If you want to use MSVCRT.DLL, you should extract **MSVCRT.zip** archive available
[here](https://github.com/gildor2/UModel/releases) to the directory LIBS one level above of UModel directory.
So, the directory structure should look like this
```
├── Libs
│   └── MSVCRT
│       ├── include
│       ├── lib
│       └── msvcrt.project
├── UModel
│   ├── Core
│   ├── Unreal
│   ...
│   ├── build.sh
│   ...
```
Also you may change MSVCRT library path by changing **WDKCRT** variable in *common.project*.


Debugging in Visual Studio
--------------------------
UE Viewer was released without a Visual Studio solution. By the way it is still possible to debug it within an IDE. You
can build a Debug version of viewer by uncommenting ```#define MAX_DEBUG 1``` in *UmodelTool/Build.h* and rebuilding the
project. After that you'll get executable with optimizations disabled, and with some extra features. For example,
if umodel.exe crashes, and it is started with *-debug* option, standard Windows window appears with prompt to close
program or debug it. You may choose "Debug with Visual Studio" there.

Also you may use `--debug` parameter for build.sh script. This will generate separate set of object files and link into
debug version of the executable (with the same executable file's name). You may quickly switch between "debug" and "release"
builds without having to fully recompile the program.

If you want to debug umodel.exe in Visual Studio without having a crash, you may load it either from IDE (```File |
Open | Project/Solution```, then select *umodel.exe*), or you may type

    devenv umodel.exe

from console.

It is recommended to use **Visual Studio 2013** IDE or newer because it has more advanced debugging features than previous studio
versions. You may copy **Tools/umodel.natvis** file to *C:\Users\Your_user_folder\My Documents\Visual Studio 20NN\Visualizers*,
and after that you'll be able to view *TArray* and *FString* structures during debug session.

### Visual Studio Code
As was mentioned earlier, UE Viewer source code comes with Visual Studio Code project. You may easily edit, launch and debug viewer
with it. For debugging, there are 2 configurations: "No arguments" runs UE Viewer with default startup UI, and for command line use
you may launch 2nd "Volatile" configuration, which reads command line string from file *docs/cmdline.cfg* - please refer to
[Response files documentation](https://github.com/gildor2/UModel/wiki/Response-file) for details on its format.

Directory structure
-------------------
Below is the list of major folders which exists in this repository or which are generated during build process.
```
├── .vscode               # Visual Studio Code project files
├── Core                  # corelibraries not related to Unreal engine
│   └── GL                # OpenGL wrapper builder
├── Docs                  # miscellaneous text files
├── Exporters             # exporters for different object types
├── Libs                  # third-party libraries used for building
├── MeshInstance          # mesh renderers
├── obj                   # all compiled object files goes there
├── Tools
│   ├── CompatTable       # source of compatibility table
│   ├── MaxActorXImport   # ActorX Importer script for 3ds Max
│   ├── PackageExtract    # Unreal package extractor source
│   └── PackageUnpack     # unreal package decompressor source
├── UI                    # library used to show UI on Windows
├── UmodelTool            # source code of umodel itself
├── Unreal                # source code of Unreal Engine framework
│   └── Shaders           # shaders used in UModel's renderer
├── Viewers               # viewers for different object types
├── build.sh              # main build script
├── common.project        # main project file, reused between different sub-projects
├── t.bat                 # Windows CMD caller for test.sh
└── test.sh               # internal script used for testing
```

License
-------
The code is not covered with any existing license yet, however I'm thinking about adding BSD 3-clause license. I just probably
need help from some people who knows about that more than I (and I don't like the idea of adding license boilerplate into all
source code files).
