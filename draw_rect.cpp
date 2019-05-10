// Нарисовать прямоугольник на рабочем столе.

#include <iostream>
#include <Windows.h>

int main() {

	/* hide console window */
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);

	/* Calling GetDC with argument 0 retrieves the desktop's DC */
	HDC hDC_Desktop = GetDC(0);

	/* Draw a simple blue rectangle on the desktop */
	RECT rect = { 20, 20, 200, 200 };
	HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
	FillRect(hDC_Desktop, &rect, blueBrush);

	Sleep(10);
	return 0;
}
