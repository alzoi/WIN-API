// Вывод прямоугольника в окно консоли.
// Сборка:
// gcc -c main.c -o main.o
// gcc main.o C:\CodeBlocks\MinGW\x86_64-w64-mingw32\lib\libgdi32.a -o main.exe

#include <stdio.h>
#include <stdlib.h>

// Определяем константу для доступа ко всем библиотекам Windows 10.
#define _WIN32_WINNT 0x0A00

#include <windows.h>

int main() {

   // Получаем описатель (дескриптор) консольного окна.
   HWND hwnd = GetConsoleWindow();

   // Получаем дескриптор контекста графического устройства связанного с окном консоли.
   HDC dc = GetDC(hwnd);

   // Получаем дескриптор стандартного объекта "кисть, закрашивающая сплошным цветом"
   // и устанавливаем его в устройстве в качестве выбранного элемента.
   SelectObject(dc, GetStockObject(DC_BRUSH));
   // В устройстве dc устанавливаем цвет для выбранной кисти.
   SetDCBrushColor(dc, RGB(255, 0, 255));

   // Рисуем прямоугольник в устройстве dc.
   Rectangle(dc, 100, 100, 250, 250);

   return 0;
}
