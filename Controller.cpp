#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP

#include <regex>
#include <string>
#include "Controller.h"
#include <iostream>

using namespace std;

Controller::Controller()
{
    this->admin = Admin();
    this->fileHandler = FileHandler();
    this->seletedMenu = ' ';
}
Controller::Controller(FileHandler fileText, Admin adminAccount)
{
    this->admin = Admin{adminAccount};
    this->fileHandler = FileHandler{fileText};
    this->seletedMenu = ' ';
}
Controller::~Controller()
{
    this->admin = Admin();
    this->fileHandler = FileHandler();
    this->seletedMenu = ' ';
}
bool Controller::isAccountInList(string username, vector<User> listToCheck)
{
    bool isContain = false;
    for (auto account = listToCheck.begin(); account != listToCheck.end(); account++)
    {
        if (account->getAccountInfo().first == username)
        {
            isContain = true;
            break;
        }
    }
    return isContain;
}
void Controller::printListOfAccounts()
{
    this->admin.printListOfAccounts();
}

bool Controller::isPasswordInCorrectForm(string password)
{
    return regex_match(password, regex(PASSWORD_RULES));
}
void Controller::setSelectedMenu()
{
    cout << "Please enter according number listed below: " << endl
         << "Change password - Enter 1" << endl
         << "Create new account - Enter 2" << endl
         << "Delete an account using admin account - Enter 3" << endl
         << "Delete an account using user account - Enter 4" << endl
         << "-------------------------------------" << endl
         << "Press any key to exit" << endl;
    cin >> this->seletedMenu;
}
void Controller::printSelection()
{
    switch (this->seletedMenu)
    {
    case CHANGE_PASSWORD:
        cout << "Your Selection is Change Password" << endl;
        cout << "----------CHANGE PASSWORD SECTION----------" << endl;
        break;
    case CREATE_ACCOUNT:
        cout << "Your Selection is Create Account" << endl;
        cout << "----------CREATE ACCOUNT SECTION----------" << endl;
        break;
    case DELETE_ACCOUNT_BY_ADMIN:
        cout << "Your Selection is Delete Account as an admin" << endl;
        cout << "----------DELETE ACCOUNT SECTION----------" << endl;
        break;
    case DELETE_ACCOUNT_BY_USER:
        cout << "Your Selection is Delete Account as a user " << endl;
        cout << "----------DELETE ACCOUNT SECTION----------" << endl;
        break;
    }
}
char Controller::getSelectedMenu()
{
    return this->seletedMenu;
}
void Controller::createNewAccount()
{
    User account;
    account.setAccountInfo();
    pair<string, pair<string, bool>> accountInfo = account.getAccountInfo();
    if (this->isPasswordInCorrectForm(accountInfo.second.first))
    {
        this->admin.createNewAccount(account);
        this->fileHandler.updateListOfAccountsToTextFile(this->admin.getListOfAccounts());
        cout << "Create new account successful..." << endl;
    }
    else
        cout << "Please enter another username or password" << endl;
}
void Controller::login()
{
    this->user.setAccountInfo();
}
bool Controller::isLoginSuccessful()
{
    bool isSuccessful = false;
    if (this->admin.isValidAccount(this->user.getAccountInfo()))
    {
        isSuccessful = true;
    }
    else
    {
        cout << "Login fail! Please try again..." << endl;
    }
    return isSuccessful;
}
void Controller::changePassword()
{
    string newPassword;
    cout << "Enter new password: " << endl;
    cin >> newPassword;
    if (this->isPasswordInCorrectForm(newPassword))
    {
        this->user.changePassword(newPassword);
        this->admin.updateAccountInfo(this->user);
        this->fileHandler.updateListOfAccountsToTextFile(this->admin.getListOfAccounts());
    }
    else
        cout << "Please enter new password in correct format!" << endl;
}
void Controller::deleteAccountByAdmin()
{
    this->admin.deleteAnAccount(this->user.getAccountInfo().first);
    this->fileHandler.updateListOfAccountsToTextFile(this->admin.getListOfAccounts());
    cout << "Delete account successful!" << endl;
}
void Controller::deleteAccountByUser()
{
    this->user.deleteAccount();
    this->admin.updateAccountInfo(this->user);
    this->admin.syncListOfInactiveAccounts();
}
void Controller::printInActiveAccounts()
{
    this->admin.printListOfInactiveAccounts();
}
void Controller::reviewInActiveAccounts()
{
    char isStop = false;
    string username;
    do
    {
        cout << "Please enter username of a account that you appove to delete it: " << endl;
        cin >> username;
        if (this->isAccountInList(username, this->admin.getListOfInactiveAccounts()))
        {
            this->admin.deleteAnAccountInInactiveList(username);
        }
        cout << "Press 0 to continue delete account..." << endl;
        cout << "Press any key to exit!" << endl;
        cin >> isStop;
        if (this->admin.getListOfInactiveAccounts().empty())
        {
            cout << "You have nothing to delete..." << endl;
            cout << "Exit....." << endl;
        }

    } while (isStop == '0' && !this->admin.getListOfInactiveAccounts().empty());
}
bool Controller::convertStringToBool(string stringValue)
{
    bool returnValue = true;
    if (stringValue == "0")
    {
        returnValue = false;
    }
    return returnValue;
}

#endif