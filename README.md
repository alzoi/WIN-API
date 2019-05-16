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
