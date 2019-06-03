
// Исключаем редко используемые компоненты из заголовков Windows.
#define WIN32_LEAN_AND_MEAN

// Файлы заголовков Windows
#include <windows.h>

// Файлы заголовков среды выполнения C.
#include <tchar.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

	// Точка входа в программу, после загрузки программы в память, ОС передаёт управление в эту функцию.
	// Входные параметры:
	// hInstance - описатель программы.

	TCHAR szAppName[] = _T("HelloWin");
	HWND         hwnd;
	MSG          msg;	
	WNDCLASSEX   wndclass = {0};

	// Регистрация в ОС класса окна.
	wndclass.cbSize         = sizeof(WNDCLASSEX);
	wndclass.hInstance		= hInstance;
	wndclass.lpszClassName	= szAppName;
	wndclass.lpfnWndProc		= WndProc;
	wndclass.style				= CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hIcon				= LoadIcon(nullptr, IDI_APPLICATION);
	wndclass.hIconSm        = LoadIcon(nullptr, IDI_APPLICATION);
	wndclass.hCursor			= LoadCursor(nullptr, IDC_ARROW);
	wndclass.hbrBackground  = nullptr; //(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= nullptr;

	if (!RegisterClassEx(&wndclass)) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	// Создание окна с именем szAppName.
	hwnd = CreateWindow(
		szAppName,
		_T("The Hello Program"),
		// Стиль окна.
		WS_OVERLAPPEDWINDOW,
		// X, Y и размеры окна Width и Height
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		// Дескриптор (описатель) родительского окна, его нет.
		nullptr,
		// Меню.
		nullptr,
		hInstance,
		// Произвольный параметр создания окна.
		nullptr
	);              

	ShowWindow(hwnd, iCmdShow);
	//UpdateWindow(hwnd);

	while(GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	
	// Оконная функция главного окна вызывается операционной системой,
	// когда требуется передать сообщение из очереди для данного приложения.

	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

	switch (message) {
		case WM_CREATE:
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rect);

			DrawText(hdc, TEXT("Hello, Windows!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps);
			
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
