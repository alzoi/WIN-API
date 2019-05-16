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


## GDI (Graphics Device Interface)
https://docs.microsoft.com/ru-ru/windows/desktop/gdi/windows-gdi  


## GDI+
https://docs.microsoft.com/en-us/windows/desktop/api/_gdiplus/  

## Direct2D
https://docs.microsoft.com/ru-ru/windows/desktop/learnwin32/your-first-direct2d-program  

## Кодировка
https://docs.microsoft.com/ru-ru/windows/desktop/learnwin32/working-with-strings  

Когда приложениям требовалась поддержка как Windows NT, так и Windows 95, Windows 98 и Windows Me, было полезно скомпилировать один и тот же код для строк ANSI или Unicode, в зависимости от целевой платформы. С этой целью Windows SDK предоставляет макросы, которые отображают строки в Unicode или ANSI, в зависимости от платформы.  

Макрос | Тип в кодировке Unicode (utf-8) | Тип в кодировке ANSI
------ | --------------------------------|----------------------
TCHAR | wchar_t | char
TEXT("x") | L"x" | "x"
_T("x") | L"x" | "x"

Если приложение необходимо скомпилировать для поддержки строк Unicode, необходимо определить символы препроцессора
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
```

* Функция SetWindowTextA() поддерживает строки в кодировке ANSI.
* Функция SetWindowTextW() поддерживает строки в кодировке Unicode.

# Сборка программ
Стандарты компилятора с и с++ отличаются, например представление литералов
```c
#include <stdio.h>

int main(void) {
  // В компиляторе gcc (язык c) литерал 'a' имеет тип int, размер 4 байта для 32-битной архитектуры x32.
  // В компиляторе g++ (язык c++) литерал 'a' имеет тип char, размер 1 байт.
  printf("I was compiled as %s!\n", sizeof('a') == 1 ? "C++" : "C");
  return 0;
}
```
