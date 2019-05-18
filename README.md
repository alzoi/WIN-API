# WIN-API

## Ссылки 
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

Многие старые функции CRT имеют новые, более безопасные версии. Если безопасная функция существует, то старая менее безопасная версия помечена как нерекомендуемая (deprecated), а новая версия имеет суффикс _s ("secure" - "безопасный").
Пример: функция printf() заменяется более безопасной функцией printf_s() и так далее...  

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

# Компоновка (сборка приложения из объектных файлов и файлов библиотек).
main: main.o
	gcc -Wl,--subsystem,windows main.o -o main

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
