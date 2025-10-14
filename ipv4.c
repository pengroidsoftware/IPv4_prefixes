#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ipv4.h"
#include "ipv4_types.h"
#include "errno.h"

#define PREFIXES_BUFFOR_NUMBER 255

/* INFO Decided not to use dynamic memory allocation for data collection - not using heap in embedded solutions */
prefix_t prefixes_collections[PREFIXES_BUFFOR_NUMBER] = {
                                //    {{192,0,0,1},255},
                                //    {{168,0,0,51},40},
                                //    {{255,0,0,1},16}
                                    {{0,0,0,0},0}
                                  };

uint32_t prefixes_collections_cnt = 0u;

static uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}

static bool check_if_already_added(prefix_t ip_prefix){

    // TO DO check if ip base exist

    // TO DO if exist check mask

    return false;
}

static void swap_items(prefix_t* item1, prefix_t* item2)
{
    prefix_t temp;

    temp.ip_address.ipv4_address_raw_data = item1->ip_address.ipv4_address_raw_data;
    temp.mask = item1->mask;

    item1->ip_address.ipv4_address_raw_data = item2->ip_address.ipv4_address_raw_data;
    item1->mask = item2->mask;

    item2->ip_address.ipv4_address_raw_data = temp.ip_address.ipv4_address_raw_data;
    item2->mask = temp.mask;
}

static int write_new_prefix(prefix_t ip_prefix)
{
    if(prefixes_collections_cnt < PREFIXES_BUFFOR_NUMBER)
    {
        /* INFO Sorted collection will be easier and more efficintly to check frequently -> time lost here for sorting will be get while checking IP addresses */

        /* Add new prefix at the and of collection and sort collection from the smaller base*/
        prefixes_collections_cnt;

        prefixes_collections[prefixes_collections_cnt].ip_address.ipv4_address_raw_data = swap_uint32(ip_prefix.ip_address.ipv4_address_raw_data);
        prefixes_collections[prefixes_collections_cnt].mask = ip_prefix.mask;

        for(int i = prefixes_collections_cnt; i > 0; i--)
        {
            if(prefixes_collections[prefixes_collections_cnt].ip_address.ipv4_address_raw_data < prefixes_collections[prefixes_collections_cnt - 1].ip_address.ipv4_address_raw_data)
            {
                /* Swap items to sort prefixes colection */
                swap_items(&prefixes_collections[prefixes_collections_cnt],&prefixes_collections[prefixes_collections_cnt-1]);
            }
            else
            {
                /* Break the lopp, collection is already sorted */
                break;
            }
        }

        prefixes_collections_cnt++;      
    }
    else
    {
        return E_OUT_OF_SPACE;
    }

    return E_OK;

}

/* Debug function */

void printf_prefix(prefix_t prefix_input){
    printf("%d.%d.%d.%d/%d\n",
        prefix_input.ip_address.ipv4_address_struct_data.ipv4_4,
        prefix_input.ip_address.ipv4_address_struct_data.ipv4_3,
        prefix_input.ip_address.ipv4_address_struct_data.ipv4_2,
        prefix_input.ip_address.ipv4_address_struct_data.ipv4_1,
        prefix_input.mask
    );
}

/* *** */

/* API functions */

int add_ipv4_prefix(prefix_t ip_prefix){

    if(check_if_already_added(ip_prefix) == true)
    {
        return E_ALREADY_ADDED;
    }

    if (write_new_prefix(ip_prefix) != E_OK);
    {
        return E_OUT_OF_SPACE;
    }
    
    return E_OK;
}

int del_ipv4_prefix(uint32_t base, uint8_t mask){
    return E_OK;
}
char check_ipv4(uint32_t ip){
    return E_OK;
}

/* *** */

