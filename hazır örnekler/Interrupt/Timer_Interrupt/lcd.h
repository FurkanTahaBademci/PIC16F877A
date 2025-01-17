#define lcd_dat PORTD
#define rs RC0
#define rw RC1
#define en RC2
#define delay for(i=0;i<1000;i++)

int i;

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);

void lcd_init()
{
	TRISC0=TRISC1=TRISC2=TRISD=0;
	cmd(0x38);
	cmd(0x0e);
	cmd(0x06);
	cmd(0x80);
}

void cmd(unsigned char a)
{
	lcd_dat=a;
	rs=0;
	rw=0;
	en=1;
	delay;
	en=0;
}

void dat(unsigned char b)
{
	lcd_dat=b;
	rs=1;
	rw=0;
	en=1;
	delay;
	en=0;
}

void show(unsigned char *s)
{
	while(*s)
	{
		dat(*s++);
	}
}
		
	