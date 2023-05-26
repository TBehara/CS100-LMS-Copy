#ifndef LMS_HPP
#define LMS_HPP

#include "user.hpp"
#include "search_base.hpp"
#include "../libraries/hash/sha256.h"
#include "../header/jsonManager.hpp"

class LMS {
    private:
        User *currentUser;
        list<Book> bookDatabase;
        SearchBase searchBase;
        list<Book> cart;
    public:
        LMS();
        void welcomePrompt();
        void signUpPrompt();
        void setStdInEcho(bool);
        void loginPrompt();
        void mainMenuPrompt();
        void browsePrompt();
        void checkoutCart();
        void logoutPrompt();
        void displayUserDetails(); //test commit
};
#endif