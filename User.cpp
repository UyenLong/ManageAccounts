#ifndef USER_CPP
#define USER_CPP
#include "User.h"

User::User()
{
    this->username = this->password = "";
    isActive = false;
}
User::User(string accountUsername, string accountPassword, bool activeStatus)
{
    this->username = accountUsername;
    this->password = accountPassword;
    this->isActive = activeStatus;
}
User::User(const User &copyUser)
{
    this->username = copyUser.username;
    this->password = copyUser.password;
    this->isActive = copyUser.isActive;
}
User::User(pair<string, pair<string, bool>> userInfo)
{
    this->username = userInfo.first;
    this->password = userInfo.second.first;
    this->isActive = userInfo.second.second;
}
User::~User()
{
    this->username = this->password = "";
    this->isActive = false;
}
void User::deleteAccount()
{
    this->isActive = false;
}
#endif