/*
 * Dosya:   newmain.c
 * Yazar: furkan
 *
 * Oluşturulma Tarihi: 26 Aralık 2023 Salı, 18:32
 */

#include <xc.h>

// Konfigürasyon bit ayarları
#pragma config FOSC = XT   // Osilatör Seçimi bitleri (RC osilatör)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT devre dışı)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT devre dışı)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR etkin)
#pragma config LVP = ON    // Düşük Gerilim ICSP Etkin bit (RB3/PGM pini PGM işlevine sahiptir; düşük gerilim programlaması etkin)
#pragma config CPD = OFF   // Data EEPROM Belleği Kod Koruma biti (Data EEPROM kod koruma kapalı)
#pragma config WRT = OFF   // Flash Program Belleği Yazma İzin bitleri (Yazma koruması kapalı; tüm program belleği EECON kontrolü ile yazılabilir)
#pragma config CP = OFF    // Flash Program Belleği Kod Koruma biti (Kod koruma kapalı)
#define _XTAL_FREQ 4000000 // Kristal frekansı

// UART iletişimini başlatmak için fonksiyon
void UART_basla(void)
{
    BRGH = 1;   // 4Mhz kristal ile 9600bps
    SPBRG = 25; // 4Mhz kristal ile 9600bps
    SYNC = 0;   // Asenkron mod
    SPEN = 1;   // Seri Port Etkin biti
    TRISC7 = 1; // RX pini giriş olarak ayarla
    TRISC6 = 0; // TX pini çıkış olarak ayarla
    CREN = 1;   // Sürekli Alım Etkin biti
    TXEN = 1;   // Gönderimi Etkin biti
}

// UART'ın göndermeye hazır olup olmadığını kontrol etmek için fonksiyon
char UART_bos()
{
    return TRMT; // Gönderim Kaydırma Kaydı Boş biti
}

// UART'ın veri almaya hazır olup olmadığını kontrol etmek için fonksiyon
char UART_veri_hazir()
{
    return RCIF; // Alım Kesme Bayrağı biti
}

// UART'tan bir karakter okumak için fonksiyon
char UART_oku()
{
    while (!RCIF)
        ;         // Bir karakter alınıncaya kadar bekle
    return RCREG; // Alınan karakteri döndür
}

// UART'tan bir metin okumak için fonksiyon
void UART_text_oku(char *okunan, unsigned int uzunluk)
{
    unsigned int i;
    for (int i = 0; i < uzunluk; i++)
        okunan[i] = UART_oku(); // UART'tan 'uzunluk' sayısında karakter oku
}

// UART'a bir karakter yazmak için fonksiyon
void UART_yaz(char veri)
{
    while (!TRMT)
        ;         // Gönderim tamponu boş olana kadar bekle
    TXREG = veri; // Gönderilecek veriyi gönderim kaydırıcısına yükle
}

// UART'a bir metin yazmak için fonksiyon
void UART_text_yaz(char *text)
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
        UART_yaz(text[i]); // Her karakteri sırayla gönder
}

// Ana fonksiyon
void main()
{
    TRISB = 0x00; // PORTB'yi çıkış olarak ayarla
    UART_basla(); // UART iletişimini başlat
    while (1)
    {
        if (UART_veri_hazir())
            PORTB = UART_oku(); // UART'tan gelen veriyi PORTB'ye yaz
        __delay_ms(100);        // 100 milisaniye gecikme
    }
}
