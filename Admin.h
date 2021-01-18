#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
#include <vector>

class Admin : public Account
{
private:
    int totalAccounts;
    vector<User> managedAccounts;
    vector<User> inactiveAccounts;

public:
    Admin();
    Admin(const Admin &);
    ~Admin();
    User getAccountInfoByUsername(string);
    void updateAccountInfo(User);
    void setListOfAccounts(map<string, pair<string, bool>>);
    map<string, pair<string, bool>> getListOfAccounts();
    void printListOfAccounts();
    void createNewAccount(User);
    void deleteAnAccount(string);
    void deleteAnAccountInInactiveList(string);
    void deleteListOfAccounts(vector<User>);
    void syncListOfInactiveAccounts();
    vector<User> getListOfInactiveAccounts();
    void printListOfInactiveAccounts();
    bool isValidAccount(pair<string, pair<string, bool>>);
};
#endif