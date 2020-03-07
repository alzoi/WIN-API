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
