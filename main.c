#include <stdio.h>
#include "ipv4.h"
#include "ipv4_types.h"
#include "errno.h"

extern prefix_t prefixes_collections[];

prefix_t temp = {{10,20,0,0},16};
prefix_t temp1 = {{50,0,0,2},255};
prefix_t temp2 = {{32,64,128,0},20};

int main()
{
    printf("Hello everyone :) IPv4_prefixes !\n");

    printf_prefix(prefixes_collections[0]);
    printf_prefix(prefixes_collections[1]);
    printf_prefix(prefixes_collections[2]);

    if(add_ipv4_prefix(temp) != E_OK)
    {
        // TO DO error here
    }

    printf(" *** \n");

    printf_prefix(prefixes_collections[0]);
    printf_prefix(prefixes_collections[1]);
    printf_prefix(prefixes_collections[2]);

    if(add_ipv4_prefix(temp1) != E_OK)
    {
        // TO DO error here
    }

    printf(" *** \n");

    printf_prefix(prefixes_collections[0]);
    printf_prefix(prefixes_collections[1]);
    printf_prefix(prefixes_collections[2]);

    if(add_ipv4_prefix(temp2) != E_OK)
    {
        // TO DO error here
    }

    printf(" *** \n");

    printf_prefix(prefixes_collections[0]);
    printf_prefix(prefixes_collections[1]);
    printf_prefix(prefixes_collections[2]);
    
    return E_OK;
}