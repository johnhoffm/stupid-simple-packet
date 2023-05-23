#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

// packet size in bytes
#define PKT_SIZE 128
#define HDR_SIZE 6
#define PAYLOAD_SIZE 122 // PKT_SIZE - HDR_SIZE

const char* OUT_DIR = "packets/";

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

void savePktToFile(struct hoffcsp_pkt* pkt, FILE* fp){
    fwrite (pkt, sizeof(struct hoffcsp_pkt), 1, fp);
}

void printPkt(struct hoffcsp_pkt* pkt){
    savePktToFile(pkt, stdout);
}

int main() {
    char buffer[PAYLOAD_SIZE] = {0};
    struct hoffcsp_pkt pkt = {0};

    FILE *fp;
    char fileName[100]; // can overflow if very many packets
    int pktNum = 0;
    size_t bytesRead;

    if (mkdir(OUT_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 && errno != EEXIST){
        perror("Cannot create directory for packets.");
        return 1;
    }

    while ((bytesRead = fread(buffer, sizeof(char), PAYLOAD_SIZE, stdin)) > 0) {
        buildPkt(&pkt, bytesRead, buffer);
        sprintf(&fileName, "%s%d.hoff", OUT_DIR, pktNum);

        fp = fopen(fileName, "wb+");
        savePktToFile(&pkt, fp);
        fclose(fp);

        // prettyPrintBytes(&pkt);

        pktNum = pktNum + 1;
    }
    
    return 0;
}
