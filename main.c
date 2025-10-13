#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    uint8_t ipv4_1;
    uint8_t ipv4_2;
    uint8_t ipv4_3;
    uint8_t ipv4_4;
}ipv4_t;

typedef struct {
ipv4_t ip_address;
uint8_t mask;
}prefix_t;

prefix_t master_collections[2] = {{127,0,0,1,255},
                                 {192,168,0,1,32}};

void printf_prefix(prefix_t prefix_input){
    printf("%d.%d.%d.%d/%d\n",
        prefix_input.ip_address.ipv4_1,
        prefix_input.ip_address.ipv4_2,
        prefix_input.ip_address.ipv4_3,
        prefix_input.ip_address.ipv4_4,
        prefix_input.mask
    );
}

int main()
{
    printf("Hello everyone :) IPv4_prefixes !\n");

    printf_prefix(master_collections[0]);
    printf_prefix(master_collections[1]);
    
    return 0;
}