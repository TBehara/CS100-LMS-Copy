#include "../header/jsonManager.hpp"
using namespace std;

void jsonManager::write(User toWrite) {
    string userName = toWrite.getUsername();
    string fileName = userName + ".json";
    string interestsFileName = userName + "_interests.json";
    string booksFileName = userName + "_checkedBooks.json";

    string passHash = toWrite.hashPassword();
    double userFine = toWrite.getFine();
    string jsonFine = to_string(userFine);

    string dirName = "./JSON/" + userName;
    int check = mkdir(dirName.c_str(), 0777);

    ofstream userDataFS("JSON/" + userName + "/" + fileName);
    ofstream userInterestsFS("JSON/" + userName + "/" + interestsFileName);
    ofstream userBooksFS("JSON/" + userName + "/" + booksFileName);
    json userObj = {
        {"Username", userName},
        {"UserHash", passHash},
        {"UserFine", jsonFine}
    };

    json userInterests;
    auto interestsData = userInterests.array();
    unsigned int i;
    for (i = 0; i < toWrite.interestKeyWords.size(); i++) {
        userInterests = {
            {"Interest", toWrite.interestKeyWords.at(i)}
        };
        interestsData.push_back(userInterests);
    }

    json userBooks;
    auto checkedBookData = userBooks.array();
    unsigned int j;
    for (j = 0; j < toWrite.checkedBookNames.size(); j++) {
        userBooks = {
            {"Book", toWrite.checkedBookNames.at(j)}
        };
        checkedBookData.push_back(userBooks);
    }


    userDataFS << userObj;
    userDataFS.close();
    userInterestsFS << interestsData;
    userInterestsFS.close();
    userBooksFS << checkedBookData;
    userBooksFS.close();
}

User jsonManager::findUser(User toRead) {
    return toRead;
}