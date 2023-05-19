#include "../header/user.hpp"
#include <functional>
#include <stdexcept>
using std::runtime_error;

User::User() : username("Guest"), hashedPassword(0), fine(0) {
}

User::User(const string& username, const string& password) : username(username), fine(0) {
    hashedPassword = hash<string>{}(password);
}

string User::getUsername() const {
    return username;
}

int User::hashPassword() const {
    return hashedPassword;
}

double User::getFine() const {
    return fine;
}

void User::setUsername(const string& username) {
    this->username = username;
}

void User::setFine(double fine) {
    this->fine = fine;
}

void User::removeBook(const Book& returnedBook) {
    for(auto it : checkedOutBooks) {
        if(it == returnedBook) {
            checkedOutBooks.remove(it);
            return;
        }
    }
    return;
}

void User::addBook(const Book& checkoutBook) {
    for(auto it : checkedOutBooks) {
        if(it == checkoutBook) {
            throw runtime_error(it.getTitle() + " by " + it.getAuthor() + " is already checked out");
        }
    }
    checkedOutBooks.push_back(checkoutBook);
}

void User::displayMenu() {
    //THIS IS A STUB
    return;
}

const list<Book>& User::getBooks() const {
    return checkedOutBooks;
}