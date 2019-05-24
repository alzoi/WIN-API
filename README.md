# WIN-API

## Ссылки 
https://docs.microsoft.com/ru-ru/cpp/cpp/cpp-language-reference?view=vs-2019  
https://docs.microsoft.com/ru-ru/cpp/?view=vs-2019  
https://docs.microsoft.com/ru-ru/windows/desktop/  
https://docs.microsoft.com/ru-ru/windows/desktop/api/  
https://docs.microsoft.com/ru-ru/cpp/windows/desktop-applications-visual-cpp?view=vs-2019
https://docs.microsoft.com/en-us/windows/desktop/learnwin32/your-first-windows-program  
http://www.charlespetzold.com/books.html  
http://www.charlespetzold.com/pw5/index.html  
http://www.firststeps.ru/mfc/winapi/hook/hook1.html
https://www.codeproject.com/Articles/559385/Custom-Controls-in-Win-API-The-Basics  
http://old-dos.ru/index.php?page=files&mode=files&do=show&id=1493  
http://mdb-blog.blogspot.com/2010/11/microsoft-spy-or-spyxx-for-download.html  
https://www.codeproject.com/Articles/2078/Guide-to-WIN32-Paint-for-Intermediates  

## Безопасные функции
https://docs.microsoft.com/ru-ru/cpp/c-runtime-library/security-features-in-the-crt?view=vs-2019  

Многие старые функции CRT имеют новые, более безопасные версии. Если безопасная функция существует, то старая менее безопасная версия помечена как нерекомендуемая (deprecated), а новая версия имеет суффикс **_s** ("secure" - "безопасный").
Пример: функция printf() заменяется более безопасной функцией printf_s() и так далее...  

## Инструменты
Сравнение данных http://meldmerge.org/

## GDI (Graphics Device Interface)
https://docs.microsoft.com/ru-ru/windows/desktop/gdi/windows-gdi  


## GDI+
https://docs.microsoft.com/en-us/windows/desktop/api/_gdiplus/  

## Direct2D
https://docs.microsoft.com/ru-ru/windows/desktop/learnwin32/your-first-direct2d-program  

## Кодировка
https://docs.microsoft.com/ru-ru/windows/desktop/learnwin32/working-with-strings  
https://docs.microsoft.com/ru-ru/cpp/text/generic-text-mappings-in-tchar-h?view=vs-2019  

Когда приложениям требовалась поддержка как Windows NT, так и Windows 95, Windows 98 и Windows Me, было полезно скомпилировать один и тот же код для строк ANSI или Unicode, в зависимости от целевой платформы. С этой целью Windows SDK предоставляет макросы, которые отображают строки в Unicode или ANSI, в зависимости от платформы.  

Макрос | Тип в кодировке Unicode (utf-8) | Тип в кодировке ANSI | Файл определения макроса
------ | --------------------------------|----------------------|-------------
TCHAR | wchar_t | char | windows.h
TEXT("x") | L"x" | "x" | windows.h
_TCHAR | wchar_t | char | tchar.h
_T("x") | L"x" | "x" | tchar.h

Если приложение необходимо скомпилировать для поддержки строк Unicode, необходимо определить символы препроцессора в коде программы (допускается макроопределения указывать при компиляции программы)
```c
#ifndef UNICODE
#define UNICODE
#define _UNICODE
#endif
```
После этого определённые в заголовках библиотек Windows SDK и Microsoft C будут переключены на функции с поддержкой юникода, примерно следующим образом
```c
#ifdef UNICODE
	#define SetWindowText  SetWindowTextW
#else
	#define SetWindowText  SetWindowTextA
#endif

#ifdef _UNICODE
	#define _tcslen     wcslen
#else
	#define _tcslen     strlen
#endif

#ifdef _UNICODE 
	#define _T(c) L##c
	#define TEXT(c) L##c
#else 
	#define _T(c) c
	#define TEXT(c) c
#endif
```
Макрос _UNICODE используется в заголовочных файлах библиотеки С, а макрос UNICODE - в заголовочных файлах библиотеки Windows SDK.

* Функция SetWindowTextA() поддерживает строки в кодировке ANSI.
* Функция SetWindowTextW() поддерживает строки в кодировке Unicode.

