/*********************************************************************
 *
 *                Microchip USB Bootloader Version 1.0
 *
 *********************************************************************
 * FileName:        usbdrv.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the �Company�) for its PICmicro� Microcontroller is intended and
 * supplied to you, the Company�s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
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
 * -usbdrv.c-
 * This file contains functions that check the hardware interrupts for
 * USB events. The main function, USBDriverService(), should be called once
 * every main loop.
 * This is a mini-version of the actual usbdrv.c from the Microchip USB
 * Library. Many functions were removed to make the whole bootload application
 * fit under 2KB, which is the size of the boot block.
 *****************************************************************************/


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "sys\typedefs.h"
#include "sys\usb.h"
#include "io_cfg.h"             // Required for USBCheckBusStatus()

/** V A R I A B L E S ********************************************************/
#pragma udata

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void USBModuleEnable(void);
void USBModuleDisable(void);

void USBSuspend(void);
void USBWakeFromSuspend(void);

void USBProtocolResetHandler(void);
void USB_SOF_Handler(void);
void USBStallHandler(void);
void USBErrorHandler(void);

/** D E C L A R A T I O N S **************************************************/
#pragma code
/******************************************************************************
 * Function:        void USBCheckBusStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine enables/disables the USB module by monitoring
 *                  the USB power signal.
 *
 * Note:            None
 *****************************************************************************/
void USBCheckBusStatus(void)
{
    UCON = 0b00001000;              // Enable USBEN only
    /*
     * After enabling the USB module, it takes some time for the voltage
     * on the D+ or D- line to rise high enough to get out of the SE0 condition.
     * The USB Reset interrupt should not be unmasked until the SE0 condition is
     * cleared. This helps preventing the firmware from misinterpreting this
     * unique event as a USB bus reset from the USB host.
     */
    while(UCONbits.SE0);            // Blocking loop
    UIR = 0;                        // Clear all USB interrupts
    UIE = 0b00010001;               // Unmask RESET & IDLE interrupts only
    usb_device_state = POWERED_STATE;
}//end USBCheckBusStatus

/******************************************************************************
 * Function:        void USBDriverService(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine is the heart of this firmware. It manages
 *                  all USB interrupts.
 *
 * Note:            Device state transitions through the following stages:
 *                  DETACHED -> ATTACHED -> POWERED -> DEFAULT ->
 *                  ADDRESS_PENDING -> ADDRESSED -> CONFIGURED -> READY
 *****************************************************************************/
void USBDriverService(void)
{   
    /*
     * Task A: Service USB Activity Interrupt
     */

    if(UIRbits.ACTVIF && UIEbits.ACTVIE)
    {
        UCONbits.SUSPND = 0;
        UIEbits.ACTVIE = 0;
        UIRbits.ACTVIF = 0;
    }//end if
            
    /*
     * Task B: Service USB Bus Reset Interrupt.
     * When bus reset is received during suspend, ACTVIF will be set first,
     * once the UCONbits.SUSPND is clear, then the URSTIF bit will be asserted.
     * This is why URSTIF is checked after ACTVIF.
     *
     * The USB reset flag is masked when the USB state is in
     * DETACHED_STATE or ATTACHED_STATE, and therefore cannot
     * cause a USB reset event during these two states.
     */
    if(UIRbits.URSTIF && UIEbits.URSTIE)    USBProtocolResetHandler();
    
    /*
     * Task C: Service other USB interrupts
     */
    if(UIRbits.IDLEIF && UIEbits.IDLEIE)
    {
        UIEbits.ACTVIE = 1;                     // Enable bus activity interrupt
        UIRbits.IDLEIF = 0;
        UCONbits.SUSPND = 1;                    // Put USB module in power conserve
                                                // mode, SIE clock inactive
        /* Now, go into power saving */
        PIE2bits.USBIE = 1;                     // Set wakeup source
        Sleep();
        PIR2bits.USBIF = 0;
    }//end if
    
    if(UIRbits.STALLIF && UIEbits.STALLIE)
    {
        if(UEP0bits.EPSTALL == 1)
        {
            USBPrepareForNextSetupTrf();        // Firmware Work-Around
            UEP0bits.EPSTALL = 0;
        }//end if
        UIRbits.STALLIF = 0;
    }//end if

    /*
     * Pointless to continue servicing if the host has not sent a bus reset.
     * Once bus reset is received, the device transitions into the DEFAULT
     * state and is ready for communication.
     */
    if(usb_device_state < DEFAULT_STATE) return;

    /*
     * Task D: Servicing USB Transaction Complete Interrupt
     */
    if(UIRbits.TRNIF && UIEbits.TRNIE)
    {
        /*
         * USBCtrlEPService only services transactions over EP0.
         * It ignores all other EP transactions.
         */
        USBCtrlEPService();
        
        /*
         * Other EP can be serviced later by responsible device class firmware.
         * Each device driver knows when an OUT or IN transaction is ready by
         * checking the buffer ownership bit.
         * An OUT EP should always be owned by SIE until the data is ready.
         * An IN EP should always be owned by CPU until the data is ready.
         *
         * Because of this logic, it is not necessary to save the USTAT value
         * of non-EP0 transactions.
         */
        UIRbits.TRNIF = 0;
    }//end if(UIRbits.TRNIF && UIEbits.TRNIE)
    
}//end USBDriverService

/******************************************************************************
 * Function:        void USBProtocolResetHandler(void)
 *
 * PreCondition:    A USB bus reset is received from the host.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Currently, this routine flushes any pending USB
 *                  transactions. It empties out the USTAT FIFO. This action
 *                  might not be desirable in some applications.
 *
 * Overview:        Once a USB bus reset is received from the host, this
 *                  routine should be called. It resets the device address to
 *                  zero, disables all non-EP0 endpoints, initializes EP0 to
 *                  be ready for default communication, clears all USB
 *                  interrupt flags, unmasks applicable USB interrupts, and
 *                  reinitializes internal state-machine variables.
 *
 * Note:            None
 *****************************************************************************/
void USBProtocolResetHandler(void)
{
    UIR = 0;                        // Clears all USB interrupts
    UIE = 0b01111011;               // Enable all interrupts except ACTVIE
    UADDR = 0x00;                   // Reset to default address
    UEP0 = EP_CTRL|HSHK_EN;         // Init EP0 as a Ctrl EP, see usbdrv.h
    while(UIRbits.TRNIF == 1)       // Flush any pending transactions
        UIRbits.TRNIF = 0;
    UCONbits.PKTDIS = 0;            // Make sure packet processing is enabled
    USBPrepareForNextSetupTrf();    // Declared in usbctrltrf.c
    usb_active_cfg = 0;             // Clear active configuration
    usb_device_state = DEFAULT_STATE;
}//end USBProtocolResetHandler

/** EOF usbdrv.c *************************************************************/
