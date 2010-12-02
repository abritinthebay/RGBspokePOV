#include "main.h"
#include "xtal_freq.h"
#include <p18cxxx.h>

#pragma config PLLDIV = 5, CPUDIV = OSC1_PLL2, USBDIV = 2, FOSC = HSPLL_HS //CPU=48 MHz
#pragma config PWRT = ON
#pragma config BOR = OFF
#pragma config VREGEN = ON 	// USB Voltage Regulator Enable: on
#pragma config WDT = OFF 	// Watchdog Timer: off
#pragma config MCLRE = ON  // MCLR Enable: on (disable in program for RE3)
#pragma config PBADEN = OFF // PORTB<4:0> pins are configured as digital I/O on Reset
#pragma config LVP = OFF 	// Low Voltage ICSP: off
#pragma config CPB = ON		// boot block code protection: on
#pragma config WRTB = ON	// boot block write protection: on
#pragma config CCP2MX = OFF
#pragma config STVREN = OFF

#pragma udata

volatile unsigned long TickCount;

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR_BOOT = 0x000800
void _reset_boot (void)
{
	_asm goto _startup _endasm
}
#pragma code


// Normal reset vector is already decleared at 0x000000 in c018i.c



#pragma code _HIGH_INTERRUPT_VECTOR_BOOT = 0x000808
void _high_ISR_boot (void)
{
	_asm
	goto InterruptHandlerHigh //jump to interrupt routine
	_endasm
}
#pragma code

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000008
void _high_ISR (void)
{
	_asm
	goto InterruptHandlerHigh //jump to interrupt routine
	_endasm
}
#pragma code



#pragma code _LOW_INTERRUPT_VECTOR_BOOT = 0x000818
void _low_ISR_boot (void)
{
	_asm
	goto InterruptHandlerLow //jump to interrupt routine
	_endasm
}
#pragma code

#pragma code _LOW_INTERRUPT_VECTOR = 0x000018
void _low_ISR (void)
{
	_asm
	goto InterruptHandlerLow //jump to interrupt routine
	_endasm
}
#pragma code



#pragma code
#pragma interrupt InterruptHandlerHigh

void InterruptHandlerHigh(void)
{
	
}

#pragma code
#pragma interrupt InterruptHandlerLow
void InterruptHandlerLow(void)
{	
	    
	// clear flag
	PIR1bits.TMR1IF = 0;
	
	// set timer initial value to get NUMBER_OF_INSTR at timer overflow
	TMR1H=TICK_COUNTER_HIGH;
	TMR1L=TICK_COUNTER_LOW;
	
	TickCount++;
}

#pragma code

void timer1_init(void)
{
	// set timer initial value to get NUMBER_OF_INSTR at timer overflow
	//TMR1H=TICK_COUNTER_HIGH;
	//TMR1L=TICK_COUNTER_LOW;
	
	TMR1H=0xFF;
	TMR1L=0xA0;
	
	// reset TickCount
	TickCount=0;
	
	//1:1 prescaler, internal source Fosc/4
	T1CON=0x81;
	
	// Low priority 
	IPR1bits.TMR1IP = 0;
	
	// Enable interrupt
	PIE1bits.TMR1IE = 1;
}

void on_init(void)
{
	PIE1 = 0x00;
	PIR1 = 0x00;
	PIE2 = 0x00;
	PIR2 = 0x00;
	T1CON = 0x00;
	T2CON = 0x00;
	CCP1CON = 0x00;
	ADCON0 = 0x00;
	ADCON1 = 0x0F;
	CMCON = 0x07;	
	LATB = 0x00;
	LATC = 0x00;
	UCFG = 0x00;
	IPR1 = 0x00;
	IPR2 = 0x00;
	WDTCON = 0x00;
	RCON = 0x80; // enable interrupt priorities
	INTCON = 0xC0; // enable interrupts of high and low priority
	INTCON2 = 0x00;
	INTCON3 = 0x00;
	SPPCFG = 0x00;
	SPPCON = 0x00;
	UCON = 0x00;
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	TRISE = 0x00;
}
	
//static far unsigned char PWM[24][6];
// (1R 1G 1B 2R 2G 2B ... 7R 7G 7B)

#pragma udata PWMARRAY
static unsigned char PWM0_0;
static unsigned char PWM1_0;
static unsigned char PWM2_0;
static unsigned char PWM3_0;
static unsigned char PWM4_0;
static unsigned char PWM5_0;
static unsigned char PWM6_0;
static unsigned char PWM7_0;
static unsigned char PWM8_0;
static unsigned char PWM9_0;
static unsigned char PWM10_0;
static unsigned char PWM11_0;
static unsigned char PWM12_0;
static unsigned char PWM13_0;
static unsigned char PWM14_0;
static unsigned char PWM15_0;
static unsigned char PWM16_0;
static unsigned char PWM17_0;
static unsigned char PWM18_0;
static unsigned char PWM19_0;
static unsigned char PWM20_0;
static unsigned char PWM21_0;
static unsigned char PWM22_0;
static unsigned char PWM23_0;

static unsigned char PWM0_1;
static unsigned char PWM1_1;
static unsigned char PWM2_1;
static unsigned char PWM3_1;
static unsigned char PWM4_1;
static unsigned char PWM5_1;
static unsigned char PWM6_1;
static unsigned char PWM7_1;
static unsigned char PWM8_1;
static unsigned char PWM9_1;
static unsigned char PWM10_1;
static unsigned char PWM11_1;
static unsigned char PWM12_1;
static unsigned char PWM13_1;
static unsigned char PWM14_1;
static unsigned char PWM15_1;
static unsigned char PWM16_1;
static unsigned char PWM17_1;
static unsigned char PWM18_1;
static unsigned char PWM19_1;
static unsigned char PWM20_1;
static unsigned char PWM21_1;
static unsigned char PWM22_1;
static unsigned char PWM23_1;

