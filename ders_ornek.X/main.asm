
; PIC16F877A Configuration Bit Settings

; ASM source line config statements

#include "p16F877A.inc"

; CONFIG
; __config 0xFFFD
 __CONFIG _FOSC_XT & _WDTE_ON & _PWRTE_OFF & _BOREN_ON & _LVP_ON & _CPD_OFF & _WRT_OFF & _CP_OFF
  
    ORG 0X00
    goto START
START
    CLRF PORTB
    BCF STATUS,C
    MOVLW h'A8'
    ADDLW h'B7'
    MOVWF PORTB
    SWAPF PORTB,1
    COMF PORTB,1
    RLF PORTB,1
    RLF PORTB,1
    END