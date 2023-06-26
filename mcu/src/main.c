#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#include "dac.h"
#include "uart.h"
#include "parser.h"
#include "pmt_config.h"


void printU(char* string);

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
    char buf[BUF_SIZE];

    init();

    P1OUT |= BIT1;

    while(true)
    {
        if(rxbuf_is_full())
        {
            get_rxbuf(buf);
            
            pmt_data_t parsed;
            
            if(parse_command(buf, &parsed))
            {
                if(parsed.pmt == SIGNAL)
                {
                    set_dac_voltage(dac2, parsed.data);
                } else {
                    set_dac_voltage(dac3, parsed.data);
                }
            } else {
                printU("invalid input\r");
            }
            printU(buf);
        }
    }
}

void printU(char* string)
{
    int i = 0;
    int j;
    while(string[i] != '\0')
    {
        UCA0TXBUF = string[i];      

        // delay loop to slow down UART transmission.
        // TODO: there must be a better way to do this and actually send the chars at the baud rate, but this is just temporary for now...
        for (j = 0; j < 1000; j++)
        {
            __asm__("NOP");
        }
        i++;
    }

    UCA0TXBUF = '\n';
}
