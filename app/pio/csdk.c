
#include<hardware/pio.h>
#include<hardware/clocks.h>

static inline void seg7_program_init(PIO pio, int sm, int offset, unsigned int freq,
                                     unsigned int sideset_pins_base,
                                     unsigned int set_pins_base, unsigned int out_pin)
{
    pio_sm_config c = seg7_program_get_default_config(offset);
    // set pinctrl for gpios
     // Set this pin's GPIO function (connect PIO to the pad)
    for(int i=0;i<5;++i)
    {
        pio_gpio_init(pio,i);
    }
    pio_gpio_init(pio,25);
    // Set the pin direction to output at the PIO
    // from  GPIO0 to GPIO4
    pio_sm_set_consecutive_pindirs(pio,sm,set_pins_base,5,true);
    sm_config_set_out_pins(&c, out_pin, 1);
    sm_config_set_sideset_pins(&c,sideset_pins_base);
    sm_config_set_set_pins(&c,set_pins_base,1);

    sm_config_set_out_shift(&c,false,true,7);
    // set clock div for frequency
    float div=clock_get_hz(clk_sys)/freq;
    sm_config_set_clkdiv(&c,div);
    
    /*
    todo 
    1. set clockdiv 5mhz ->done
    2.  connect pio to pins i.e pinctrl->done
    */
   
  

// Load our configuration, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);
// Set the state machine running
    pio_sm_set_enabled(pio, sm, true);
}