static unsigned char PWM0_2;
static unsigned char PWM1_2;
static unsigned char PWM2_2;
static unsigned char PWM3_2;
static unsigned char PWM4_2;
static unsigned char PWM5_2;
static unsigned char PWM6_2;
static unsigned char PWM7_2;
static unsigned char PWM8_2;
static unsigned char PWM9_2;
static unsigned char PWM10_2;
static unsigned char PWM11_2;
static unsigned char PWM12_2;
static unsigned char PWM13_2;
static unsigned char PWM14_2;
static unsigned char PWM15_2;
static unsigned char PWM16_2;
static unsigned char PWM17_2;
static unsigned char PWM18_2;
static unsigned char PWM19_2;
static unsigned char PWM20_2;
static unsigned char PWM21_2;
static unsigned char PWM22_2;
static unsigned char PWM23_2;

static unsigned char PWM0_3;
static unsigned char PWM1_3;
static unsigned char PWM2_3;
static unsigned char PWM3_3;
static unsigned char PWM4_3;
static unsigned char PWM5_3;
static unsigned char PWM6_3;
static unsigned char PWM7_3;
static unsigned char PWM8_3;
static unsigned char PWM9_3;
static unsigned char PWM10_3;
static unsigned char PWM11_3;
static unsigned char PWM12_3;
static unsigned char PWM13_3;
static unsigned char PWM14_3;
static unsigned char PWM15_3;
static unsigned char PWM16_3;
static unsigned char PWM17_3;
static unsigned char PWM18_3;
static unsigned char PWM19_3;
static unsigned char PWM20_3;
static unsigned char PWM21_3;
static unsigned char PWM22_3;
static unsigned char PWM23_3;

static unsigned char PWM0_4;
static unsigned char PWM1_4;
static unsigned char PWM2_4;
static unsigned char PWM3_4;
static unsigned char PWM4_4;
static unsigned char PWM5_4;
static unsigned char PWM6_4;
static unsigned char PWM7_4;
static unsigned char PWM8_4;
static unsigned char PWM9_4;
static unsigned char PWM10_4;
static unsigned char PWM11_4;
static unsigned char PWM12_4;
static unsigned char PWM13_4;
static unsigned char PWM14_4;
static unsigned char PWM15_4;
static unsigned char PWM16_4;
static unsigned char PWM17_4;
static unsigned char PWM18_4;
static unsigned char PWM19_4;
static unsigned char PWM20_4;
static unsigned char PWM21_4;
static unsigned char PWM22_4;
static unsigned char PWM23_4;

static unsigned char PWM0_5;
static unsigned char PWM1_5;
static unsigned char PWM2_5;
static unsigned char PWM3_5;
static unsigned char PWM4_5;
static unsigned char PWM5_5;
static unsigned char PWM6_5;
static unsigned char PWM7_5;
static unsigned char PWM8_5;
static unsigned char PWM9_5;
static unsigned char PWM10_5;
static unsigned char PWM11_5;
static unsigned char PWM12_5;
static unsigned char PWM13_5;
static unsigned char PWM14_5;
static unsigned char PWM15_5;
static unsigned char PWM16_5;
static unsigned char PWM17_5;
static unsigned char PWM18_5;
static unsigned char PWM19_5;
static unsigned char PWM20_5;
static unsigned char PWM21_5;
static unsigned char PWM22_5;
static unsigned char PWM23_5;

static unsigned char PWMTickCount;
static unsigned char Segment;
static unsigned char Pixel;
static unsigned char CurrentPixel;
static unsigned char EffectPixelOffset;

static unsigned int PixelPointer;
static unsigned char PixelPointerUpper;
static unsigned char PixelPointerLower;

static unsigned long TargetTime;
static unsigned long CorrectedTime;
static unsigned long TurnStart;

static unsigned long EffectStart;
static unsigned long EffectLength;


#pragma code

