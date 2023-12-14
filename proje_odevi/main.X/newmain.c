#include <pic.h>

#define RS RB0
#define RW RB1
#define E RB2

// PIC konfigürasyon ayarları
__CONFIG(FOSC_HS &WDTE_OFF & PWRTE_OFF & CP_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF);

#define DUGME_SAG RA1 // Örneğin, sağ yön düğmesinin bağlı olduğu pin
#define DUGME_SOL RA2 // Örneğin, sol yön düğmesinin bağlı olduğu pin

// Fonksiyon prototipleri
void adcOku();
void lcdBaslangic();
void komut(unsigned char a);
void veri(unsigned char b);
void ekrandaGoster(unsigned char *metin);
void bekle(int milisaniye);

#define _XTAL_FREQ 4000000 // 4 MHz kristal kullan?l?yorsa

void main()
{
    // Giriş/Çıkış tanımlamaları
    TRISB = 0; // Port B ve Port C Çıkış (LCD)
    TRISD = 0;
    TRISA0 = 1; // RA0 giriş (ADC)

    // LCD başlangıç ayarları
    lcdBaslangic();
    ekrandaGoster("Furkan T.Bademci");
    komut(0xC0); // ikinci sat?ra ge�
    ekrandaGoster("G210104016");
    bekle(3000);

    lcdBaslangic();
    ekrandaGoster("ADC DEGERI :");

    while (1)
    {
        // ADC değerini göstermek için LCD konumunu ayarla ve ADC okuma fonksiyonunu çağır
        komut(0x8C);
        adcOku();
    }
}

void lcdBaslangic()
{
    // LCD başlangıç ayarları
    komut(0x38); // 8-bit veri, 2 satır, 5x7 font
    komut(0x0C); // Ekranı aç, imleci kapat
    komut(0x06); // Yazıyı kaydır, imleci sabit tut
    komut(0x80); // DDRAM adresini başlangıca ayarl
    komut(0x01); // ekran? tem?zlea
}

void komut(unsigned char a)
{
    // LCD'ye komut gönderme
    PORTD = a;
    RS = 0;
    RW = 0;
    E = 1;
    bekle(10);
    E = 0;
}

void veri(unsigned char b)
{
    // LCD'ye veri gönderme
    PORTD = b;
    RS = 1;
    RW = 0;
    E = 1;
    bekle(10);
    E = 0;
}

void ekrandaGoster(unsigned char *metin)
{
    // LCD'ye karakter dizisi gönderme
    while (*metin)
    {
        veri(*metin++);
    }
}

void adcOku()
{
    unsigned int adcDeger;

    // ADC ayarları
    ADCON1 = 0xc0; // Sağa dayalı
    ADCON0 = 0x85; // ADC açık, FOSC/64
    while (GO_nDONE)
        ;                                  // Dönüşüm bitene kadar bekle
    adcDeger = ((ADRESH << 8) | (ADRESL)); // Sonucu sakla
    adcDeger = (adcDeger / 3) - 1;

    // ADC değerini LCD'ye gönderme
    veri((adcDeger / 1000) + 48);
    veri(((adcDeger / 100) % 10) + 48);
    veri(((adcDeger / 10) % 10) + 48);
    veri((adcDeger % 10) + 48);

    komut(0xC0); // ikinci sat?ra ge�
    if (DUGME_SAG == 1)
    {
        ekrandaGoster("Sag");
        while (DUGME_SAG == 1)
            ;
        __delay_ms(100); // Debouncing için kısa bir bekleme
    }

    if (DUGME_SOL == 1)
    {
        ekrandaGoster("Sol");
        while (DUGME_SOL == 1)
            ;
        __delay_ms(100); // Debouncing için kısa bir bekleme
    }
}

void bekle(int milisaniye)
{
    int i;
    for (i = 0; i < milisaniye; i++)
    {
        __delay_ms(1);
    }
}