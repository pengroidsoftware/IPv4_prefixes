#include <stdio.h>
#include "ipv4.h"
#include "ipv4_types.h"
#include "errno.h"

void dev_tests()
{
    prefix_t temp = {{10,20,0,0},16};
    prefix_t temp1 = {{50,0,0,2},255};
    prefix_t temp2 = {{168,64,128,0},20};

    prefix_t tempa = {{5,20,0,0},16};
    prefix_t temp1a = {{50,0,0,2},32};
    prefix_t temp2a = {{50,0,0,2},32};

    prefix_t not_existing = {{99,0,0,2},255};

    printf_collection();

    if(add_ipv4_prefix(temp) != E_OK)
    {
        // TO DO error here
    }

    printf_collection();

    if(add_ipv4_prefix(temp1) != E_OK)
    {
        // TO DO error here
    }

    printf_collection();

    if(add_ipv4_prefix(temp2) != E_OK)
    {
        // TO DO error here
    }

    printf_collection();

    if(add_ipv4_prefix(tempa) != E_OK)
    {
        // TO DO error here
    }

    printf_collection();

    if(add_ipv4_prefix(temp1a) != E_OK)
    {
        // TO DO error here
    }

    printf_collection();

    if(add_ipv4_prefix(temp2a) != E_OK)
    {
        // TO DO error here
    }

    printf_collection();

    if(del_ipv4_prefix(temp2a) != E_OK)
    {
        // TO DO error here
    }

    printf_collection();

    if(del_ipv4_prefix(not_existing) != E_OK)
    {
        // TO DO error here
    }

    printf_collection();
}

int main()
{
    dev_tests();
    return E_OK;
}