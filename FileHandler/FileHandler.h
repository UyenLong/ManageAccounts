#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <string>
#include <map>
#include <utility>

using namespace std;
class FileHandler
{
private:
    string fileName;
    map<string, pair<string, bool>> listOfAccounts;

public:
    FileHandler();
    ~FileHandler();
    FileHandler(string);
    FileHandler(const FileHandler &);
    map<string, pair<string, bool>> getListOfAccountsFromTextFile();
    void updateListOfAccountsToTextFile(map<string, pair<string, bool>>);
};
#endif