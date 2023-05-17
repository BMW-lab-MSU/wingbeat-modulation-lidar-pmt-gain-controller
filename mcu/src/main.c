#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>


void dac_init(void) {

    // Enable the 1.5 V internal reference
    /* NOTE: the MSP430FR2355 internal reference defaults to 1.5 V, but
             but can be changed to 2.0 or 2.5V. */
    PMMCTL2 |= INTREFEN;

    // Set the DAC reference to the internal 1.5 V reference
    // TODO: internal reference doesn't work. I must need to do some additional settings
    SAC0DAC |= DACSREF_1;
    SAC1DAC |= DACSREF_1;

    // Multiplex the P1.1 and P1.5 to select the DAC outputs
    P1SEL1 |= BIT1 | BIT5;
    P1SEL0 |= BIT1 | BIT5;

    // Enable the DACs
    SAC0DAC |= DACEN;
    SAC1DAC |= DACEN;

    // Select the DAC as the positive input source
    SAC0OA |= PSEL_1;
    SAC1OA |= PSEL_1;

    // Select the PGA source for the negative input; the PGA will be configured for buffer mode
    SAC0OA |= NSEL_1;
    SAC1OA |= NSEL_1;

    // Set the PGA to buffer mode
    SAC0PGA |= MSEL_1;
    SAC1PGA |= MSEL_1;

    // Enable the positive input and negative input muxes
    SAC0OA |= PMUXEN | NMUXEN;
    SAC1OA |= PMUXEN | NMUXEN;

    // Enable the op-amp outputs
    SAC0OA |= OAEN;
    SAC1OA |= OAEN;

    // Enable smart analog combo (SAC) modules 0 and 1
    SAC0OA |= SACEN;
    SAC1OA |= SACEN;


//    SAC_DAC_selectRefVoltage(SAC0_BASE, SAC_DAC_SECONDARY_REFERENCE);
//    SAC_DAC_selectRefVoltage(SAC1_BASE, SAC_DAC_SECONDARY_REFERENCE);
//
//    SAC_DAC_enable(SAC0_BASE);
//    SAC_DAC_enable(SAC1_BASE);
}

void init(void) {
    // Disable watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Disable the GPIO power-on default high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // SET P1.0 direction as output
    P1DIR |= 0x01;

    dac_init();
}


void main(void) {

    init();

    // set DAC voltages
    SAC0DAT = 0x0555u;
    SAC1DAT = 0x0fffu;

    while(true) {
        volatile unsigned int i;            // volatile to prevent optimization

        P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR

        i = 50000u;                          // SW Delay
        do i--;
        while(i != 0);
    }
}
