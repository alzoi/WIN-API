# Установка библиотеки wxWidgets
https://www.youtube.com/watch?v=FOIbK4bJKS8&t=1484s

Скачиваем ZIP архив
https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.3/wxWidgets-3.1.3.zip

Открываем проект в VS 2019  
C:\lib\wxWidgets-3.1.3\build\msw\wx_vc16.sln  

Компилируем для Debug и Release конфигураций

Создаём новый пустой С++ проект.
В свойствах проекта выбираем:
- Компоновщик > Система: WINDOWS
- C/C++ > Общие > Дополнительные каталоги включаемых файлов: C:\lib\wxWidgets-3.1.3\include\;C:\lib\wxWidgets-3.1.3\include\msvc;
- Компоновщик > Общие > Дополнительные каталоги библиотек: C:\lib\wxWidgets-3.1.3\lib\vc_lib;
