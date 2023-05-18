#include <msp430.h>

void init_uart(void)
{
    // Put USCI_A0 into software reset
    // It needs to be in software reset for us to modify some register settings
    UCA0CTLW0 |= UCSWRST;

    // Use the SMCLK as the UART clock
    // SMCLK defaults to 1 MHz?
    UCA0CTLW0 |= UCSSEL__SMCLK;
    
    // Set baud rate to 115200 bps.
    // SMCLK is set to 1 MHz by default, so that's what I'm using as the UART clock
    // Calculations are from here: 
    // https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
    
    // Set the prescaler to 8
    UCA0BRW = 8;

    // Set the secondary modulation stage to 214
    UCA0MCTLW |= 0xd600;

    /*
     Multiplex the UART pins to P1.6 (UCA0RXD) and P1.7 (UCA0TXD)
     */
    // Mux RXD (P1.6)
    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT6;
    // Mux TXD (P1.7)
    P1SEL1 &= ~BIT7;
    P1SEL0 |= BIT7;

    // Take USCI_A0 out of software reset
    UCA0CTLW0 &= ~UCSWRST;

    // Enable the receive interrupt
    UCA0IE |= UCRXIE;
    __enable_interrupt();
}

#pragma vector = EUSCI_A0_VECTOR
__interrupt void uart_rx_isr(void)
{
    if (UCA0RXBUF == 't')
    {
        P1OUT ^= BIT0;                      // Toggle P1.0 using exclusive-OR
    }
}
