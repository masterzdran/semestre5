// =============================================================================================
//
//  Funções Genéricas para manipulação das Slide Bars Controls dos Windows Common Controls
//
//    .
//
//    Nuno Oliveira, Luís Assunção, Carlos Gonçalves
//    Secção de Engenharia de Sistemas Novembro de 2001
//
// =============================================================================================

#ifndef _SLIDE_BAR_H_
#define _SLIDE_BAR_H_

// necessário para utilização do system call SignalObjectAndWait utilizado na classe Semaforo
#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>

#include <commctrl.h>

// ----------------------------------------------------------------------------------------------------------------
// Inicia a SlideBar idSlideBar com intervalos entre 0 e nMax.
//
// Associa à slide bar uma edit Box ou Static Text (buddyId) onde é escrito o valor da Slide Bar
void initSlideBar(HWND hDlg, int idSlideBar, int nMax, int posInitial, int buddyId);

// ----------------------------------------------------------------------------------------------------------------
// Processa os eventos de uma slide Bar do tipo horizontal
//
// Os valores das labels são proporcionais ao valor do cursor
BOOL ProcessLinear_OnHScroll_SlideBar(HWND hDlg, HWND hwndCtl, UINT code, int pos);

// ----------------------------------------------------------------------------------------------------------------
// Processa os eventos de uma slide Bar do tipo horizontal
//
// Os valores das labels não são proporcionais ao valor do cursor
BOOL Process_OnHScroll_SlideBar(HWND hDlg, HWND hwndCtl, UINT code, int pos);

// ----------------------------------------------------------------------------------------------------------------
// Processa os eventos de uma slide Bar do tipo vertical
//
// Os valores das labels são proporcionais ao valor do cursor
BOOL ProcessLinear_OnVScroll_SlideBar(HWND hDlg, HWND hwndCtl, UINT code, int pos);

// ----------------------------------------------------------------------------------------------------------------
// Processa os eventos de uma slide Bar do tipo vertical
//
// Os valores das labels não são proporcionais ao valor do cursor
BOOL Process_OnVScroll_SlideBar(HWND hDlg, HWND hwndCtl, UINT code, int pos);

#endif  // _SLIDE_BAR_H_
