#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <list>
#include "book.hpp"
using namespace std;


class User {
    private:
        string username;
        double fine;
        list<Book> checkedOutBooks;
    public:
        User();
        string getUsername();
        string hashPassword(); //getPassword() on the UML diagram
        double getFine();
        void setUsername(string username);
        void setFine(double fine); //fine is an int on the UML diagram so we should change the one on the diagram to a double
        void removeBook(Book returnedBook);
        void addBook(Book checkoutBook);
        virtual void displayMenu();
};
#endif