#include<zephyr/kernel.h>
#include<zephyr/drivers/gpio.h>
#include<zephyr/drivers/uart.h>
#include"../include/z7seg.h"

const struct gpio_dt_spec led= GPIO_DT_SPEC_GET(DT_ALIAS(led0),gpios);


int  main()
{

    if(!gpio_is_ready_dt(&led))
    {
        return 0;
       
    }
    gpio_pin_configure_dt(&led,GPIO_OUTPUT_LOW);
    
   struct z7seg led_7seg;

    init_7seg(&led_7seg);
    int ret=init_gpios();
    if(ret==0)
    {
        return 0;
    }
    gpio_pin_set_dt(&led,ret);
    while (true)
    {
        // loop through all the 10 elements in the array

        for(int i=0;i<=sizeof(led_7seg.binary_codes)/sizeof(int);i++)
    {
        led_7seg.curr_value=i;
        shift(&led_7seg);
        k_msleep(500);
    }
    }
    
    return 0;
}