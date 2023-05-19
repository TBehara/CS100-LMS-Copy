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
        void write(User toWrite);
        User findUser(User toRead);        
};
#endif