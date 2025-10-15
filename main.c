#include <stdio.h>
#include "ipv4.h"
#include "ipv4_types.h"
#include "errno.h"

void dev_tests()
{
    prefix_t temp = {{10,20,0,0},16};
    prefix_t temp_copy = {{10,20,0,192},16};
    prefix_t temp1 = {{50,0,0,2},255};
    prefix_t temp2 = {{168,64,128,0},20};

    prefix_t tempa = {{5,20,0,0},16};
    prefix_t temp1a = {{50,0,0,2},32};
    prefix_t temp2a = {{50,0,0,2},32};

    prefix_t not_existing = {{99,0,0,2},255};

    printf_collection();

    add_ipv4_prefix(temp);

    printf_collection();

    add_ipv4_prefix(temp1);

    printf_collection();

    add_ipv4_prefix(temp2);

    printf_collection();

    add_ipv4_prefix(tempa);

    printf_collection();

    add_ipv4_prefix(temp1a);

    printf_collection();

    add_ipv4_prefix(temp2a);

    printf_collection();

    del_ipv4_prefix(temp2a);

    printf_collection();

    del_ipv4_prefix(not_existing);

    printf_collection();

    del_ipv4_prefix(not_existing);

    check_ipv4(not_existing.ip_address.ipv4_address_raw_data);
    check_ipv4(temp_copy.ip_address.ipv4_address_raw_data);

    printf_collection();
}

int main()
{
    dev_tests();
    return E_OK;
}