#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ipv4.h"
#include "ipv4_types.h"
#include "errno.h"

#define PREFIXES_BUFFOR_NUMBER 255

//#define DEBUG

/* INFO Decided not to use dynamic memory allocation for data collection - not using heap in embedded solutions */
prefix_t prefixes_collections[PREFIXES_BUFFOR_NUMBER] = {0};
uint32_t prefixes_collections_cnt = 0u;

static bool check_if_prefix_exists(prefix_t* ip_prefix, uint8_t* index){

    if(ip_prefix == NULL) return false;

    /* No elements */
    if(prefixes_collections_cnt < 1) return false;

    /* If there is only one element, compere it*/
    if(prefixes_collections_cnt == 1){
        if(index != NULL) *index = 0u;
        return (
                 (prefixes_collections[0].ip_address.ipv4_address_raw_data == ip_prefix->ip_address.ipv4_address_raw_data) && 
                 (prefixes_collections[0].mask == ip_prefix->mask)
               ) 
                ? true : false;
    }

    /* Chek edges if the comparison is not necessary*/
    if(prefixes_collections[prefixes_collections_cnt-1].ip_address.ipv4_address_raw_data < ip_prefix->ip_address.ipv4_address_raw_data) 
    {
        /* New bigger base prefix, not already added one, skipp */
        return false;
    }

    if(prefixes_collections[0].ip_address.ipv4_address_raw_data > ip_prefix->ip_address.ipv4_address_raw_data) 
    {
        /* New smaller base prefix, skipp */
        return false;
    }

    /* Use bisection algorithm to check if prefix exists*/

    uint8_t low_index = 0;
    uint8_t high_index = prefixes_collections_cnt - 1;
    uint32_t mid = 0;
    
    while (low_index <= high_index) {
        
        mid = ( low_index + high_index ) >> 1; /* mid == (low + high) / 2 */

        if (prefixes_collections[mid].ip_address.ipv4_address_raw_data == ip_prefix->ip_address.ipv4_address_raw_data) 
        {
#ifdef DEBUG
            printf ("DEBUG: Found the same base\n");
#endif
            /* Compare mask */
            if(prefixes_collections[mid].mask == ip_prefix->mask)
            {
                /* Prefix found */
#ifdef DEBUG
                printf ("DEBUG: Found the same base and the same mask.\n");
#endif
                if(index != NULL) *index = mid;
                return true;
            }
            else
            {
#ifdef DEBUG
                printf ("DEBUG: but different mask, keep looking\n");
#endif
                /* Base prefix found, but mask different, check +-n items for the same base but different mask*/
                bool keep_looking_flag = false;
                uint8_t n = 0;
                /* Target may be on the both side, iterate for the same base but different mask*/
                do{
                    keep_looking_flag = false;
                    n++;

                    if( (n <= mid) && (prefixes_collections[mid - n].ip_address.ipv4_address_raw_data == ip_prefix->ip_address.ipv4_address_raw_data))
                    {
                        /* Compare mask */
                        if(prefixes_collections[mid-n].mask == ip_prefix->mask)
                        {
#ifdef DEBUG
                            printf ("DEBUG: Found the same base and the same mask.\n");
#endif
                            if(index != NULL) *index = mid-n;
                            return true;
                        }
                        else
                        {
                            keep_looking_flag = true;
                        }
                    }

                    if(((mid + n) <= PREFIXES_BUFFOR_NUMBER) && (prefixes_collections[mid + n].ip_address.ipv4_address_raw_data == ip_prefix->ip_address.ipv4_address_raw_data))
                    {
                        /* Compare mask */
                        if(prefixes_collections[mid+n].mask == ip_prefix->mask)
                        {
#ifdef DEBUG
                            printf ("DEBUG: Found the same base and the same mask.\n");
#endif
                            if(index != NULL) *index = mid+n;
                            return true;
                        }
                        else
                        {
                            keep_looking_flag = true;
                        }
                    }

                }while(keep_looking_flag == true);

                return false;
            }
        }

        /* Target is may be the right side*/
        if (prefixes_collections[mid].ip_address.ipv4_address_raw_data < ip_prefix->ip_address.ipv4_address_raw_data) {
            low_index = mid + 1;
        }
        /* Target may be on the lef side*/
        else 
        {
            high_index = mid - 1;
        }
    }

    /* return not found */
    return false;
}

static void swap_items(prefix_t* item1, prefix_t* item2)
{

    if(item1 == NULL || item2 == NULL) return;
    
    prefix_t temp;

    temp.ip_address.ipv4_address_raw_data = item1->ip_address.ipv4_address_raw_data;
    temp.mask = item1->mask;

    item1->ip_address.ipv4_address_raw_data = item2->ip_address.ipv4_address_raw_data;
    item1->mask = item2->mask;

    item2->ip_address.ipv4_address_raw_data = temp.ip_address.ipv4_address_raw_data;
    item2->mask = temp.mask;
}

static void clear_item(prefix_t* item1)
{
    if(item1 == NULL) return;

    item1->ip_address.ipv4_address_raw_data = 0u;
    item1->mask = 0u;
}

