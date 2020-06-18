# Установка компилятора MinGW в Windows
Запускаем файл установщик MinGW-W64-install.exe данный файл нужно скачать с сайта https://sourceforge.net/projects/mingw-w64/files/  

В папке https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/ в zip архивах хранятся исходные коды всех релизов компилятора MinGW.  
Компилятор лучше установить в папку без пробелов, например D:\dev\mingw64\  

После установки, в переменную операционной среды PATH прописываем путь до папки:
- для архитектуры x32 папка D:\dev\mingw64\mingw32\bin  
- для архитектуры x64 папка D:\dev\mingw64\mingw64\bin

В командной строке проверяем версию установленного компилятора
```
gcc -v
g++ -v
```
Библиотеки (lib) и заголовочные файлы (include) будут находиться в папке **D:\dev\mingw64\mingw32\i686-w64-mingw32\**

# Установка Code::Blocks
Бесплатная кроссплатформенная среда разработки на языках C, C++ и Fortran. Code::Blocks написана на С++ и использует библиотеку wxWidgets.  

Заходим на портал http://www.codeblocks.org/downloads/binaries  
- для архитектуры x64 выбираем версию [codeblocks-20.03mingw-setup.exe](https://www.fosshub.com/Code-Blocks.html?dwl=codeblocks-20.03mingw-setup.exe) данный установщик содержит компилятор MinGW для x64 битной архитектуры операционной системы Windows.  
- для x32 нужно скачать среду разработки без встроенного компилятора [codeblocks-20.03-32bit-setup.exe](https://www.fosshub.com/Code-Blocks.html?dwl=codeblocks-20.03-32bit-setup.exe)  

Во время установки все опции оставляем по умолчанию: нажимаем Next и OK.  
Среду лучше установить в папку D:\dev\codeblocks\  

Запускаем Code::Blocks в меню *Settings* > *Compiler...*  
Выбираем вкладку *Toolchain executables* и нажимаем кнопку *Auto-detect*  
Система должна определить папку в которую был установлен компилятор, например D:\dev\mingw64\mingw32

## Разработка приложений
Библиотеки добавляются в проект через меню *Project* > *Build options*
На вкладке *Linker settings* нажимаем кнопку *Add* и добавляем файл библиотеки, например [GDI](https://ru.wikipedia.org/wiki/GDI) (для работы с графикой в Windows) **D:\dev\mingw64\mingw32\i686-w64-mingw32\lib\libgdi32.a**
