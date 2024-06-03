#include<zephyr/kernel.h>
#include<zephyr/drivers/gpio.h>
#include<zephyr/drivers/uart.h>
#include"../include/z7seg.h"
#include<zephyr/device.h>

#include<zephyr/drivers/misc/pio_rpi_pico/pio_rpi_pico.h>

#include"7seg.pio.h"

const struct gpio_dt_spec led= GPIO_DT_SPEC_GET(DT_ALIAS(led0),gpios);
const struct device *const seg_pio=DEVICE_DT_GET(DT_ALIAS(piodt));

void exec_pio()
{
    PIO pio=pio_rpi_pico_get_pio(seg_pio);
    uint offset=pio_add_program(pio,&hello_program);
    uint sm=pio_claim_unused_sm(pio,true);

    hello_program_init(pio,sm,offset,25);
    while(true)
    {
        pio_sm_put_blocking(pio,sm,1);
        k_msleep(500);
        pio_sm_put_blocking(pio,sm,0);
        k_msleep(500);
    }
}

int  main()
{
    exec_pio();
    
    return 0;
}