#include <iostream>
#include "Controller.h"

using namespace std;

int main()
{
    FileHandler textFile{ACCOUNT_FILE};
    map<string, pair<string, bool>> listOfAccountsFromTextFile = textFile.getListOfAccountsFromTextFile();
    Admin accountManager;
    accountManager.setListOfAccounts(listOfAccountsFromTextFile);
    Controller controller{textFile, accountManager};
    cout << "List of accounts before changing..." << endl;
    controller.printListOfAccounts();
    char isStop = false;
    do
    {
        controller.setSelectedMenu();
        controller.printSelection();
        char selection = controller.getSelectedMenu();
        if (selection == CREATE_ACCOUNT)
        {
            controller.createNewAccount();
        }
        else
        {
            cout << "Please login before updating your account:" << endl;
            controller.login();
            if (controller.isLoginSuccessful())
            {
                switch (selection)
                {
                case CHANGE_PASSWORD:
                    controller.changePassword();
                    break;
                case DELETE_ACCOUNT_BY_ADMIN:
                    controller.deleteAccountByAdmin();
                    break;
                case DELETE_ACCOUNT_BY_USER:
                    controller.deleteAccountByUser();
                    controller.printInActiveAccounts();
                    controller.printListOfAccounts();
                    controller.reviewInActiveAccounts();
                    break;
                }
            }
        }
        cout << "List of accounts after changing..." << endl;
        controller.printListOfAccounts();
        cout << "Please enter 0 if you want to go back to the menu." << endl;
        cout << "Press any key to exit..." << endl;
        cin >> isStop;
    } while (isStop == '0');
}