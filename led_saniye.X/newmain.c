/*
 * File:   newmain.c
 * Author: furkan
 * LED YAKMA VE SONDURME KODU 
 * Created on 07 Kas?m 2023 Sal?, 16:39
 */


#include <xc.h>
#define _XTAL_FREQ 4000000

void main(void) {
    TRISB=0x00;
    
    while(1)
    {
        PORTB=0b00000001;
        __delay_ms(100);
        PORTB=0b00000000;
        __delay_ms(100);
    }
    return;
}
