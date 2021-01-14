#ifndef ACCOUNT_CPP
#define ACCOUNT_CPP
#include "Account.h"
#include <iostream>

Account::Account()
{
    this->username = this->password = "";
    isActive = false;
}
Account::~Account()
{
    this->username = this->password = "";
    this->isActive = false;
}
void Account::setAccountInfo()
{
    cout << "Enter username: " << endl;
    cin >> this->username;
    cout << "Enter password: " << endl;
    cin >> this->password;
    this->isActive = true;
}
void Account::setAccountInfo(const Account &copyAccount)
{
    this->username = copyAccount.username;
    this->password = copyAccount.password;
    this->isActive = copyAccount.isActive;
}
void Account::printAccountInfo()
{
    cout << "Username: " << this->username << "\tPassword: " << this->password << "\t Is Active:" << this->isActive << endl;
}
pair<string, pair<string, bool>> Account::getAccountInfo()
{
    return make_pair(this->username, make_pair(this->password, this->isActive));
}
void Account::login()
{
    cout << "Login successful!" << endl;
}
void Account::changePassword(string newPassword)
{
    this->password = newPassword;
    cout << "Change password successful!" << endl;
}
#endif