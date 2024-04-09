#include <iostream>
#include <windows.h>
#include "accont.hpp"


int main() {

    SetConsoleOutputCP(CP_UTF8);
    int op;
    std::string user, password;

    std::cout << "USUARIO: ";
    std::cin >> user;

    std::cout << "SENHA: ";
    std::cin >> password;

    accont client(user,password);

    std::cout << "\n1 - LOGAR\n2 - CADASTRAR: " << std::endl;
    std::cin >> op;

    switch (op) {
        case 1:
            client.login();
            break;
        case 2:
            client.cadastro();
            break;
        default:
            break;
            }
    return 0;
}