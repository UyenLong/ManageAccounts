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
private:
    string username;
    string password;

public:
    Account()
    {
        this->username = this->password = "";
    }
    Account(string accountUsername, string accountPassword)
    {
        this->username = accountUsername;
        this->password = accountPassword;
    }
    ~Account()
    {
        this->username = this->password = "";
    }
    void setAccountInfo()
    {
        cout << "Enter username: " << endl;
        cin >> this->username;
        cout << "Enter password: " << endl;
        cin >> this->password;
    }
    void printAccountInfo()
    {
        cout << "Username: " << this->username << "\tPassword: " << this->password << endl;
    }
    pair<string, string> getAccountInfo()
    {
        return make_pair(this->username, this->password);
    }
    void login()
    {
        cout<<"Login successful!"<<endl;
    }
    void changePassword(string newPassword)
    {
        this->password = newPassword;
        cout<<"Change password successful!"<<endl;
    }
};

class AccountManager
{
private:
    int totalAccount;
    vector<Account> account;

public:
    AccountManager()
    {
        this->totalAccount = 0;
        this->account = {};
    }
    ~AccountManager()
    {
        this->totalAccount = 0;
        this->account = {};
    }
    void setListOfAccounts(map<string, string> listOfAccounts)
    {
        this->totalAccount = listOfAccounts.size();
        map<string, string>::iterator inputListAccount;
        for (inputListAccount = listOfAccounts.begin(); inputListAccount != listOfAccounts.end(); ++inputListAccount)
        {
            this->account.push_back(Account(inputListAccount->first, inputListAccount->second));
        }
    }
    map<string, string> getListOfAccounts()
    {
        map<string, string> listOfAccounts;
        for (size_t accountId = 0; accountId < this->totalAccount; ++accountId)
        {
            listOfAccounts.insert(this->account[accountId].getAccountInfo());
        }
        return listOfAccounts;
    }
    void printListOfAccounts()
    {
        cout<<"------------------------------------------------------------"<<endl
        <<"List of Accounts:"<<endl;
        for (size_t accountId = 0; accountId < this->totalAccount; ++accountId)
        {
            this->account[accountId].printAccountInfo();
        }
        cout<<"------------------------------------------------------------"<<endl;
    }
    void createNewAccount(Account newAccount)
    {
        this->totalAccount++;
        cout<<"Username: "<<newAccount.getAccountInfo().first<<"\t"<<"Password: "<<newAccount.getAccountInfo().second<<endl;
        this->account.push_back(Account(newAccount.getAccountInfo().first, newAccount.getAccountInfo().second));      
        cout<<"Create new account successful!"<<endl;
    }
    void deleteAnAccount(Account deleteAccount)
    {    
        this->totalAccount--;
        for (auto accountInList = this->account.begin(); accountInList != this->account.end(); ) {
            if (accountInList->getAccountInfo() == deleteAccount.getAccountInfo()) {
                accountInList = this->account.erase(accountInList);
                break;
            }
        }
    }
}; 

map<string, string> getListOfAccountsFromTextFile(string fileName)
{
    map<string, string> listOfAccounts;
    ifstream fileText;
    fileText.open(fileName);
    string accountInfo;
    while (getline(fileText, accountInfo))
    {
        size_t spaceCharacter = accountInfo.find(" ");
        listOfAccounts[accountInfo.substr(0, spaceCharacter)] = accountInfo.substr(spaceCharacter + 1);
    }
    fileText.close();
    return listOfAccounts;
}

void updateListOfAccountsToTextFile(string fileName, map<string, string> newListOfAccounts)
{
    ofstream fileText;
    fileText.open(fileName);
    map<string, string>::iterator account;
    for (account = newListOfAccounts.begin(); account != newListOfAccounts.end(); ++account)
    {
        fileText << account->first << " " << account->second << endl;
    }
    fileText.close();
}

bool hasAccountExisted(string username, map<string, string> listOfAccounts)
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

char getSelectedMenu()
{
    char selectedMenu;
    cout << "Please enter according number listed below: " << endl
         << "Login - Enter 1" << endl
         << "Change password - Enter 2" << endl
         << "Create new account - Enter 3" << endl
         << "Delete an account - Enter 4" << endl
         << "-------------------------------------" << endl
         << "Press any key to exit" << endl
         << "Your selection is: "<<endl;
    cin >> selectedMenu;
    return selectedMenu;
}

bool isValidAccount(pair<string, string> checkAccount, map<string, string> listOfAccounts)
{
    bool isValid = false;
    map<string, string>::iterator account;
    for (account = listOfAccounts.begin(); account != listOfAccounts.end(); ++account)
    {
        if (account->first == checkAccount.first && account->second == checkAccount.second)
        {
            isValid = true;
            break;
        }
    }
    return isValid;
}

int main()
{
    AccountManager accountManager;
    Account account;
    string newPassword;
    char selectedMenu = getSelectedMenu();
    account.setAccountInfo();
    pair<string, string> accountInfo = account.getAccountInfo();
    map<string, string> textFile = getListOfAccountsFromTextFile(ACCOUNT_FILE);
    accountManager.setListOfAccounts(textFile);
    cout<<"List of accounts before changing..."<<endl;
    accountManager.printListOfAccounts();
    switch(selectedMenu)
    {
        case '1':
            if(isValidAccount(account.getAccountInfo(), textFile))
            {
                account.login();
            } else cout << "Login fail..."<<endl;
            break;
        case '2':
            cout<<"Enter new password: "<<endl;
            cin>> newPassword;
            if(isValidAccount(account.getAccountInfo(), textFile) && isPasswordInCorrectForm(newPassword))
            {
                account.changePassword(newPassword);
            } else cout<<"Please enter valid account or new password in correct format!"<<endl;
            break;
        case '3':
            if(!hasAccountExisted(accountInfo.first, accountManager.getListOfAccounts()) && isPasswordInCorrectForm(accountInfo.second)) 
            {
                accountManager.createNewAccount(account);
                updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
            } else cout << "Please enter another username or password"<<endl;
            cout<<"List of accounts after changing..."<<endl;
            accountManager.printListOfAccounts();
            break;
        case '4':
            accountManager.deleteAnAccount(account);
            updateListOfAccountsToTextFile(ACCOUNT_FILE, accountManager.getListOfAccounts());
            cout<<"List of accounts after changing..."<<endl;
            accountManager.printListOfAccounts();
            break;
    }
}