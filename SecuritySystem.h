#ifndef SECURITYSYSTEM_H_INCLUDED
#define SECURITYSYSTEM_H_INCLUDED

void enableSecuritySystem();
void disableSecuritySystem();
int isSecurtySystemEnabled();

// MySQL
void goIn(int userID);
void goOut(int userID);

struct deviceInfo{
    int id;
    char* name;
};

#endif // SECURITYSYSTEM_H_INCLUDED
