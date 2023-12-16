#include "LCD_library.h"

void bekle_milisaniye(unsigned int milisaniye) {
    for (unsigned int i = 0; i < milisaniye; i++) {
        __delay_ms(1);
    }
}

void komut_calistir(unsigned char komut) {
    RW = 0;
    RS = 0;
    E = 1;
    LCD_PORT = (komut & 0xF0);
    E = 0;
    bekle_milisaniye(1);
    E = 1;
    LCD_PORT = ((komut & 0x0F) << 4);
    E = 0;
    bekle_milisaniye(1);
}

void komut_gonder(unsigned char komut) {
    komut_calistir(komut);
}

void metin_yaz(const char *metin) {
    bekle_milisaniye(1);
    while (*metin) {
        RS = 1;
        E = 1;
        LCD_PORT = (*metin & 0xF0);
        E = 0;
        bekle_milisaniye(1);
        E = 1;
        LCD_PORT = ((*metin & 0x0F) << 4);
        E = 0;
        bekle_milisaniye(1);
        metin++;
    }
}

void ekran_temizle(void) {
    komut_gonder(EKRANI_TEMIZLE);
    bekle_milisaniye(2);
}

void imleci_ayarla(unsigned char x, unsigned char y) {
    if (x == 1)
        komut_gonder(SATIR_1 + ((y - 1) % 16));
    else
        komut_gonder(SATIR_2 + ((y - 1) % 16));
}

void kutuphaneyi_baslat(void) {
    RS = 0;
    E = 0;
    RW = 0;
    bekle_milisaniye(15);
    E = 1;
    komut_calistir(BASLANGICA_DON);
    bekle_milisaniye(2);
    komut_calistir(CIFT_SATIR);
    komut_calistir(SAGA_KAYDIR);
    komut_calistir(IMLEC_KAPALI);
    ekran_temizle();
    komut_calistir(SATIR_1);
}
