#ifndef USER_H
#define USER_H
#include "Account.h"

class User : public Account
{
public:
    User();
    User(string, string, bool);
    User(const User &);
    User(pair<string, pair<string, bool>>);
    ~User();
    void deleteAccount();
};
#endif