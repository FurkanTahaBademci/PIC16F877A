
#include "../main.X/LCD_library.h"

const float oran = 5.0 / 1024.0;
unsigned int adc_deger_okuma(unsigned char kanal)
{
    if (kanal > 7)
        return 0;
    ADCON0 &= 0xB11000101;
    ADCON0 |= (kanal << 3);
    __delay_ms(2);
    GO_nDONE = 1;
    while (GO_nDONE)
        ;
    return ((ADRESH << 8) + ADRESL);
}

void main()
{
    unsigned int V;
    TRISA = 1;          // giris
    TRISB = 0B11000000; // cikis
    TRISC = 0;          // cikis
    TRISD = 0;          // cikis
    PORTC = 0;          // portc sifirla
    PORTB = 0;          // portb sifirla
    PORTD = 0;          // portd sifirla

    T2CON = 0B00000101;   // timer2 on, prescaler 4
    CCP1CON = 0B00001111; // pwm modu
    ADCON0 = 0B00000001;
    ADCON1 = 0B10000000;
    TMR2 = 0;
    PR2 = 255;

    kutuphaneyi_baslat();
    ekran_temizle();
    metin_yaz("Furkan T.Bademci");
    imleci_ayarla(2, 1);
    metin_yaz("G210104016");
    bekle_milisaniye(1000);
    ekran_temizle();

    while (1)
    {
        if (RB6 == 1)
        {
            RC3 = 1;
            RC5 = 1;
            imleci_ayarla(2, 6);
            metin_yaz("YON:SAG");
        }
        if (RB6 == 0)
        {
            RC3 = 0;
            RC5 = 0;
        }
        if (RB7 == 1)
        {
            RC4 = 1;
            RC6 = 1;
            imleci_ayarla(2, 6);
            metin_yaz("YON:SOL");
        }
        if (RB7 == 0)
        {
            RC4 = 0;
            RC6 = 0;
        }
    }
    V = adc_deger_okuma(0);
    CCPR1L = V >> 2;
    CCP1X = V & 1;
    CCP1Y = V & 2;
    __delay_ms(1000);

    V = (int)((((ADRESH * 256) + ADRESL) * oran) / 5) * 100;
    imleci_ayarla(1, 6);
    metin_yaz("HIZ:");
    komut_gonder(V % 100 / 10 + 48);  // ONLAR BASAMAGI
    komut_gonder(V % 10 + 48);        // BIRLER BASAMAGI
}
