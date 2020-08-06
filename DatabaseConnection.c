#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "DatabaseConnection.h"

MYSQL* mysqlConnection;

void finish_with_error()
{
  fprintf(stderr, "%s\n", mysql_error(mysqlConnection));
  mysql_close(mysqlConnection);
  exit(1);
}

void openDBConnection(){
    char* host = "lia-gaming.de";
    char* user = "schule";
    char* passwd = "123";
    char* db = "POA_2020";

    mysqlConnection = mysql_init(NULL);
    if(mysqlConnection == NULL){
        printf("Fehler beim Initialisieren von MySQL.");
        return;
    }

    if(mysql_real_connect (mysqlConnection, host, user, passwd, db, 0, NULL, 0) == NULL){
        unsigned int error = mysql_errno(mysqlConnection);
        printf("MySQL Error: %u (%s)\n", error, mysql_error(mysqlConnection));
    }else
        printf("MySQL Verbindung hergestellt!\nVerbunden zu '%s' als '%s'\n", host, user);
}

void closeDBConnection(){
    mysql_close(mysqlConnection);
}

char* getMySQLClientInfo(){
    return mysql_get_client_info();
}

MYSQL_RES* getMySQLResult(char* querry){
    if (mysql_query(mysqlConnection, querry))
        finish_with_error();

    return mysql_store_result(mysqlConnection);
}

void sendMySQLQuerry(char* querry){
    mysql_query(mysqlConnection, querry);

}
