#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#define ACCOUNT_FILE "accountInfo.txt"
#define PASSWORD_LENGTH 8

using namespace std;

enum class CharacterType
{
    upperCharacter = 0,
    lowerCharacter = 1,
    specialCharacter = 2
};

class Account
{
protected:
    string username;
    string password;
    bool isActive;

public:
    Account()
    {
        this->username = this->password = "";
        isActive = false;
    }
    ~Account()
    {
        this->username = this->password = "";
        this->isActive = false;
    }
    void setAccountInfo()
    {
        cout << "Enter username: " << endl;
        cin >> this->username;
        cout << "Enter password: " << endl;
        cin >> this->password;
        this->isActive = true;
    }
    void printAccountInfo()
    {
        cout << "Username: " << this->username << "\tPassword: " << this->password << "\t Is Active:" << this->isActive << endl;
    }
    pair<string, pair<string, bool>> getAccountInfo()
    {
        return make_pair(this->username, make_pair(this->password, this->isActive));
    }
    void login()
    {
        cout << "Login successful!" << endl;
    }
    void changePassword(string newPassword)
    {
        this->password = newPassword;
        cout << "Change password successful!" << endl;
    }
};

class User : public Account
{
public:
    User()
    {
        this->username = this->password = "";
        isActive = false;
    }
    User(string accountUsername, string accountPassword, bool activeStatus)
    {
        this->username = accountUsername;
        this->password = accountPassword;
        this->isActive = activeStatus;
    }
    ~User()
    {
        this->username = this->password = "";
        this->isActive = false;
    }
    void deleteAccount()
    {
        this->isActive = false;
    }
};

