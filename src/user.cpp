#include "../header/user.hpp"

User::User() {

}

string User::getUsername() {
    return this->username;
}

string User::hashPassword() {
    return "";
}

double User::getFine() {
    return this->fine;
}

vector<string>& User::getPrevBookNames() {
    return this->prevCheckedBookNames;
}

vector<string>& User::getCurrBookNames() {
    return this->currCheckedBookNames;
}
        
vector<string>& User::getInterestKeywords() {
    return this->interestKeyWords;
}

void User::setPrevBookNames(vector<string> &bookNames) {
    this->prevCheckedBookNames = bookNames;
}

void User::setCurrBookNames(vector<string> &bookNames) {
    this->currCheckedBookNames = bookNames;
}

void User::setInterestKeywords(vector<string> &interestWords) {
    this->interestKeyWords = interestWords;
}

void User::setUsername(string username) {
    this->username = username;
}

void User::setFine(double fine) {
    this->fine = fine;
}

void User::removeBook(Book returnedBook) {

}

void User::addBook(Book checkoutBook) {

}

void User::displayMenu() {

}