#include <msp430.h>

#include "dac.h"

void init_dac(void)
{
    // I used section 2.5 of the following app note to figure out
    // how to configure the "smart analog combo" to operate in DAC mode
    // https://www.ti.com/lit/an/slaa833a/slaa833a.pdf

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
}

void set_dac0_data(uint16_t data)
{
    SAC0DAT = data;
}

void set_dac1_data(uint16_t data)
{
    SAC1DAT = data;
}
