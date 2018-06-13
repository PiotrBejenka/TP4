// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
RECT drawArea2 = { 500, 0, 700, 1000 };

int value;
int i = 0;
int pasazerowie = 0;
int r = 0;

const int floor1 = 400, floor2 = 300, floor3 = 200, floor4 = 100, floor5 = 0;

std::vector<int> czekajacy;
std::vector<int> docelowe;

// buttons
HWND hwndButton;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void poziom1() {
	czekajacy.push_back(floor1);
	r++;
}
void poziom2() {
	czekajacy.push_back(floor2);
	r++;
}
void poziom3() {
	czekajacy.push_back(floor3);
	r++;
}
void poziom4() {
	czekajacy.push_back(floor4);
	r++;
}
void poziom5() {
	czekajacy.push_back(floor5);
	r++;
}
void docelowe1() {
	docelowe.push_back(floor1);
}
void docelowe2() {
	docelowe.push_back(floor2);
}
void docelowe3() {
	docelowe.push_back(floor3);
}
void docelowe4() {
	docelowe.push_back(floor4);
}
void docelowe5() {
	docelowe.push_back(floor5);
}
string intToString(int toConvert) {
	string result = "";
	int divider = 100;
	int temp = 0;
	for (int i = 0; i < 3; i++) {
		temp = toConvert / divider;
		result += temp + 48;
		toConvert -= temp*divider;
		divider = divider / 10;

	}
	return result;
}
void tekst(HDC hdc)
{
	Graphics graphics(hdc);


	// Create a string.
	//WCHAR string[] = L"Iloœæ osób w windzie:";

	string str = intToString(czekajacy.back());

	
	wstring widestr = wstring(str.begin(), str.end());
	const wchar_t* widecstr = widestr.c_str();

	WCHAR string[] = { *widecstr };

	// Initialize arguments.
	Font myFont(L"Arial", 10);
	PointF origin(610.0f, 10.0f);
	SolidBrush blackBrush(Color(255, 0, 0, 0));

	// Draw string.
	graphics.DrawString(
		string,
		1,
		&myFont,
		origin,
		&blackBrush);
}


void ruch() {

	do
	{
	
	
		if (i == 0)
		{
			if (czekajacy.front() == value)
			{
				i = 1;
				Sleep(250);
				if (czekajacy.size() - 1 > 0)
				{
					czekajacy.erase(czekajacy.begin());
				}

			}
			else
			{
				if (czekajacy.front() > value)
				{
					value++;
				}
				else
				{
					value--;
				}
			}
		}
		else
		{
			if (docelowe.front() == value)
			{
				i = 0;
				Sleep(250);
				if (docelowe.size() - 1 > 0)
				{
					docelowe.erase(docelowe.begin());
					r--;
				}
				
			}
			else
			{
				if (docelowe.front() > value)
				{
					value++;
				}
				else
				{
					value--;
				}
			}
		}
	
	
	
	//} while (czekajacy.back() =! value);
	}while (r != 0);
	
	}

void MyOnPaint(HDC hdc)
{
	//int pietro[4];
	//pietro[0] = floor1;
	//pietro[1] = floor2;
	//pietro[2] = floor3;
	//pietro[3] = floor4;
	//pietro[4] = floor5;


	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 0));
	graphics.DrawLine(&pen, 0, floor5 + 150, 500, floor5 + 150);
	graphics.DrawLine(&pen, 600, floor4 + 150, 1200, floor4 + 150);
	graphics.DrawLine(&pen, 0, floor3 + 150, 500, floor3 + 150);
	graphics.DrawLine(&pen, 600, floor2 + 150, 1200, floor2 + 150);
	graphics.DrawLine(&pen, 0, floor1 + 150, 500, floor1 + 150);

	graphics.DrawRectangle(&pen, 500, value, 100, 150);

	tekst(hdc);
	ruch();
	
}
void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

int OnCreate(HWND window)
{
	SetTimer(window, TMR_1, 25, 0);
	return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
	docelowe.push_back(floor1);
	czekajacy.push_back(floor1);

	value = floor1;

	MSG msg;
	HACCEL hAccelTable;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	OnCreate(hWnd);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 50,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 75,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 100,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 125,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1160, 125,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1160, 175,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON6,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1160, 200,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON7,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1160, 225,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON8,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 225,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON9,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 250,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON10,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 300,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON11,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 325,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON12,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1160, 325,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON13,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1160, 350,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON14,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1160, 375,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON15,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1160, 425,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON16,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 425,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON17,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 450,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON18,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 475,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON19,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 500,                                  // the left and top co-ordinates
		25, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON20,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);


	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		
	case ID_BUTTON1:
		poziom5();
		docelowe4();
		break;
	case ID_BUTTON2:
		poziom5();
		docelowe3();
		break;
	case ID_BUTTON3:
		poziom5();
		docelowe2();
		break;
	case ID_BUTTON4:
		poziom5();
		docelowe1();
		break;
	case ID_BUTTON5:
		poziom4();
		docelowe5();
		break;
	case ID_BUTTON6:
		poziom4();
		docelowe3();
		break;
	case ID_BUTTON7:
		poziom4();
		docelowe2();
		break;
	case ID_BUTTON8:
		poziom4();
		docelowe1();
		break;
	case ID_BUTTON9:
		poziom3();
		docelowe5();
		break;
	case ID_BUTTON10:
		poziom3();
		docelowe4();
		break;
	case ID_BUTTON11:
		poziom3();
		docelowe2();
		break;
	case ID_BUTTON12:
		poziom3();
		docelowe1();
		break;
	case ID_BUTTON13:
		poziom2();
		docelowe5();
		break;
	case ID_BUTTON14:
		poziom2();
		docelowe4();
		break;
	case ID_BUTTON15:
		poziom2();
		docelowe3();
		break;
	case ID_BUTTON16:
		poziom2();
		docelowe1();
		break;
	case ID_BUTTON17:
		poziom1();
		docelowe5();
		break;
	case ID_BUTTON18:
		poziom1();
		docelowe4();
		break;
	case ID_BUTTON19:
		poziom1();
		docelowe3();
		break;
	case ID_BUTTON20:
		poziom1();
		docelowe2();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		

	
		
	
	case WM_TIMER:
		switch (wParam)
		{
		
		case TMR_1:
			//force window to repaint
		
			InvalidateRect(hWnd, &drawArea2, TRUE);
			hdc = BeginPaint(hWnd, &ps);
			MyOnPaint(hdc);
			EndPaint(hWnd, &ps);
			break;
		}



	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
