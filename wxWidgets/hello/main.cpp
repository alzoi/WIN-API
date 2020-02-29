// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp {
public:
	virtual bool OnInit();
};

class MyFrame1 : public wxFrame {
public:
	MyFrame1();
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};

enum {
	// Идентификатор для меню Hello.
	ID_Hello = 1
};

// Основная функция main.
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
// Инициализация приложения.

	// Создаём форму.
	MyFrame1* frame = new MyFrame1();
	frame->Show(true);
	return true;
}

MyFrame1::MyFrame1() : wxFrame(NULL, wxID_ANY, "Заголовок формы") {
// Конструктор главной формы.

	// Меню Файл.
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, "Выход", "Закрытие окна");

	// Меню Справка.
	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	// Создаём строку меню.
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);

	// Создаём строку статуса.
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");

	// Привязка обработчиков событий к пунктам меню.
	Bind(wxEVT_MENU, &MyFrame1::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MyFrame1::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame1::OnExit,  this, wxID_EXIT);

}

void MyFrame1::OnExit(wxCommandEvent& event) {
// Обработчик события - выбор пункта меню "Выход".

	Close(true);
}

void MyFrame1::OnAbout(wxCommandEvent& event) {
// Обработчик события - выбор пункта меню "Справка".

	wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame1::OnHello(wxCommandEvent& event) {
// Обработчик события - выбор пункта меню "Привет".

	wxLogMessage("Hello world from wxWidgets!");
}
