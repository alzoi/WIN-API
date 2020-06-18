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

# Установка Code::Blocks
Бесплатная кроссплатформенная среда разработки на языках C, C++ и Fortran. Code::Blocks написана на С++ и использует библиотеку wxWidgets.  
Для установки среды заходим на портал http://www.codeblocks.org/downloads/binaries и для архитектуры x32 выбираем версию [codeblocks-20.03mingw-32bit-setup.exe](https://www.fosshub.com/Code-Blocks.html?dwl=codeblocks-20.03mingw-32bit-setup.exe)  
Во время установки все опции оставляем по умолчанию: нажимаем Next и OK.

Библиотеки и заголовочные файлы будут находиться в папке C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\

