#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <list>
#include "../header/book.hpp"
#include <vector>
using namespace std;


class User {
    private:
        string username;
        double fine;
        list<Book> checkedOutBooks;
        vector<string> interestKeyWords = {"Hello", "Taran", "WRLD"};
        vector<string> prevCheckedBookNames = {"Hello", "Taran", "WRLD"};
        vector<string> currCheckedBookNames = {"Hello", "Taran", "WRLD"};
    public:
        User();
        string getUsername();
        string hashPassword(); //getPassword() on the UML diagram
        double getFine();
        void setUsername(string username);
        void setFine(double fine); //fine is an int on the UML diagram so we should change the one on the diagram to a double
        void removeBook(Book returnedBook);
        void addBook(Book checkoutBook);
        vector<string>& getPrevBookNames();
        vector<string>& getCurrBookNames();
        vector<string>& getInterestKeywords();
        void setPrevBookNames(vector<string> &bookNames);
        void setCurrBookNames(vector<string> &bookNames);
        void setInterestKeywords(vector<string> &interestWords);
        virtual void displayMenu();
};
#endif