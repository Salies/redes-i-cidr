#include <stdio.h>
#include <stdint.h>

int main () {

    const char* testLine = "555.168.112.54";

    char name[100];
    int speed;

    volatile uint32_t ipAddress=0;
    unsigned char* ipAddressBytes = (unsigned char*)&ipAddress;


    if (sscanf(testLine, "%hhu.%hhu.%hhu.%hhu", ipAddressBytes+3, ipAddressBytes+2,ipAddressBytes+1,ipAddressBytes+0) == 4) {
        printf("%08X\n", ipAddress);
    }

    return 0;   
}