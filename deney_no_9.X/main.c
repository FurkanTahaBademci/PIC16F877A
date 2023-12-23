#include <xc.h>
#include <pic16f877.h>
#include <stdio.h>
#pragma config FOSC = XT   // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON    // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF   // Flash Program Memory Write Enable bits (Write protection off; all program memory may be
#pragma config CP = OFF    // Flash Program Memory Code Protection bit (Code protection off)
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
float D0;
float D1;
float D2;
float AN0;
float AN1;
float AN2;
void Lcd_Port(char a)
{
    if (a & 1)
        RD4 = 1;
    else
        RD4 = 0;
    if (a & 2)
        RD5 = 1;
    else
        RD5 = 0;
    if (a & 4)
        RD6 = 1;
    else
        RD6 = 0;
    if (a & 8)
        RD7 = 1;
    else
        RD7 = 0;
}
void Lcd_Cmd(char a) // LCD komut fonksiyonu
{
    RS = 0;
    Lcd_Port(a);
    E = 1;
    __delay_ms(4);
    E = 0;
}
Lcd_Clear() // LCD temizleme fonksiyonu
{
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}
void Lcd_Set_Cursor(char a, char b) // LCD satır sutün seçme fonksiyonu
{
    char temp, z, y;
    if (a == 1)
    {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
    else if (a == 2)
    {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}
void Lcd_Init() // LCD başlatma fonksiyonu
{
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}
void Lcd_Write_Char(char a) // LCD ye karatter yazdırma fonksiyonu
{
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1;
    Lcd_Port(y >> 4);
    E = 1;
    __delay_us(40);
    E = 0;
    Lcd_Port(temp);
    E = 1;
    __delay_us(40);
    E = 0;
}
void Lcd_Write_String(char *a) // LCD ye string yazdırma fonksiyonu
{
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}
void main()
{

    char char_digital[15];
    TRISA = 0XFF;
    TRISD = 0X00;
    TRISC = 0X00;
    PORTC = 0X00;
    PORTD = 0X00;

    Lcd_Init();
    ADCON0bits.ADON = 1;
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG3 = 0;
    ADCON1bits.ADFM = 1;

    while (1)
    {
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 0;
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE)
            ;
        // Lcd_Clear();
        D0 = ADRESH * 256 + ADRESL;
        AN0 = D0 * 0.0048;
        Lcd_Set_Cursor(1, 1);
        sprintf(char_digital, "%.2f", AN0);
        Lcd_Write_String("AN0=");
        Lcd_Set_Cursor(1, 5);
        Lcd_Write_String(char_digital);

        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 1;
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE)
            ;
        D1 = ADRESH * 256 + ADRESL;
        AN1 = D1 * 0.0048;
        Lcd_Set_Cursor(1, 9);
        sprintf(char_digital, "%.2f", AN1);
        Lcd_Write_String("AN1=");
        Lcd_Set_Cursor(1, 13);
        Lcd_Write_String(char_digital);

        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS0 = 0;
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE)
            ;
        D2 = ADRESH * 256 + ADRESL;
        AN2 = D2 * 0.0048;
        Lcd_Set_Cursor(2, 1);
        sprintf(char_digital, "%.2f", AN2);
        Lcd_Write_String("AN2=");
        Lcd_Set_Cursor(2, 5);
        Lcd_Write_String(char_digital);
            
    }
}