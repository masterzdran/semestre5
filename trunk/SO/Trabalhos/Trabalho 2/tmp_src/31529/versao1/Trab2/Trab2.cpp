// Trab2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Trab2.h"


#define MAX_LOADSTRING 100
#define MAX_BUFFER 21

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

GestorDePistas * gestor;
//Objecto de sincronização utilizado para assegurar de que há somente uma thread de cada vez
//a remover itens da ListBox.
Semaforo * sDelFromLB;
//buffer utilizado para efectuar as leituras dos objectos existentes na parte gráfica
TCHAR buffer[MAX_BUFFER];
//indica se o alerta de furacao esta ligado ou não
bool _bFuracao;

typedef INT (*CountPlanesFunc)(void);
typedef Plane * (*LandOrLiftPlanesFunc)(void);

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


INT Landing_Animate_Id[] = {
    IDC_AT0,  IDC_AT1,  IDC_AT2,  IDC_AT3,  IDC_AT4,  IDC_AT5,  IDC_AT6,  IDC_AT7,  IDC_AT8,
    IDC_AT9,  IDC_AT10, IDC_AT11, IDC_AT12, IDC_AT13, IDC_AT14, IDC_AT15, IDC_AT16, IDC_AT17,
    IDC_AT18, IDC_AT19, IDC_AT20, IDC_AT21, IDC_AT22, IDC_AT23, IDC_AT24, IDC_AT25
}
, Takeoff_Animate_Id[] = {
    IDC_DS0,  IDC_DS1,  IDC_DS2,  IDC_DS3,  IDC_DS4,  IDC_DS5,  IDC_DS6,  IDC_DS7,  IDC_DS8,
    IDC_DS9,  IDC_DS10, IDC_DS11, IDC_DS12, IDC_DS13, IDC_DS14, IDC_DS15, IDC_DS16, IDC_DS17,
    IDC_DS18, IDC_DS19, IDC_DS20, IDC_DS21, IDC_DS22, IDC_DS23, IDC_DS24, IDC_DS25
};


void loadIntoBufferPlanesCount(Plane::PlaneDirection direction)
{
	int n;
	if(Plane::LAND==direction)
	{
		n = gestor->getCountPlanesToLand();
	}
	else if(Plane::LIFTOFF==direction)
	{
		n = gestor->getCountPlanesToLift();
	}
	_itot(n,buffer,10);
}

Plane* executeLandOrListFunction(Plane::PlaneDirection direction)
{
	if(Plane::LAND==direction)
	{
		return gestor->esperarPistaParaAterrar();
	}
	else if(Plane::LIFTOFF==direction)
	{
		return gestor->esperarPistaParaDescolar();
	}
}

INT * getAnimationEditText(INT idLane)
{
	if(idLane==1)
	{
		return Landing_Animate_Id;
	}
	else if(idLane==0)
	{
		return Takeoff_Animate_Id;
	}

}
void doAnimation(Plane * plane, HWND hDlg, INT animationEditTexts)
{
		Edit_SetText(GetDlgItem(hDlg, animationEditTexts), plane->GetName());
        Sleep(200);
        Edit_SetText(GetDlgItem(hDlg, animationEditTexts), TEXT("   "));
}
void perform(HWND hDlg, HWND hList, HWND hEditList,Plane::PlaneDirection direction
			 //,CountPlanesFunc cpf,LandOrLiftPlanesFunc lolpf,
			 )
{
	Plane * plane = gestor->criarAviaoPara(direction);
	ListBox_AddString(hList,plane->GetName());
	//_itot_s(cpf(),buffer,sizeof(_TCHAR)*MAX_BUFFER,10);
	loadIntoBufferPlanesCount(direction);
	
	Edit_SetText(hEditList,buffer);
	
	plane = executeLandOrListFunction(direction);
	sDelFromLB->Wait();
	int temp = ListBox_FindStringExact(hList,0,plane->GetName());
	ListBox_DeleteString(hList,temp);
	sDelFromLB->Signal();

	//_itot_s(cpf(),buffer,sizeof(_TCHAR)*MAX_BUFFER,10);
	loadIntoBufferPlanesCount(direction);
	Edit_SetText(hEditList,buffer);

	INT * animationEditTexts = getAnimationEditText(plane->_idLane);
	
	if(plane->GetDirection()==Plane::LAND)
	{
		for (int i=0; i < 26; ++i) {
			doAnimation(plane,hDlg,animationEditTexts[i]);
		}
	}
	else if(plane->GetDirection()==Plane::LIFTOFF)
	{
		for(int i = 25; i>=0;--i)
		{
			doAnimation(plane,hDlg,animationEditTexts[i]);
		}
	}

	gestor->libertarPista(plane);
}



DWORD WINAPI thAviaoAterrar(LPVOID param) 
{
    HWND hDlg = (HWND)param;
	HWND hList = GetDlgItem(hDlg,IDC_LAND_LIST);
	HWND hEditList = GetDlgItem(hDlg,IDC_N_LAND_LIST);
	
	perform(hDlg,hList,hEditList,Plane::LAND
		//,&(gestor->getCountPlanesToLand),&(gestor->esperarPistaParaAterrar),
		);

    return 0;
}

DWORD WINAPI thAviaoDescolar(LPVOID p) 
{
    HWND hDlg = (HWND)p;
	HWND hList = GetDlgItem(hDlg,IDC_LIFT_LIST);
	HWND hEditList = GetDlgItem(hDlg,IDC_N_LIFT_LIST);

	perform(hDlg,hList,hEditList,Plane::LIFTOFF);
    return 0;
}

