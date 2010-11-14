// --------------------------------------------------------------------------------------------------------------------
//      Funções Genéricas para manipulação das Slide Bars
//
#include "../Include/SlideBar.h"



// ----------------------------------------------------------------------------------------------------------------
// Inicia a SlideBar idSlideBar com intervalos entre 0 e nMax.
//
// Associa à slide bar uma edit Box ou Static Text (buddyId) onde é escrito o valor da Slide Bar
void initSlideBar(HWND hDlg, int idSlideBar, int nMax, int posInitial, int buddyId) {
  // ----------------------------------------------------------------------------------------
  // SLIDER BAR
  HWND hSlider = GetDlgItem(hDlg, idSlideBar);

  // intervalo de valores da barra 
  SendMessage(hSlider, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, nMax));

  // intervalo entre as marcas da barra  
  SendMessage(hSlider, TBM_SETTICFREQ, 1, 0);
    
  // número de posições logicas da barra em resposta ao teclado como as setas (RIGHT ARROW ou DOWN ARROW)
  // defaut = 1
  SendMessage(hSlider, TBM_SETLINESIZE, 0, (LPARAM)1);
  // número de posições logicas da barra em resposta ao teclado (PgUp e PgDown) e clicks do rato
  // defaut = 1
  SendMessage(hSlider, TBM_SETPAGESIZE, 0, (LPARAM)1);


  // associa até dois objectos gráficos aos extremos da barra...
  SetWindowLong(hSlider, GWL_USERDATA, (LONG)GetDlgItem(hDlg, buddyId));
  
  // iniciar valor de sleep da thread So estorva - numerico e slide bar
  SendMessage(hSlider, TBM_SETPOS, TRUE, (LPARAM)posInitial);
  SendMessage(hDlg, WM_HSCROLL, MAKELONG(TB_THUMBTRACK, posInitial), (WPARAM)hSlider);
} // end initSlideBar


// ----------------------------------------------------------------------------------------------------------------
// Processa os eventos de uma slide Bar do tipo horizontal
//
// Os valores das labels são proporcionais ao valor do cursor
BOOL ProcessLinear_OnHScroll_SlideBar(HWND hDlg, HWND hwndCtl, UINT code, int pos) {
  TCHAR auxBuffer[16];
  HWND hBuddy;

  switch( code ) {
    // nestas duas notificações o argumento pos contém a posição do cursor
    case TB_THUMBPOSITION:    // enviada depois de se largar o left button do mouse numa situação de arrasto do cursor
    case TB_THUMBTRACK:       // enviada enquando se esta a arrastar o cursor da barra
      _stprintf(auxBuffer, TEXT("%d"), pos);

      // obtem a caixa para escrita do valor
      hBuddy = (HWND)GetWindowLong(hwndCtl, GWL_USERDATA);
      
      SendMessage(hBuddy, WM_SETTEXT, 0, (LPARAM)auxBuffer);
      return TRUE;

    // Estes dois grupos de notificações necessitam de enviar a menssagem TBM_GETPOS para 
    // determinarem a posição do cursor
    // estas notificações são enviadas devido a manipulações com o teclado
    case TB_BOTTOM:           // VK_END
    case TB_LINEDOWN:         // VK_RIGHT or VK_DOWN
    case TB_LINEUP:           // VK_LEFT or VK_UP
    case TB_TOP:              // VK_HOME

    // São enviadas nas duas situações: teclado e rato
    case TB_ENDTRACK:         // WM_KEYUP o utilizador libertou uma tecla que enviou um tecla virtual relevante
    case TB_PAGEDOWN:         // VK_NEXT  click por baixo ou do lado direito do cursor
    case TB_PAGEUP:           // VK_PRIOR click por cima ou do lado esquerdo do cursor
      pos = SendMessage(hwndCtl, TBM_GETPOS, 0, 0);

      _stprintf(auxBuffer, TEXT("%d"), pos);
            
      // obtem a caixa para escrita do valor
      hBuddy = (HWND)GetWindowLong(hwndCtl, GWL_USERDATA);

      SendMessage(hBuddy, WM_SETTEXT, 0, (LPARAM)auxBuffer);
      return TRUE;
  } // switch( code )

  return TRUE;
} // end ProcessLinear_OnHScroll_SlideBar


