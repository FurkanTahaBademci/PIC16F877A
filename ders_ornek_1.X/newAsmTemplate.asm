
; PIC16F877A Configuration Bit Settings

; ASM source line config statements

#include "p16F877A.inc"

; CONFIG
; __config 0xFFFD
 __CONFIG _FOSC_XT & _WDTE_ON & _PWRTE_OFF & _BOREN_ON & _LVP_ON & _CPD_OFF & _WRT_OFF & _CP_OFF



#define led PORTD,0
 
    ORG 0X00  ;program ba?lama için yap?lan i?lem
    goto START
START
    CLRF PORTD  ; portD nin tamam? s?f?rlar
    BANKSEL TRISD
    CLRF TRISD  ; pord nin tamam?n? output yap?yoruz
    BANKSEL PORTD
LOOP
    fill (nop),10
    BSF led
    fill (nop),10
    BCF led
    goto LOOP
    END