void pwm_init(void)
{
	PWM0_0 = 7;
	PWM1_0 = 7;
	PWM2_0 = 7;
	PWM3_0 = 7;
	PWM4_0 = 7;
	PWM5_0 = 7;
	PWM6_0 = 7;
	PWM7_0 = 7;
	PWM8_0 = 7;
	PWM9_0 = 7;
	PWM10_0 = 7;
	PWM11_0 = 7;
	PWM12_0 = 7;
	PWM13_0 = 7;
	PWM14_0 = 7;
	PWM15_0 = 7;
	PWM16_0 = 7;
	PWM17_0 = 7;
	PWM18_0 = 7;
	PWM19_0 = 7;
	PWM20_0 = 7;
	PWM21_0 = 7;
	PWM22_0 = 7;
	PWM23_0 = 7;
	
	PWM0_1 = 7;
	PWM1_1 = 7;
	PWM2_1 = 7;
	PWM3_1 = 7;
	PWM4_1 = 7;
	PWM5_1 = 7;
	PWM6_1 = 7;
	PWM7_1 = 7;
	PWM8_1 = 7;
	PWM9_1 = 7;
	PWM10_1 = 7;
	PWM11_1 = 7;
	PWM12_1 = 7;
	PWM13_1 = 7;
	PWM14_1 = 7;
	PWM15_1 = 7;
	PWM16_1 = 7;
	PWM17_1 = 7;
	PWM18_1 = 7;
	PWM19_1 = 7;
	PWM20_1 = 7;
	PWM21_1 = 7;
	PWM22_1 = 7;
	PWM23_1 = 7;
	
	PWM0_2 = 7;
	PWM1_2 = 7;
	PWM2_2 = 7;
	PWM3_2 = 7;
	PWM4_2 = 7;
	PWM5_2 = 7;
	PWM6_2 = 7;
	PWM7_2 = 7;
	PWM8_2 = 7;
	PWM9_2 = 7;
	PWM10_2 = 7;
	PWM11_2 = 7;
	PWM12_2 = 7;
	PWM13_2 = 7;
	PWM14_2 = 7;
	PWM15_2 = 7;
	PWM16_2 = 7;
	PWM17_2 = 7;
	PWM18_2 = 7;
	PWM19_2 = 7;
	PWM20_2 = 7;
	PWM21_2 = 7;
	PWM22_2 = 7;
	PWM23_2 = 7;
	
	PWM0_3 = 7;
	PWM1_3 = 7;
	PWM2_3 = 7;
	PWM3_3 = 7;
	PWM4_3 = 7;
	PWM5_3 = 7;
	PWM6_3 = 7;
	PWM7_3 = 7;
	PWM8_3 = 7;
	PWM9_3 = 7;
	PWM10_3 = 7;
	PWM11_3 = 7;
	PWM12_3 = 7;
	PWM13_3 = 7;
	PWM14_3 = 7;
	PWM15_3 = 7;
	PWM16_3 = 7;
	PWM17_3 = 7;
	PWM18_3 = 7;
	PWM19_3 = 7;
	PWM20_3 = 7;
	PWM21_3 = 7;
	PWM22_3 = 7;
	PWM23_3 = 7;
	
	PWM0_4 = 7;
	PWM1_4 = 7;
	PWM2_4 = 7;
	PWM3_4 = 7;
	PWM4_4 = 7;
	PWM5_4 = 7;
	PWM6_4 = 7;
	PWM7_4 = 7;
	PWM8_4 = 7;
	PWM9_4 = 7;
	PWM10_4 = 7;
	PWM11_4 = 7;
	PWM12_4 = 7;
	PWM13_4 = 7;
	PWM14_4 = 7;
	PWM15_4 = 7;
	PWM16_4 = 7;
	PWM17_4 = 7;
	PWM18_4 = 7;
	PWM19_4 = 7;
	PWM20_4 = 7;
	PWM21_4 = 7;
	PWM22_4 = 7;
	PWM23_4 = 7;
	
	PWM0_5 = 7;
	PWM1_5 = 7;
	PWM2_5 = 7;
	PWM3_5 = 7;
	PWM4_5 = 7;
	PWM5_5 = 7;
	PWM6_5 = 7;
	PWM7_5 = 7;
	PWM8_5 = 7;
	PWM9_5 = 7;
	PWM10_5 = 7;
	PWM11_5 = 7;
	PWM12_5 = 7;
	PWM13_5 = 7;
	PWM14_5 = 7;
	PWM15_5 = 7;
	PWM16_5 = 7;
	PWM17_5 = 7;
	PWM18_5 = 7;
	PWM19_5 = 7;
	PWM20_5 = 7;
	PWM21_5 = 7;
	PWM22_5 = 7;
	PWM23_5 = 7;
	
	Segment = 0;
	PWMTickCount = 0;
	TargetTime = 0;
	CorrectedTime = 0;
	TurnStart = 0;
	EffectPixelOffset = 0;
	
	SEGMENT_1X = 0;
	SEGMENT_1Y = 0;
	SEGMENT_1Z = 0;
	SEGMENT_2X = 0;
	SEGMENT_2Y = 0;
	SEGMENT_2Z = 0;
}

unsigned long diff(unsigned long Start, unsigned long End)
{
	if (End > Start)
	{
		return End - Start;
	}
	else
	{
		return Start - End;
	}
}

void set_mclr(unsigned char value)
{
	unsigned char *pnt;
	
	//Setup writes: EEPGD=1,CFGS=1,WREN=1
	EECON1 = 0b11000100;
	TBLPTR = 0x300005;
	TABLAT = (value & 0x01) << 7;
	INTCONbits.GIE = 0;
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	EECON1bits.WREN = 0;
	INTCONbits.GIE = 1;
}

