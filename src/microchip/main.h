#ifndef _MAIN_H
#define _MAIN_H

#pragma code

#define TICKS_PER_SECOND (50000) //50kHz interrupt for timer0, 1 tick=20us

#define NUMBER_OF_INSTR ((XTAL_FREQ/4)/TICKS_PER_SECOND)//prescaler 1:1 (Fosc/4)
#define TIMER_PRESET_VALUE (0xFFFF-NUMBER_OF_INSTR)
#define TICK_COUNTER_HIGH ((TIMER_PRESET_VALUE>>8)&0xFF)
#define TICK_COUNTER_LOW (TIMER_PRESET_VALUE&0xFF)

#define CODE_ADDR_UPPER 0x00
#define CODE_ADDR_LOWER 0x3000

#if (NUMBER_OF_INSTR>0xFFFF) 
#error "NUMBER OF INSTR too large"
#endif

#define PORT_LED1R LATB
#define BIT_LED1R 5
#define PORT_LED1G LATB
#define BIT_LED1G 3
#define PORT_LED1B LATB
#define BIT_LED1B 4

#define LED1R PORT_LED1Rbits.PORT_LED1RBIT_LED1R
#define LED1G PORT_LED1Gbits.PORT_LED1GBIT_LED1G
#define LED1B PORT_LED1Bbits.PORT_LED1BBIT_LED1B

#define PORT_LED2R LATB
#define BIT_LED2R 2
#define PORT_LED2G LATB
#define BIT_LED2G 0
#define PORT_LED2B LATB
#define BIT_LED2B 1

#define LED2R PORT_LED2Rbits.PORT_LED2RBIT_LED2R
#define LED2G PORT_LED2Gbits.PORT_LED2GBIT_LED2G
#define LED2B PORT_LED2Bbits.PORT_LED2BBIT_LED2B

#define PORT_LED3R LATD
#define BIT_LED3R 7
#define PORT_LED3G LATD
#define BIT_LED3G 5
#define PORT_LED3B LATD
#define BIT_LED3B 6

#define LED3R PORT_LED3Rbits.PORT_LED3RBIT_LED3R
#define LED3G PORT_LED3Gbits.PORT_LED3GBIT_LED3G
#define LED3B PORT_LED3Bbits.PORT_LED3BBIT_LED3B

#define PORT_LED4R LATD
#define BIT_LED4R 4
#define PORT_LED4G LATC
#define BIT_LED4G 6
#define PORT_LED4B LATC
#define BIT_LED4B 7

#define LED4R PORT_LED4Rbits.PORT_LED4RBIT_LED4R
#define LED4G PORT_LED4Gbits.PORT_LED4GBIT_LED4G
#define LED4B PORT_LED4Bbits.PORT_LED4BBIT_LED4B

#define PORT_LED5R LATA
#define BIT_LED5R 5
#define PORT_LED5G LATD
#define BIT_LED5G 3
#define PORT_LED5B LATA
#define BIT_LED5B 4

#define LED5R PORT_LED5Rbits.PORT_LED5RBIT_LED5R
#define LED5G PORT_LED5Gbits.PORT_LED5GBIT_LED5G
#define LED5B PORT_LED5Bbits.PORT_LED5BBIT_LED5B

#define PORT_LED6R LATD
#define BIT_LED6R 2
#define PORT_LED6G LATD
#define BIT_LED6G 0
#define PORT_LED6B LATD
#define BIT_LED6B 1

#define LED6R PORT_LED6Rbits.PORT_LED6RBIT_LED6R
#define LED6G PORT_LED6Gbits.PORT_LED6GBIT_LED6G
#define LED6B PORT_LED6Bbits.PORT_LED6BBIT_LED6B

#define PORT_LED7R LATC
#define BIT_LED7R 2
#define PORT_LED7G LATC
#define BIT_LED7G 0
#define PORT_LED7B LATC
#define BIT_LED7B 1

#define LED7R PORT_LED7Rbits.PORT_LED7RBIT_LED7R
#define LED7G PORT_LED7Gbits.PORT_LED7GBIT_LED7G
#define LED7B PORT_LED7Bbits.PORT_LED7BBIT_LED7B

#define PORT_LED8R LATE
#define BIT_LED8R 2
#define PORT_LED8G LATE
#define BIT_LED8G 0
#define PORT_LED8B LATE
#define BIT_LED8B 1

#define LED8R PORT_LED8Rbits.PORT_LED8RBIT_LED8R
#define LED8G PORT_LED8Gbits.PORT_LED8GBIT_LED8G
#define LED8B PORT_LED8Bbits.PORT_LED8BBIT_LED8B

#define SEGMENT_1X LATBbits.LATB6
#define SEGMENT_1Y LATAbits.LATA3
#define SEGMENT_1Z LATAbits.LATA2
#define SEGMENT_2X LATAbits.LATA0
#define SEGMENT_2Y LATBbits.LATB7
#define SEGMENT_2Z LATAbits.LATA1

void InterruptHandlerHigh(void);
void InterruptHandlerLow(void);
void on_init(void);
void main(void);
void timer1_init(void);
void DelayUs(unsigned char cnt);
void Delays100Us(unsigned long cnt);
void DelayMs(unsigned long cnt);
unsigned long DifferenceMs(unsigned long StartTick, unsigned long StopTick);
unsigned long Difference100Us(unsigned long StartTick, unsigned long StopTick);

#endif //_MAIN_H
