#include <Windows.h>
#include <atlstr.h>
#define _UNICODE
#include "graphic.h"



graphic picture;

void reinter(double* mtrx) {
	for (int i = 0; i < 16; i++) {
		mtrx[i] = 0;
	}
	mtrx[0] = mtrx[5] = mtrx[10] = mtrx[15] = 1;
}



LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	HPEN hPen = CreatePen(PS_SOLID, 0.5, RGB(0, 0, 0));

	vector3d center = {};

	GetClientRect(hWnd, &rect);

	center.x = rect.right / 2;
	center.y = rect.bottom / 2;

	double atm[16] = { 0 };
	reinter(atm);

	switch (uMsg) {
	case WM_CREATE:

		center.z = 0;

		picture.GetGraph(center);

		break;

	case WM_PAINT:

		picture.GetPerspicere(atm);

		hdc = BeginPaint(hWnd, &ps);

		picture.DrawGraph(hdc, hPen);

		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:

		switch (wParam) {

		case VK_LEFT:
			//<-

			picture.xMove(-10.0, atm);

			UpdateWindow(hWnd);
			break;

		case VK_RIGHT:
			//->

			picture.xMove(10.0, atm);

			UpdateWindow(hWnd);
			break;

		case VK_UP:
			//  ^
			// / \
			//  |
			picture.xMove(-rect.right / 2.0, atm);
			picture.yMove(-rect.bottom / 2.0, atm);
			reinter(atm);

			picture.Scaling(1.1, atm);

			reinter(atm);
			picture.xMove(rect.right / 2.0 * 1.05, atm);
			picture.yMove(rect.bottom / 2.0, atm);

			UpdateWindow(hWnd);
			break;

		case VK_DOWN:
			// |
			//\ /
			// v 

			picture.xMove(-rect.right / 2.0, atm);
			picture.yMove(-rect.bottom / 2.0, atm);
			reinter(atm);

			picture.Scaling(0.9, atm);

			reinter(atm);
			picture.xMove(rect.right / 2.0 * 0.95, atm);
			picture.yMove(rect.bottom / 2.0, atm);

			UpdateWindow(hWnd);
			break;

		case VK_PRIOR:
			//PgUp

			picture.yMove(-10.0, atm);

			break;

		case VK_NEXT:
			//PgDn

			picture.yMove(10.0, atm);

			break;

		case VK_SPACE:
			//space


			UpdateWindow(hWnd);
			break;

		case 65:
			//A
			picture.xMove(-rect.right / 2.0, atm);
			reinter(atm);

			picture.RotateY(5.0, atm);

			reinter(atm);
			picture.xMove(rect.right / 2.0, atm);

			UpdateWindow(hWnd);
			break;

		case 68:
			//D
			picture.xMove(-rect.right / 2.0, atm);
			reinter(atm);

			picture.RotateY(-5.0, atm);

			reinter(atm);
			picture.xMove(rect.right / 2.0, atm);

			UpdateWindow(hWnd);
			break;

		case 87:
			//W

			picture.yMove(-(picture.pictureP[5].y + picture.pictureP[15].y) / 2.0, atm);
			reinter(atm);

			picture.RotateX(-5.0, atm);

			reinter(atm);
			picture.yMove((picture.pictureP[5].y + picture.pictureP[15].y) / 2.0, atm);

			UpdateWindow(hWnd);
			break;

		case 83:
			//S

			picture.yMove(-(picture.pictureP[5].y + picture.pictureP[15].y) / 2.0, atm);
			reinter(atm);

			picture.RotateX(5.0, atm);

			reinter(atm);
			picture.yMove((picture.pictureP[5].y + picture.pictureP[15].y) / 2.0, atm);

			UpdateWindow(hWnd);
			break;

		case 81:
			//Q

			picture.xMove(-(picture.pictureP[5].x + picture.pictureP[15].x) / 2.0, atm);
			reinter(atm);
			picture.yMove(-(picture.pictureP[5].y + picture.pictureP[15].y) / 2.0, atm);
			reinter(atm);

			picture.RotateZ(-5.0, atm);

			reinter(atm);
			picture.xMove((picture.pictureP[5].x + picture.pictureP[15].x) / 2.0, atm);
			reinter(atm);
			picture.yMove((picture.pictureP[5].y + picture.pictureP[15].y) / 2.0, atm);

			UpdateWindow(hWnd);
			break;

		case 69:
			//E

			picture.xMove(-(picture.pictureP[5].x + picture.pictureP[15].x) / 2.0, atm);
			reinter(atm);
			picture.yMove(-(picture.pictureP[5].y + picture.pictureP[15].y) / 2.0, atm);
			reinter(atm);

			picture.RotateZ(5.0, atm);

			reinter(atm);
			picture.xMove((picture.pictureP[5].x + picture.pictureP[15].x) / 2.0, atm);
			reinter(atm);
			picture.yMove((picture.pictureP[5].y + picture.pictureP[15].y) / 2.0, atm);

			UpdateWindow(hWnd);
			break;

		}

		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		DeleteObject(hPen);
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}
	return 0;

}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = L"WinClass";
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Cannot register class", L"ERROR", MB_OK);
		return 0;
	}
	hWnd = CreateWindowEx(NULL, L"WinClass", L"Астроида", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	if (!hWnd) {
		MessageBox(NULL, L"Cannot create window", L"ERROR", MB_OK);
		return 0;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}