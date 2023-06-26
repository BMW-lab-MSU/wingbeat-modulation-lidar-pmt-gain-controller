// #include "pmt_config.h"
#include "parser.h"
#include "string.h"
#include "ctype.h"

// from here: https://stackoverflow.com/questions/9907160/how-to-convert-enum-names-to-string-in-c
const char const pmt_type_str[] = 
{
    [SIGNAL] = 's',
    [TRIGGER] = 't'
};

bool parse_command(const char *input, pmt_data_t *parsed)
{
    // validate command format
    if(!validate_format(input))
    {
        return false;
    }

    // extract PMT type and voltage value
    if(input[0] == pmt_type_str[SIGNAL])
    {
        parsed->pmt = SIGNAL;
    } else {
        parsed->pmt = TRIGGER;
    }
    
    const char* number = &input[1];
    uint16_t voltage = atoi(number);
    parsed->data = voltage;

    // if all is well, store the PMT type and voltage in the parsed structure and return true,
    // otherwise, return false to tell the caller that the command isn't valid
    //uint16_t bound = pmts[parsed->pmt].control_voltage_upper_bound;
    if(!validate_voltage_bounds(voltage,pmts[parsed->pmt].control_voltage_upper_bound,pmts[parsed->pmt].control_voltage_lower_bound))
    {
        return false;
    }

    return true;
}

//checks that length is 5, first char is SIGNAL or TRIGGER char, and remaining chars are digits
bool validate_format(const char *input)
{
    if(strlen(input) == 6 &
       (input[0] == pmt_type_str[SIGNAL] | input[0] == pmt_type_str[TRIGGER]) &
       (isdigit(input[1]) & isdigit(input[2]) & isdigit(input[3]) & isdigit(input[4])))
    {
        return true;
    }
    return false;
}

// might put this into parse_command if we stop caring about tests
bool validate_voltage_bounds(const uint16_t voltage, const uint16_t upper_bound, const uint16_t lower_bound)
{
    if(voltage > upper_bound | voltage < lower_bound)
    {
        return false;
    }
    return true;
}