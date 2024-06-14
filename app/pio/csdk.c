
#include<hardware/pio.h>
#include<hardware/clocks.h>

/***
 * @brief
 *  function to configure pio for 7seg 
 * @param PIO pio state instance
 * @param sm 0...3 pio state machine 
 * @param offset pio program offset
 * @param side_set_pins_base  since 2 pins are used for side_set 
 * i.e RCLK and SRCLK 
 *  2 consecutive  pins will be configured for sideset including the base pin 
 *  e.g if base is GPIO0, GPIO1 will 
 * also be  side_set pin 
 * @param set_pins_base  similar to side set except pins will be configured as set , set  pins are
 *  connected to OE and SRCLK
 * the base pin should be connected to OE and following pin connected to SRCLR
 * @param out_pin only a single out pin is required
 * @retval void
 */
static inline void seg7_program_init(PIO pio, int sm, int offset, unsigned int freq,
                                     unsigned int sideset_pins_base,
                                     unsigned int set_pins_base, unsigned int out_pin)
{
    pio_sm_config c = seg7_program_get_default_config(offset);
    // set pinctrl for gpios
     // Set this pin's GPIO function (connect PIO to the pad)
    for(int i =sideset_pins_base;i<=sideset_pins_base+1;++i)
    {
        pio_gpio_init(pio,i);
       
    }
    // set pins
    for(int i=set_pins_base;i<=set_pins_base+1;++i)
    {
        pio_gpio_init(pio,i);
    }
    // out pin 
    pio_gpio_init(pio,out_pin);
    //configure sideset pindirs
     pio_sm_set_consecutive_pindirs(pio,sm,sideset_pins_base,2,true);
    //set pins
    pio_sm_set_consecutive_pindirs(pio,sm,set_pins_base,2,true);
    // config direction for out pin
    pio_sm_set_consecutive_pindirs(pio,sm,out_pin,1,true);
    
    // configure pins for assembly instructions
    sm_config_set_out_pins(&c, out_pin, 1);
    sm_config_set_sideset_pins(&c,sideset_pins_base);
    sm_config_set_set_pins(&c,set_pins_base,2);

    sm_config_set_out_shift(&c,true,true,7);
    // set clock div for frequency
    float div=clock_get_hz(clk_sys)/freq;
    sm_config_set_clkdiv(&c,div);
    
// Load our configuration, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);
// Set the state machine running
    pio_sm_set_enabled(pio, sm, true);
}
