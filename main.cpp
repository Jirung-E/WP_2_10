/* TODO
* [x] 색상변경칸 기능 부여
* [x] 크기변경칸 기능 부여
* [x] 모양변경칸 기능 부여
* [ ] 돌 번갈아가며 움직이도록 변경
*/

#include <windows.h>
#include <tchar.h>

#include "Field.h"


HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program";


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	static Field field { 40, 40 };

	switch(iMsg) {
	case WM_CREATE:
		break;
	case WM_CHAR:
		switch(wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case L'a': case L'A':
			field.moveLeft(0);
			break;
		case L'd': case L'D':
			field.moveRight(0);
			break;
		case L'w': case L'W':
			field.moveUp(0);
			break;
		case L's': case L'S':
			field.moveDown(0);
			break;
		case L'r': case L'R':
			field.reset();
		}
		break;
	case WM_KEYDOWN:
		switch(wParam) {
		case VK_LEFT:
			field.moveLeft(1);
			break;
		case VK_RIGHT:
			field.moveRight(1);
			break;
		case VK_UP:
			field.moveUp(1);
			break;
		case VK_DOWN:
			field.moveDown(1);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		field.show(hWnd, hdc);
		EndPaint(hWnd, &ps);
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX WndClass;
	MSG Message;

	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW | WS_SYSMENU, 100, 50, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}
