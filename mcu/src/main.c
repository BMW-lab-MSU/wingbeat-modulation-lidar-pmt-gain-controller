#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#include "dac.h"
#include "uart.h"

// Set up DACs
// TODO: maybe I should pass these into the init function instead of using globals...
struct dac_t dac0 = 
{
    .sac_base_addr = SAC0_BASE,
    .port_base_addr = PA_BASE,
    .port_bit = BIT1,
};
struct dac_t dac1 = 
{
    .sac_base_addr = SAC1_BASE,
    .port_base_addr = PA_BASE,
    .port_bit = BIT5,
};

void init(void)
{
    // Disable watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Disable the GPIO power-on default high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // SET P1.0 direction as output
    P1DIR |= 0x01;


    init_dac(dac0);
    init_dac(dac1);

    init_uart();
}


void main(void) {

    init();

    // set DAC voltages
    set_dac_data(dac0, 0x01aau);
    set_dac_data(dac1, 0x0fffu);

    P1OUT |= BIT1;

    while(true)
    {

    }

}
