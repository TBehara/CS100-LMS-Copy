#include <iostream>
#include "LMS.hpp"


LMS::LMS() {
    
}

void LMS::welcomePrompt() {

}

void LMS::signUpPrompt() {

}

void LMS::loginPrompt() {
    std::string username;
    std::string password;
    std::string hashPassword;



    std::cout << "\t\t\tLogin" << std::endl;
    std::cout << std::endl;
    std::cout << "Username: ";
    std::cin.ignore();
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);
    //hashPasword = computeHash(password);
    //if (hash == hash in the database) {
        //"You have successfully logged in!"
    //}
    //else {
        //please try again
    //}

    mainMenuPrompt();
}

void LMS::mainMenuPrompt() {
    
}

void LMS::logoutPrompt() {

}

void LMS::displayUserDetails() {

}