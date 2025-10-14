#ifndef IPV4_TYPES_H
#define IPV4_TYPES_H

#include <stdint.h>

typedef struct{
    uint8_t ipv4_1;
    uint8_t ipv4_2;
    uint8_t ipv4_3;
    uint8_t ipv4_4;
}ipv4_struct_t;

typedef union{
    ipv4_struct_t ipv4_address_struct_data;
    uint32_t ipv4_address_raw_data;
}ipv4_t;

typedef struct {
    ipv4_t ip_address;
    uint8_t mask;
}prefix_t;

#endif