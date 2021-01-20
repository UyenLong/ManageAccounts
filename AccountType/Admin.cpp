#ifndef ADMIN_CPP
#define ADMIN_CPP
#include "Admin.h"
#include <iostream>
#include "User.h"

Admin::Admin()
{
    this->username = this->password = "";
    isActive = false;
    this->totalAccounts = 0;
    this->managedAccounts = {};
}
Admin::Admin(const Admin &account)
{
    this->managedAccounts = account.managedAccounts;
    this->totalAccounts = account.managedAccounts.size();
}
Admin::~Admin()
{
    this->username = this->password = "";
    isActive = false;
    this->totalAccounts = 0;
    this->managedAccounts = {};
}
User Admin::getAccountInfoByUsername(string username)
{
    User accountInfo;
    for (auto account = this->managedAccounts.begin(); account != this->managedAccounts.end(); ++account)
    {
        if (account->getAccountInfo().first == username)
        {
            accountInfo = User{username, account->getAccountInfo().second.first, account->getAccountInfo().second.second};
            break;
        }
    }
    return accountInfo;
}
void Admin::updateAccountInfo(User updateAccount)
{
    vector<User>::iterator account;
    for (account = this->managedAccounts.begin(); account < this->managedAccounts.end(); ++account)
    {
        if (account->getAccountInfo().first == updateAccount.getAccountInfo().first)
        {
            account->setAccountInfo(updateAccount);
            break;
        }
    }
}
void Admin::setListOfAccounts(map<string, pair<string, bool>> listOfAccounts)
{
    this->totalAccounts = listOfAccounts.size();
    this->managedAccounts = {};
    map<string, pair<string, bool>>::iterator account;
    for (account = listOfAccounts.begin(); account != listOfAccounts.end(); ++account)
    {
        this->managedAccounts.push_back(User(account->first, account->second.first, account->second.second));
    }
}
map<string, pair<string, bool>> Admin::getListOfAccounts()
{
    map<string, pair<string, bool>> listOfAccounts;
    for (size_t accountId = 0; accountId < this->totalAccounts; ++accountId)
    {
        listOfAccounts.insert(this->managedAccounts[accountId].getAccountInfo());
    }
    return listOfAccounts;
}
void Admin::printListOfAccounts()
{
    cout << "------------------------------------------------------------" << endl
         << "List of Accounts:" << endl;
    for (size_t account = 0; account < this->totalAccounts; ++account)
    {
        this->managedAccounts[account].printAccountInfo();
    }
    cout << "------------------------------------------------------------" << endl;
}
void Admin::createNewAccount(User newAccount)
{
    this->totalAccounts++;
    cout << "Username: " << newAccount.getAccountInfo().first << "\t"
         << "Password: " << newAccount.getAccountInfo().second.first << endl;
    this->managedAccounts.push_back(User(newAccount));
}
void Admin::deleteAnAccount(string usernameOfAccount)
{
    this->totalAccounts--;
    int indexOfAccount = 0;
    for (auto accountInList = this->managedAccounts.begin(); accountInList != this->managedAccounts.end(); ++accountInList)
    {
        if (accountInList->getAccountInfo().first == usernameOfAccount)
        {
            this->managedAccounts.erase(this->managedAccounts.begin() + indexOfAccount);
            break;
        }
        indexOfAccount++;
    }
}
void Admin::deleteAnAccountInInactiveList(string usernameOfAccount)
{
    int indexOfAccount = 0;
    for (auto accountInList = this->inactiveAccounts.begin(); accountInList != this->inactiveAccounts.end(); ++accountInList)
    {
        if (accountInList->getAccountInfo().first == usernameOfAccount)
        {
            this->inactiveAccounts.erase(this->managedAccounts.begin() + indexOfAccount);
            break;
        }
        indexOfAccount++;
    }
}
void Admin::deleteListOfAccounts(vector<User> listOfAccounts)
{
    this->totalAccounts -= listOfAccounts.size();
    int indexOfAccount = 0;
    for (auto accountInList = listOfAccounts.begin(); accountInList != listOfAccounts.end(); ++accountInList)
    {
        this->managedAccounts.erase(this->managedAccounts.begin() + indexOfAccount);
        indexOfAccount++;
    }
}
void Admin::syncListOfInactiveAccounts()
{
    vector<User>::iterator account;
    this->inactiveAccounts.clear();
    for (account = this->managedAccounts.begin(); account != this->managedAccounts.end(); ++account)
    {
        if (!account->getAccountInfo().second.second)
        {
            this->inactiveAccounts.push_back(User(account->getAccountInfo().first, account->getAccountInfo().second.first, account->getAccountInfo().second.second));
        }
    }
}
vector<User> Admin::getListOfInactiveAccounts()
{
    vector<User> returnedList;
    for (auto account = this->inactiveAccounts.begin(); account != this->inactiveAccounts.end(); ++account)
    {
        returnedList.push_back(User{account->getAccountInfo()});
    }
    return returnedList;
}
void Admin::printListOfInactiveAccounts()
{
    vector<User>::iterator account;
    cout << "Inactive accounts: " << endl;
    for (account = this->inactiveAccounts.begin(); account < this->inactiveAccounts.end(); ++account)
    {
        account->printAccountInfo();
    }
}
bool Admin::isValidAccount(pair<string, pair<string, bool>> checkAccount)
{
    bool isValid = false;
    vector<User>::iterator account;
    for (account = this->managedAccounts.begin(); account != managedAccounts.end(); ++account)
    {
        if (account->getAccountInfo().first == checkAccount.first && account->getAccountInfo().second.first == checkAccount.second.first)
        {
            isValid = true;
            break;
        }
    }
    return isValid;
}

#endif