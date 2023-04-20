// Reads data from file and splits it into CSP pkts
// "hoffcsp" packet format

// TODO:
// - Makefile
// - add spec for hoffcsp_pkt

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

void buildPkt(struct hoffcsp_pkt* pkt, uint16_t length, const char* payload){
    pkt->preamble = 0xFFFFFFFF;
    pkt->length = length;
    memcpy(pkt->payload, payload, length);
}

void prettyPrintBytes(struct hoffcsp_pkt* pkt_ptr){
    struct hoffcsp_pkt pkt = *pkt_ptr;
    // pretty print packet bytes
    printf("%zu bytes:\n", sizeof(pkt));
    for (int i = 0; i < sizeof(pkt); i++) {
        printf("%02x ", ((unsigned char *)&pkt)[i]);
    }
    printf("\n");
}

int main() {
    struct hoffcsp_pkt pkt = {0};
    char buf[] = "hello world";
    int length = sizeof(buf);
    buildPkt(&pkt, length, buf);
    
    prettyPrintBytes(&pkt);
    
    return 0;
}
