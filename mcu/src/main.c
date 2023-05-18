#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#include "dac.h"
#include "uart.h"

// Set up DACs
// TODO: maybe I should pass these into the init function instead of using globals...
struct dac_t dac2 =
{
    .sac_base_addr = SAC2_BASE,
    .port_base_addr = P3_BASE,
    .port_bit = BIT1,
};
struct dac_t dac3 =
{
    .sac_base_addr = SAC3_BASE,
    .port_base_addr = P3_BASE,
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

    init_dac(dac2);
    init_dac(dac3);

    init_uart();
}


void main(void)
{

    init();

    // set DAC voltages
    set_dac_data(dac2, 0x0abcu);
    set_dac_data(dac3, 0x0fffu);

    P1OUT |= BIT1;

    while(true)
    {

    }

}
