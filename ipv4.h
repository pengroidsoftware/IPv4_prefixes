#ifndef IPV4_H
#define IPV4_H

#include <stdint.h>
#include "ipv4_types.h"

/* API functions */
int add_ipv4_prefix(prefix_t ip_prefix);
int del_ipv4_prefix(prefix_t ip_prefix);
char check_ipv4(prefix_t ip);

/* Debug function */
void printf_prefix(prefix_t prefix_input);
void printf_collection();

#endif