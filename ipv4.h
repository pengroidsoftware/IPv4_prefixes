#ifndef IPV4_H
#define IPV4_H

#include <stdint.h>
#include "ipv4_types.h"

/* API functions */
int8_t add_ipv4_prefix(prefix_t ip_prefix);
int8_t del_ipv4_prefix(prefix_t ip_prefix);
int8_t check_ipv4(uint32_t ip);

/* Debug function */
void printf_prefix(prefix_t prefix_input);
void printf_collection();

#endif