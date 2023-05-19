#include "../header/user.hpp"
#include <functional>

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

void User::removeBook(Book returnedBook) {
    //THIS IS A STUB
    return;
}

void User::addBook(Book checkoutBook) {
    //THIS IS A STUB
    return;
}

void User::displayMenu() {
    //THIS IS A STUB
    return;
}

const list<Book>& User::getBooks() const {
    return checkedOutBooks;
}