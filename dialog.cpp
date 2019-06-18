#include <windows.h>
#include <tchar.h>

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	// Оконная процедура диалога.

	// Обработка сообщений.
	switch (msg) {
		
		// Загрузка окна.
		case WM_INITDIALOG:
			return TRUE;		
				
		// Нажатие кнопок диалога.
		case WM_COMMAND:
			
			// Проверка идентификаторов кнопок.
			switch (LOWORD(wParam)) {
				
				// Cancle или OK.
				case IDCANCEL:
				case IDOK:
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
