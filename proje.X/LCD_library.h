/*
 * File:   LCD_library.h
 * Author: furkan
 *
 * Created on 16 Aralık 2023 Cumartesi, 20:03
 */

#ifndef LCD_LIBRARY_H
#define LCD_LIBRARY_H

#include <xc.h>

#pragma config FOSC = XT   // Osilatör Seçim bitleri (RC osilatörü?)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT etkin değil)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT devre dışı)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR etkin)
#pragma config LVP = ON    // Düşük Gerilim Programlamayı Etkinleştir (RB3/PGM pini PGM işlevine sahiptir; düşük gerilim programlaması etkin)
#pragma config CPD = OFF   // Data EEPROM Belleği Kod Koruma biti (Data EEPROM kod koruma kapalı)
#pragma config WRT = OFF   // Flash Program Belleği Yazma İzin bitleri (Yazma koruması kapalı; tüm program belleği EECON kontrolü ile yazılabilir)
#pragma config CP = OFF    // Flash Program Belleği Kod Koruma biti (Kod koruma kapalı)

#define _XTAL_FREQ 4000000 // Kristal frekansı (4MHz)

// LCD Pin Tanımlamaları
#define RS RB0         // Register Select
#define RW RB1         // Read/Write
#define E RB2          // Enable
#define LCD_PORT PORTD // LCD Data Port

// LCD Komutları
#define EKRANI_TEMIZLE 1
#define BASLANGICA_DON 2
#define SAGA_KAYDIR 4
#define SOLA_KAYDIR 6
#define IMLEC_KAPALI 12
#define IMLEC_ALT_CIZGI 14
#define IMLEC_FLAS 15
#define IMLEC_SOLA_KAYDIR 16
#define SAGA_KAYDIRMA 24
#define SOLA_KAYDIRMA 28
#define EKRANI_KAPAT 8
#define SATIR_1 128
#define SATIR_2 192
#define KARAKTER_URET_ADRES 64
#define CIFT_SATIR 40
#define TEK_SATIR 32

// Fonksiyon Prototipleri
extern void bekle_milisaniye(unsigned int milisaniye);
extern void komut_gonder(unsigned char komut);
extern void ekran_temizle(void);
extern void metin_yaz(const char *metin);
extern void imleci_ayarla(unsigned char x, unsigned char y);
extern void kutuphaneyi_baslat(void);
extern void komut_calistir(unsigned char komut);

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif /* LCD_LIBRARY_H */
