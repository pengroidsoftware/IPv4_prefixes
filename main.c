#include <stdio.h>
#include "ipv4.h"
#include "ipv4_types.h"

extern prefix_t master_collections[];

int main()
{
    printf("Hello everyone :) IPv4_prefixes !\n");

    printf_prefix(master_collections[0]);
    printf_prefix(master_collections[1]);
    printf_prefix(master_collections[2]);
    
    return 0;
}