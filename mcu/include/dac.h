#ifndef DAC_H
#define DAC_H

#include <stdint.h>

struct dac_t {
    const uint16_t *sac_base_addr;
    const uint16_t *port_base_addr;
    const uint16_t port_bit;
    uint16_t data;
};

void init_dac(struct dac_t dac);

// TODO: I'll probably abstract this so there is a "dac" struct that knows which register
//       to write to based upon the DAC #. Basically a DAC class, but in C :)
// void set_dac0_data(uint16_t data);
// void set_dac1_data(uint16_t data);
void set_dac_data(struct dac_t dac, uint16_t data);

#endif // DAC_H