static int8_t write_new_prefix(prefix_t* ip_prefix)
{
    if(ip_prefix == NULL) return E_NULL_EXCEPTION;

    if(prefixes_collections_cnt < PREFIXES_BUFFOR_NUMBER - 1 ) // check if there is place fore one more, the prefixes_collections_cnt points to the next free in this moment
    {
        /* INFO Sorted collection will be easier and more efficintly to check frequently -> time lost here for sorting will be get while checking IP addresses */

        /* Add new prefix at the and of collection and sort collection from the smaller base*/
        prefixes_collections_cnt;

        prefixes_collections[prefixes_collections_cnt].ip_address.ipv4_address_raw_data = ip_prefix->ip_address.ipv4_address_raw_data;
        prefixes_collections[prefixes_collections_cnt].mask = ip_prefix->mask;

        for(int i = prefixes_collections_cnt; i > 0; i--)
        {
            if(prefixes_collections[i].ip_address.ipv4_address_raw_data < prefixes_collections[i - 1].ip_address.ipv4_address_raw_data)
            {
                /* Swap items to sort prefixes colection */
                swap_items(&prefixes_collections[i],&prefixes_collections[i-1]);
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

static int8_t remove_prefix(uint8_t index)
{
    if((prefixes_collections_cnt > 0) && (index < prefixes_collections_cnt)) /* double check, already checked upper*/
    {
        /* Clear deleted item */
        clear_item(&prefixes_collections[index]);

        /* Move all items to the left*/
        for(uint8_t i = index; i < prefixes_collections_cnt; i++){

            swap_items(&prefixes_collections[i],&prefixes_collections[i+1]);
        }

        prefixes_collections_cnt--;

        return E_OK;
    }

    return E_NOT_EXIST;
}

/* Debug function */

void printf_prefix(prefix_t* prefix_input){

    if(prefix_input == NULL) return;

    printf("%d.%d.%d.%d/%d\n",
        prefix_input->ip_address.ipv4_address_struct_data.ipv4_1,
        prefix_input->ip_address.ipv4_address_struct_data.ipv4_2,
        prefix_input->ip_address.ipv4_address_struct_data.ipv4_3,
        prefix_input->ip_address.ipv4_address_struct_data.ipv4_4,
        prefix_input->mask
    );
}

void printf_collection(){
    printf("\n\n*** Collections items = [%d] ***\n", prefixes_collections_cnt);
    for(uint8_t i = 0; i < prefixes_collections_cnt; i++){
        printf("[%d] = ", i); printf_prefix(&prefixes_collections[i]);
    }
    printf("*******************************\n\n");
}

/* *** */

/* API functions */

int8_t add_ipv4_prefix(prefix_t *ip_prefix){

    if(ip_prefix == NULL) return E_NULL_EXCEPTION;
    if(ip_prefix->mask > 32) return E_INVALID_MASK;

    int8_t errno_ret = E_NOT_EXIST;

    printf(">>> Add prefix: "); printf_prefix(ip_prefix);

    if(check_if_prefix_exists(ip_prefix, NULL) == true)
    {
        printf(">>> Prefix already exists\n");
        return E_ALREADY_ADDED;
    }
    else
    {
        errno_ret = write_new_prefix(ip_prefix);
    }

    if(errno_ret == E_OK) printf(">>> Prefix added\n");
    else printf("<<< Prefix not added\n");
    
    return errno_ret;
}

int8_t del_ipv4_prefix(prefix_t* ip_prefix){

    if(ip_prefix == NULL) return E_NULL_EXCEPTION;
    if(ip_prefix->mask > 32) return E_INVALID_MASK;

    int8_t errno_ret = E_NOT_EXIST;

    printf("<<< Remove prefix: "); printf_prefix(ip_prefix);

    uint8_t index = 0u;

    if(check_if_prefix_exists(ip_prefix,&index) == false)
    {
        printf("<<< Prefix NOT found\n");
        return E_NOT_EXIST;
    }
    else
    {
        errno_ret = remove_prefix(index);
    }

    if(errno_ret == E_OK) printf("<<< Prefix removed\n");
    else printf("<<< Prefix not removed\n");
    
    return errno_ret;
}

int8_t check_ipv4(uint32_t ip){

    prefix_t ip_prefix = {0u};
    ip_prefix.ip_address.ipv4_address_raw_data = ip;
 
    printf(">^< Check IP: "); printf_prefix(&ip_prefix);

    /* Iterate all mask from the biggest*/
    for(int8_t temp_mask = 32; temp_mask >= 0; temp_mask--)
    {
        /* prepare prefix variable with temporary mask*/

        uint32_t mask_bits = (-1) << (32 - temp_mask);
        ip_prefix.ip_address.ipv4_address_raw_data = ip & ~(mask_bits);
        ip_prefix.mask = (uint8_t)temp_mask;

        /* Check if calculated mask exists */
        if (check_if_prefix_exists(&ip_prefix,NULL) == true ) 
        {
            printf(">^< Checked prefix found: "); printf_prefix(&ip_prefix);
            return temp_mask;
            //return E_OK;
        }

      }
    printf(">^< Checked prefix NOT found\n");

    return E_NOT_FOUND;
}

/* *** */

