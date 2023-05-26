#ifndef JSONMANAGER_HPP
#define JSONMANAGER_HPP

#include "../libraries/nlohmann/json.hpp"
using json = nlohmann::json;
#include "../header/user.hpp"
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
        static string loadUser(User* toRead);
        static string findUserFile(const string&);
};
#endif