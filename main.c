#include <stdio.h>
#include <stdint.h>

int main(void) {
    // Pegando um endereço IP válido
    // números inadequados, mas não inválidos (por exemplo, maiores que 255) resultarão em overflow
    uint32_t ip = 0; // representando o IP em um número de 32, para maior eficiência
    unsigned char* ip_oct = (unsigned char*) & ip; // separando os octetos
    printf("Insira um endereço: ");

    if (scanf("%hhu.%hhu.%hhu.%hhu", ip_oct + 3, ip_oct + 2, ip_oct + 1, ip_oct) != 4) {
        printf("Endereço inválido.\n");
        return 1;
    }

    // Pegando uma notação de máscara (número de 0-32) válida.
    // uchar é o menor número possível de alocar (1 byte) pela linguagem C
    unsigned char mask_p;
    printf("Escolha uma máscara (0-32): /");
    scanf("%hhu", &mask_p);

    if(mask_p < 0 || mask_p > 32) {
        printf("Máscara inválida.\n");
        return 1;
    }

    // A partir de um prefixo CIDR (mask_p, de 0-32), gera uma máscara (endereço) e seus respectivos octetos
    uint32_t mask = 0xFFFFFFFFUL << (32 - mask_p);
    unsigned char* mask_oct = (unsigned char*) & mask;

    printf("%hhu.%hhu.%hhu.%hhu", mask_oct[3], mask_oct[2], mask_oct[1], mask_oct[0]);

    return 0;
}