#include<zephyr/kernel.h>
#include<zephyr/drivers/gpio.h>
#include<zephyr/drivers/uart.h>
#include"../include/z7seg.h"
#include<zephyr/device.h>

#include<zephyr/drivers/misc/pio_rpi_pico/pio_rpi_pico.h>

#include"7seg.pio.h"

#define SIDE_SET_BASE 3
#define PIO_FREQ 1000000
#define SET_BASE 0
#define OUT_PIN 2
// ;GPIO0->OE
// ;GPIO1->SRCLR
// ;GPIO2->SER
// ;GPIO3->SRCLK
// ;GPIO4->RCLK


const struct gpio_dt_spec led= GPIO_DT_SPEC_GET(DT_ALIAS(led0),gpios);
const struct device *const seg_pio=DEVICE_DT_GET(DT_ALIAS(piodt));

void exec_pio(struct z7seg *seg)
{
    PIO pio=pio_rpi_pico_get_pio(seg_pio);
    uint offset=pio_add_program(pio,&seg7_program);
    uint sm=pio_claim_unused_sm(pio,true);

    seg7_program_init(pio,sm,offset,PIO_FREQ,SIDE_SET_BASE,SET_BASE,OUT_PIN);
    while(true)
    {
         k_msleep(1000);
        pio_sm_put_blocking(pio,sm,seg->binary_codes[seg->curr_value]);
        k_msleep(1000);
        seg->curr_value=(seg->curr_value+1)%10;
    }
}

int  main()
{
    if(!device_is_ready(seg_pio))
    {
        return 1;
    }
    struct z7seg led_seg;
    exec_pio(&led_seg);
    
    return 0;
}