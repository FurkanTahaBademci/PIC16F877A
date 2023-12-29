#include "LCD_library.h"

void bekle_milisaniye(unsigned int milisaniye)
{
    // Millisaniye cinsinden beklemeyi sağlayan fonksiyon
    for (unsigned int i = 0; i < milisaniye; i++)
    {
        __delay_ms(1); // XC8 derleyicisine özgü bir fonksiyon, belirtilen süre kadar bekler
    }
}

void komut_calistir(unsigned char komut)
{
    // LCD'ye bir komut gönderen fonksiyon
    RW = 0;                           // Yazma işlemi olacağı için RW (Read/Write) pinini 0 yap
    RS = 0;                           // Register Select pinini komut moduna getir
    E = 1;                            // Enable pinini yüksek seviyeye çek
    LCD_PORT = (komut & 0xF0);        // Komutun üst 4 bitini veri portuna yaz
    E = 0;                            // Enable pinini düşük seviyeye çek
    bekle_milisaniye(10);             // 10 milisaniye bekleme
    E = 1;                            // Enable pinini tekrar yüksek seviyeye çek
    LCD_PORT = ((komut & 0x0F) << 4); // Komutun alt 4 bitini veri portuna yaz
    E = 0;                            // Enable pinini düşük seviyeye çek
    bekle_milisaniye(10);             // 10 milisaniye bekleme
}

void komut_gonder(unsigned char komut)
{
    // LCD'ye komut gönderen bir arayüz
    komut_calistir(komut);
}

void metin_yaz(const char *metin)
{
    // LCD'ye metin yazan fonksiyon
    bekle_milisaniye(1); // 1 milisaniye bekleme
    while (*metin)
    {
        RS = 1;                            // Register Select pinini veri moduna getir
        E = 1;                             // Enable pinini yüksek seviyeye çek
        LCD_PORT = (*metin & 0xF0);        // Metnin üst 4 bitini veri portuna yaz
        E = 0;                             // Enable pinini düşük seviyeye çek
        bekle_milisaniye(1);               // 1 milisaniye bekleme
        E = 1;                             // Enable pinini tekrar yüksek seviyeye çek
        LCD_PORT = ((*metin & 0x0F) << 4); // Metnin alt 4 bitini veri portuna yaz
        E = 0;                             // Enable pinini düşük seviyeye çek
        bekle_milisaniye(1);               // 1 milisaniye bekleme
        metin++;                           // Bir sonraki karaktere geç
    }
}

void ekran_temizle(void)
{
    // LCD ekranını temizleyen fonksiyon
    komut_gonder(EKRANI_TEMIZLE);
    bekle_milisaniye(2); // 2 milisaniye bekleme
}

void imleci_ayarla(unsigned char x, unsigned char y)
{
    // LCD imlecini belirtilen konuma taşıyan fonksiyon
    if (x == 1)
        komut_gonder(SATIR_1 + ((y - 1) % 16));
    else
        komut_gonder(SATIR_2 + ((y - 1) % 16));
}

void kutuphaneyi_baslat(void)
{
    // LCD kütüphanesini başlatan fonksiyon
    RS = 0;                         // Register Select pinini komut moduna getir
    E = 0;                          // Enable pinini düşük seviyeye çek
    RW = 0;                         // Read/Write pinini yazma moduna getir
    bekle_milisaniye(15);           // 15 milisaniye bekleme
    E = 1;                          // Enable pinini yüksek seviyeye çek
    komut_calistir(BASLANGICA_DON); // Başlangıç konumuna dön komutunu gönder
    bekle_milisaniye(2);            // 2 milisaniye bekleme
    komut_calistir(CIFT_SATIR);     // Çift satır modunu aktifleştir
    komut_calistir(SAGA_KAYDIR);    // Ekranı sağa kaydır komutunu gönder
    komut_calistir(IMLEC_KAPALI);   // İmleci kapat komutunu gönder
    ekran_temizle();                // Ekranı temizle
    komut_calistir(SATIR_1);        // İmleci ilk satıra getir
}
