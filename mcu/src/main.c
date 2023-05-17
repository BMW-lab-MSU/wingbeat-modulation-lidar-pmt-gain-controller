#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#include "dac.h"


void init(void) {
    // Disable watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Disable the GPIO power-on default high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // SET P1.0 direction as output
    P1DIR |= 0x01;

    init_dac();
}


void main(void) {

    init();

    // set DAC voltages
    set_dac0_data(0x0555u);
    set_dac1_data(0x0fffu);

    while(true) {
        volatile unsigned int i;            // volatile to prevent optimization

        P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR

        i = 50000u;                          // SW Delay
        do i--;
        while(i != 0);
    }
}
