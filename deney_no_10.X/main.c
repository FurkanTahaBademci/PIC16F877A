#include <xc.h>
#include <pic16f877.h>
#include <stdio.h>

#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 4000000
#define Sil 1
#define BasaDon 2
#define SolaYaz 4
#define SagaYaz 5
#define ImlecGizle 12
#define ImlecYanSon 15

#define ImlecGeri 16
#define KaydirSaga 24
#define KaydirSola 28
#define EkraniKapat 8
#define BirinciSatir 128
#define IkinciSatir 192
#define KarakterUretAdres 64
#define CiftSatir8Bit 56
#define CiftSatir4Bit 48
#define TekSatir8Bit 40
#define TekSatir4Bit 32

#define RS RC0
#define RW RC1
#define E RC2
#define Data PORTD

#define sut1 PORTBbits.RB4
#define sut2 PORTBbits.RB5
#define sut3 PORTBbits.RB6
#define sut4 PORTBbits.RB7
#define sat1 PORTBbits.RB3
#define sat2 PORTBbits.RB2
#define sat3 PORTBbits.RB1
#define sat4 PORTBbits.RB0

void keypad_oku(void) // KEYPAD okuma fonksiyonu
{
    sat1 = 1;
    if (sut1 == 1)
    {
        __delay_ms(20);

        PORTD = 0x0A;
    }
    if (sut2 == 1)
    {
        __delay_ms(20);

        PORTD = 0X03;
    }
    if (sut3 == 1)
    {
        __delay_ms(20);

        PORTD = 0X02;
    }
    if (sut4 == 1)
    {
        __delay_ms(20);

        PORTD = 0X01;
    }
    sat1 = 0;
    sat2 = 1;
    if (sut1 == 1)
    {
        __delay_ms(20);

        PORTD = 0x0B;
    }
    if (sut2 == 1)
    {
        __delay_ms(20);

        PORTD = 0x06;
    }
    if (sut3 == 1)
    {
        __delay_ms(20);

        PORTD = 0x05;
    }
    if (sut4 == 1)
    {
        __delay_ms(20);

        PORTD = 0x04;
    }
    sat2 = 0;
    sat3 = 1;
    if (sut1 == 1)
    {
        __delay_ms(20);

        PORTD = 0x0C;
    }
    if (sut2 == 1)
    {
        __delay_ms(20);

        PORTD = 0x09;
    }
    if (sut3 == 1)
    {
        __delay_ms(20);

        PORTD = 0x08;
    }
    if (sut4 == 1)
    {
        __delay_ms(20);

        PORTD = 0x07;
    }
    sat3 = 0;
    sat4 = 1;
    if (sut1 == 1)
    {
        __delay_ms(20);

        PORTD = 0x0D;
    }
    if (sut2 == 1)
    {
        __delay_ms(20);

        PORTD = 0x0F;
    }
    if (sut3 == 1)
    {
        __delay_ms(20);

        PORTD = 0x00;
    }
    if (sut4 == 1)
    {
        __delay_ms(20);

        PORTD = 0x0E;
    }
    sat4 = 0;
}
void main(void)
{
    TRISD = 0X00; // D portu komple ï¿½?k?? yap?ld?
    TRISB = 0XF0; // B portu komple 4 msb biti giri? 4 lsb biti ï¿½?k?? yap?ld?
    TRISC = 0X00; // C portu komple ï¿½?k?? yap?ld?
    PORTD = 0X00; // D portu s?f?rland?
    PORTC = 0X00; // C portu s?f?rland?


    while (1)
    {
        keypad_oku(); // keypad okuma fonksiyonuna gidildi.
    }
}