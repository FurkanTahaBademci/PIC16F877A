
#include "LCD_library.h"
#include <stdio.h>

void duty_gir(int deger)
{
    // CCP1X ve CCP1Y, PWM çıkışının kontrol bitlerini temsil eder.
    // Bu bitler, PWM sinyalinin çıkış düzeyini belirler.
    CCP1X = deger & 2; // en düşük bit kontrol biti CCP1X'e atanır.
    CCP1Y = deger & 1; // en düşük bit kontrol biti CCP1Y'ye atanır.

    // CCPR1L, PWM görev döngüsünün üst 8 bitini içerir.
    // Bu, PWM sinyalinin yüksek düzey süresini belirler.
    CCPR1L = deger >> 2; // deger'ın sağa kaydırılmasıyla CCPR1L'ye atanır.
}

void main()
{
    int adc_deger;              // ADC (Analog-Digital Converter) değeri için bir tamsayı değişkeni
    float voltaj_deger;         // Voltaj değeri için bir ondalık (float) değişken
    char voltaj_deger_char[10]; // Voltaj değerini karakter dizisi olarak depolamak için bir dizi

    // Giriş/Çıkış Ayarları
    TRISA = 1;          // Port A'nın tüm pinleri giriş olarak ayarlanmıştır.
    TRISB = 0B11100000; // Port B'nin ilk beş pinini giriş, diğer pinleri çıkış olarak ayarlanmıştır.
    TRISC = 0;          // Port C'nin tüm pinleri çıkış olarak ayarlanmıştır.
    TRISD = 0;          // Port D'nin tüm pinleri çıkış olarak ayarlanmıştır.

    PORTA = 0; // Port A'nın tüm pinleri sıfırlanmıştır.
    PORTC = 0; // Port C'nin tüm pinleri sıfırlanmıştır.
    PORTB = 0; // Port B'nin tüm pinleri sıfırlanmıştır.
    PORTD = 0; // Port D'nin tüm pinleri sıfırlanmıştır.

    // Timer2 Ayarları
    T2CON = 0B00000101; // Timer2'nin ön bölücüsü 1:1 ve zamanlayıcı modu olarak ayarlanmıştır.

    // CCP Modül Ayarları (PWM)
    CCP1CON = 0B00001111; // CCP1 modülü PWM modunda çalışacak şekilde ayarlanmıştır.

    // ADC Ayarları
    ADCON1 = 0b11000000; // ADC'nin sağ hizalı ve referans gerilimi ayarları yapılmıştır.
    ADCON0 = 0b00010001; // ADC modu, CH0 kanalı ve başlatma işlemi için ayarlar yapılmıştır.

    TMR2 = 0; // Timer2 değeri sıfırlanmıştır.

    PR2 = 255; // Timer2'nin ön yükleme değeri ayarlanmıştır (taşma frekansını belirler).

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
            ; // ADC dönüşümünün tamamlanmasını bekler.

        adc_deger = (ADRESH * 256 + ADRESL); // ADC değeri hesaplanır.

        voltaj_deger = adc_deger * 0.0049; // ADC değeri voltaja dönüştürülür.

        // PWM ile Hız Kontrolü
        if (voltaj_deger > 4.97)
        {
            duty_gir(1023); // PWM görev döngüsü 100%
            imleci_ayarla(1, 5);
            metin_yaz("HIZ:%100");
        }
        else if (voltaj_deger > 3.75)
        {
            duty_gir(750); // PWM görev döngüsü 75%
            imleci_ayarla(1, 5);
            metin_yaz("HIZ: %75");
        }
        else if (voltaj_deger > 2.50)
        {
            duty_gir(512); // PWM görev döngüsü 50%
            imleci_ayarla(1, 5);
            metin_yaz("HIZ: %50");
        }
        else if (voltaj_deger > 1.75)
        {
            duty_gir(250); // PWM görev döngüsü 25%
            imleci_ayarla(1, 5);
            metin_yaz("HIZ: %25");
        }
        else if (voltaj_deger > 0.00)
        {
            duty_gir(0); // PWM görev döngüsü 0%, durma
            imleci_ayarla(1, 5);
            metin_yaz("HIZ: %00");
            RC3 = 0; // Motor yön kontrolü
            RC5 = 0;
            RC4 = 0;
            RC6 = 0;
        }

        // Motor Yön Kontrolü
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