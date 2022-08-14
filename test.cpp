#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main(void){
    std::string str_ip = "Please enter a correct IP address : ";
    cout << str_ip; cin >> str_ip;

    std::stringstream ss(str_ip);
    int v = 0, n = 3; uint32_t real_ip;
    while(true)
    {
        if(ss >> v && n >= 0)
        {
            char c;
            ((uint8_t*)&real_ip)[n] = v;
            ss >> c;
        } else break;
        n--;
    }

    cout << "The IP address entered : " << real_ip << endl;

    return 0;
}