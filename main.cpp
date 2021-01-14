#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include "Account.h"
#include "User.h"
#include "Admin.h"
#define ACCOUNT_FILE "accountInfo.txt"
#define PASSWORD_LENGTH 8
#define CHANGE_PASSWORD '1'
#define CREATE_ACCOUNT '2'
#define DELETE_ACCOUNT_BY_ADMIN '3'
#define DELETE_ACCOUNT_BY_USER '4'

using namespace std;

enum class CharacterType
{
    upperCharacter = 0,
    lowerCharacter = 1,
    specialCharacter = 2
};

bool convertStringToBool(string stringValue)
{
    bool returnValue = true;
    if (stringValue == "0")
    {
        returnValue = false;
    }
    return returnValue;
}

map<string, pair<string, bool>> getListOfAccountsFromTextFile(string fileName)
{
    map<string, pair<string, bool>> listOfAccounts;
    ifstream fileText;
    fileText.open(fileName);
    string accountInfo;
    while (getline(fileText, accountInfo))
    {
        size_t spaceCharacter = accountInfo.find(" ");
        string username = accountInfo.substr(0, spaceCharacter);
        accountInfo = accountInfo.substr(spaceCharacter + 1, accountInfo.size() - 1);
        spaceCharacter = accountInfo.find(" ");
        pair<string, bool> passwordAndStatus;
        passwordAndStatus.first = accountInfo.substr(0, spaceCharacter);
        passwordAndStatus.second = convertStringToBool(accountInfo.substr(spaceCharacter + 1));
        listOfAccounts[username] = passwordAndStatus;
    }
    fileText.close();
    return listOfAccounts;
}

void updateListOfAccountsToTextFile(string fileName, map<string, pair<string, bool>> newListOfAccounts)
{
    ofstream fileText;
    fileText.open(fileName);
    map<string, pair<string, bool>>::iterator account;
    for (account = newListOfAccounts.begin(); account != newListOfAccounts.end(); ++account)
    {
        fileText << account->first << " " << account->second.first << " " << account->second.second << endl;
    }
    fileText.close();
}

bool isStringHaveCharacterType(string stringName, CharacterType type)
{
    bool isContain = false;
    char firstCharacter, endCharacter;
    switch (type)
    {
    case CharacterType::upperCharacter:
        firstCharacter = 'A';
        endCharacter = 'Z';
        break;
    case CharacterType::lowerCharacter:
        firstCharacter = 'a';
        endCharacter = 'z';
        break;
    default:
        firstCharacter = ' ';
        endCharacter = '/';
        break;
    }
    for (size_t strIndex = 0; strIndex < stringName.length(); strIndex++)
    {
        if (stringName[strIndex] >= firstCharacter && stringName[strIndex] <= endCharacter)
        {
            isContain = true;
            break;
        }
    }
    return isContain;
}

bool isLengthOfStringGreaterThan(string stringName, int length)
{
    return stringName.length() >= length;
}

bool isPasswordInCorrectForm(string password)
{
    bool isCorrectForm = true;
    CharacterType typeUpper = CharacterType::upperCharacter;
    CharacterType typeLower = CharacterType::lowerCharacter;
    CharacterType typeSpecial = CharacterType::specialCharacter;
    return isStringHaveCharacterType(password, typeUpper) && isStringHaveCharacterType(password, typeLower) && isStringHaveCharacterType(password, typeSpecial) && isLengthOfStringGreaterThan(password, PASSWORD_LENGTH);
}

char getSelectedMenu()
{
    char selectedMenu;
    cout << "Please enter according number listed below: " << endl
         << "Change password - Enter 1" << endl
         << "Create new account - Enter 2" << endl
         << "Delete an account using admin account - Enter 3" << endl
         << "Delete an account using user account - Enter 4" << endl
         << "-------------------------------------" << endl
         << "Press any key to exit" << endl
         << "Your selection is: " << endl;
    cin >> selectedMenu;
    return selectedMenu;
}

void printSelection(char selectedMenu)
{
    switch (selectedMenu)
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

int main()
{
    map<string, pair<string, bool>> textFile = getListOfAccountsFromTextFile(ACCOUNT_FILE);
    Admin accountManager;
    accountManager.setListOfAccounts(textFile);
    cout << "List of accounts before changing..." << endl;
    accountManager.printListOfAccounts();
    char selectedMenu = getSelectedMenu();
    printSelection(selectedMenu);
    if (selectedMenu == CREATE_ACCOUNT)
    {
        User account;
        account.setAccountInfo();
        pair<string, pair<string, bool>> accountInfo = account.getAccountInfo();
        if (isPasswordInCorrectForm(accountInfo.second.first))
        {
            accountManager.createNewAccount(account);
            updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
            cout << "List of accounts after changing..." << endl;
            accountManager.printListOfAccounts();
        }
        else
            cout << "Please enter another username or password" << endl;
    }
    else
    {
        cout << "Please login before updating your account:" << endl;
        User account;
        account.setAccountInfo();
        if (accountManager.isValidAccount(account.getAccountInfo()))
        {
            account.login();
            pair<string, pair<string, bool>> accountInfo = account.getAccountInfo();
            string newPassword;
            switch (selectedMenu)
            {
            case CHANGE_PASSWORD:
                cout << "Enter new password: " << endl;
                cin >> newPassword;
                if (isPasswordInCorrectForm(newPassword))
                {
                    account.changePassword(newPassword);
                    accountManager.updateAccountInfo(account);
                    cout << "List of accounts after changing..." << endl;
                    accountManager.printListOfAccounts();
                    updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
                }
                else
                    cout << "Please enter new password in correct format!" << endl;
                break;
            case DELETE_ACCOUNT_BY_ADMIN:
                accountManager.deleteAnAccount(account);
                updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
                cout << "List of accounts after changing..." << endl;
                accountManager.printListOfAccounts();
                break;
            case DELETE_ACCOUNT_BY_USER:
                account.deleteAccount();
                accountManager.updateAccountInfo(account);
                accountManager.printListOfInactiveAccounts(accountManager.getListOfInactiveAccounts());
                bool isApprove;
                cout << "As an Admin," << endl
                     << "Please enter 0 if approve the request." << endl
                     << "Please press any key if disapprove the request." << endl;
                cin >> isApprove;
                if (!isApprove)
                {
                    accountManager.deleteAnAccount(account);
                    updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
                    cout << "List of accounts after changing..." << endl;
                    accountManager.printListOfAccounts();
                }
                break;
            }
        }
        else
            cout << "Login fail..." << endl;
    }
}