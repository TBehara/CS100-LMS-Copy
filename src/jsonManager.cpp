#include "../header/jsonManager.hpp"
using namespace std;

void jsonManager::write(User* toWrite) {
    string userName = toWrite->getUsername();
    string fileName = userName + ".json";
    string interestsFileName = userName + "_interests.json";
    string booksFileName = userName + "_checkedBooks.json";
    string currBooksFileName = userName + "_currBooks.json";

    string passHash = toWrite->hashPassword();
    double userFine = toWrite->getFine();
    string jsonFine = to_string(userFine);
    bool adminStatus = toWrite->getAdminStatus();

    string dirName = "./JSON/" + userName;
    int makeUserDir = mkdir(dirName.c_str(), 0777);

    ofstream userDataFS("JSON/" + userName + "/" + fileName);
    ofstream userInterestsFS("JSON/" + userName + "/" + interestsFileName);
    ofstream userBooksFS("JSON/" + userName + "/" + booksFileName);
    ofstream userCurrBooksFS("JSON/" + userName + "/" + currBooksFileName);
    json userObj = {
        {"Username", userName},
        {"UserHash", passHash},
        {"UserFine", jsonFine},
        {"AdminStatus", adminStatus}
    };

    json userInterests;
    auto interestsData = userInterests.array();
    unsigned int iterOne;
    for (iterOne = 0; iterOne < toWrite->getInterestKeywords().size(); iterOne++) {
        userInterests = {
            {"Interest", toWrite->getInterestKeywords().at(iterOne)}
        };
        interestsData.push_back(userInterests);
    }

    json userBooks;
    auto checkedBookData = userBooks.array();
    unsigned int iterTwo;
    for (iterTwo = 0; iterTwo < toWrite->getPrevBookNames().size(); iterTwo++) {
        userBooks = {
            {"Book", toWrite->getPrevBookNames().at(iterTwo)}
        };
        checkedBookData.push_back(userBooks);
    }

    json userCheckedBooks;
    auto currBookData = userCheckedBooks.array();
    unsigned int iterThree;
    for (iterThree = 0; iterThree < toWrite->getCurrBookNames().size(); iterThree++) {
        userCheckedBooks = {
            {"Book", toWrite->getCurrBookNames().at(iterThree)}
        };
        currBookData.push_back(userCheckedBooks);
    }


    userDataFS << userObj;
    userDataFS.close();
    userInterestsFS << interestsData;
    userInterestsFS.close();
    userBooksFS << checkedBookData;
    userBooksFS.close();
    userCurrBooksFS << currBookData;
    userCurrBooksFS.close();
}

void jsonManager::updateJSON(User* toUpdate) {
    write(toUpdate);
}

string jsonManager::loadUser(User* toRead) {
    string userName = toRead->getUsername();
    string fileName = userName + ".json";
    string interestsFileName = userName + "_interests.json";
    string booksFileName = userName + "_checkedBooks.json";
    string currBooksFileName = userName + "_currBooks.json";

    ifstream userDataFS("JSON/" + userName + "/" + fileName);
    if (!userDataFS.is_open()) {
        return "false";
    }

    ifstream userCurrBooksFS("JSON/" + userName + "/" + currBooksFileName);
    ifstream userPrevBooksFS("JSON/" + userName + "/" + booksFileName);
    ifstream userInterestsFS("JSON/" + userName + "/" + interestsFileName);

    json dataObj = json::parse(userDataFS);
    toRead->setUsername(dataObj["Username"]);
    string userFine = dataObj["UserFine"];
    double fine = stod(userFine);
    string userHash = dataObj["UserHash"];
    toRead->setFine(fine);
    userDataFS.close();

    json interestObj = json::parse(userInterestsFS);
    vector<string> userInterests;
    for (auto& elem : interestObj) {
        userInterests.push_back(elem["Interest"]);
    }
    toRead->setInterestKeywords(userInterests);
    userInterestsFS.close();

    json prevBookObj = json::parse(userPrevBooksFS);
    vector<string> userPrevBooks;
    for (auto& elem : prevBookObj) {
        userPrevBooks.push_back(elem["Book"]);
    }
    toRead->setPrevBookNames(userPrevBooks);

    json currBookObj = json::parse(userCurrBooksFS);
    vector<string> userCurrBooks;
    for (auto& elem : currBookObj) {
        userCurrBooks.push_back(elem["Book"]);
    }
    toRead->setCurrBookNames(userCurrBooks);
    return userHash;
}