File custom.h

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
