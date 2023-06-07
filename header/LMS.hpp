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
    private:
        void welcomePrompt();
        void signUpPrompt();
        void setStdInEcho(bool);
        void loginPrompt();
        void mainMenuPrompt();
        void browsePrompt();
        list<Book> browseByGenre();
        list<Book> browseByTitle();
        list<Book> browseByAuthor();
        list<Book> browseByStringInput();
        list<Book> bookEntriesToBooks(const list<list<Book>::iterator> &);
        void checkoutCart();
        void logoutPrompt();
        void displayUserDetails();
        void checkoutPrompt();
        void returnPrompt();
        void renewPrompt();
        void getRecommendationsPrompt();
        void viewAccountPrompt(const User&);
        public:
        enum Book::Genre stringToGenre(const string& genre);
        // admin exclusive prompts
        private:
        void manageBooksPrompt();
        void addAdminPrompt();
        void adminAddBookPrompt();
        void adminRemoveBookPrompt();
};
#endif