class Admin : public Account
{
private:
    int totalAccounts;
    vector<User> managedAccounts;

public:
    Admin()
    {
        this->username = this->password = "";
        isActive = false;
        this->totalAccounts = 0;
        this->managedAccounts = {};
    }
    ~Admin()
    {
        this->username = this->password = "";
        isActive = false;
        this->totalAccounts = 0;
        this->managedAccounts = {};
    }
    void setListOfAccounts(map<string, pair<string, bool>> listOfAccounts)
    {
        this->totalAccounts = listOfAccounts.size();
        map<string, pair<string, bool>>::iterator account;
        for (account = listOfAccounts.begin(); account != listOfAccounts.end(); ++account)
        {
            this->managedAccounts.push_back(User(account->first, account->second.first, account->second.second));
        }
    }
    map<string, pair<string, bool>> getListOfAccounts()
    {
        map<string, pair<string, bool>> listOfAccounts;
        for (size_t accountId = 0; accountId < this->totalAccounts; ++accountId)
        {
            listOfAccounts.insert(this->managedAccounts[accountId].getAccountInfo());
        }
        return listOfAccounts;
    }
    void printListOfAccounts()
    {
        cout << "------------------------------------------------------------" << endl
             << "List of Accounts:" << endl;
        for (size_t account = 0; account < this->totalAccounts; ++account)
        {
            this->managedAccounts[account].printAccountInfo();
        }
        cout << "------------------------------------------------------------" << endl;
    }
    void createNewAccount(User newAccount)
    {
        this->totalAccounts++;
        cout << "Username: " << newAccount.getAccountInfo().first << "\t"
             << "Password: " << newAccount.getAccountInfo().second.first << endl;
        this->managedAccounts.push_back(User(newAccount.getAccountInfo().first, newAccount.getAccountInfo().second.first, newAccount.getAccountInfo().second.second));
        cout << "Create new account successful!" << endl;
    }
    void deleteAnAccount(User deleteAccount)
    {
        this->totalAccounts--;
        for (auto accountInList = this->managedAccounts.begin(); accountInList != this->managedAccounts.end();)
        {
            if (accountInList->getAccountInfo() == deleteAccount.getAccountInfo())
            {
                accountInList = this->managedAccounts.erase(accountInList);
                break;
            }
        }
    }
    void deleteListOfAccounts(vector<User> listOfDeleteAccounts)
    {
        this->totalAccounts -= listOfDeleteAccounts.size();
        for (auto accountInTextFile = this->managedAccounts.begin(); accountInTextFile != this->managedAccounts.end();)
        {
            for (auto accountInDeleteList = listOfDeleteAccounts.begin(); accountInDeleteList != listOfDeleteAccounts.end();)
            {
                if (accountInTextFile == accountInDeleteList)
                {
                    accountInTextFile = this->managedAccounts.erase(accountInTextFile);
                }
            }
        }
    }
    vector<User> getListOfInactiveAccounts()
    {
        vector<User> listOfInactiveAccounts;
        vector<User>::iterator account;
        for (account = this->managedAccounts.begin(); account != this->managedAccounts.end(); ++account)
        {
            if (account->getAccountInfo().second.second)
            {
                listOfInactiveAccounts.push_back(User(account->getAccountInfo().first, account->getAccountInfo().second.first, account->getAccountInfo().second.second));
            }
        }
        return listOfInactiveAccounts;
    }
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

bool hasAccountExisted(string username, map<string, pair<string, bool>> listOfAccounts)
{
    bool hasExisted = false;
    auto account = listOfAccounts.find(username);
    if (account != listOfAccounts.end())
        hasExisted = true;
    return hasExisted;
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

bool isValidAccount(pair<string, pair<string, bool>> checkAccount, map<string, pair<string, bool>> listOfAccounts)
{
    bool isValid = false;
    map<string, pair<string, bool>>::iterator account;
    for (account = listOfAccounts.begin(); account != listOfAccounts.end(); ++account)
    {
        if (account->first == checkAccount.first && account->second.first == checkAccount.second.first)
        {
            isValid = true;
            break;
        }
    }
    return isValid;
}

char getSelectedMenu()
{
    char selectedMenu;
    cout << "Please enter according number listed below: " << endl
         << "Login - Enter 1" << endl
         << "Change password - Enter 2" << endl
         << "Create new account - Enter 3" << endl
         << "Delete an account using admin account - Enter 4" << endl
         << "Delete an account using user account - Enter 5" << endl
         << "-------------------------------------" << endl
         << "Press any key to exit" << endl
         << "Your selection is: " << endl;
    cin >> selectedMenu;
    return selectedMenu;
}

int main()
{
    Admin accountManager;
    User account;
    string newPassword;
    char selectedMenu = getSelectedMenu();
    account.setAccountInfo();
    pair<string, pair<string, bool>> accountInfo = account.getAccountInfo();
    map<string, pair<string, bool>> textFile = getListOfAccountsFromTextFile(ACCOUNT_FILE);
    accountManager.setListOfAccounts(textFile);
    cout << "List of accounts before changing..." << endl;
    accountManager.printListOfAccounts();
    switch (selectedMenu)
    {
    case '1':
        if (isValidAccount(account.getAccountInfo(), textFile))
        {
            account.login();
        }
        else
        {
            cout << "Login fail..." << endl;
        }
        break;
    case '2':
        cout << "Enter new password: " << endl;
        cin >> newPassword;
        if (isValidAccount(account.getAccountInfo(), textFile) && isPasswordInCorrectForm(newPassword))
        {
            account.changePassword(newPassword);
            accountManager.printListOfAccounts();
            updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
        }
        else
        {
            cout << "Please enter valid account or new password in correct format!" << endl;
        }
        break;
    case '3':
        if (!hasAccountExisted(accountInfo.first, accountManager.getListOfAccounts()) && isPasswordInCorrectForm(accountInfo.second.first))
        {
            accountManager.createNewAccount(account);
            updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
        }
        else
        {
            cout << "Please enter another username or password" << endl;
        }
        cout << "List of accounts after changing..." << endl;
        accountManager.printListOfAccounts();
        break;
    case '4':
        accountManager.deleteAnAccount(account);
        updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
        cout << "List of accounts after changing..." << endl;
        accountManager.printListOfAccounts();
        break;
    case '5':
        account.deleteAccount();
        bool isApprove;
        cout << "As an Admin," << endl
             << "Please enter 0 if approve the request." << endl
             << "Please press any key if disapprove the request." << endl;
        cin >> isApprove;
        if (!isApprove)
        {
            accountManager.deleteAnAccount(account);
        }
        updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
        cout << "List of accounts after changing..." << endl;
        accountManager.printListOfAccounts();
        break;
    }
}