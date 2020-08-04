#ifndef DATABASECONNECTION_H_INCLUDED
#define DATABASECONNECTION_H_INCLUDED

void openDBConnection();
void closeDBConnection();
char* getMySQLClientInfo();
MYSQL_RES* getMySQLResult(char* querry);

#endif // DATABASECONNECTION_H_INCLUDED
