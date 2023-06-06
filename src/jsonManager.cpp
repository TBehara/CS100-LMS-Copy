#include "../header/jsonManager.hpp"

#include <filesystem>

using namespace std;

void jsonManager::write(User* toWrite) {
    string userName = toWrite->getUsername();
    string fileName = userName + ".json";
    string interestsFileName = userName + "_interests.json";
    string booksFileName = userName + "_checkedBooks.json";
    string currBooksFileName = userName + "_currBooks.json";
    json currUserBooks;
    auto currBooksData = currUserBooks.array();

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
    
    json userObj;
    unsigned int userPriority;
    if (!toWrite->getAdminStatus()) {
       userObj = {
        {"Username", userName},
        {"UserHash", passHash},
        {"UserFine", jsonFine},
        {"AdminStatus", adminStatus}
        };
    }
    else {
        userPriority = toWrite->getPriority();
        userObj = {
            {"Username", userName},
            {"UserHash", passHash},
            {"UserFine", jsonFine},
            {"AdminStatus", adminStatus},
            {"Priority", userPriority}
        };
    }

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

    for (auto it: toWrite->getCheckedOutBooks()) {
        addToUserBase(it, userName + "/" + currBooksFileName);
    }


    userDataFS << userObj.dump(4) << endl;
    userDataFS.close();
    userInterestsFS << interestsData.dump(4) << endl;
    userInterestsFS.close();
    userBooksFS << checkedBookData.dump(4) << endl;
    userBooksFS.close();
    userCurrBooksFS << currBooksData.dump(4) << endl;
    userCurrBooksFS.close();
}

void jsonManager::updateJSON(User* toUpdate) {
    write(toUpdate);
}

string jsonManager::loadUser(User* toRead) {
    //cout << "CALLED LOAD USER" << endl;
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

    //cout << "UP till here good" << endl;
    json currBookObj = json::parse(userCurrBooksFS);
    list<Book> userCurrBooks = loadUserBooks(toRead);
    toRead->setCheckedOutBooks(userCurrBooks);
    
    return userHash;
}

string jsonManager::findUserFile(const string &username) {
    string filePath;
    string dirPath = "./JSON";
    if (filesystem::exists(dirPath)) {
        for (const auto &entry : filesystem::directory_iterator(dirPath)) {
            string dirName = entry.path().filename().string();
            if (dirName == username) {
                string fileName = username + ".json";
                filePath = entry.path().string() + "/" + fileName;
                break;
            }
        }
    }
    return filePath;
}

void jsonManager::addToSearchBase(Book &book) {
    json bookBase;
    auto bookBaseData = bookBase.array();
    string fileName = "BookBase.json";
    ifstream bookBaseINFS("JSON/" + fileName);
    if (bookBaseINFS.is_open()) {
        json booksObj = json::parse(bookBaseINFS);
        for (auto& obj: booksObj) {
            bookBaseData.push_back(obj);
        }
        bookBaseINFS.close();
        string rmFile = "JSON/" + fileName;
        int deleteFile = remove(rmFile.c_str());
    }
    ofstream bookBaseOFS("JSON/" + fileName);
    list<Book::Genre> bookGenres = book.getGenres();
    vector<string> bookGenreStrings;
    for (auto it: bookGenres) {
        string genre;
        if (it == Book::Genre::FICTION) {
            genre = "FICTION";
        }
        else if (it == Book::Genre::NONFICTION) {
            genre = "NONFICTION";
        }
        else if (it == Book::Genre::FANTASY) {
            genre = "FANTASY";
        }
        else if (it == Book::Genre::NOVEL) {
            genre = "NOVEL";
        }
        else if (it == Book::Genre::MYSTERY) {
            genre = "MYSTERY";
        }
        else if (it == Book::Genre::SCIFI) {
            genre = "SCIFI";
        }
        else if (it == Book::Genre::HISTORICAL_FICTION) {
            genre = "HISTORICAL_FICTION";
        }
        else if (it == Book::Genre::LITERARY_FICTION) {
            genre = "LITERARY_FICTION";
        }
        else if (it == Book::Genre::NARRATIVE) {
            genre = "NARRATIVE";
        }
        else if (it == Book::Genre::ALWAYS_AT_END) {
            genre = "ALWAYS_AT_END";
        }
        bookGenreStrings.push_back(genre);
    }
    bookBase = {
            {"Title", book.getTitle()},
            {"Author", book.getAuthor()},
    };

    int iter;
    for (iter = 0; iter < bookGenreStrings.size(); iter++) {
        string iterString = std::to_string(iter);
        string genreNum = "Genre" + iterString;
        bookBase[genreNum] = bookGenreStrings.at(iter);
    }

    bookBase["NumGenres"] = bookGenreStrings.size();

    bookBaseData.push_back(bookBase);
    bookBaseOFS << bookBaseData;
    bookBaseOFS.close();
}