Компилятор Visual C++ поддерживает char и wchar_t как встроенные типы данных для кодировок ANSI и Unicode.  
Чтобы объявить литерал широких символов (для хранения символа используется более 1 байта, то есть кодировка Unicode) или строковый литерал широких символов, необходимо поставить L перед литералом
```c
wchar_t a = L'a';
wchar_t *str = L"hello";
// Тип для Unicode символов.
typedef wchar_t WCHAR;
```

# Сборка программ
Утилита gcc это коллекция компиляторов C, C++, Objective-C, Fortran , Ada, Go и D.  
Файлы с расширением *.c компилируются как язык C.  
Файлы с расширением *.cc и *.cpp компилируются как язык C++.  

Стандарты компилятора C и C++ отличаются, например представление литералов
```c
#include <stdio.h>

int main(void) {
  // В компиляторе gcc (язык C) литерал 'a' имеет тип int,
  //размер 4 байта для 32-битной архитектуры (x32) процессора.
  // В компиляторе g++ (язык C++) литерал 'a' имеет тип char, размер 1 байт.
  printf("I was compiled as %s!\n", sizeof('a') == 1 ? "C++" : "C");
  return 0;
}
```
Компиляция указанного кода в файлах с разным расширением даст отличающиеся результаты:
* для расширения *.c утилита gcc запустит компиляторы cc1 и код будет обработан по стандарту языка С;
* для расширения *.cc или *.cpp утилита gcc запустит компиляторы g++ и код будет обработан по стандарту языка С++.
```c
$ gcc -o test test.c
$ ./test
I was compiled as C!
$ g++ -o test test.cc
$ ./test
I was compiled as C++!
```

### Автоматизация сборки программ
Файл Makefile
```c
all: main

# Компоновка (сборка приложения из объектных файлов и файла библиотеки gdi32, в опции -Wl задаются параметры для компоновщика).
main: main.o
	gcc -Wl,--subsystem,windows main.o -lgdi32 -o main

# Компиляция.
main.o: main.cpp
	gcc -c -D UNICODE -D _UNICODE main.cpp
```
Команда сборки
```
make
```

Процесс получения исполняемого файла приложения
```
# Препроцессор.
cpp hello.c > hello.i 
# или -E препроцессор, -P удаляет комментарии
gcc -E -P hello.c > hello.i
# Компиляция, создаётся файл ассемблерных инструкций hello.s
gcc -S hello.i
# Ассемблирование преобразование ассемблерных инструкций в машинный объектный код.
as hello.s -o hello.o
# Компановка (связывание) объектных файлов и библиотек в исполняемый файл.
ld hello.o ...libraries... -o hello
```

## Установка MinGW (компилятор gcc для Windows)
https://www.ics.uci.edu/~pattis/common/handouts/mingweclipse/mingw.html  

Пример вывода в консоль UTF-8 символов для пакета MinGW в операционной системе Windows
```c
// source.cpp - пример вывода в консоль символов Unicode.

// Активация использования символов Unicode.
#define UNICODE
#define _UNICODE

#include <tchar.h>

#include <io.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	
	// Переключаем консоль на поддержку символов кодировки UTF-8 (_O_U8TEXT = 0x40000).
	_setmode(_fileno(stdout), 0x40000);
	const _TCHAR * str = _T("Привет ☺\x263a\n");
	_tprintf(_T("%s"), str);
	
	// Ожидание ввода.
	getchar();
	//int e; 
	//_tscanf(_T("%d"), &e);
	
	return e;
}
```
Пример вывода в консоль UTF-8 символов для пакета SDK Microsoft Visual Studio в операционной системе Windows
```c
// source.cpp - пример вывода в консоль символов Unicode.

// Активация использования символов Unicode.
#define UNICODE
#define _UNICODE

#include <tchar.h>

#include <fcntl.h>
#include <io.h>
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[]) {
		
	// Переключаем консоль на поддержку символов кодировки UTF-8.
	_setmode(_fileno(stdout), _O_U8TEXT);
	
	// Вывод строки.
	_tprintf_s(_T("Привет ☺"));
	_tprintf_s(_T("\x263a\n"));
	
	// Ожидание ввода.
	getchar();
	//int e; 
	//_tscanf_s(_T("%d"), &e);
	
	return e;
}
```

