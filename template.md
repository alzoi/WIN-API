# File custom.h
```
// File custom.h

#ifndef _CUSTOM_H_
#define _CUSTOM_H_

#include <windows.h>

// Объявление прототипов функций.
// Оконная функции для получения сообщений,
// ОС передаёт сообщения из очереди обработки именно в эту функцию обратного вызова.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawEx(HWND p_hWnd);
void DrawEx1(HWND p_hWnd);

// Определение констант.
// Идентификаторы для кодов кнопок.
#define ID_KEY1	100

#endif // _CUSTOM_H_
```

# File main.cpp
```
// File main.cpp

// Определяем манифест, для использования стилей элементов определённых в ОС.
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

#include <windows.h>
#include "custom.h"

// Определение глобальных переменных:
// Строка - Имя класса главного окна.
const wchar_t *G_WinName = L"FormMain";
//wchar_t G_WinName[] = L"FormMain";
//	Дескриптор текущего экземпляра приложения, этот дескриптор содержит адрес начала кода программы.
static HINSTANCE G_hInstance;
// Дескриптор элемента (окна) - Кнопка1.
static HWND G_hButton1;

int APIENTRY wWinMain(
	// Дескриптор текущего приложения
	HINSTANCE p_this,
	// В современных системах всегда 0
	HINSTANCE p_prev,
	// Командная строка
	LPTSTR p_cmd,
	// Режим отображения окна
	int p_mode
) {
	// Функция - Стандартная точка входа в программу.

	// Дескриптор главного окна программы
	HWND hWnd;
	// Структура для хранения сообщения
	MSG msg;
	// Класс окна	
	WNDCLASS wc = { 0 };

	G_hInstance = p_this;

	// Определение класса окна
	wc.hInstance = G_hInstance;
	// Имя класса окна
	wc.lpszClassName = G_WinName;
	// Функция окна для обработки сообщения от ОС (операционной системы)
	wc.lpfnWndProc = WndProc;
	// Стиль окна
	wc.style = NULL; //CS_HREDRAW | CS_VREDRAW;
	// Стандартная иконка
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// Стандартный курсор
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// Нет меню
	wc.lpszMenuName = NULL;
	// Нет дополнительных данных класса
	wc.cbClsExtra = 0;
	// Нет дополнительных данных окна
	wc.cbWndExtra = 0;

	// Заполнение окна цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW); //CreateSolidBrush(GetSysColor(COLOR_3DFACE));//(HBRUSH)(COLOR_WINDOW + 1);

	// Регистрация класса окна в ОС, выход, если ошибка.
	if (!RegisterClass(&wc)) {
		return 0;
	}

	// Создаём окно и получаем указатель (дескриптор) на него.
	hWnd = CreateWindow(
		// Имя класса окна.
		G_WinName,
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

	// Выход, если ошибка
	if (!hWnd) {
		return NULL;
	}

	// Показываем окно hWnd
	ShowWindow(hWnd, p_mode);
	// Обновляем окно
	UpdateWindow(hWnd);

	// Цикл обработки сообщений от ОС, GetMessage выбирает очередное сообщение из очереди и блокирует поток, если в очереди пусто.
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		// Функция трансляции кодов нажатой клавиши.
		TranslateMessage(&msg);
		// Посылает сообщение в оконную функцию WndProc() окна.
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND p_hWnd, UINT p_message, WPARAM p_wParam, LPARAM p_lParam) {
	// Оконная функция вызывается операционной системой, когда требуется передать сообщение из очереди для данного приложения.

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
```
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
