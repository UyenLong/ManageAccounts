#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "FileHandler.h"
#include "Admin.h"
#include <string>
#define ACCOUNT_FILE "accountInfo.txt"
#define PASSWORD_RULES "(?=.*[a-z])(?=.*[A-Z])(?=.*[@$!%*?&]).{8,}"
#define CHANGE_PASSWORD '1'
#define CREATE_ACCOUNT '2'
#define DELETE_ACCOUNT_BY_ADMIN '3'
#define DELETE_ACCOUNT_BY_USER '4'

using namespace std;

class Controller
{
private:
    char seletedMenu;
    FileHandler fileHandler;
    Admin admin;
    User user;
public:
    Controller();
    Controller(FileHandler, Admin);
    ~Controller();
    bool isAccountInList(string, vector<User>);
    void printListOfAccounts();
    void setSelectedMenu();
    void printSelection();
    char getSelectedMenu();
    bool isPasswordInCorrectForm(string);
    void createNewAccount();
    void login();
    bool isLoginSuccessful();
    void changePassword();
    void deleteAccountByAdmin();
    void deleteAccountByUser();
    void printInActiveAccounts();
    void reviewInActiveAccounts();
    bool convertStringToBool(string);
};

#endif