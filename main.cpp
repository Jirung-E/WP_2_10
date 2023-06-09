/* TODO
* [x] 색상변경칸 기능 부여
* [x] 크기변경칸 기능 부여
* [x] 모양변경칸 기능 부여
* [x] 돌 번갈아가며 움직이도록 변경
*     [x] 에러메세지 출력
*     [x] 서로 안겹치도록
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
	static bool s1moved = false;
	static bool s2moved = false;
	static bool s1error = false;
	static bool s2error = false;

	switch(iMsg) {
	case WM_CREATE:
		break;
	case WM_CHAR:
		switch(wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case L'r': case L'R':
			field.reset();
			break;
		case VK_RETURN:
			field.generateMaze();
			break;
		}
		if(s1moved == false && s2moved == false) {
			switch(wParam) {
			case L'a': case L'A':
				field.moveLeft(0);
				s1moved = true;
				break;
			case L'd': case L'D':
				field.moveRight(0);
				s1moved = true;
				break;
			case L'w': case L'W':
				field.moveUp(0);
				s1moved = true;
				break;
			case L's': case L'S':
				field.moveDown(0);
				s1moved = true;
				break;
			}
		}
		else {
			switch(wParam) {
			case L'a': case L'A':
			case L'd': case L'D':
			case L'w': case L'W':
			case L's': case L'S':
				Beep(500, 100);
				s1error = true;
				break;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		if(s2moved == false && s1moved == true) {
			switch(wParam) {
			case VK_LEFT:
				field.moveLeft(1);
				s2moved = true;
				break;
			case VK_RIGHT:
				field.moveRight(1);
				s2moved = true;
				break;
			case VK_UP:
				field.moveUp(1);
				s2moved = true;
				break;
			case VK_DOWN:
				field.moveDown(1);
				s2moved = true;
				break;
			}
		}
		else {
			switch(wParam) {
			case VK_LEFT:
			case VK_RIGHT:
			case VK_UP:
			case VK_DOWN:
				Beep(1000, 100);
				s2error = true;
				break;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		field.show(hWnd, hdc);
		if(s1moved == true && s2moved == true) {
			s1moved = false;
			s2moved = false;
		}
		if(s1error || s2error) {
			TCHAR str[100];
			wsprintf(str, L"이미 움직인 돌입니다. 다른 돌을 움직여주세요.");
			TextOut(hdc, 0, 0, str, lstrlen(str));
			s1error = false;
			s2error = false;
		}
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
