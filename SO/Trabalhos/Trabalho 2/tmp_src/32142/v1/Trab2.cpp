// Trab2.cpp : Defines the entry point for the application.

#include "headers\stdafx.h"
#include "headers\Trab2.h"
#include <windowsx.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{


	// criar Dialog do 2º trabalho prático
	
	//DialogBox(hInst, MAKEINTRESOURCE(IDD_TRAB2_DIALOG), NULL, About);
	DialogBox(hInst, MAKEINTRESOURCE(IDD_RUNWAY), NULL, About);
	


	return (int) 0;
}

int Landing_Animate_Id[] = {
    IDC_AT0,  IDC_AT1,  IDC_AT2,  IDC_AT3,  IDC_AT4,  IDC_AT5,  IDC_AT6,  IDC_AT7,  IDC_AT8,
    IDC_AT9,  IDC_AT10, IDC_AT11, IDC_AT12, IDC_AT13, IDC_AT14, IDC_AT15, IDC_AT16, IDC_AT17,
    IDC_AT18, IDC_AT19, IDC_AT20, IDC_AT21, IDC_AT22, IDC_AT23, IDC_AT24, IDC_AT25
};

int Takeoff_Animate_Id[] = {
    IDC_DS0,  IDC_DS1,  IDC_DS2,  IDC_DS3,  IDC_DS4,  IDC_DS5,  IDC_DS6,  IDC_DS7,  IDC_DS8,
    IDC_DS9,  IDC_DS10, IDC_DS11, IDC_DS12, IDC_DS13, IDC_DS14, IDC_DS15, IDC_DS16, IDC_DS17,
    IDC_DS18, IDC_DS19, IDC_DS20, IDC_DS21, IDC_DS22, IDC_DS23, IDC_DS24, IDC_DS25
};

DWORD WINAPI thAviaoAterrar(LPVOID p) 
{
    HWND hDlg = (HWND)p;

    for (int i=0; i < 26; ++i) {
        Edit_SetText(GetDlgItem(hDlg, Landing_Animate_Id[i]), TEXT("A01"));
        Sleep(200);
        Edit_SetText(GetDlgItem(hDlg, Landing_Animate_Id[i]), TEXT("   "));
    }

    return 0;
}

DWORD WINAPI thAviaoDescolar(LPVOID p) 
{
    HWND hDlg = (HWND)p;

    for (int i=26; i >= 0; --i) {
        Edit_SetText(GetDlgItem(hDlg, Takeoff_Animate_Id[i]), TEXT("A13"));
        Sleep(300);
        Edit_SetText(GetDlgItem(hDlg, Takeoff_Animate_Id[i]), TEXT("   "));
    }

    return 0;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HANDLE hAviaoAterrar;
    static HANDLE hAviaoDescolar;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:

		Edit_SetText(GetDlgItem(hDlg, IDC_EDIT5), TEXT("0"));
		Edit_SetText(GetDlgItem(hDlg, IDC_EDIT2), TEXT("0"));
		Edit_SetText(GetDlgItem(hDlg, IDC_EDIT1), TEXT("2"));
		Edit_SetText(GetDlgItem(hDlg, IDC_EDIT4), TEXT("4"));

		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST4),TEXT("A03"));
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST4),TEXT("A04"));
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST4),TEXT("A06"));
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST4),TEXT("A08"));
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST1),TEXT("A05"));	
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST1),TEXT("A07"));

		//Button_SetCheck(GetDlgItem(hDlg, IDC_CHECK1), TRUE);
		//Button_SetCheck(GetDlgItem(hDlg, IDC_CHECK2), TRUE);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
        switch ( LOWORD(wParam) ) {
            case IDC_CREATE_LANDING:
                CreateThread(NULL, 0, thAviaoAterrar, (LPVOID)hDlg, 0, NULL);
                break;

            case IDC_CREATE_TAKEOFF:
                CreateThread(NULL, 0, thAviaoDescolar, (LPVOID)hDlg, 0, NULL);
                break;

                break;
            case IDCANCEL:
                EndDialog(hDlg, LOWORD(wParam));
			    return (INT_PTR)TRUE;
        }
		break;
	}
	return (INT_PTR)FALSE;
}
