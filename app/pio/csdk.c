
#include<hardware/pio.h>
#include<hardware/clocks.h>


static inline void hello_program_init(PIO pio,int sm ,int offset,uint pin)
{
     pio_sm_config c = hello_program_get_default_config(offset);

     sm_config_set_out_pins(&c, pin, 1);
     // Set this pin's GPIO function (connect PIO to the pad)
    pio_gpio_init(pio, pin);
// Set the pin direction to output at the PIO
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
// Load our configuration, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);
// Set the state machine running
    pio_sm_set_enabled(pio, sm, true);
    
}
