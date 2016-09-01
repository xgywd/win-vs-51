#include<windows.h>

typedef struct tagWINCLASS
{ 
	UINT ia;
	WNDPROC ipfwndproc;
	int cba;
	int cbb;
	HINSTANCE hinstance;
	HICON   hicon;
	HCURSOR hcorsor;
	HBRUSH beak;
	LPCSTR lpsza;
	LPCSTR lpszb; 
}winclass,* win;

winclass a;
HWND hwnd;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hb,PSTR szc,int iCmdShow)
{ 
	MSG msg;

	TCHAR szAppName []= L"ƒ„∫√ ¿ΩÁ!";

	a.ia=CS_HREDRAW|CS_VREDRAW;

	a.ipfwndproc=WndProc;
	a.cba=0;
	a.cbb=0; 
	a.hinstance=hinstance;
	a.hicon=LoadIcon(hinstance,IDI_APPLICATION);
	a.hcorsor=LoadCursor(NULL,IDC_ARROW);
	a.beak=(HBRUSH)GetStockObject(WHITE_BRUSH);
	a.lpsza=NULL;
	a.lpszb=(LPCSTR)szAppName;
	
	RegisterClass((WNDCLASS*)&a);
	
	hwnd=CreateWindow
	(     
		szAppName,
		TEXT("Hello World!"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinstance,
		NULL
	);
	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

return 0;	
}
LRESULT CALLBACK WndProc(HWND hwnd,UINT a,WPARAM b,LPARAM c)
{

}