void jsonManager::addToUserBase(Book &book, string fileName) {
    json bookBase;
    auto bookBaseData = bookBase.array();
    ifstream bookBaseINFS("JSON/" + fileName);
    if (bookBaseINFS.is_open()) {
        json booksObj = json::parse(bookBaseINFS);
        for (auto& obj: booksObj) {
            bookBaseData.push_back(obj);
        }
        bookBaseINFS.close();
        string rmFile = "JSON/" + fileName;
        int deleteFile = remove(rmFile.c_str());
    }
    ofstream bookBaseOFS("JSON/" + fileName);
    list<Book::Genre> bookGenres = book.getGenres();
    vector<string> bookGenreStrings;
    for (auto it: bookGenres) {
        string genre;
        if (it == Book::Genre::FICTION) {
            genre = "FICTION";
        }
        else if (it == Book::Genre::NONFICTION) {
            genre = "NONFICTION";
        }
        else if (it == Book::Genre::FANTASY) {
            genre = "FANTASY";
        }
        else if (it == Book::Genre::NOVEL) {
            genre = "NOVEL";
        }
        else if (it == Book::Genre::MYSTERY) {
            genre = "MYSTERY";
        }
        else if (it == Book::Genre::SCIFI) {
            genre = "SCIFI";
        }
        else if (it == Book::Genre::HISTORICAL_FICTION) {
            genre = "HISTORICAL_FICTION";
        }
        else if (it == Book::Genre::LITERARY_FICTION) {
            genre = "LITERARY_FICTION";
        }
        else if (it == Book::Genre::NARRATIVE) {
            genre = "NARRATIVE";
        }
        else if (it == Book::Genre::ALWAYS_AT_END) {
            genre = "ALWAYS_AT_END";
        }
        bookGenreStrings.push_back(genre);
    }
    bookBase = {
            {"Title", book.getTitle()},
            {"Author", book.getAuthor()},
    };

    int iter;
    for (iter = 0; iter < bookGenreStrings.size(); iter++) {
        string iterString = std::to_string(iter);
        string genreNum = "Genre" + iterString;
        bookBase[genreNum] = bookGenreStrings.at(iter);
    }

    bookBase["NumGenres"] = bookGenreStrings.size();

    bookBaseData.push_back(bookBase);
    bookBaseOFS << bookBaseData;
    bookBaseOFS.close();
}

bool jsonManager::findBook(string bookTitle, Book& toReturn, string fileName) {
    ifstream bookBaseINFS("JSON/" + fileName);
    json booksObj = json::parse(bookBaseINFS);
    for (auto& obj: booksObj) {
        if (obj["Title"] == bookTitle) {
            list<Book::Genre> genreList;
            int iter;
            for (iter = 0; iter < obj["NumGenres"]; iter++) {
                string iterString = std::to_string(iter);
                string genreNum = "Genre" + iterString;
                string genre = obj[genreNum];
                Book::Genre enumGenre;
                if (genre == "FICTION") {
                        enumGenre = Book::Genre::FICTION;
                }
                else if (genre == "NONFICTION") {
                    enumGenre = Book::Genre::NONFICTION;
                }
                else if (genre == "FANTASY") {
                    enumGenre = Book::Genre::FANTASY;
                }
                else if (genre == "NOVEL") {
                    enumGenre = Book::Genre::NOVEL;
                }
                else if (genre == "MYSTERY") {
                    enumGenre = Book::Genre::MYSTERY;
                }
                else if (genre == "SCIFI") {
                    enumGenre = Book::Genre::SCIFI;
                }
                else if (genre == "HISTORICAL_FICTION") {
                    enumGenre = Book::Genre::HISTORICAL_FICTION;
                }
                else if (genre == "LITERARY_FICTION") {
                    enumGenre = Book::Genre::LITERARY_FICTION;
                }
                else if (genre == "NARRATIVE") {
                    enumGenre = Book::Genre::NARRATIVE;
                }
                else if (genre == "ALWAYS_AT_END") {
                    enumGenre = Book::Genre::ALWAYS_AT_END;
                }
                genreList.push_back(enumGenre);
            }
            Book returnBook = Book(obj["Title"], obj["Author"], genreList);
            toReturn = returnBook;
            return true;
        }
    }
    return false;
}

list<Book> jsonManager::loadBooks() {
    list<Book> toReturn;
    string fileName = "BookBase.json";
    ifstream loadINFS("JSON/" + fileName);
    json booksObj = json::parse(loadINFS);
    for (auto& obj: booksObj) {
        list<Book::Genre> genres;
        Book toAdd = Book("", "", genres);
        bool foundBook = findBook(obj["Title"], toAdd, fileName);
        toReturn.push_back(toAdd);
    }
    loadINFS.close();
    return toReturn;
}

list<Book> jsonManager::loadUserBooks(User* toLoad) {
    list<Book> toReturn;
    string fileName = toLoad->getUsername() + "/" + toLoad->getUsername() + "_currBooks.json";
    ifstream loadINFS("JSON/" + fileName);
    json booksObj = json::parse(loadINFS);
    for (auto& obj: booksObj) {
        list<Book::Genre> genres;
        Book toAdd = Book("", "", genres);
        bool foundBook = findBook(obj["Title"], toAdd, fileName);
        toReturn.push_back(toAdd);
    }
    loadINFS.close();
    return toReturn;
}