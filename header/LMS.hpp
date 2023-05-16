#ifndef LMS_HPP
#define LMS_HPP

#include "user.hpp"
#include "search_base.hpp"

class LMS {
    private:
        User currentUser;
        list<Book> bookDatabase;
        list <searchBase> searchBase;
    public:
        LMS();
        void welcomePrompt();
        void signUpPrompt();
        void loginPrompt();
        void mainMenuPrompt();
        void logoutPrompt();
        void displayUserDetails(); //test commit
};
#endif