#include <iostream>
#include "../header/LMS.hpp"
#include <string>

#include "../header/LMS.hpp"

// used to disable password echo
#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include "../libraries/nlohmann/json.hpp"


LMS::LMS() {
    welcomePrompt();
}

void LMS::welcomePrompt() {
    std::string input;
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
    std::cin >> input;
    if (input == "L" || input == "l") {
        loginPrompt();
    } else if (input == "S" || input == "s") {
        signUpPrompt();
    } else {
        std::cout << "Invalid input. Please try again" << std::endl;
        welcomePrompt();
    }
}

void LMS::signUpPrompt() {
    std::string name;
    std::string username;
    std::string password;
    std::string confirmPassword;
    
    std::cout   << "\t\t\tRegister" << std::endl
                << "Please fill out the following fields so we may create an account for you" << std::endl
                << "Full Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    std::cout   << "Username: ";
    std::getline(std::cin, username);

    std::cout   << "Password: ";
    setStdInEcho(false);
    std::getline(std::cin, password);
    setStdInEcho(true);
    std::cout   << std::endl;

    std::cout   << "Confirm Password: ";
    setStdInEcho(false);
    std::getline(std::cin, confirmPassword);
    setStdInEcho(true);
    std::cout   << std::endl;

    if (password == confirmPassword) {
        std::cout << "Account created successfully!" << std::endl;
        // TODO: create account
    } else {
        std::cout << "Passwords do not match. Please try again" << std::endl;
        signUpPrompt();
    }
}

// stolen from https://stackoverflow.com/questions/1413445/reading-a-password-from-stdcin
void LMS::setStdInEcho(bool enable = true) {
    #ifdef WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
        DWORD mode;
        GetConsoleMode(hStdin, &mode);

        if( !enable )
            mode &= ~ENABLE_ECHO_INPUT;
        else
            mode |= ENABLE_ECHO_INPUT;

        SetConsoleMode(hStdin, mode );

    #else
        struct termios tty;
        tcgetattr(STDIN_FILENO, &tty);
        if( !enable )
            tty.c_lflag &= ~ECHO;
        else
            tty.c_lflag |= ECHO;

        (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    #endif
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
    currentUser->displayMenu();

    bool adminStatus = currentUser->getAdminStatus();

    std::string input;
    std::cin >> input;
    if (adminStatus) {
        if (input == "1") {
            // manage books in system
        } else if (input == "2") {
            // add lower level admin
        } else if (input == "3") {
            // checkout books in cart
        } else if (input == "4") {
            // return a book
        } else if (input == "5") {
            // renew a book
        } else if (input == "6") {
            // browse/search for books/add books to cart
        } else if (input == "7") {
            // view books on account & fees
        } else if (input == "8") {
            // get book recommendations
        } else if (input == "9") {
            // save and logout
        } else {
            std::cout << "Invalid input. Please try again" << std::endl;
            mainMenuPrompt();
        }
    } else {
        if (input == "1") {
            // checkout books in cart
        } else if (input == "2") {
            // return a book
        } else if (input == "3") {
            // renew a book
        } else if (input == "4") {
            // browse books
        } else if (input == "5") {
            // view books on account & fees
        } else if (input == "6") {
            // get book recommendations
        } else if (input == "7") {
            // save and logout
        } else {
            std::cout << "Invalid input. Please try again" << std::endl;
            mainMenuPrompt();
        }
    }
}

void LMS::logoutPrompt() {

}

void LMS::displayUserDetails() {

}

// main menu prompts

void LMS::checkoutPrompt() {

}

void LMS::returnPrompt() {

}

void LMS::renewPrompt() {

}

void LMS::browsePrompt() {

}

void LMS::getRecommendationsPrompt() {

}

void LMS::viewAccountPrompt(const User &user) {

}

// admin prompts

void LMS::manageBooksPrompt() {

}

void LMS::addAdminPrompt() {

}