void read_pixels(void)
{	
	PixelPointer = (unsigned char)Pixel + (unsigned char)EffectPixelOffset;
	PixelPointer = CODE_ADDR_LOWER + 48 * (unsigned int)PixelPointer;
	PixelPointerUpper = (PixelPointer >> 8) & 0xFF;
	PixelPointerLower = PixelPointer & 0xFF;
	
	_asm
		MOVLW CODE_ADDR_UPPER
		MOVWF TBLPTRU, 0
		MOVF PixelPointerUpper, 0, BANKED
		MOVWF TBLPTRH, 0
		MOVF PixelPointerLower, 0, BANKED
		MOVWF TBLPTRL, 0
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS				// Read TABLAT to WREG;  WREG = RRRGGGBB
		MOVWF CurrentPixel, BANKED			// Put WREG in current_pixel
		RLNCF CurrentPixel, 1, BANKED		// Shift C_P to left;   WREG = RRGGGBBR
		MOVF CurrentPixel, 0, BANKED 		// Put C_P in WREG
		ANDLW 0x06							// AND WREG with 0x06;   WREG = 00000BB0
		MOVWF PWM2_0, BANKED				// Put WREG in blue channel
		
		RLNCF CurrentPixel, 1, BANKED		// Shift C_P to left;    C_P  = RGGGBBRR
		RLNCF CurrentPixel, 1, BANKED		// Shift C_P to left;    C_P  = GGGBBRRR
		MOVF CurrentPixel, 0, BANKED 		// Put C_P in WREG
		ANDLW 0x07							// AND WREG with 0x07;   WREG = 00000RRR
		MOVWF PWM0_0, BANKED				// Put WREG in red channel
		
		RLNCF CurrentPixel, 1, BANKED		// Shift C_P to left;    C_P  = GGBBRRRG
		RLNCF CurrentPixel, 1, BANKED		// Shift C_P to left;    C_P  = GBBRRRGG
		RLNCF CurrentPixel, 1, BANKED		// Shift C_P to left;    C_P  = BBRRRGGG
		MOVF CurrentPixel, 0, BANKED 		// Put C_P in WREG
		ANDLW 0x07							// AND WREG with 0x07;   WREG = 00000GGG
		MOVWF PWM1_0, BANKED				// Put WREG in green channel
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM5_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM3_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM4_0, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM8_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM6_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM7_0, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM11_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM9_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM10_0, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM14_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM12_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM13_0, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM17_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM15_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM16_0, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM20_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM18_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM19_0, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM23_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM21_0, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM22_0, BANKED
		
		
		
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM2_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM0_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM1_1, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM5_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM3_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM4_1, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM8_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM6_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM7_1, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM11_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM9_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM10_1, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM14_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM12_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM13_1, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM17_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM15_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM16_1, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM20_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM18_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM19_1, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM23_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM21_1, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM22_1, BANKED
		
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM2_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM0_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM1_2, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM5_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM3_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM4_2, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM8_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM6_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM7_2, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM11_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM9_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM10_2, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM14_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM12_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM13_2, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM17_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM15_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM16_2, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM20_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM18_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM19_2, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM23_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM21_2, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM22_2, BANKED
		
		
		
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM2_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM0_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM1_3, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM5_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM3_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM4_3, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM8_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM6_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM7_3, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM11_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM9_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM10_3, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM14_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM12_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM13_3, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM17_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM15_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM16_3, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM20_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM18_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM19_3, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM23_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM21_3, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM22_3, BANKED
		
		
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM2_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM0_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM1_4, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM5_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM3_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM4_4, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM8_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM6_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM7_4, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM11_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM9_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM10_4, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM14_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM12_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM13_4, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM17_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM15_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM16_4, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM20_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM18_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM19_4, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM23_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM21_4, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM22_4, BANKED
		
		
		
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM2_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM0_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM1_5, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM5_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM3_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM4_5, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM8_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM6_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM7_5, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM11_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM9_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM10_5, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM14_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM12_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM13_5, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM17_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM15_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM16_5, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM20_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM18_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM19_5, BANKED
		
		TBLRDPOSTINC
		MOVF TABLAT, 0, ACCESS
		MOVWF CurrentPixel, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x06
		MOVWF PWM23_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM21_5, BANKED
		
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		RLNCF CurrentPixel, 1, BANKED
		MOVF CurrentPixel, 0, BANKED
		ANDLW 0x07
		MOVWF PWM22_5, BANKED
	_endasm
}

void effect_reset(void)
{
	EffectPixelOffset = 0;
}

void effect_next(void)
{
	EffectPixelOffset++;
}

