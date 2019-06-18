// dialog.cpp - пример использования диалоговых окон размещённых в файле ресурсов приложения.
// На форме диалога две кнопки OK и Cancel.
// Для того, чтобы задать пользовательскую отрисовку кнопки OK необходимо установить свойство Owner Draw = true .

#include <windows.h>
#include <tchar.h>

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	// Оконная процедура диалога.

	LPDRAWITEMSTRUCT pdis;
	RECT rc;
	HBRUSH brush;

	// Обработка сообщений.
	switch (msg) {
		
		// Загрузка окна.
		case WM_INITDIALOG:
			return TRUE;		
		
		// Отрисовка пользовательской графики для дочерних окон (элементов интерфейса).
		case WM_DRAWITEM:
			
			// Получаем параметры элемента.
			pdis = (LPDRAWITEMSTRUCT)lParam;
			
			// Рисуем на поверхности кнопки OK.
			if(pdis->CtlID == IDOK) {

				// Получаем описатель стандартной белой кисти для заливки фона кнопки.
				brush = (HBRUSH)GetStockObject(WHITE_BRUSH);

				// Если кнопка нажата.
				if (pdis->itemState & ODS_SELECTED){
					
					// Создаём логическую кисть (её нужно удалять).
					//brush = CreateSolidBrush(RGB(150, 150, 150));
					
					// Получаем указатель на системну кисть.
					brush = (HBRUSH)GetSysColorBrush(COLOR_3DSHADOW);
				}
				
				// Основа кнопки.
				FillRect(pdis->hDC, &pdis->rcItem, brush);
				FrameRect(pdis->hDC, &pdis->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));
				SetBkMode(pdis->hDC, TRANSPARENT);
				TextOut(pdis->hDC, pdis->rcItem.right/2-5, 5, "OK", 2);

				// Если кнопка получила фокус выбора.
				if (pdis->itemState & ODS_FOCUS) {
					rc = pdis->rcItem;
					rc.left		+=3;
					rc.top		+=3;
					rc.bottom	-=3;
					rc.right		-=3;
					FrameRect(pdis->hDC, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
				}

				// Удаляем логическую кисть.
				//DeleteObject(brush);
			}

			return 0;
				
		// Нажатие кнопок диалога.
		case WM_COMMAND:
			
			// Проверка идентификаторов кнопок.
			switch (LOWORD(wParam)) {
				
				// Cancle или OK.
				case IDCANCEL:
				//case IDOK:
					// Закрываем окно.
					EndDialog(hwnd, 0);
					return TRUE;
			}
			return FALSE;
				
		// Закрытие окна.
		case WM_CLOSE:
			EndDialog(hwnd, 0);
			return TRUE;
	}

	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd) {
	
	// Основная функция приложения.

	// Создаём модальное окно диалога с идентификатором 101 (который преобразуется в строку), которое должно быть создано (описано) в файле ресурсов проекта *.rc.
	DialogBox(hInst, MAKEINTRESOURCE(101), 0, DlgProc);
	
	return 0;
}
