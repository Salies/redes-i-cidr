#include <stdio.h>
#include <stdint.h>

int main (void) {

    const char* testLine = "192.168.112.54";

    uint32_t ipAddress=0;
    unsigned char* ipAddressBytes = (unsigned char*)&ipAddress;


    if (scanf("%hhu.%hhu.%hhu.%hhu", ipAddressBytes+3, ipAddressBytes+2,ipAddressBytes+1,ipAddressBytes+0) == 4) {
        printf("%08X\n", ipAddress);
    }

    return 0;   
}