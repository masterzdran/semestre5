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


//includes para teste!!!
#include "GestorDePistas.cpp"
#include "Plane.cpp"

GestorDePistas* gestor = new GestorDePistas();
DWORD number_Next_Plane_Land = 1;
DWORD number_Next_Plane_takeoff = 1;
bool hurricane = false;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{	
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
	//criar aviao
	Plane* plane = new Plane(number_Next_Plane_Land++);
	int idPista = 1;
	//valor retornado pelo esperaPistaparaAterrar!!
	idPista = gestor->esperarPistaParaAterrar(plane);
	//_TCHAR buffer[20];
	//_itot(number,buffer,10);
	HWND hWnd;
	int sleep = 0;
	for (int i=0; i <= 25; ++i) {
		if(idPista == 0) hWnd =  GetDlgItem(hDlg, Landing_Animate_Id[i]);
		else hWnd = GetDlgItem(hDlg, Takeoff_Animate_Id[i]);
		Edit_SetText(hWnd, plane->GetName()/*buffer*/);
        Sleep(200);
        Edit_SetText(hWnd, TEXT("   "));
	}
	//invocar libertarPista
	gestor->libertarPista(idPista);
    return 0;
}

DWORD WINAPI thAviaoDescolar(LPVOID p) 
{
    HWND hDlg = (HWND)p;
	//criar aviao
	Plane* plane = new Plane(number_Next_Plane_takeoff++);
	int idPista = 0;
	//valor retornado pelo esperaPistaparaAterrar!!
	idPista = gestor->esperarPistaParaDescolar(plane);

	//_TCHAR buffer[20];
	//_itot(number,buffer,10);
	HWND hWnd;
	int sleep = 0;
	for (int i=25; i >= 0; --i) {
		if(idPista == 0) hWnd =  GetDlgItem(hDlg, Landing_Animate_Id[i]);
		else hWnd = GetDlgItem(hDlg, Takeoff_Animate_Id[i]);
		Edit_SetText(hWnd, plane->GetName());
        Sleep(300);
        Edit_SetText(hWnd, TEXT("   "));
	}
	//invocar libertarPista
	gestor->libertarPista(idPista);
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

		//Method: Edit_SetText -  Sets the text of an edit control.
		Edit_SetText(GetDlgItem(hDlg, NUMBER_LANDING), TEXT("0"));
		Edit_SetText(GetDlgItem(hDlg, NUMBER_TAKEOFF), TEXT("0"));
		//Edit_SetText(GetDlgItem(hDlg, IDC_EDIT1), TEXT("2"));
		//Edit_SetText(GetDlgItem(hDlg, IDC_EDIT4), TEXT("4"));

		//Method: ListBox_AddString - Adds a string to a list box.
		/*ListBox_AddString(GetDlgItem(hDlg, IDC_LIST4),TEXT("A03"));
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST4),TEXT("A04"));
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST4),TEXT("A06"));
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST4),TEXT("A08"));
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST1),TEXT("A05"));	
		ListBox_AddString(GetDlgItem(hDlg, IDC_LIST1),TEXT("A07"));*/
		

		//Method: Button_SetCheck - Sets the check state of a radio button or check box.
		Button_SetCheck(GetDlgItem(hDlg, IDC_CHECK1), TRUE);
		Button_SetCheck(GetDlgItem(hDlg, IDC_CHECK2), TRUE);
		return (INT_PTR)TRUE;
	_TCHAR buffer[10];
	case WM_COMMAND:
        switch ( LOWORD(wParam) ) {
            case IDC_CREATE_LANDING:
				//ler numero de avioes a aterrar
				Edit_GetText(GetDlgItem(hDlg,NUMBER_LANDING),buffer, 10);
				for(int i = 0; i < _ttoi(buffer); ++i){
					CreateThread(NULL, 0, thAviaoAterrar, (LPVOID)hDlg, 0, NULL);
				}
                break;

            case IDC_CREATE_TAKEOFF:
				//ler numero de avioes a descolar
				Edit_GetText(GetDlgItem(hDlg,NUMBER_TAKEOFF),buffer, 10);
				for(int i = 0; i < _ttoi(buffer); ++i){
					CreateThread(NULL, 0, thAviaoDescolar, (LPVOID)hDlg, 0, NULL);
				}
                break;
			
			case HURRICANE_WARNING:
				gestor->alertaFuracao(!hurricane);
				hurricane = !hurricane;
				break;

			case OPEN_RUNWAY1:
				gestor->abrirPista(0);
				Edit_SetText(GetDlgItem(hDlg, STATE_RUNWAY1), TEXT("Aberta"));
				break;

			case CLOSE_RUNWAY1:
				gestor->fecharPista(0);
				Edit_SetText(GetDlgItem(hDlg, STATE_RUNWAY1), TEXT("Fechada"));
				break;

			case OPEN_RUNWAY2:
				gestor->abrirPista(1);
				Edit_SetText(GetDlgItem(hDlg, STATE_RUNWAY2), TEXT("Aberta"));
				break;

			case CLOSE_RUNWAY2:
				gestor->fecharPista(1);
				Edit_SetText(GetDlgItem(hDlg, STATE_RUNWAY2), TEXT("Fechada"));
				break;

            case IDCANCEL:
				//Method: EndDialog - Destroys a modal dialog box, causing the system to end any processing for the dialog box. 
                EndDialog(hDlg, LOWORD(wParam));
			    return (INT_PTR)TRUE;
        }
		break;
	}
	return (INT_PTR)FALSE;
}
