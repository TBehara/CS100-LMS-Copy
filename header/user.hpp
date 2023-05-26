#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <list>
#include "../header/book.hpp"
#include <vector>
using namespace std;


class User {
    private:
        string username, hashedPassword;
        double fine;
        list<Book> checkedOutBooks;
        vector<string> interestKeyWords;
        vector<string> prevCheckedBookNames;
        vector<string> currCheckedBookNames;
    public:
        User();
        User(const string&, const string&);
        string getUsername() const;
        string hashPassword() const; //getPassword() on the UML diagram
        void setHash(const string&);
        double getFine() const;
        void setUsername(const string& username);
        void setFine(double fine); //fine is an int on the UML diagram so we should change the one on the diagram to a double
        vector<string>& getPrevBookNames();
        vector<string>& getCurrBookNames();
        vector<string>& getInterestKeywords();
        void setPrevBookNames(vector<string> &bookNames);
        void setCurrBookNames(vector<string> &bookNames);
        void setInterestKeywords(vector<string> &interestWords);
        void removeBook(const Book& returnedBook);
        void addBook(const Book& checkoutBook);
        const list<Book>& getBooks() const;
        virtual bool getAdminStatus();
        virtual void displayMenu();
};
#endif