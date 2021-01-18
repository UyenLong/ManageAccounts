#ifndef FILEHANDLER_CPP
#define FILEHANDLER_CPP
#include "FileHandler.h"
#include "Controller.h"
#include <iostream>
#include <fstream>

FileHandler::FileHandler()
{
    this->fileName = "";
    this->listOfAccounts = {};
}
FileHandler::FileHandler(const FileHandler &fileHandler)
{
    this->fileName = fileHandler.fileName;
    this->listOfAccounts = fileHandler.listOfAccounts;
}
FileHandler::~FileHandler()
{
    this->fileName = "";
    this->listOfAccounts = {};
}
FileHandler::FileHandler(string nameOfFile)
{
    this->fileName = nameOfFile;
    this->listOfAccounts = this->getListOfAccountsFromTextFile();
}
map<string, pair<string, bool>> FileHandler::getListOfAccountsFromTextFile()
{
    Controller controller;
    map<string, pair<string, bool>> listOfAccounts;
    ifstream fileText;
    fileText.open(this->fileName);
    string accountInfo;
    while (getline(fileText, accountInfo))
    {
        size_t spaceCharacter = accountInfo.find(" ");
        string username = accountInfo.substr(0, spaceCharacter);
        accountInfo = accountInfo.substr(spaceCharacter + 1, accountInfo.size() - 1);
        spaceCharacter = accountInfo.find(" ");
        pair<string, bool> passwordAndStatus;
        passwordAndStatus.first = accountInfo.substr(0, spaceCharacter);
        passwordAndStatus.second = controller.convertStringToBool(accountInfo.substr(spaceCharacter + 1));
        listOfAccounts[username] = passwordAndStatus;
    }
    fileText.close();
    return listOfAccounts;
}

void FileHandler::updateListOfAccountsToTextFile(map<string, pair<string, bool>> newListOfAccounts)
{
    ofstream fileText;
    fileText.open(this->fileName);
    map<string, pair<string, bool>>::iterator account;
    for (account = newListOfAccounts.begin(); account != newListOfAccounts.end(); ++account)
    {
        fileText << account->first << " " << account->second.first << " " << account->second.second << endl;
    }
    fileText.close();
}
#endif