// ----------------------------------------------------------------------------------------------------------------
// Processa os eventos de uma slide Bar do tipo horizontal
//
// Os valores das labels não são proporcionais ao valor do cursor
BOOL Process_OnHScroll_SlideBar(HWND hDlg, HWND hwndCtl, UINT code, int pos) {
  static int tabValSlider[] = {0, 1, 10, 100, 1000, 2000, 3000, 4000};
  TCHAR auxBuffer[16];
  HWND hBuddy;

  switch( code ) {
    // nestas duas notificações o argumento pos contém a posição do cursor
    // case TB_THUMBPOSITION: // enviada depois de se largar o left button do mouse numa situação de arrasto do cursor
    case TB_THUMBTRACK:       // enviada enquando se esta a arrastar o cursor da barra
      _stprintf(auxBuffer, TEXT("%d"), tabValSlider[pos] );

      // obtem a caixa para escrita do valor
      hBuddy = (HWND)GetWindowLong(hwndCtl, GWL_USERDATA);

      SendMessage(hBuddy, WM_SETTEXT, 0, (LPARAM)auxBuffer);
      return TRUE;

    // Estes dois grupos de notificações necessitam de enviar a menssagem TBM_GETPOS para 
    // determinarem a posição do cursor
    // estas notificações são enviadas devido a manipulações com o teclado
    case TB_BOTTOM:           // VK_END
    case TB_LINEDOWN:         // VK_RIGHT or VK_DOWN
    case TB_LINEUP:           // VK_LEFT or VK_UP
    case TB_TOP:              // VK_HOME

    // São enviadas nas duas situações: teclado e rato
    case TB_ENDTRACK:         // WM_KEYUP o utilizador libertou uma tecla que enviou um tecla virtual relevante
    case TB_PAGEDOWN:         // VK_NEXT  click por baixo ou do lado direito do cursor
    case TB_PAGEUP:           // VK_PRIOR click por cima ou do lado esquerdo do cursor
      pos = SendMessage(hwndCtl, TBM_GETPOS, 0, 0);

      _stprintf(auxBuffer, TEXT("%d"), tabValSlider[pos]);
            
      // obtem a caixa para escrita do valor
      hBuddy = (HWND)GetWindowLong(hwndCtl, GWL_USERDATA);

      SendMessage(hBuddy, WM_SETTEXT, 0, (LPARAM)auxBuffer);
      return TRUE;
  } // switch( code )

  return TRUE;
} // end Process_OnHScroll_SlideBar


