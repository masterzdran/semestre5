/****************************************************************************

	IPL  - Instituto Politecnico de Lisboa
	  ISEL - Instituto Superior de Engenharia de Lisboa
	    DEEC - Departamento de Engenharia Electronica e Comunicacoes
	      SES  - Sec‡Æo de Engenharia de Sistemas

	FUNDAMENTOS DE SISTEMAS OPERATIVOS

	TestAndSet.C

****************************************************************************/
/* Interface: TestAndSet.h */
//int val= 0 // livre, 1 // ocupado
//void enter_csection(int &val);
//void leave_csection(int &val);

/* Implementation  */

int testandset(int &val)
{
	unsigned  res = 0;

  __asm {
	  mov esi, val
      mov ebx, 1
	  xchg [esi], ebx
      mov res, ebx
    }
  return!(res);
}

void enter_csection(int &val)
{
 while (!testandset(val)) Sleep(0);
}

void leave_csection(int &val)
{
 val = 0;
}
