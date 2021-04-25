#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hwndButton1;
HWND hwndButton2;
HWND hwndButton3;
HWND hwndButton4;
HWND hwndButton5;

HWND hLabel1;
HWND hLabel2;

HWND hwndText, hwndTextInt;

HANDLE hFileFirstTxt, hFileFirstBin, hOutTxt, hInTxt, hOutBin, hInBin, hOutBinDump;

using namespace std;

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstane,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{

	WNDCLASSEX wcex;

	HBRUSH brush = CreateSolidBrush(RGB(255, 182, 193));
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = brush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "window class1";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("Window class creation failed for window 1"),
			_T("Window Class Failed"),
			MB_ICONERROR);

		return 1;
	}

	HWND hWnd = CreateWindow(
		wcex.lpszClassName,
		"Parent Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 400,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow1 failed!"),
			_T("Window Creation Filed"),
			MB_ICONERROR);

		return 1;
	}

	ShowWindow(hWnd,
		nCmdShow);


	hwndButton1 = CreateWindow("BUTTON",
		"Write to text file",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		30,
		200,
		170,
		30,
		hWnd,
		(HMENU)1001,
		(HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE),
		NULL);

	hwndButton2 = CreateWindow("BUTTON",
		"Read from text file",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		280,
		200,
		170,
		30,
		hWnd,
		(HMENU)1002,
		(HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE),
		NULL);

	hwndButton3 = CreateWindow("BUTTON",
		"Write to binary file",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		30,
		250,
		170,
		30,
		hWnd,
		(HMENU)1003,
		(HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE),
		NULL);

	hwndButton4 = CreateWindow("BUTTON",
		"Read from binary file",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		280,
		250,
		170,
		30,
		hWnd,
		(HMENU)1004,
		(HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE),
		NULL);

    hLabel1 = CreateWindow("static", "ST_U",
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                           60, 20, 70, 16,
                           hWnd, (HMENU)100,
                           (HINSTANCE) GetWindowLong (hWnd, GWLP_HINSTANCE), NULL);
    SetWindowText(hLabel1, "String");

    hLabel2 = CreateWindow("static", "ST_U",
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                           60, 80, 70, 16,
                           hWnd, (HMENU)100,
                           (HINSTANCE) GetWindowLong (hWnd, GWLP_HINSTANCE), NULL);
    SetWindowText(hLabel2, "Int");

	hwndText = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL,
		WS_CHILD | WS_VISIBLE, 150, 20, 200,
		40, hWnd, NULL, NULL, NULL);

	hwndTextInt = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL,
		WS_CHILD | WS_VISIBLE, 150, 80, 200,
		40, hWnd, NULL, NULL, NULL);

	UpdateWindow(hWnd);

	hFileFirstTxt = CreateFile(_T("C:\\Users\\79038\\readme.txt"), GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(HANDLE(hFileFirstTxt));

	hFileFirstBin = CreateFile(_T("C:\\Users\\79038\\readme.bin"), GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(HANDLE(hFileFirstBin));

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc,
			5, 5,
			NULL, NULL);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
	{

		if (wParam == 1001)
		{

			hInTxt = CreateFile(_T("C:\\Users\\79038\\readme.txt"), GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hInTxt == INVALID_HANDLE_VALUE) {
				//для вывода ошибки
				TCHAR s[100];
				_stprintf_s(s, _T("%X"), GetLastError());
				MessageBox(0, s, "Error", MB_OK);

				return 2;
			}

			TCHAR str[100];

			wchar_t* wEndString;
			char* cEndString;

			char s[100];
			int iBuff;

			//SendMessage(hwndText, WM_GETTEXT, 100, LPARAM(str));
			GetWindowText(hwndText, str, sizeof(str));
			GetWindowTextA(hwndTextInt, s, sizeof(iBuff));

			iBuff = strtol(s, &cEndString, 0);

            wsprintf(str, _T("%s %d\n"), str, iBuff);

            WriteFile(hInTxt, str, sizeof(str), NULL, NULL);

			CloseHandle(HANDLE(hInTxt));
			break;
		}

		if (wParam == 1002)
		{
			hOutTxt = CreateFile(_T("C:\\Users\\79038\\readme.txt"), GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hOutTxt == INVALID_HANDLE_VALUE) {

				TCHAR s[100];
				_stprintf_s(s, _T("%X"), GetLastError());
				MessageBox(0, s, "Error", MB_OK);

				return 2;
			}

			DWORD dwTemp;
			TCHAR str[100];

			ReadFile(hOutTxt, str, sizeof(str), &dwTemp, NULL);

			MessageBox(hWnd, str, "TXT", MB_OK);

			CloseHandle(HANDLE(hOutTxt));
			break;
		}

		if (wParam == 1003)
		{
			hInBin = CreateFile(_T("C:\\Users\\79038\\readme.bin"), GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hInBin == INVALID_HANDLE_VALUE) {

				TCHAR s[100];
				_stprintf_s(s, _T("%X"), GetLastError());
				MessageBox(0, s, "Error", MB_OK);

				return 2;
			}

			TCHAR text[100];
			//SendMessage(hwndText, WM_GETTEXT, 100, LPARAM(text));

			wchar_t* wEndString;
			char* cEndString;

			char s[100];
			int iBuff, sizeOfStr;

			GetWindowText(hwndText, text, sizeof(text));
			GetWindowTextA(hwndTextInt, s, sizeof(iBuff));

			iBuff = strtol(s, &cEndString, 0);
			sizeOfStr = (GetWindowTextLength(hwndText) + 1) * sizeof(TCHAR);


			WriteFile(hInBin, &sizeOfStr, sizeof(int), NULL, 0);
			WriteFile(hInBin, text, sizeOfStr, NULL, 0);
			WriteFile(hInBin, &iBuff, sizeof(int), NULL, 0);

			CloseHandle(HANDLE(hInBin));
			break;
		}

		if (wParam == 1004)
		{
			hOutBin = CreateFile(_T("C:\\Users\\79038\\readme.bin"), GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hOutBin == INVALID_HANDLE_VALUE) {
				//для вывода ошибки
				TCHAR s[100];
				_stprintf_s(s, _T("%X"), GetLastError());
				MessageBox(0, s, "Error", MB_OK);

				return 2;
			}

			DWORD dwTemp;
			TCHAR str[100];
			int sizeOfStr, number;

			ReadFile(hOutBin, &sizeOfStr, sizeof(int), &dwTemp, NULL);
			ReadFile(hOutBin, str, sizeOfStr, &dwTemp, NULL);
			ReadFile(hOutBin, &number, sizeof(number), &dwTemp, NULL);

			wsprintf(str, _T("%s %d\n") , str, number);


			MessageBox(hWnd, str, "BIN", MB_OK);


			CloseHandle(HANDLE(hOutBin));
			break;
		}

		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
};