## Система сборки Microsoft Visual C++

Для выполнения операций компиляции исходных кодов на языке C/C++ и сборки исполняемых программ (*.exe файлов) необходимо подготовить рабочее окружение (создать необходимые переменные, настроить пути к стандартным библиотекам [CRT](https://docs.microsoft.com/ru-ru/cpp/c-runtime-library/crt-library-features?view=vs-2019), заголовкам библиотечных функций и [SDK](https://docs.microsoft.com/ru-ru/visualstudio/extensibility/visual-studio-sdk?view=vs-2019)).  
Окружение создаётся с помощью скриптов, которые входят в инструментарий построения приложений [Build Tools для Visual Studio](https://docs.microsoft.com/ru-ru/cpp/build/building-on-the-command-line?view=vs-2019).  
В состав Build Tools входят скрипты командной строки, которые расположены в папке Visual Studio
```
\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\
```
Основной скрипт для сборки приложения находится в файле vcvarsall.bat (внутри он запускает скрипт VsDevCmd.bat).  
Для подготовки всех необходимых переменных рабочего окружения операционной системы, которые позволяют выполнять сборку программ на пратформе x86 (32-битная архитектура процессоров) нужно создать bat-файл следующего содержания
```bat
@REM Файл - build.bat

@echo off

@REM Запустить скрипт создания рабочего окружения для сборки.
call "D:\Programs\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

@REM Добавить папку, в которой расположен данный bat-файл в перечень доступных директорий ОС.
set path = %~dp0;%path%
```
Справка по скрипту vcvarsall.bat
```cmd
vcvarsall.bat /help
```
В скриптах могут использоваться различные директивы

Директива | Описание
----------|----------
%~dp0 | получить полный путь в котором расположен файл скрипта
%* | получить все параметры переданные скрипту
%my_variable% | получить значение переменной my_variable

Можно использовать скрипт VsDevCmd.bat, если параметры не указаны, то будет подготовлено окружение для создания 32-разрядного кода x86
```
D:\Programs\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat
```
Скрипт VsDevCmd.bat запускается и при работе кода из vcvarsall.bat, ссылка на скрипт размещена в меню
```
Пуск > Все программы > Visual Studio 2017 > Visual Studio Tools > Командная строка разработчика для VS 2017
```
Все установленные переменные рабочего окружения можно посмотреть комадной
```cmd
set
```
Для сравнения можно посмотреть вывод команды **set** до запуска bat-скрипта Build системы.  
Анатомия CRT  
https://rsdn.org/article/cpp/crt.xml  
http://bytepointer.com/resources/pietrek_libctiny_2001.htm  

## Cmder  
Использование Cmder в качестве командной строки разработчика для Visual Studio
[medium.com/@ricardoserradas/how-to-use-cmder](https://medium.com/@ricardoserradas/how-to-use-cmder-as-the-developer-command-prompt-for-visual-studio-bcc54a99fc9d)  

Настрока задачи (task) VC для запуска командной оболочки Cmder с активированной командной строкой разработчика Visual Studio  
```
cmd /k ""%ConEmuDir%\..\init.bat" & "D:\Programs\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"" -new_console:d:"D:\Project\":t:"MSVC++"
```
Свойства ярлыка для запуска Cmder созданной задачей VC
```cmd
D:\Programs\cmder_mini\Cmder.exe /TASK VC
```

## Компиляция
https://docs.microsoft.com/ru-ru/cpp/build/reference/compiling-a-c-cpp-program?view=vs-2019  

Просмотр содержимого файла библиотеки vcruntimed.lib
```cmd
lib -list vcruntimed.lib
dumpbin -exports vcruntimed.lib
dumpbin -symbols vcruntimed.lib
```
Получение из машинных кодов объектного файла инструкций языка Ассемблера, то есть процесс дизассемблирования
```
dumpbin -disasm main.obj
```
Просмотр заголовков исполняемого файла
dumpbin -headers main.exe

Собрать программу и записать карту вызово в файл main.map
cl main.c -link -map
