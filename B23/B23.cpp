#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#define	MI_LEZH 101
#define MI_POD 102



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
HINSTANCE hInst;
int sw;


int APIENTRY _tWinMain(HINSTANCE This, 
	HINSTANCE Prev, 
	LPTSTR cmd, 
	int mode) 
{
	HWND hWnd; 
	MSG msg; 
	hInst = This;
	WNDCLASS wc;
	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wc.lpszMenuName = _T("menudemo");
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 12);
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName,
		_T("B23"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hWnd, mode);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HBRUSH hBrush;
	static int sx, sy;
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hPen;
	HMENU hMenu, hPopupMenu;
	TCHAR str0[] = _T("Мячик");
	TCHAR str1[] = _T("Лежит");
	TCHAR str2[] = _T("Подпрыгнул");

	switch (message)
	{
	case WM_COMMAND:
		hMenu = GetMenu(hWnd);
		switch (LOWORD(wParam))
		{
		case MI_LEZH:
			sw = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_POD:
			sw = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_CREATE:
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, MI_LEZH, str1);
		AppendMenu(hPopupMenu, MF_STRING, MI_POD, str2);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hWnd, hMenu);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(1, 50, RGB(0, 200, 0));
		SelectObject(hdc, hPen);
		MoveToEx(hdc, 0, 1000, NULL);
		LineTo(hdc, 1920, 1000);
		hPen = CreatePen(NULL, 0, NULL);
		hBrush = CreateSolidBrush(RGB(200, 0, 0));
		if (sw == 1)
		{
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);
			Ellipse(hdc, 100, 890, 200, 990);
		}
		if (sw == 2)
		{
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);
			Ellipse(hdc, 100, 600, 200, 700);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); break;
		DeleteObject(hBrush);
		DeleteObject(hPen);
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}