void main(void)
{
	// initialize values and registers
	on_init();
	
	// disable mclr so we can use it to register magnetic sensor
	set_mclr(0);
	
	// enable the timer
	timer1_init();
	
	// initialize our custom pwm module
	pwm_init();
	
	
	TargetTime = 10000;
	CorrectedTime = TickCount + TargetTime;
	
	EffectLength = 100000;

	while(1)
	{	
		PWMTickCount++;
		
		// one extra 'cool down' period in which all led's go off and Segment can be switched
		if (PWMTickCount == (unsigned char)9)
		{	
			switch (Segment)
			{
				case 0:
					SEGMENT_1X = 0;
				break;
				case 1:
					SEGMENT_1Y = 0;
				break;
				case 2:
					SEGMENT_1Z = 0;
				break;
				case 3:
					SEGMENT_2X = 0;
				break;
				case 4:
					SEGMENT_2Y = 0;
				break;
				case 5:
					SEGMENT_2Z = 0;
				break;
			}
		}
				
		if (PWMTickCount >= (unsigned char)10)
		{
			PWMTickCount = 1;
			
			if (TickCount - CorrectedTime < (unsigned long)30)
			{
				Pixel++;
				
				read_pixels();
				
				// Overshoot = TickCount-CorrectedTime
				// CorrectedTime = TickCount + TargetTime - Overshoot
				CorrectedTime = CorrectedTime + TargetTime;
			}
			
			Segment++;
			
			if (Segment >= (unsigned char)6)
			{
				Segment = 0;
				
				if (!PORTEbits.RE3)
				{
					if (diff(TurnStart, TickCount) > (unsigned long)7000)
					{
						Pixel = 0;
						
						TargetTime = (TickCount - TurnStart) / 256;
						CorrectedTime = TickCount + TargetTime;
						TurnStart = TickCount;
					}
					
					if (diff(TurnStart, TickCount) < (unsigned long)15000)
					{
						//effect_reset();
						//EffectStart = TickCount;
					}
				}
				
				if (diff(EffectStart, TickCount) > EffectLength)
				{
					effect_next();
					EffectStart = TickCount;
				}
			}
			
			switch (Segment)
			{
				case 0:
					SEGMENT_1X = 1;
				break;
				case 1:
					SEGMENT_1Y = 1;
				break;
				case 2:
					SEGMENT_1Z = 1;
				break;
				case 3:
					SEGMENT_2X = 1;
				break;
				case 4:
					SEGMENT_2Y = 1;
				break;
				case 5:
					SEGMENT_2Z = 1;
				break;
			}
			
			// only once every cycle check if we should shutdown
			if (diff(TurnStart, TickCount) > (unsigned long)150000)
			{
				set_mclr(1);
				INTCONbits.GIE = 0;
				_asm
					SLEEP
					goto 0x00
				_endasm
			}
		}
		
		_asm
			MOVLB 1
			
			MOVLW 0
			CPFSGT Segment, BANKED
			GOTO segment_0
			
			MOVLW 1
			CPFSGT Segment, BANKED
			GOTO segment_1
			
			MOVLW 2
			CPFSGT Segment, BANKED
			GOTO segment_2
			
			MOVLW 3
			CPFSGT Segment, BANKED
			GOTO segment_3
			
			MOVLW 4
			CPFSGT Segment, BANKED
			GOTO segment_4
			
			GOTO segment_5
			
			segment_0:
			MOVF PWM0_0, 0, BANKED
			BCF PORT_LED1R, BIT_LED1R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1R, BIT_LED1R, ACCESS
			
			MOVF PWM1_0, 0, BANKED
			BCF PORT_LED1G, BIT_LED1G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1G, BIT_LED1G, ACCESS
			
			MOVF PWM2_0, 0, BANKED
			BCF PORT_LED1B, BIT_LED1B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1B, BIT_LED1B, ACCESS
			
			
			MOVF PWM3_0, 0, BANKED
			BCF PORT_LED2R, BIT_LED2R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2R, BIT_LED2R, ACCESS
			
			MOVF PWM4_0, 0, BANKED
			BCF PORT_LED2G, BIT_LED2G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2G, BIT_LED2G, ACCESS
			
			MOVF PWM5_0, 0, BANKED
			BCF PORT_LED2B, BIT_LED2B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2B, BIT_LED2B, ACCESS
			
			
			MOVF PWM6_0, 0, BANKED
			BCF PORT_LED3R, BIT_LED3R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3R, BIT_LED3R, ACCESS
			
			MOVF PWM7_0, 0, BANKED
			BCF PORT_LED3G, BIT_LED3G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3G, BIT_LED3G, ACCESS
			
			MOVF PWM8_0, 0, BANKED
			BCF PORT_LED3B, BIT_LED3B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3B, BIT_LED3B, ACCESS
			
			
			MOVF PWM9_0, 0, BANKED
			BCF PORT_LED4R, BIT_LED4R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4R, BIT_LED4R, ACCESS
			
			MOVF PWM10_0, 0, BANKED
			BCF PORT_LED4G, BIT_LED4G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4G, BIT_LED4G, ACCESS
			
			MOVF PWM11_0, 0, BANKED
			BCF PORT_LED4B, BIT_LED4B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4B, BIT_LED4B, ACCESS
			
			
			MOVF PWM12_0, 0, BANKED
			BCF PORT_LED5R, BIT_LED5R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5R, BIT_LED5R, ACCESS
			
			MOVF PWM13_0, 0, BANKED
			BCF PORT_LED5G, BIT_LED5G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5G, BIT_LED5G, ACCESS
			
			MOVF PWM14_0, 0, BANKED
			BCF PORT_LED5B, BIT_LED5B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5B, BIT_LED5B, ACCESS
			
			
			MOVF PWM15_0, 0, BANKED
			BCF PORT_LED6R, BIT_LED6R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6R, BIT_LED6R, ACCESS
			
			MOVF PWM16_0, 0, BANKED
			BCF PORT_LED6G, BIT_LED6G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6G, BIT_LED6G, ACCESS
			
			MOVF PWM17_0, 0, BANKED
			BCF PORT_LED6B, BIT_LED6B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6B, BIT_LED6B, ACCESS
			
			
			MOVF PWM18_0, 0, BANKED
			BCF PORT_LED7R, BIT_LED7R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7R, BIT_LED7R, ACCESS
			
			MOVF PWM19_0, 0, BANKED
			BCF PORT_LED7G, BIT_LED7G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7G, BIT_LED7G, ACCESS
			
			MOVF PWM20_0, 0, BANKED
			BCF PORT_LED7B, BIT_LED7B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7B, BIT_LED7B, ACCESS
			
			
			MOVF PWM21_0, 0, BANKED
			BCF PORT_LED8R, BIT_LED8R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8R, BIT_LED8R, ACCESS
			
			MOVF PWM22_0, 0, BANKED
			BCF PORT_LED8G, BIT_LED8G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8G, BIT_LED8G, ACCESS
			
			MOVF PWM23_0, 0, BANKED
			BCF PORT_LED8B, BIT_LED8B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8B, BIT_LED8B, ACCESS
			
			GOTO end
			
			
			segment_1:
			MOVF PWM0_1, 0, BANKED
			BCF PORT_LED1R, BIT_LED1R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1R, BIT_LED1R, ACCESS
			
			MOVF PWM1_1, 0, BANKED
			BCF PORT_LED1G, BIT_LED1G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1G, BIT_LED1G, ACCESS
			
			MOVF PWM2_1, 0, BANKED
			BCF PORT_LED1B, BIT_LED1B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1B, BIT_LED1B, ACCESS
			
			
			MOVF PWM3_1, 0, BANKED
			BCF PORT_LED2R, BIT_LED2R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2R, BIT_LED2R, ACCESS
			
			MOVF PWM4_1, 0, BANKED
			BCF PORT_LED2G, BIT_LED2G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2G, BIT_LED2G, ACCESS
			
			MOVF PWM5_1, 0, BANKED
			BCF PORT_LED2B, BIT_LED2B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2B, BIT_LED2B, ACCESS
			
			
			MOVF PWM6_1, 0, BANKED
			BCF PORT_LED3R, BIT_LED3R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3R, BIT_LED3R, ACCESS
			
			MOVF PWM7_1, 0, BANKED
			BCF PORT_LED3G, BIT_LED3G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3G, BIT_LED3G, ACCESS
			
			MOVF PWM8_1, 0, BANKED
			BCF PORT_LED3B, BIT_LED3B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3B, BIT_LED3B, ACCESS
			
			
			MOVF PWM9_1, 0, BANKED
			BCF PORT_LED4R, BIT_LED4R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4R, BIT_LED4R, ACCESS
			
			MOVF PWM10_1, 0, BANKED
			BCF PORT_LED4G, BIT_LED4G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4G, BIT_LED4G, ACCESS
			
			MOVF PWM11_1, 0, BANKED
			BCF PORT_LED4B, BIT_LED4B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4B, BIT_LED4B, ACCESS
			
			
			MOVF PWM12_1, 0, BANKED
			BCF PORT_LED5R, BIT_LED5R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5R, BIT_LED5R, ACCESS
			
			MOVF PWM13_1, 0, BANKED
			BCF PORT_LED5G, BIT_LED5G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5G, BIT_LED5G, ACCESS
			
			MOVF PWM14_1, 0, BANKED
			BCF PORT_LED5B, BIT_LED5B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5B, BIT_LED5B, ACCESS
			
			
			MOVF PWM15_1, 0, BANKED
			BCF PORT_LED6R, BIT_LED6R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6R, BIT_LED6R, ACCESS
			
			MOVF PWM16_1, 0, BANKED
			BCF PORT_LED6G, BIT_LED6G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6G, BIT_LED6G, ACCESS
			
			MOVF PWM17_1, 0, BANKED
			BCF PORT_LED6B, BIT_LED6B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6B, BIT_LED6B, ACCESS
			
			
			MOVF PWM18_1, 0, BANKED
			BCF PORT_LED7R, BIT_LED7R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7R, BIT_LED7R, ACCESS
			
			MOVF PWM19_1, 0, BANKED
			BCF PORT_LED7G, BIT_LED7G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7G, BIT_LED7G, ACCESS
			
			MOVF PWM20_1, 0, BANKED
			BCF PORT_LED7B, BIT_LED7B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7B, BIT_LED7B, ACCESS
			
			
			MOVF PWM21_1, 0, BANKED
			BCF PORT_LED8R, BIT_LED8R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8R, BIT_LED8R, ACCESS
			
			MOVF PWM22_1, 0, BANKED
			BCF PORT_LED8G, BIT_LED8G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8G, BIT_LED8G, ACCESS
			
			MOVF PWM23_1, 0, BANKED
			BCF PORT_LED8B, BIT_LED8B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8B, BIT_LED8B, ACCESS
			
			GOTO end
			
			
			
			segment_2:
			MOVF PWM0_2, 0, BANKED
			BCF PORT_LED1R, BIT_LED1R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1R, BIT_LED1R, ACCESS
			
			MOVF PWM1_2, 0, BANKED
			BCF PORT_LED1G, BIT_LED1G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1G, BIT_LED1G, ACCESS
			
			MOVF PWM2_2, 0, BANKED
			BCF PORT_LED1B, BIT_LED1B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1B, BIT_LED1B, ACCESS
			
			
			MOVF PWM3_2, 0, BANKED
			BCF PORT_LED2R, BIT_LED2R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2R, BIT_LED2R, ACCESS
			
			MOVF PWM4_2, 0, BANKED
			BCF PORT_LED2G, BIT_LED2G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2G, BIT_LED2G, ACCESS
			
			MOVF PWM5_2, 0, BANKED
			BCF PORT_LED2B, BIT_LED2B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2B, BIT_LED2B, ACCESS
			
			
			MOVF PWM6_2, 0, BANKED
			BCF PORT_LED3R, BIT_LED3R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3R, BIT_LED3R, ACCESS
			
			MOVF PWM7_2, 0, BANKED
			BCF PORT_LED3G, BIT_LED3G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3G, BIT_LED3G, ACCESS
			
			MOVF PWM8_2, 0, BANKED
			BCF PORT_LED3B, BIT_LED3B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3B, BIT_LED3B, ACCESS
			
			
			MOVF PWM9_2, 0, BANKED
			BCF PORT_LED4R, BIT_LED4R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4R, BIT_LED4R, ACCESS
			
			MOVF PWM10_2, 0, BANKED
			BCF PORT_LED4G, BIT_LED4G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4G, BIT_LED4G, ACCESS
			
			MOVF PWM11_2, 0, BANKED
			BCF PORT_LED4B, BIT_LED4B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4B, BIT_LED4B, ACCESS
			
			
			MOVF PWM12_2, 0, BANKED
			BCF PORT_LED5R, BIT_LED5R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5R, BIT_LED5R, ACCESS
			
			MOVF PWM13_2, 0, BANKED
			BCF PORT_LED5G, BIT_LED5G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5G, BIT_LED5G, ACCESS
			
			MOVF PWM14_2, 0, BANKED
			BCF PORT_LED5B, BIT_LED5B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5B, BIT_LED5B, ACCESS
			
			
			MOVF PWM15_2, 0, BANKED
			BCF PORT_LED6R, BIT_LED6R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6R, BIT_LED6R, ACCESS
			
			MOVF PWM16_2, 0, BANKED
			BCF PORT_LED6G, BIT_LED6G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6G, BIT_LED6G, ACCESS
			
			MOVF PWM17_2, 0, BANKED
			BCF PORT_LED6B, BIT_LED6B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6B, BIT_LED6B, ACCESS
			
			
			MOVF PWM18_2, 0, BANKED
			BCF PORT_LED7R, BIT_LED7R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7R, BIT_LED7R, ACCESS
			
			MOVF PWM19_2, 0, BANKED
			BCF PORT_LED7G, BIT_LED7G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7G, BIT_LED7G, ACCESS
			
			MOVF PWM20_2, 0, BANKED
			BCF PORT_LED7B, BIT_LED7B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7B, BIT_LED7B, ACCESS
			
			
			MOVF PWM21_2, 0, BANKED
			BCF PORT_LED8R, BIT_LED8R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8R, BIT_LED8R, ACCESS
			
			MOVF PWM22_2, 0, BANKED
			BCF PORT_LED8G, BIT_LED8G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8G, BIT_LED8G, ACCESS
			
			MOVF PWM23_2, 0, BANKED
			BCF PORT_LED8B, BIT_LED8B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8B, BIT_LED8B, ACCESS
			
			GOTO end
			
			
			segment_3:
			MOVF PWM0_3, 0, BANKED
			BCF PORT_LED1R, BIT_LED1R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1R, BIT_LED1R, ACCESS
			
			MOVF PWM1_3, 0, BANKED
			BCF PORT_LED1G, BIT_LED1G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1G, BIT_LED1G, ACCESS
			
			MOVF PWM2_3, 0, BANKED
			BCF PORT_LED1B, BIT_LED1B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1B, BIT_LED1B, ACCESS
			
			
			MOVF PWM3_3, 0, BANKED
			BCF PORT_LED2R, BIT_LED2R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2R, BIT_LED2R, ACCESS
			
			MOVF PWM4_3, 0, BANKED
			BCF PORT_LED2G, BIT_LED2G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2G, BIT_LED2G, ACCESS
			
			MOVF PWM5_3, 0, BANKED
			BCF PORT_LED2B, BIT_LED2B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2B, BIT_LED2B, ACCESS
			
			
			MOVF PWM6_3, 0, BANKED
			BCF PORT_LED3R, BIT_LED3R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3R, BIT_LED3R, ACCESS
			
			MOVF PWM7_3, 0, BANKED
			BCF PORT_LED3G, BIT_LED3G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3G, BIT_LED3G, ACCESS
			
			MOVF PWM8_3, 0, BANKED
			BCF PORT_LED3B, BIT_LED3B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3B, BIT_LED3B, ACCESS
			
			
			MOVF PWM9_3, 0, BANKED
			BCF PORT_LED4R, BIT_LED4R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4R, BIT_LED4R, ACCESS
			
			MOVF PWM10_3, 0, BANKED
			BCF PORT_LED4G, BIT_LED4G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4G, BIT_LED4G, ACCESS
			
			MOVF PWM11_3, 0, BANKED
			BCF PORT_LED4B, BIT_LED4B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4B, BIT_LED4B, ACCESS
			
			
			MOVF PWM12_3, 0, BANKED
			BCF PORT_LED5R, BIT_LED5R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5R, BIT_LED5R, ACCESS
			
			MOVF PWM13_3, 0, BANKED
			BCF PORT_LED5G, BIT_LED5G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5G, BIT_LED5G, ACCESS
			
			MOVF PWM14_3, 0, BANKED
			BCF PORT_LED5B, BIT_LED5B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5B, BIT_LED5B, ACCESS
			
			
			MOVF PWM15_3, 0, BANKED
			BCF PORT_LED6R, BIT_LED6R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6R, BIT_LED6R, ACCESS
			
			MOVF PWM16_3, 0, BANKED
			BCF PORT_LED6G, BIT_LED6G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6G, BIT_LED6G, ACCESS
			
			MOVF PWM17_3, 0, BANKED
			BCF PORT_LED6B, BIT_LED6B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6B, BIT_LED6B, ACCESS
			
			
			MOVF PWM18_3, 0, BANKED
			BCF PORT_LED7R, BIT_LED7R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7R, BIT_LED7R, ACCESS
			
			MOVF PWM19_3, 0, BANKED
			BCF PORT_LED7G, BIT_LED7G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7G, BIT_LED7G, ACCESS
			
			MOVF PWM20_3, 0, BANKED
			BCF PORT_LED7B, BIT_LED7B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7B, BIT_LED7B, ACCESS
			
			
			MOVF PWM21_3, 0, BANKED
			BCF PORT_LED8R, BIT_LED8R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8R, BIT_LED8R, ACCESS
			
			MOVF PWM22_3, 0, BANKED
			BCF PORT_LED8G, BIT_LED8G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8G, BIT_LED8G, ACCESS
			
			MOVF PWM23_3, 0, BANKED
			BCF PORT_LED8B, BIT_LED8B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8B, BIT_LED8B, ACCESS
			
			GOTO end
			
			
			segment_4:
			MOVF PWM0_4, 0, BANKED
			BCF PORT_LED1R, BIT_LED1R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1R, BIT_LED1R, ACCESS
			
			MOVF PWM1_4, 0, BANKED
			BCF PORT_LED1G, BIT_LED1G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1G, BIT_LED1G, ACCESS
			
			MOVF PWM2_4, 0, BANKED
			BCF PORT_LED1B, BIT_LED1B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1B, BIT_LED1B, ACCESS
			
			
			MOVF PWM3_4, 0, BANKED
			BCF PORT_LED2R, BIT_LED2R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2R, BIT_LED2R, ACCESS
			
			MOVF PWM4_4, 0, BANKED
			BCF PORT_LED2G, BIT_LED2G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2G, BIT_LED2G, ACCESS
			
			MOVF PWM5_4, 0, BANKED
			BCF PORT_LED2B, BIT_LED2B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2B, BIT_LED2B, ACCESS
			
			
			MOVF PWM6_4, 0, BANKED
			BCF PORT_LED3R, BIT_LED3R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3R, BIT_LED3R, ACCESS
			
			MOVF PWM7_4, 0, BANKED
			BCF PORT_LED3G, BIT_LED3G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3G, BIT_LED3G, ACCESS
			
			MOVF PWM8_4, 0, BANKED
			BCF PORT_LED3B, BIT_LED3B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3B, BIT_LED3B, ACCESS
			
			
			MOVF PWM9_4, 0, BANKED
			BCF PORT_LED4R, BIT_LED4R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4R, BIT_LED4R, ACCESS
			
			MOVF PWM10_4, 0, BANKED
			BCF PORT_LED4G, BIT_LED4G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4G, BIT_LED4G, ACCESS
			
			MOVF PWM11_4, 0, BANKED
			BCF PORT_LED4B, BIT_LED4B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4B, BIT_LED4B, ACCESS
			
			
			MOVF PWM12_4, 0, BANKED
			BCF PORT_LED5R, BIT_LED5R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5R, BIT_LED5R, ACCESS
			
			MOVF PWM13_4, 0, BANKED
			BCF PORT_LED5G, BIT_LED5G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5G, BIT_LED5G, ACCESS
			
			MOVF PWM14_4, 0, BANKED
			BCF PORT_LED5B, BIT_LED5B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5B, BIT_LED5B, ACCESS
			
			
			MOVF PWM15_4, 0, BANKED
			BCF PORT_LED6R, BIT_LED6R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6R, BIT_LED6R, ACCESS
			
			MOVF PWM16_4, 0, BANKED
			BCF PORT_LED6G, BIT_LED6G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6G, BIT_LED6G, ACCESS
			
			MOVF PWM17_4, 0, BANKED
			BCF PORT_LED6B, BIT_LED6B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6B, BIT_LED6B, ACCESS
			
			
			MOVF PWM18_4, 0, BANKED
			BCF PORT_LED7R, BIT_LED7R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7R, BIT_LED7R, ACCESS
			
			MOVF PWM19_4, 0, BANKED
			BCF PORT_LED7G, BIT_LED7G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7G, BIT_LED7G, ACCESS
			
			MOVF PWM20_4, 0, BANKED
			BCF PORT_LED7B, BIT_LED7B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7B, BIT_LED7B, ACCESS
			
			
			MOVF PWM21_4, 0, BANKED
			BCF PORT_LED8R, BIT_LED8R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8R, BIT_LED8R, ACCESS
			
			MOVF PWM22_4, 0, BANKED
			BCF PORT_LED8G, BIT_LED8G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8G, BIT_LED8G, ACCESS
			
			MOVF PWM23_4, 0, BANKED
			BCF PORT_LED8B, BIT_LED8B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8B, BIT_LED8B, ACCESS
			
			GOTO end
			
			
			segment_5:
			MOVF PWM0_5, 0, BANKED
			BCF PORT_LED1R, BIT_LED1R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1R, BIT_LED1R, ACCESS
			
			MOVF PWM1_5, 0, BANKED
			BCF PORT_LED1G, BIT_LED1G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1G, BIT_LED1G, ACCESS
			
			MOVF PWM2_5, 0, BANKED
			BCF PORT_LED1B, BIT_LED1B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED1B, BIT_LED1B, ACCESS
			
			
			MOVF PWM3_5, 0, BANKED
			BCF PORT_LED2R, BIT_LED2R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2R, BIT_LED2R, ACCESS
			
			MOVF PWM4_5, 0, BANKED
			BCF PORT_LED2G, BIT_LED2G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2G, BIT_LED2G, ACCESS
			
			MOVF PWM5_5, 0, BANKED
			BCF PORT_LED2B, BIT_LED2B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED2B, BIT_LED2B, ACCESS
			
			
			MOVF PWM6_5, 0, BANKED
			BCF PORT_LED3R, BIT_LED3R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3R, BIT_LED3R, ACCESS
			
			MOVF PWM7_5, 0, BANKED
			BCF PORT_LED3G, BIT_LED3G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3G, BIT_LED3G, ACCESS
			
			MOVF PWM8_5, 0, BANKED
			BCF PORT_LED3B, BIT_LED3B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED3B, BIT_LED3B, ACCESS
			
			
			MOVF PWM9_5, 0, BANKED
			BCF PORT_LED4R, BIT_LED4R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4R, BIT_LED4R, ACCESS
			
			MOVF PWM10_5, 0, BANKED
			BCF PORT_LED4G, BIT_LED4G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4G, BIT_LED4G, ACCESS
			
			MOVF PWM11_5, 0, BANKED
			BCF PORT_LED4B, BIT_LED4B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED4B, BIT_LED4B, ACCESS
			
			
			MOVF PWM12_5, 0, BANKED
			BCF PORT_LED5R, BIT_LED5R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5R, BIT_LED5R, ACCESS
			
			MOVF PWM13_5, 0, BANKED
			BCF PORT_LED5G, BIT_LED5G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5G, BIT_LED5G, ACCESS
			
			MOVF PWM14_5, 0, BANKED
			BCF PORT_LED5B, BIT_LED5B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED5B, BIT_LED5B, ACCESS
			
			
			MOVF PWM15_5, 0, BANKED
			BCF PORT_LED6R, BIT_LED6R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6R, BIT_LED6R, ACCESS
			
			MOVF PWM16_5, 0, BANKED
			BCF PORT_LED6G, BIT_LED6G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6G, BIT_LED6G, ACCESS
			
			MOVF PWM17_5, 0, BANKED
			BCF PORT_LED6B, BIT_LED6B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED6B, BIT_LED6B, ACCESS
			
			
			MOVF PWM18_5, 0, BANKED
			BCF PORT_LED7R, BIT_LED7R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7R, BIT_LED7R, ACCESS
			
			MOVF PWM19_5, 0, BANKED
			BCF PORT_LED7G, BIT_LED7G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7G, BIT_LED7G, ACCESS
			
			MOVF PWM20_5, 0, BANKED
			BCF PORT_LED7B, BIT_LED7B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED7B, BIT_LED7B, ACCESS
			
			
			MOVF PWM21_5, 0, BANKED
			BCF PORT_LED8R, BIT_LED8R, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8R, BIT_LED8R, ACCESS
			
			MOVF PWM22_5, 0, BANKED
			BCF PORT_LED8G, BIT_LED8G, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8G, BIT_LED8G, ACCESS
			
			MOVF PWM23_5, 0, BANKED
			BCF PORT_LED8B, BIT_LED8B, ACCESS
			CPFSGT PWMTickCount, BANKED
			BSF PORT_LED8B, BIT_LED8B, ACCESS
			
			end:
		_endasm
	}
}
