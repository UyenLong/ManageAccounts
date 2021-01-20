#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <map>
#include <utility>

using namespace std;
class Account
{
protected:
    string username;
    string password;
    bool isActive;

public:
    Account();
    ~Account();
    void setAccountInfo();
    void setAccountInfo(const Account &);
    void printAccountInfo();
    pair<string, pair<string, bool>> getAccountInfo();
    void login();
    void changePassword(string);
};
#endif