#include <stdio.h>
#include "ipv4.h"
#include "ipv4_types.h"
#include "errno.h"

void random_dev_tests()
{
    prefix_t temp =         {{10,20,0,0},16};
    prefix_t temp_copy =    {{10,20,0,192},16};
    prefix_t temp1 =        {{50,0,0,2},255};
    prefix_t temp2 =        {{168,64,128,0},20};

    prefix_t tempa =        {{5,20,0,0},16};
    prefix_t temp1a =       {{50,0,0,2},32};
    prefix_t temp2a =       {{50,0,0,2},32};

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

void adding_out_of_range_tests()
{
    int8_t error = E_OK;
     prefix_t prefix =         {{10,20,0,0},16};

     for(int i = 0 ; i < 256; i++)
     {
        error = add_ipv4_prefix(prefix);
     }

     if(error != E_ALREADY_ADDED) printf (" FAIL ");

     for(int i = 0 ; i < 500; i++)
     {
        prefix.ip_address.ipv4_address_raw_data++;
        error = add_ipv4_prefix(prefix);
     }

     if(error != E_OUT_OF_SPACE) printf (" FAIL ");
}

void removing_test()
{
    int8_t error = E_OK;
    prefix_t prefix =         {{0,0,0,0},16};

     printf_collection();

     for(int i = 0 ; i < 50; i++)
     {
        prefix.ip_address.ipv4_address_raw_data = i;
        error = add_ipv4_prefix(prefix);
     }
     
     printf_collection();

     for(int i = 0 ; i < 50; i++)
     {
        prefix.ip_address.ipv4_address_raw_data = i;
        error = del_ipv4_prefix(prefix);
     }

     printf_collection();

}

void removing_out_of_range_test()
{
    int8_t error = E_OK;
    prefix_t prefix =         {{0,0,0,0},16};

     printf_collection();

     for(int i = 0 ; i < 300; i++)
     {
        prefix.ip_address.ipv4_address_raw_data = i;
        error = add_ipv4_prefix(prefix);
     }
     
     printf_collection();

     for(int i = 0 ; i < 300; i++)
     {
        prefix.ip_address.ipv4_address_raw_data = i;
        error = del_ipv4_prefix(prefix);
     }

     printf_collection();

}

void checking_out_of_range_test()
{
    int8_t error = E_OK;
    prefix_t prefix =         {{0,0,0,0},16};

    printf_collection();

    for(int i = 0 ; i < 350; i++)
    {
        prefix.ip_address.ipv4_address_raw_data = i;
        error = add_ipv4_prefix(prefix);
    }
     
    printf_collection();

    for(int i = 0 ; i < 350; i++)
    {
        prefix.ip_address.ipv4_address_raw_data = i;
        error = check_ipv4(prefix.ip_address.ipv4_address_raw_data);
    }

    printf_collection();

    for(int i = 0 ; i < 350; i++)
    {
        prefix.ip_address.ipv4_address_raw_data = i;
        error = del_ipv4_prefix(prefix);
    }

    printf_collection();

}

int main()
{
    //random_dev_tests();
    //adding_out_of_range_tests();
    //removing_test();
    removing_out_of_range_test();
    //checking_out_of_range_test();

    return E_OK;
}