// ----------------------------------------------------------------------------------------------------------------
// Processa os eventos de uma slide Bar do tipo vertical
//
// Os valores das labels são proporcionais ao valor do cursor
BOOL ProcessLinear_OnVScroll_SlideBar(HWND hDlg, HWND hwndCtl, UINT code, int pos) {            
  TCHAR auxBuffer[16];

  HWND hBuddy;

  switch( code ) {
    // nestas duas notificações o argumento pos contém a posição do cursor
    case TB_THUMBPOSITION:    // enviada depois de se largar o left button do mouse numa situação de arrasto do cursor
    case TB_THUMBTRACK:       // enviada enquando se esta a arrastar o cursor da barra
      _stprintf(auxBuffer, TEXT("%d"), pos);

      // obtem a caixa para escrita do valor
      hBuddy = (HWND)GetWindowLong(hwndCtl, GWL_USERDATA);

      SendMessage(hBuddy, WM_SETTEXT, 0, (LPARAM)auxBuffer);
      return TRUE;

    // Estes dois grupos de notificações necessitam de enviar a menssagem TBM_GETPOS para 
    // determinarem a posição do cursor
    // estas notificações são enviadas devido a manipulações com o teclado
    case TB_BOTTOM:           // VK_END
    case TB_LINEDOWN:         // VK_RIGHT or VK_DOWN
    case TB_LINEUP:           // VK_LEFT or VK_UP
    case TB_TOP:              // VK_HOME

    // São enviadas nas duas situações: teclado e rato
    case TB_ENDTRACK:         // WM_KEYUP o utilizador libertou uma tecla que enviou um tecla virtual relevante
    case TB_PAGEDOWN:         // VK_NEXT  click por baixo ou do lado direito do cursor
    case TB_PAGEUP:           // VK_PRIOR click por cima ou do lado esquerdo do cursor

      pos = SendMessage(hwndCtl, TBM_GETPOS, 0, 0);
      _stprintf(auxBuffer, TEXT("%d"), pos);
            
      // obtem a caixa para escrita do valor
      hBuddy = (HWND)GetWindowLong(hwndCtl, GWL_USERDATA);

      SendMessage(hBuddy, WM_SETTEXT, 0, (LPARAM)auxBuffer);
      return TRUE;
  } // switch( code )

  return TRUE;
} // end ProcessLinear_OnVScroll_SlideBar



// ----------------------------------------------------------------------------------------------------------------
// Processa os eventos de uma slide Bar do tipo vertical
//
// Os valores das labels não são proporcionais ao valor do cursor
BOOL Process_OnVScroll_SlideBar(HWND hDlg, HWND hwndCtl, UINT code, int pos) {
  static int tabValSlider[] = {0, 1, 10, 100, 1000, 2000, 3000, 4000};
  TCHAR auxBuffer[16];
  HWND hBuddy;

  switch( code ) {
    // nestas duas notificações o argumento pos contém a posição do cursor
    // case TB_THUMBPOSITION: // enviada depois de se largar o left button do mouse numa situação de arrasto do cursor
    case TB_THUMBTRACK:       // enviada enquando se esta a arrastar o cursor da barra
      _stprintf(auxBuffer, TEXT("%d"), tabValSlider[pos] );

      // obtem a caixa para escrita do valor
      hBuddy = (HWND)GetWindowLong(hwndCtl, GWL_USERDATA);

      SendMessage(hBuddy, WM_SETTEXT, 0, (LPARAM)auxBuffer);
      return TRUE;

    // Estes dois grupos de notificações necessitam de enviar a menssagem TBM_GETPOS para 
    // determinarem a posição do cursor
    // estas notificações são enviadas devido a manipulações com o teclado
    case TB_BOTTOM:           // VK_END
    case TB_LINEDOWN:         // VK_RIGHT or VK_DOWN
    case TB_LINEUP:           // VK_LEFT or VK_UP
    case TB_TOP:              // VK_HOME

    // São enviadas nas duas situações: teclado e rato
    case TB_ENDTRACK:         // WM_KEYUP o utilizador libertou uma tecla que enviou um tecla virtual relevante
    case TB_PAGEDOWN:         // VK_NEXT  click por baixo ou do lado direito do cursor
    case TB_PAGEUP:           // VK_PRIOR click por cima ou do lado esquerdo do cursor
      pos = SendMessage(hwndCtl, TBM_GETPOS, 0, 0);

      _stprintf(auxBuffer, TEXT("%d"), tabValSlider[pos]);
            
      // obtem a caixa para escrita do valor
      hBuddy = (HWND)GetWindowLong(hwndCtl, GWL_USERDATA);

      SendMessage(hBuddy, WM_SETTEXT, 0, (LPARAM)auxBuffer);
      return TRUE;
  } // switch( code )

  return TRUE;
} // end Process_OnVScroll_SlideBar
