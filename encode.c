// Reads data from file and splits it into CSP pkts
// "hoffcsp" packet format

// TODO:
// - Makefile
// - add spec for hoffcsp_pkt

#include <stdint.h>
#include <string.h>
#include <stdio.h>

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

void prettyPrintBytes(struct hoffcsp_pkt* pktPtr){
    struct hoffcsp_pkt pkt = *pktPtr;
    // pretty print packet bytes
    printf("%zu bytes:\n", sizeof(pkt));
    for (int i = 0; i < sizeof(pkt); i++) {
        printf("%02x ", ((unsigned char *)&pkt)[i]);
    }
    printf("\n");
}

void printPkt(struct hoffcsp_pkt* pkt){
    fwrite (pkt, sizeof(struct hoffcsp_pkt), 1, stdout);
}

int main() {
    char buffer[PAYLOAD_SIZE] = {0};
    struct hoffcsp_pkt pkt = {0};

    size_t bytesRead;
    while ((bytesRead = fread(buffer, sizeof(char), PAYLOAD_SIZE, stdin)) > 0) {
        buildPkt(&pkt, bytesRead, buffer);
        // prettyPrintBytes(&pkt);
        printPkt(&pkt);
    }
    
    return 0;
}
