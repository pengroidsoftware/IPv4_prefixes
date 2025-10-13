#include <stdio.h>
#include <stdlib.h>

#include "ipv4.h"
#include "ipv4_types.h"

prefix_t master_collections[3] = {
                                  {127,0,0,1,255},
                                  {192,168,0,1,32},
                                  {255,255,0,1,255},
                                 };

void printf_prefix(prefix_t prefix_input){
    printf("%d.%d.%d.%d/%d\n",
        prefix_input.ip_address.ipv4_1,
        prefix_input.ip_address.ipv4_2,
        prefix_input.ip_address.ipv4_3,
        prefix_input.ip_address.ipv4_4,
        prefix_input.mask
    );
}

/* API functions (mey be moved for dedicated folder) */

int add_ipv4_prefix(ipv4_t base, uint8_t mask){
    return 0;
}

int del_ipv4_prefix(ipv4_t base, uint8_t mask){
    return 0;
}
char check_ipv4(ipv4_t ip){
    return 0;
}

/* *** END API functions *** */

