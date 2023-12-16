/*
 * File:   TIMER_KESME_ORNEK.c
 * Author: furkan
 *
 * Created on 08 Kas?m 2023 Çar?amba, 13:04
 */
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


void main(void) {
    
    TRISA= 0x10;    // A PORTLARINI INPUT YAPTIK
    TRISB = 0x00;   // B PORTLATINI OUTPUT YAPTIK
    
    PORTA= 0x00;    // CIKISLARI TEMIZLEDIK
    PORTB= 0x00;    // CIKISLARI TEMIZLEDIK
    
    TMR0 = -1;      // 1 KEZ ICIN TIMER KURDUK
    T0CS = 1;      
    T0SE = 0;       // YÜKSELEN KENAR TETIKLEMES? ?Ç?M 
    PSA = 0;        // PSA AÇIP 1:2 ORANINDAN TIMER 2 AÇIM OLUR
    
    PS0 = 0;
    PS1 = 0;
    PS2 = 0;
    
    T0IF = 0;    // DAHA ONCEDEN TASMA OLAB?L?R O YUZDEN SIFIRLIYORUZ
    
    GIE = 1;    // INTERAPLARA YETKILENDIRME 
    T0IE = 1;   // T0 ICIN ?NTERAPT AÇTIK
    
    
    while(1);
     
    return;
}


void __interrupt() kesme(void)
{
    char i;
    if (T0IF)  // TASMA OLDUYSA
    {
        i++;
        PORTB = i;
        T0IF = 0;  // TASMA BAYRAGINI SIFIRLADIK KI SONRAKI TASMADA TEKRAR BAYRAK KURULAB?LS?N
        TMR0 = -1; 
        
        if (i==16)
        {
            i = 0;
        }
    }
}