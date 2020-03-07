# Makefile
# Сборка С/C++ проекта в Windows.

# Перейти в каталог с данным файлом и выполнить инициализацию рабочего
# окружения для компиляции программ c/c++:
# D:\vs2017c\VC\Auxiliary\Build\vcvars32.bat
# D:\vs2017c\VC\Tools\MSVC\14.13.26128\bin\Hostx86\x86\nmake.exe

all: hello.exe

CC		=cl
CFLAGS		=/nologo /MT /c /TC /W3 /D "_USING_V110_SDK71_" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE"

LINKER		=link
LINKLIBS	=user32.lib gdi32.lib
LINKFLAGS	=/nologo /SUBSYSTEM:WINDOWS",5.01" /MACHINE:X86


all: hello.exe

hello.exe: hello.obj
	$(LINKER) $(LINKFLAGS) hello.obj $(LINKLIBS) /OUT:hello.exe

hello.obj: hello.c
	$(CC) $(CFLAGS) hello.c
	
# Цель для очистки данных сборки.
cls:
	del *.exe *.obj
