#include "Tacografo.h"
#include "TYPES.h"
#include "Menu.h"
#include "MenuFunctions.h"

extern Option menu2Options[__MAX_FUNCTION_MENU_2__];
extern Option menu1Options[__MAX_FUNCTION_MENU_1__];
Percurso percurso;
void Tacografo_init(){
    //initiate all need modules
}


int main(){
  Status program_status;
  while (true){
    
    switch(program_status){
      case OK_PRESS:
        Menu_Generic(percurso,&menu1Options,__MAX_FUNCTION_MENU_1__);
        break;
      case MENU_PRESS:
        Menu_Generic(percurso,&menu2Options,__MAX_FUNCTION_MENU_2__);
        break;
      case RESET_PRESS:
        resetTotal((PVOID)(&percurso));
        break;      
    }
    
  
  }



  return EXIT_SUCCESS;
}
