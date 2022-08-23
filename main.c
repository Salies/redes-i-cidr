/*
    Redes de Computadores I
    Atividade 3 - Cálculo de endereço IPv4
    Aluno: Daniel Henrique Serezane Pereira
*/

#include <stdio.h>
#include <stdint.h>

// Protótipos
unsigned long long p(unsigned char n);

// ulonglong não seria necessário, mas sinceramente não quero fazer tratamento especial...
// Retorna 2 elevado a n
unsigned long long p(unsigned char n) {
    if(n == 0) return 1; // não deve acontecer, mas...
    unsigned long long out = 2;
    for(unsigned char i = 1; i < n; i++)
        out *= 2;
    return out;
}

int main(void) {
    // Pegando um endereço IP válido
    // números inadequados, mas não inválidos (por exemplo, maiores que 255) resultarão em overflow
    uint32_t ip = 0; // representando o IP em um número inteiro > 0 de 32 bits, para maior eficiência
    unsigned char* ip_oct = (unsigned char*) & ip; // separando os octetos
    printf("Insira um endereço: ");

    if (scanf("%hhu.%hhu.%hhu.%hhu", ip_oct + 3, ip_oct + 2, ip_oct + 1, ip_oct) != 4) {
        printf("Endereço inválido.\n");
        return 1;
    }
    
    // Pegando uma notação de máscara (número de 1-32) válida.
    // uchar é o menor número possível de alocar (1 byte) pela linguagem C
    unsigned char mask_p;
    printf("Escolha uma máscara (0-32): /");
    scanf("%hhu", &mask_p);

    if(mask_p < 0 || mask_p > 32) {
        printf("Máscara inválida.\n");
        return 1;
    }

    // A partir de um prefixo CIDR (mask_p, de 1-32), gera uma máscara (endereço) e seus respectivos octetos
    uint32_t mask = 0xFFFFFFFFUL << (32 - mask_p);
    unsigned char* mask_oct = (unsigned char*) & mask;

    // Endereço de rede: AND lógico entre ip e mask
    // lembrando que é necessário gerar esse uint32, pois os octetos são meramente ponteiros
    // o gasto de memória é um só (32 bits por valor)
    uint32_t net = (ip & mask);
    unsigned char* net_oct = (unsigned char*) & net;

    // Máscara wildcard (inversa da máscara)
    uint32_t wild = ~mask; 
    unsigned char* wild_oct = (unsigned char*) & wild;

    // Endereço de broadcast: OR lógico com a máscara inversa
    uint32_t broad = (ip | wild); 
    unsigned char* broad_oct = (unsigned char*) & broad;

    // Quantidade de hosts
    unsigned long long h = p(32 - mask_p);

    // Exibe o resultado
    printf("\nEndereço IP: %hhu.%hhu.%hhu.%hhu/%d", ip_oct[3], ip_oct[2], ip_oct[1], ip_oct[0], mask_p);
    printf("\nMáscara de subnet: %hhu.%hhu.%hhu.%hhu", mask_oct[3], mask_oct[2], mask_oct[1], mask_oct[0]);
    printf("\nMáscara wildcard: %hhu.%hhu.%hhu.%hhu", wild_oct[3], wild_oct[2], wild_oct[1], wild_oct[0]);
    printf("\nEndereço de rede: %hhu.%hhu.%hhu.%hhu", net_oct[3], net_oct[2], net_oct[1], net_oct[0]);
    printf("\nEndereço de broadcast: %hhu.%hhu.%hhu.%hhu", broad_oct[3], broad_oct[2], broad_oct[1], broad_oct[0]);
    printf("\nNúmero de endereços: %llu", h);
    if (h >= 2)
        printf("\nNuméro de endereços válidos: %llu", h - 2);
    if(h <= 2)
        printf("\nNão há range endereços usáveis.\n");
    else
        printf("\nRange usável de endereços: %hhu.%hhu.%hhu.%hhu - %hhu.%hhu.%hhu.%hhu\n", 
    net_oct[3], net_oct[2], net_oct[1], (net_oct[0] + 1), 
    broad_oct[3], broad_oct[2], broad_oct[1], (broad_oct[0] - 1));

    return 0;
}