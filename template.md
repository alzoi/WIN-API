# File custom.h

```cpp
// File custom.h

#ifndef _CUSTOM_H_
#define _CUSTOM_H_

#include <windows.h>

// Объявление прототипов функций.
void DrawEx(HWND p_hWnd);
void DrawEx1(HWND p_hWnd);

// Определение констант.
// Идентификаторы для кодов кнопок.
#define ID_KEY1	100

#endif // _CUSTOM_H_
```

# File main.cpp

```cpp
// File main.cpp

// Включить общие элементы управления уличшенного стиля (версия v6) в манифест.
#pragma comment(linker,"\"/manifestdependency:type='Win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

// Исключите редко используемые компоненты из заголовков Windows.
#define WIN32_LEAN_AND_MEAN

// Файлы заголовков Windows.
#include <windows.h>
#include "custom.h"

//#
// Объявления функций:

// Регистрация класса главного окна.
ATOM RegisterMainClass(HINSTANCE p_instance, const wchar_t* p_name_class);

// Создать главное окно.
HWND CreateMainWindow(HINSTANCE p_instance, int p_mode, const wchar_t* p_name_window);

// Оконная функции для получения сообщений, ОС передаёт сообщения из очереди обработки
// именно в эту функцию обратного вызова.
LRESULT CALLBACK WndMainProc(HWND, UINT, WPARAM, LPARAM);

//#
// Глобальные переменные:

//	Дескриптор текущего экземпляра приложения, этот дескриптор содержит адрес начала кода программы.
static HINSTANCE G_hInstance;
// Дескриптор элемента (окна) - Кнопка1.
static HWND G_hButton1;

int APIENTRY wWinMain(
	// Указатель на дескриптор текущего приложения (*.exe) загруженного в память ОС, инстанция, экземпляр приложения.
	_In_ HINSTANCE p_this,
	// В современных системах всегда 0 (в 16 битных ОС - указатель на предыдущий экземпляр приложения).
	_In_opt_ HINSTANCE p_prev,
	// Командная строка в Unicode (UTF-8).
	_In_ LPTSTR p_cmd,
	// Режим отображения окна (свёрнуто, развёрнуто и т. д.).
	_In_ int p_mode
) {
	// Функция - Стандартная точка входа в программу.

	// Имя экземпляра класса главного окна приложения.
	const wchar_t *MainWinName = L"FormMain";

	// Создаём главное окно приложения.
	HWND hWnd = CreateMainWindow(p_this, p_mode, MainWinName);
	if (hWnd == nullptr) {
		return 1;
	}

	// Структура для хранения сообщений от ОС.
	MSG msg = { 0 };

	// Цикл обработки сообщений от ОС, GetMessage выбирает очередное сообщение из очереди и блокирует поток, если в очереди пусто.
	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (IsDialogMessage(hWnd, &msg)) {
			continue;
		}
		// Функция трансляции кодов нажатой клавиши клавиатуры.
		TranslateMessage(&msg);
		// Посылаем сообщение в оконную функцию окна данного приложения.
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
HWND CreateMainWindow(HINSTANCE p_Inst, int p_mode, const wchar_t* p_name_window) {
// Создаём главное окно.

	// Регистрация класса главного окна данного приложения, выход если ошибка.
	if (!RegisterMainClass(p_Inst, p_name_window)) {
		return nullptr;
	}

	// Запоминаем экземпляр приложения в глобальной переменной.
	G_hInstance = p_Inst;

	// Создаём окно и получаем указатель (дескриптор) на него.
	HWND hWnd = CreateWindow(
		// Имя класса окна.
		p_name_window,
		// Заголовок окна, сообщаем компилятору, что строка задана в кодировке UTF-8.
		L"Каркас классического Windows-приложения (世界你好!)",
		// Стиль окна
		WS_OVERLAPPEDWINDOW,
		// X, Y и размеры окна Width и Height
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// Дескриптор родительского окна
		HWND_DESKTOP,
		// Нет меню
		NULL,
		// Дескриптор приложения
		G_hInstance,
		// Дополнительной информации нет
		NULL
	);

	if (!hWnd) {
		return nullptr;
	}

	// Показываем окно hWnd
	ShowWindow(hWnd, p_mode);
	// Обновляем окно, для запуска перерисовки.
	UpdateWindow(hWnd);

	return hWnd;
}

ATOM RegisterMainClass(HINSTANCE p_instance, const wchar_t *p_name_class) {
	// Регистрация класса окна.

	// Класс окна.
	WNDCLASSEXW wc = { 0 };

	// Размер структуры.
	wc.cbSize = sizeof(WNDCLASSEX);
	// Определение класса окна
	wc.hInstance = p_instance;
	// Имя класса окна
	wc.lpszClassName = p_name_class;
	// Функция окна для обработки сообщения от ОС (операционной системы)
	wc.lpfnWndProc = WndMainProc;
	// Стиль окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// Стандартная иконка
	wc.hIcon = LoadIcon(wc.hInstance, IDI_APPLICATION);
	// Маленькая иконка.
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);
	// Стандартный курсор
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// Нет меню
	wc.lpszMenuName = NULL;
	// Нет дополнительных данных класса
	wc.cbClsExtra = 0;
	// Нет дополнительных данных окна
	wc.cbWndExtra = 0;
	// Заполнение окна цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //CreateSolidBrush(GetSysColor(COLOR_3DFACE));//(HBRUSH)(COLOR_WINDOW + 1);

	// Регистрация класса окна в ОС.
	return RegisterClassExW(&wc);
}

LRESULT CALLBACK WndMainProc(HWND p_hWnd, UINT p_message, WPARAM p_wParam, LPARAM p_lParam) {
	// Оконная функция главного окна вызывается операционной системой, когда требуется передать сообщение из очереди для данного приложения.

	//HINSTANCE L_hInstance;
	// Получаем декскриптор текущего приложения.
	//L_hInstance = (HINSTANCE)GetWindowLong(p_hWnd, GWL_HINSTANCE);

	// Обработчик сообщений
	switch (p_message) {
		// Создание окна.
		case WM_CREATE:
			// Создаём окно класса BUTTON
			G_hButton1 = CreateWindow(L"BUTTON", L"OK",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 100, 200, 120, 28,
				// Указатель на родительское окно.
				p_hWnd,
				// Код кнопки.
				(HMENU)ID_KEY1,
				// Дескриптор приложения.
				G_hInstance,
				NULL
			);
			break;

		// Обработка команд.
		case WM_COMMAND:
			if (LOWORD(p_wParam) == ID_KEY1) {
				MessageBox(p_hWnd, L"Clicked the real button.", L"Click!", MB_OK);
			}
			//switch (p_wParam) {
			//	case ID_KEY1:
			//		MessageBox(p_hWnd, L"Clicked the real button.", L"Click!", MB_OK);
			//		break;
			//	}
			break;
		
		// Необходимость отрисовки области окна.
		case WM_PAINT:
			DrawEx(p_hWnd);
			break;
		
		// Завершение программы
		case WM_DESTROY:
			// Выходим из цикла обработки сообщений
			PostQuitMessage(0);
			break;
		
		// Обработка остальных сообщений по умолчанию
		default:
			return DefWindowProc(p_hWnd, p_message, p_wParam, p_lParam);
	}
	return 0L;
}
```

