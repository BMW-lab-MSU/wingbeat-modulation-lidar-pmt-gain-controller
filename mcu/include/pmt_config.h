#ifndef PMT_CONFIG_H
#define PMT_CONFIG_H

#include <stdint.h>

typedef enum {
    SIGNAL,
    TRIGGER
} pmt_type;

// from here: https://stackoverflow.com/questions/9907160/how-to-convert-enum-names-to-string-in-c
const char const pmt_type_str[] = 
{
    [SIGNAL] = 's',
    [TRIGGER] = 't'
};

typedef struct
{
    // PMT type from the pmt_type enum
    const pmt_type pmt;
    // control voltage upper limit, in mV
    const uint16_t control_voltage_upper_bound;
    // control voltage lower limit, in mV
    const uint16_t control_voltage_lower_bound;
} pmt_info_t;

// // Signal PMT info
// // TODO: this comment sucks. add real documentation
// static pmt_info_t signal_pmt_info = 
// {
//     .pmt = SIGNAL,
//     .control_voltage_upper_bound = 1000,
//     .control_voltage_lower_bound = 250
// };

// // Trigger PMT info
// // TODO: this comment sucks. add real documentation
// static pmt_info_t trigger_pmt_info =
// {
//     .pmt = TRIGGER,
//     .control_voltage_upper_bound = 900,
//     .control_voltage_lower_bound = 250
// };

static const pmt_info_t pmts[] = 
{
    // Output signal PMT info
    {
        .pmt = SIGNAL,
        .control_voltage_upper_bound = 1000,
        .control_voltage_lower_bound = 250,
    },
    // Trigger PMT info
    {
        .pmt = TRIGGER,
        .control_voltage_upper_bound = 900,
        .control_voltage_lower_bound = 250,
    }
};

#endif // PMT_CONFIG_H