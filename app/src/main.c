#include<zephyr/kernel.h>
#include<zephyr/drivers/gpio.h>
#include<zephyr/drivers/uart.h>
#include"../include/z7seg.h"

const struct gpio_dt_spec led= GPIO_DT_SPEC_GET(DT_ALIAS(led0),gpios);

struct k_timer timer0;
struct k_work work;
struct z7seg led_7seg;

void timer_cb(struct k_timer *timer)
{
    k_work_submit(&work);
}
void update_sr(struct k_work *work)
{
     
     shift(&led_7seg);
    led_7seg.curr_value+=1;
     if( led_7seg.curr_value>=10)
     {
            led_7seg.curr_value=0;
     }
}

int  main()
{

    if(!gpio_is_ready_dt(&led))
    {
        return 0;
       
    }
    gpio_pin_configure_dt(&led,GPIO_OUTPUT_LOW);
    
   k_work_init(&work,update_sr);
 k_timer_init(&timer0,timer_cb,NULL);
 k_timer_start(&timer0,K_SECONDS(1),K_SECONDS(1));
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

     k_sleep(K_FOREVER);
    
    }
    
    return 0;
}