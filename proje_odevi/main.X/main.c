

#include <LCD_library.h>

void main()
{

    TRISA = 1;          // giris
    TRISB = 0B11000000; // cikis
    TRISC = 0;          // cikis
    TRISD = 0;          // cikis
    PORTC = 0;          // portc sifirla
    PORTB = 0;          // portb sifirla

    T2CON = 0B00000101;  // timer2 on, prescaler 4
    CC1ON = 0B
}
