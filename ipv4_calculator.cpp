// Simple IPV4 calculator
// Author: Daniel Serezane
// Escrita como atividade para disciplina de Redes de Computadores I
// ministrada na FCT-UNESP em 2022.
// Comments are in Portuguese.

# include <iostream>
# include <regex>
# define ip_regexp "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.?\\b){4}$"

using namespace std;

// Verifica se (string ip) é um ip válido
bool is_valid_ipv4(string ip) {
    regex ip_regex(ip_regexp);
    if(regex_match(ip, ip_regex))
        return true;
    return false;
}

// Converte a notação CIDR (/0... /32) em um endereçamento (ex.: /22 em 255.255.252.0)
void set_mask(unsigned short n, unsigned short *out_mask) {
    // octeto: i / 8 | bit: 7 - i % 8 (subtrai de 7 porque começa do mais significativo)
    for(int i = 0; i < n; i++)
        out_mask[i / 8] = (out_mask[i / 8] | (1 << (7 - (i % 8))));
}

int main(void) {
    string ip_str;
    cout << "Insira um endereço: ";
    cin >> ip_str;

    if(!is_valid_ipv4(ip_str)) {
        cout << "Endereço inválido." << endl;
        return 1;
    }

    unsigned short mask;
    cout << "Escolha uma máscara (0-32): /";
    cin >> mask;

    if(mask < 0 || mask > 32) {
        cout << "Máscara inválida." << endl;
        return 1;
    }
    
    cout << "\nEndereço escolhido: " << ip_str << "/" << mask << endl;

    unsigned short real_mask[4] = {0, 0, 0, 0};
    set_mask(mask, real_mask);

    cout << real_mask[0] << "." << real_mask[1] << "." << real_mask[2] << "." << real_mask[3] << endl;

    

    return 0;
}