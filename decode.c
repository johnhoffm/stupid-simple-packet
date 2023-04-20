#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define PKT_SIZE 128
#define HDR_SIZE 6
#define PAYLOAD_SIZE 122 // PKT_SIZE - HDR_SIZE

struct hoffcsp_pkt {
    uint32_t preamble;
    uint16_t length;
    char payload[PAYLOAD_SIZE];
};

// TODO