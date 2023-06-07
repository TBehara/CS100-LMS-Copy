#ifndef JSONMANAGER_HPP
#define JSONMANAGER_HPP

#include "../libraries/nlohmann/json.hpp"
using json = nlohmann::json;
#include "../header/user.hpp"
#include "../header/admin.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <string>
#include <vector>
#include <sys/stat.h>
using namespace std;

class jsonManager {
    public:
        static void write(User* toWrite);
        static void updateJSON(User* toUpdate);
        static bool loadUser(User* toRead);
        static string findUserFile(const string&);
        static void addToSearchBase(const Book &book);
        static void addToUserBase(Book &book, string fileName);
        static bool findBook(string bookTitle, Book& toReturn, string fileName);
        static list<Book> loadBooks();
        static list<Book> loadUserBooks(User* toLoad);
};
#endif