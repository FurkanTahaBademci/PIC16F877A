
#include "p16F877A.inc"
__CONFIG _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _BOREN_ON & _LVP_ON & _CPD_OFF & _WRT_OFF & _CP_OFF
    
RES_VECT CODE 0x0000
 
GOTO START
MAIN_PROG
 
START
   BSF STATUS,RP0 
   MOVLW 0XFF 
   MOVF TRISB 
   
   CLRF TRISD 
   BCF STATUS,RP0  
   MOVLW 0XFF 
   MOVWF PORTD
   
BUTONBAS
   BTFSS PORTB,3 
   GOTO BUTONBAS
   
BUTONCEK
   BTFSC PORTB,3
   GOTO BUTONCEK
   
   MOVLW 0X02
   SUBWF PORTD,1 
   GOTO BUTONBAS
   
END

