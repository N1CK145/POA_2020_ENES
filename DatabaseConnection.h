#ifndef DATABASECONNECTION_H_INCLUDED
#define DATABASECONNECTION_H_INCLUDED
#include <mysql/mysql.h>

void openDBConnection();
void closeDBConnection();
char* getMySQLClientInfo();
MYSQL_RES* getMySQLResult(char* querry);
void sendMySQLQuerry(char* querry);

#endif // DATABASECONNECTION_H_INCLUDED