VOID WINAPI fecharOuAbrirPista(HWND hControl,INT idLane, HWND hStatic)
{
	Button_GetText(hControl,buffer,MAX_BUFFER);
	if(buffer[0]=='A')
	{
		gestor->abrirPista(idLane);
		Button_SetText(hControl,_T("Fechar"));
		Static_SetText(hStatic,_T("Encontra-se aberta"));
	}
	else if(buffer[0]=='F')
	{
		gestor->fecharPista(idLane);
		Button_SetText(hControl,_T("Abrir"));
		Static_SetText(hStatic,_T("Encontra-se fechada"));
	}
}

VOID WINAPI pistaParaAterrarOuDescolar(HWND hControl, INT idLane, HWND hStatic)
{
	Button_GetText(hControl,buffer,MAX_BUFFER);
	if(buffer[0]=='A')
	{
		gestor->SetLanePriorityTo(Plane::LAND,idLane);
		Button_SetText(hControl,_T("Descolar"));
		Static_SetText(hStatic,_T("Dá prioridade a aterragens"));
	}
	else if(buffer[0]=='D')
	{
		gestor->SetLanePriorityTo(Plane::LIFTOFF,idLane);
		Button_SetText(hControl,_T("Aterrar"));
		Static_SetText(hStatic,_T("Dá prioridade a descolagens"));
	}
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int n_planes;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		gestor = new GestorDePistas(2);
		gestor->SetLanePriorityTo(Plane::LAND,1);
		gestor->SetLanePriorityTo(Plane::LIFTOFF,0);

		Static_SetText(GetDlgItem(hDlg,IDC_PISTA1_LL),_T("Dá prioridade a aterragens"));
		Static_SetText(GetDlgItem(hDlg,IDC_PISTA0_LL),_T("Dá prioridade a descolagens"));
		Static_SetText(GetDlgItem(hDlg,IDC_PISTA1_OC),_T("Encontra-se aberta"));
		Static_SetText(GetDlgItem(hDlg,IDC_PISTA0_OC),_T("Encontra-se aberta"));
		// é necessário para trabalhar sobre a parte grafica,
		//porque quando vai obter o indice do elemento a remover,
		//pode haver um contextswitch que provoca erros.
		sDelFromLB = new Semaforo(1,1);
		_bFuracao = false;

		Edit_SetText(GetDlgItem(hDlg, IDC_N_LAND), TEXT("0"));
		Edit_SetText(GetDlgItem(hDlg, IDC_N_LIFT), TEXT("0"));
		Edit_SetText(GetDlgItem(hDlg, IDC_N_LAND_LIST), TEXT("0"));
		Edit_SetText(GetDlgItem(hDlg, IDC_N_LIFT_LIST), TEXT("0"));
		
		//Button_SetCheck(GetDlgItem(hDlg, IDC_CHECK1), TRUE);
		//Button_SetCheck(GetDlgItem(hDlg, IDC_CHECK2), TRUE);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
        switch ( LOWORD(wParam) ) {
            case IDC_CREATE_LANDING:
				Edit_GetText(GetDlgItem(hDlg,IDC_N_LAND),buffer,MAX_BUFFER);
				n_planes = _ttoi(buffer);
				for(int i = 0;i<n_planes;++i)
				{
					CreateThread(NULL, 0, thAviaoAterrar, (LPVOID)hDlg, 0, NULL);
				}
                break;
            case IDC_CREATE_TAKEOFF:
				Edit_GetText(GetDlgItem(hDlg,IDC_N_LIFT),buffer,MAX_BUFFER);
				n_planes = _ttoi(buffer);
				for(int i = 0;i<n_planes;++i)
				{
					CreateThread(NULL, 0, thAviaoDescolar, (LPVOID)hDlg, 0, NULL);
				}
                break;
			case IDC_OPEN_LANE0:
				fecharOuAbrirPista(GetDlgItem(hDlg,IDC_OPEN_LANE0),0,GetDlgItem(hDlg,IDC_PISTA0_OC));
				break;
			case IDC_OPEN_LANE1:
				fecharOuAbrirPista(GetDlgItem(hDlg,IDC_OPEN_LANE1),1,GetDlgItem(hDlg,IDC_PISTA1_OC));
				break;
			case IDC_LIFT_LANE0:
				pistaParaAterrarOuDescolar(GetDlgItem(hDlg,IDC_LIFT_LANE0),0,GetDlgItem(hDlg,IDC_PISTA0_LL));
				break;
			case IDC_LAND_LANE1:
				pistaParaAterrarOuDescolar(GetDlgItem(hDlg,IDC_LAND_LANE1),1,GetDlgItem(hDlg,IDC_PISTA1_LL));
				break;
			case IDC_FURACAO:
				if(!_bFuracao)
				{
					gestor->fecharPista(0);
					Button_SetText(GetDlgItem(hDlg,IDC_OPEN_LANE0),_T("Abrir"));
					Static_SetText(GetDlgItem(hDlg,IDC_PISTA0_OC),_T("Encontra-se fechada"));
					gestor->fecharPista(1);
					Button_SetText(GetDlgItem(hDlg,IDC_OPEN_LANE1),_T("Abrir"));
					Static_SetText(GetDlgItem(hDlg,IDC_PISTA1_OC),_T("Encontra-se fechada"));
					Static_SetText(GetDlgItem(hDlg,IDC_LBL_FURACAO),_T("AVISO: FURACÃO!"));
				}else
				{
					Static_SetText(GetDlgItem(hDlg,IDC_LBL_FURACAO),_T(""));
				}
				_bFuracao = !_bFuracao;
				gestor->alertaFuracao(_bFuracao);
				break;
            case IDCANCEL:
                EndDialog(hDlg, LOWORD(wParam));
			    return (INT_PTR)TRUE;
        }
		break;
	}
	return (INT_PTR)FALSE;
}
