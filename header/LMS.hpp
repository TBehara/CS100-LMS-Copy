#ifndef LMS_HPP
#define LMS_HPP

#include "user.hpp"
#include "search_base.hpp"

class LMS {
    private:
        User *currentUser;
        list<Book> bookDatabase;
        list<searchBase> searchBaseList;
    public:
        LMS();
    private:
        void welcomePrompt();
        void signUpPrompt();
        void setStdInEcho(bool);
        void loginPrompt();
        void mainMenuPrompt();
        void logoutPrompt();
        void displayUserDetails();
};
#endif