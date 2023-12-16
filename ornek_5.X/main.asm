

; PIC16F877A Configuration Bit Settings

; ASM source line config statements

#include "p16F877A.inc"

; CONFIG
; __config 0xFFF9
 __CONFIG _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _BOREN_ON & _LVP_ON & _CPD_OFF & _WRT_OFF & _CP_OFF
ORG 0X00

    
BASLA
    BTFSC PORTD,0 ;Butona bas?ld? m?
    GOTO BASLA
    BSF PORTB,0 ; LED i yak.
BUTON_OFF
    BTFSS PORTD,0 ;Butonu serbest b?rak
    GOTO BUTON_OFF
    BCF PORTB,0 ; LED i söndür
    GOTO BASLA
END