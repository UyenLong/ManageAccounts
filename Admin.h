#ifndef ADMIN_H
#define ADMIN_H
#include "Account.h"
#include "User.h"
#include <vector>

class Admin : public Account
{
private:
    int totalAccounts;
    vector<User> managedAccounts;

public:
    Admin();
    ~Admin();
    void updateAccountInfo(Account);
    void setListOfAccounts(map<string, pair<string, bool>>);
    map<string, pair<string, bool>> getListOfAccounts();
    void printListOfAccounts();
    void createNewAccount(User);
    void deleteAnAccount(User);
    void deleteAnAccount(vector<User>);
    vector<User> getListOfInactiveAccounts();
    void printListOfInactiveAccounts(vector<User>);
    bool isValidAccount(pair<string, pair<string, bool>>);
};
#endif