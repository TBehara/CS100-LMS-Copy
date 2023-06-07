#include "../header/user.hpp"
#include <stdexcept>
using std::runtime_error;

User::User() : username("Guest"), hashedPassword(""), fine(0){
}


User::User(const string& username, const string& hashedPassword) : username(username), hashedPassword(hashedPassword), fine(0){
}

unsigned int User::getPriority() {
    return 0;
}

vector<string>& User::getPrevBookNames() {
    return this->prevCheckedBookNames;
}

list<Book>& User::getCheckedOutBooks() {
    return this->checkedOutBooks;
}

void User::setCheckedOutBooks(list<Book> &books) {
    this->checkedOutBooks = books;
}

// vector<string>& User::getCurrBookNames() {
//     return this->currCheckedBookNames;
// }
        
vector<string>& User::getInterestKeywords() {
    return this->interestKeyWords;
}

void User::setPrevBookNames(vector<string> &bookNames) {
    this->prevCheckedBookNames = bookNames;
}

// void User::setCurrBookNames(vector<string> &bookNames) {
//     this->currCheckedBookNames = bookNames;
// }

void User::setInterestKeywords(vector<string> &interestWords) {
    this->interestKeyWords = interestWords;
}

string User::getUsername() const {
    return username;
}

string User::hashPassword() const {
    return hashedPassword;
}

void User::setHash(const string& newHash) {
    hashedPassword = newHash;
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
    //currCheckedBookNames.push_back(checkoutBook.getTitle());
    prevCheckedBookNames.push_back(checkoutBook.getTitle());
}

void User::displayMenu() {
    std::cout << "Welcome to the Main User Menu!" << std::endl;
    std::cout << "1. Checkout books in cart" << std::endl;
    std::cout << "2. Return a book" << std::endl;
    std::cout << "3. Renew a book" << std::endl;
    std::cout << "4. Browse/Search for Books/Add to Cart" << std::endl;
    std::cout << "5. View Books on Account & Fees" << std::endl;
    std::cout << "6. Get book recommendations" << std::endl;
    std::cout << "7. Save and Logout" << std::endl;
}

const list<Book>& User::getBooks() const {
    return checkedOutBooks;
}

bool User::getAdminStatus() {
    return false;
}