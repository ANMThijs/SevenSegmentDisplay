#include "Display.h"

#pragma comment(linker, "/ENTRY:mainCRTStartup")

Display disp;
int ticks = 0;
char hexvalues[16] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77,
	0x7C, 0x39, 0x5E, 0x79, 0x71 };

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	HDC hdc;
	switch (umsg) {
	case WM_TIMER:
		disp.Set(hexvalues[ticks]);
		if (ticks == 15) {
			ticks = 0;
		}
		else {
			ticks++;
		}

		hdc = GetDC(hwnd);

		disp.Draw(hdc);

		ReleaseDC(hwnd, hdc);
		break;
	case WM_CREATE:
		disp.Init(50, 50);
		
		SetTimer(hwnd, 101, 1000, NULL);
		break;
	case WM_PAINT:
		hdc = GetDC(hwnd);

		disp.Draw(hdc);

		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 101);

		disp.Destroy();

		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, umsg, wparam, lparam);
}

int main(int argc, char** argv) {
	HINSTANCE hInst = GetModuleHandle(NULL);

	WNDCLASS wc = {};

	wc.lpszClassName = L"Main class";
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;

	RegisterClassW(&wc);

	RECT wndrect = { 50, 50, 400, 700 };
	AdjustWindowRect(&wndrect, WS_OVERLAPPEDWINDOW, false);

	HWND hwnd = CreateWindowExW(NULL, wc.lpszClassName, L"Seven Segment Display",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		wndrect.left, wndrect.top, wndrect.right, wndrect.bottom,
		NULL, NULL, hInst, NULL);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}