#ifndef ADMIN_CPP
#define ADMIN_CPP
#include "Admin.h"
#include <iostream>

Admin::Admin()
{
    this->username = this->password = "";
    isActive = false;
    this->totalAccounts = 0;
    this->managedAccounts = {};
}
Admin::~Admin()
{
    this->username = this->password = "";
    isActive = false;
    this->totalAccounts = 0;
    this->managedAccounts = {};
}
void Admin::updateAccountInfo(Account updateAccount)
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
    cout << "Create new account successful!" << endl;
}
void Admin::deleteAnAccount(User deleteAccount)
{
    this->totalAccounts--;
    int indexOfAccount = 0;
    for (auto accountInList = this->managedAccounts.begin(); accountInList != this->managedAccounts.end(); ++accountInList)
    {
        if (accountInList->getAccountInfo().first == deleteAccount.getAccountInfo().first)
        {
            this->managedAccounts.erase(this->managedAccounts.begin() + indexOfAccount);
            break;
        }
        indexOfAccount++;
    }
}
void Admin::deleteAnAccount(vector<User> listOfAccounts)
{
    this->totalAccounts -= listOfAccounts.size();
    int indexOfAccount = 0;
    for (auto accountInList = listOfAccounts.begin(); accountInList != listOfAccounts.end(); ++accountInList)
    {
        this->managedAccounts.erase(this->managedAccounts.begin() + indexOfAccount);
        indexOfAccount++;
    }
}
vector<User> Admin::getListOfInactiveAccounts()
{
    vector<User> listOfInactiveAccounts;
    vector<User>::iterator account;
    for (account = this->managedAccounts.begin(); account != this->managedAccounts.end(); ++account)
    {
        if (!account->getAccountInfo().second.second)
        {
            listOfInactiveAccounts.push_back(User(account->getAccountInfo().first, account->getAccountInfo().second.first, account->getAccountInfo().second.second));
        }
    }
    return listOfInactiveAccounts;
}
void Admin::printListOfInactiveAccounts(vector<User> listOfInactiveAccounts)
{
    vector<User>::iterator account;
    cout << "Inactive accounts: " << endl;
    for (account = listOfInactiveAccounts.begin(); account < listOfInactiveAccounts.end(); ++account)
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