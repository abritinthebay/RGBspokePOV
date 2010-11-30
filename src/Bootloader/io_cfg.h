/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.0
 *
 *********************************************************************
 * FileName:        io_cfg.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04     Original.
 ********************************************************************/

/******************************************************************************
 * -io_cfg.h-
 * I/O Configuration File
 * The purpose of this file is to provide a mapping mechanism between
 * pin functions and pin assignments. This provides a layer of abstraction
 * for the firmware code and eases the migration process from one target
 * board design to another.
 *
 *****************************************************************************/

#ifndef IO_CFG_H
#define IO_CFG_H

/** I N C L U D E S *************************************************/
#include "usb\usbcfg.h"

/** T R I S *********************************************************/
#define INPUT_PIN           1
#define OUTPUT_PIN          0

/** U S B ***********************************************************/
#define tris_usb_bus_sense  TRISAbits.TRISA1    // Input

#if defined(USE_USB_BUS_SENSE_IO)
#define usb_bus_sense       PORTAbits.RA1
#else
#define usb_bus_sense       1
#endif

#define tris_self_power     TRISAbits.TRISA2    // Input

#if defined(USE_SELF_POWER_SENSE_IO)
#define self_power          PORTAbits.RA2
#else
#define self_power          1
#endif

#define PORT_LED1R LATB
#define BIT_LED1R 5
#define PORT_LED1G LATB
#define BIT_LED1G 3
#define PORT_LED1B LATB
#define BIT_LED1B 4

#define LED1R LATBbits.LATB5
#define LED1G LATBbits.LATB3
#define LED1B LATBbits.LATB4

#define PORT_LED2R LATB
#define BIT_LED2R 2
#define PORT_LED2G LATB
#define BIT_LED2G 0
#define PORT_LED2B LATB
#define BIT_LED2B 1

#define LED2R LATBbits.LATB2
#define LED2G LATBbits.LATB0
#define LED2B LATBbits.LATB1

#define PORT_LED3R LATD
#define BIT_LED3R 7
#define PORT_LED3G LATD
#define BIT_LED3G 5
#define PORT_LED3B LATD
#define BIT_LED3B 6

#define LED3R LATDbits.LATD7
#define LED3G LATDbits.LATD5
#define LED3B LATDbits.LATD6

#define PORT_LED4R LATD
#define BIT_LED4R 4
#define PORT_LED4G LATC
#define BIT_LED4G 6
#define PORT_LED4B LATC
#define BIT_LED4B 7

#define LED4R LATDbits.LATD4
#define LED4G LATCbits.LATC6
#define LED4B LATCbits.LATC7

#define PORT_LED5R LATA
#define BIT_LED5R 5
#define PORT_LED5G LATD
#define BIT_LED5G 3
#define PORT_LED5B LATA
#define BIT_LED5B 4

#define LED5R LATAbits.LATA5
#define LED5G LATDbits.LATD3
#define LED5B LATAbits.LATA4

#define PORT_LED6R LATD
#define BIT_LED6R 2
#define PORT_LED6G LATD
#define BIT_LED6G 0
#define PORT_LED6B LATD
#define BIT_LED6B 1

#define LED6R LATDbits.LATD2
#define LED6G LATDbits.LATD0
#define LED6B LATDbits.LATD1

#define PORT_LED7R LATC
#define BIT_LED7R 2
#define PORT_LED7G LATC
#define BIT_LED7G 0
#define PORT_LED7B LATC
#define BIT_LED7B 1

#define LED7R LATCbits.LATC2
#define LED7G LATCbits.LATC0
#define LED7B LATCbits.LATC1

#define PORT_LED8R LATE
#define BIT_LED8R 2
#define PORT_LED8G LATE
#define BIT_LED8G 0
#define PORT_LED8B LATE
#define BIT_LED8B 1

#define LED8R LATEbits.LATE2
#define LED8G LATEbits.LATE0
#define LED8B LATEbits.LATE1

#define SEGMENT_1X LATBbits.LATB6
#define SEGMENT_1Y LATAbits.LATA3
#define SEGMENT_1Z LATAbits.LATA2
#define SEGMENT_2X LATAbits.LATA0
#define SEGMENT_2Y LATBbits.LATB7
#define SEGMENT_2Z LATAbits.LATA1

#endif //IO_CFG_H
