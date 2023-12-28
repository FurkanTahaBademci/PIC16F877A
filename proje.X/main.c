
#include "LCD_library.h"
#include <stdio.h>

void duty_gir(int deger)
{
    CCP1X = deger & 2;
    CCP1Y = deger & 1;
    CCPR1L = deger >> 2;
}

void main()
{
    int adc_deger;
    float voltaj_deger;
    char voltaj_deger_char[10];
    TRISA = 1;          // giris
    TRISB = 0B11100000; // cikis
    TRISC = 0;          // cikis
    TRISD = 0;          // cikis
    PORTA = 0;
    PORTC = 0; // portc sifirla
    PORTB = 0; // portb sifirla
    PORTD = 0; // portd sifirla

    T2CON = 0B00000101;   // timer2 on, prescaler 4
    CCP1CON = 0B00001111; // pwm modu
    ADCON1 = 0b11000000;  // AN ler analog, ADFM=1,ADcs2=1
    ADCON0 = 0b00010001;  // fosc/4, AN2, GODONE=0, ADON=1
    TMR2 = 0;

    PR2 = 49; // 50 sayma

    duty_gir(0);
    kutuphaneyi_baslat();
    ekran_temizle();
    metin_yaz("Furkan T.Bademci");
    imleci_ayarla(2, 1);
    metin_yaz("G210104016");
    bekle_milisaniye(400);
    ekran_temizle();
    imleci_ayarla(2, 5);
    metin_yaz("YON:DUR");

    while (1)
    {
        __delay_ms(10);
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS0 = 0;
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE)
            ;
        adc_deger = (ADRESH * 256 + ADRESL);

        voltaj_deger = adc_deger * 0.0049;

        // sprintf(voltaj_deger_char, "%.2f", voltaj_deger);
        // imleci_ayarla(1, 5);
        // metin_yaz("HIZ:");
        // imleci_ayarla(1, 9);
        // metin_yaz(voltaj_deger_char);

        // duty_gir(adc_deger);

        if (voltaj_deger > 4.97)
        {
            duty_gir(1023);
            imleci_ayarla(1, 5);

            metin_yaz("HIZ:%100");
        }
        else if (voltaj_deger > 3.75)
        {
            duty_gir(750);
            imleci_ayarla(1, 5);
            metin_yaz("HIZ: %75");
        }
        else if (voltaj_deger > 2.50)
        {
            duty_gir(512);
            imleci_ayarla(1, 5);
            metin_yaz("HIZ: %50");
        }
        else if (voltaj_deger > 1.75)
        {
            duty_gir(250);
            imleci_ayarla(1, 5);
            metin_yaz("HIZ: %25");
        }

        else if (voltaj_deger > 0.00)
        {
            duty_gir(0);
            imleci_ayarla(1, 5);
            metin_yaz("HIZ: %00");
        }

        if (RB7 == 1)
        {
            RC4 = 1;
            RC6 = 1;

            RC3 = 0;
            RC5 = 0;
            imleci_ayarla(2, 5);
            metin_yaz("YON:SOL");
        }
        if (RB6 == 1)
        {
            
            RC3 = 1;
            RC5 = 1;

            RC4 = 0;
            RC6 = 0;
            imleci_ayarla(2, 5);
            metin_yaz("YON:SAG");
        }
        if (RB5 == 1)
        {
            RC3 = 0;
            RC5 = 0;
            RC4 = 0;
            RC6 = 0;
            imleci_ayarla(2, 5);
            metin_yaz("YON:DUR");
        }
    }
}
