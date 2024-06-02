#include "../include/z7seg.h"
#include <zephyr/drivers/gpio.h>

const struct gpio_dt_spec oe = GPIO_DT_SPEC_GET(DT_NODELABEL(oe), gpios);
const struct gpio_dt_spec rclk = GPIO_DT_SPEC_GET(DT_NODELABEL(rclk), gpios);
const struct gpio_dt_spec srclk = GPIO_DT_SPEC_GET(DT_NODELABEL(srclk), gpios);
const struct gpio_dt_spec ser = GPIO_DT_SPEC_GET(DT_NODELABEL(ser), gpios);
const struct gpio_dt_spec srclr = GPIO_DT_SPEC_GET(DT_NODELABEL(srclr), gpios);

int init_gpios()
{

        if (!gpio_is_ready_dt(&oe))
        {
            return 0;
        }
        else
        {
            gpio_pin_configure_dt(&oe, GPIO_OUTPUT_LOW);
        }

        if (!gpio_is_ready_dt(&rclk))
        {
            return 0;
        }
        else
        {
            gpio_pin_configure_dt(&rclk, GPIO_OUTPUT_LOW);
        }

        if (!gpio_is_ready_dt(&srclk))
        {
            return 0;
        }
        else
        {
            gpio_pin_configure_dt(&srclk, GPIO_OUTPUT_LOW);
        }

        if (!gpio_is_ready_dt(&ser))
        {
            return 0;
        }
        else
        {
            gpio_pin_configure_dt(&ser, GPIO_OUTPUT_LOW);
        }

        if (!gpio_is_ready_dt(&srclr))
        {
            return 0;
        }
        else
        {
            gpio_pin_configure_dt(&srclr, GPIO_OUTPUT_LOW);
        }
        return 1;
}
void init_7seg(struct z7seg *this)
{
    // the code  for each number exists in  an equivalent index in the array
    // eg code of 0 is stored at index 0 and 9 at index 9
    // the codes assume a common cathode  configuration of the leds
    int arr[10] = {0b0111111, 0b0000110, 0b1011011, 0b1001111,
                       0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111};

    // store the binary codes in the struct
    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
    {
        this->binary_codes[i] = arr[i];
    }
    // decimal place
    this->dp = 0;
    this->curr_value = 0;
    return;
}
void shift(struct z7seg *this)

{
    gpio_pin_set_dt(&oe, 1);
    gpio_pin_set_dt(&srclk, 0);
    k_msleep(1);
    gpio_pin_set_dt(&srclr, 1);
    for (int i = 7; i >= 0; --i)
    { // get a single bit ,bit i
       int biti = ((1 << i) & this->binary_codes[this->curr_value]) >> i;
        // set shift register clock to high
        gpio_pin_set_dt(&srclk, 0);
        // set data value
        gpio_pin_set_dt(&ser, biti);
        k_msleep(1);
        gpio_pin_set_dt(&srclk, 1);
        k_msleep(1);
    }
    gpio_pin_set_dt(&rclk,1);
    k_msleep(2);
    gpio_pin_set_dt(&rclk,0);
    gpio_pin_set_dt(&oe, 0);
}
