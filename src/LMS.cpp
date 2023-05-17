#include "LMS.hpp"
#include <iostream>

LMS::LMS() {
    this->welcomePrompt();
}

void LMS::welcomePrompt() {
    std::cout   << "\t\tWelcome to the UC Riverside Library!" << std::endl
                << "\tWith an account at our online library, you will be able to:" << std::endl
                << "- Have access to a plethora of books and resources" << std::endl
                << "- View books based on your interests and previous books you have checked out" << std::endl
                << "- Checkout important books" << std::endl
                << "- Return/Renew books" << std::endl
                << "- View important account information" << std::endl
                << std::endl
                << "Press L to log into an existing account" << std::endl
                << "Press S to sign up for a new account" << std::endl;
}

void LMS::signUpPrompt() {

}

void LMS::loginPrompt() {

}

void LMS::mainMenuPrompt() {

}

void LMS::logoutPrompt() {

}

void LMS::displayUserDetails() {

}