# File custom.cpp

```cpp
// File custom.cpp

#include "custom.h"

void DrawEx(HWND p_hWnd) {
	// Функция рисования в окне

	// Контекст графического устройства
	HDC hdc;
	// Структура, описывающая контекст.
	PAINTSTRUCT ps;

	// Получаем контекст графического устройства для окна p_hWnd.
	hdc = BeginPaint(p_hWnd, &ps);

	if (hdc) {
		// Рисуем прямоугольники.
		for (int i = 0; i < 10; i++) {
			Rectangle(hdc, i * 30, i * 20, i * 30 + 70, i * 20 + 50);
		}
		// Вывод текста длиной 14 символов
		TextOut(hdc, 100, 70, L"Строка String 世", 15);
	}
	// Удаляем контекст из памяти
	EndPaint(p_hWnd, &ps);
}

void DrawEx1(HWND p_hWnd) {
	// Функция рисования в окне

	HDC hdc;
	// Получаем контекст окна
	hdc = GetDC(p_hWnd);
	if (hdc) {
		// Рисуем прямоугольники.
		for (int i = 0; i < 10; i++) {
			Rectangle(hdc, i * 30, i * 20, i * 30 + 70, i * 20 + 50);
		}
	}
	// Удаляем контекст из памяти
	ReleaseDC(p_hWnd, hdc);
}
```
