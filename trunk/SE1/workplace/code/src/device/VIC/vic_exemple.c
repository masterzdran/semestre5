

timer0ISRH:
  sub lr,le,#4
  stmfd sp!, {r0-r12,lr}
  ldr r1,=func0
  mov lr, pc
  bx r1
  ldmfd sp!,{r0-r12.pc}^
  
  
void func0(void){
    x++;
    TIMER0_IR =0x01
    VICVecAddr =0; //dummy write
    
}
