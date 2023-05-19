#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <list>
#include "book.hpp"
using namespace std;


class User {
    private:
        string username;
        int hashedPassword;
        double fine;
        list<Book> checkedOutBooks;
    public:
        User();
        User(const string&, const string&);
        string getUsername() const;
        int hashPassword() const; //getPassword() on the UML diagram
        double getFine() const;
        void setUsername(const string& username);
        void setFine(double fine); //fine is an int on the UML diagram so we should change the one on the diagram to a double
        void removeBook(Book returnedBook);
        void addBook(Book checkoutBook);
        const list<Book>& getBooks() const;
        virtual void displayMenu();
};
#endif