#include <zephyr/kernel.h>

#ifndef Z7SEG
#define Z7SEG

struct z7seg;

void init_7seg(struct z7seg *this);
void shift(struct z7seg *this);

int init_gpios();
// declaration of struct

struct z7seg
{

    int curr_value;
    int binary_codes[10] ; 
    int dp ;
};

#endif