
// Исключаем редко используемые компоненты из заголовков Windows.
#define WIN32_LEAN_AND_MEAN

// Файлы заголовков Windows
#include <windows.h>

// Файлы заголовков среды выполнения C.
#include <tchar.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include <crtdbg.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow) {

	// Точка входа в программу, после загрузки программы в память, ОС передаёт управление в эту функцию.
	// Входные параметры:
	// hInstance - описатель программы.

	TCHAR szAppName[] = _T("HelloWin");
	HWND         hwnd;
	MSG          msg;	
	WNDCLASSEX   wndclass = {0};

	// Регистрация в ОС класса окна.
	wndclass.cbSize			= sizeof(WNDCLASSEX);
	wndclass.hInstance		= hInstance;
	wndclass.lpszClassName	= szAppName;
	wndclass.lpfnWndProc		= WndProc;
	wndclass.style				= CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hIcon				= LoadIcon(nullptr, IDI_APPLICATION);
	wndclass.hIconSm			= LoadIcon(nullptr, IDI_APPLICATION);
	wndclass.hCursor			= LoadCursor(nullptr, IDC_ARROW);
	wndclass.hbrBackground	= nullptr; //(HBRUSH)GetStockObject(WHITE_BRUSH);
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
	// Открываем окно.
	ShowWindow(hwnd, iCmdShow);
	//UpdateWindow(hwnd);

	//while(GetMessage(&msg, nullptr, 0, 0)){}
	while(1) {
		
		// Получаем входящее (переданное ОС) сообщение из очереди сообщений нашей программы, если сообщения нет функция не блокирует поток.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Нажатие и отпускание клавиш, в переменную msg.wParam операционная система помещает виртуальный код клавиши клавиатуры.
			if (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN || msg.message == WM_KEYUP || msg.message == WM_SYSKEYDOWN) {
				_RPT3(0, "MES %x %c %x\n", msg.message, (TCHAR)msg.wParam, msg.wParam);
			}			
			
			// Выход.
			if (msg.message == WM_QUIT) {
				_RPT1(0, "%s\n", "WM_QUIT");
				break;
			}

			// Если произошло нажатие клавиши клавиатуры, просим ОС поместить в очередь входящих сообщений сообщение WM_CHAR,
			// в переменную msg.wParam операционная система помещает код нажатой клавиши в кодировке Windows-1251.
			if (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN || msg.message == WM_KEYUP || msg.message == WM_SYSKEYDOWN) {
				TranslateMessage(&msg);
			}

			// Отправляем текущее, полученное функцией PeekMessage, сообщение в ОС, которая передаст его нашей оконной процедуре.
			DispatchMessage(&msg);
			
		}
		// Обработка, если в очереди нет сообщения.
		else {

		}
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

			DrawText(hdc, TEXT("Hello, Привет, Windows!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps);
			
			return 0;
		case WM_CHAR:
			_RPT3(0, "%s %c %x\n", "WM_CHAR", (TCHAR)wParam, wParam);
			return 0;
		// Сообщение о закрытии окна.
		case WM_DESTROY:
			
			_RPT1(0, "%s\n", "WM_DESTROY");
			
			// Отправляем сообщение WM_QUIT в оконную процедуру.
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
