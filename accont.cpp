#include <iostream>
#include "accont.hpp"

accont::accont(std::string user, std::string password) //construtor
    : user(user), password(password)
{
    std::string id = user + password;
    this->id = id;
}

void accont::connection() // Estabelece a conexão com o banco de dados
{
    MYSQL_ROW row;
    const char *host = "127.0.0.1";
    const char *user = "root";
    const char *passwd = "Vini0603@";
    const char *db = "cadlog";
    unsigned int port = 3306;
    const char *unix_socket = NULL;
    unsigned long clientflag = 0;

    conn = mysql_init(NULL);

    if (!conn) {
        std::cerr << "Erro ao inicializar a conexão: " << mysql_error(conn) << std::endl;
        exit(1);
    }

    if (!mysql_real_connect(conn, host, user, passwd, db, port, unix_socket, clientflag)) {
        std::cerr << "Erro ao conectar ao banco de dados: " << mysql_error(conn) << std::endl;
        exit(1);
    }

    std::cout << "Conexão bem-sucedida!" << std::endl;

}

void accont::login() // função para logar
{
    connection(); 

    // Construa a consulta SQL para buscar o usuário e senha correspondentes
    std::string query = "SELECT * FROM client WHERE user='" + user + "' AND password='" + password + "'";
    
    // Execute a consulta
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao executar consulta: " << mysql_error(conn) << std::endl;
        return;
    }

    // Obtenha o resultado da consulta
    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Erro ao obter resultado da consulta: " << mysql_error(conn) << std::endl;
        return;
    }

    // Verifique se há alguma linha retornada pela consulta
    if (MYSQL_ROW row = mysql_fetch_row(result)) {
        // Usuário e senha correspondem
        std::cout << "Login bem-sucedido!" << std::endl;
    } else {
        // Usuário ou senha inválidos
        std::cout << "Usuário ou senha inválidos!" << std::endl;
    }

    // Libere o resultado da consulta
    mysql_free_result(result);

    // Feche a conexão com o banco de dados
    mysql_close(conn);
}

void accont::cadastro() // função para cadastrar
{
    connection();

    std::string query = "INSERT INTO client (id, user, password) VALUES ('" + id + "', '" + user + "', '" + password + "')";
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao cadastrar cliente: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Cliente cadastrado com sucesso!" << std::endl;
    }
    mysql_close(conn); // Fecha a conexão com o banco de dados

}