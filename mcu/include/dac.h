#ifndef DAC_H
#define DAC_H

#include <stdint.h>

void init_dac(void);

// TODO: I'll probably abstract this so there is a "dac" struct that knows which register
//       to write to based upon the DAC #. Basically a DAC class, but in C :)
void set_dac0_data(uint16_t data);
void set_dac1_data(uint16_t data);

#endif // DAC_H