#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Macros and methods from encode.c
// packet size in bytes
#define PKT_SIZE 128
#define HDR_SIZE 6
#define PAYLOAD_SIZE 122 // PKT_SIZE - HDR_SIZE

struct hoffcsp_pkt {
    uint32_t preamble; 
    uint16_t length;
    uint8_t payload[PAYLOAD_SIZE];
};

void buildPkt(struct hoffcsp_pkt* pkt, uint16_t length, const char* payload){
    pkt->preamble = (uint32_t) 0xFFFFFFFF ;
    pkt->length = length;
    memcpy(pkt->payload, payload, length);
}

void decodeRaw(struct hoffcsp_pkt* pkt, uint8_t* raw){
    // raw must be an array of size PKT_SIZE
    // wacky cast fixes endianness I think
    pkt->preamble = *(uint32_t*) raw;
    raw += sizeof(uint32_t);

    pkt->length = *(uint16_t*) raw;
    raw += sizeof(uint16_t);

    memcpy(pkt->payload, raw, pkt->length);
}

void printPayload(struct hoffcsp_pkt* pkt){
    fwrite(pkt->payload, pkt->length, 1, stdout);
}

void prettyPrintPkt(struct hoffcsp_pkt* pkt){
    printf("preamble: 0x%08x\n", pkt->preamble);
    printf("length: %d\n", pkt->length);
    printPayload(pkt);
    printf("\n");
}

int main() {
    uint8_t buffer[PKT_SIZE] = {0};
    struct hoffcsp_pkt pkt = {0};

    size_t bytesRead;
    while ((bytesRead = fread(buffer, sizeof(char), PKT_SIZE, stdin)) > 0) {
        decodeRaw(&pkt, buffer);
        printPayload(&pkt);
    }
    
    return 0;
}