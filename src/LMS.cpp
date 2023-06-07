#include <iostream>
#include <string>

#include "../header/LMS.hpp"
#include "../header/jsonManager.hpp"
#include "../libraries/nlohmann/json.hpp"
#include "../header/book.hpp"

using json = nlohmann::json;

// used to disable password echo
#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif


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
                << "Press S to sign up for a new account" << std::endl
                << "Press Q to quit the program" << std::endl;
    std::cin >> input;
    if (input == "Q" || input == "q") {
        return;
    }
    else if (input == "L" || input == "l") {
        loginPrompt();
    } else if (input == "S" || input == "s") {
        signUpPrompt();
    } else {
        std::cout << "Invalid input. Please try again" << std::endl;
        welcomePrompt();
    }
}

void LMS::signUpPrompt() {
    // std::string name;
    std::string username;
    std::string password;
    std::string confirmPassword;
    std::string userChoice;
    
    std::cout   << "\t\t\tRegister" << std::endl
                << "Type Q to exit back to the welcome page. Any other input to continue to signup." << std::endl;
            
    std::getline(std::cin, userChoice);
    if (userChoice == "Q" || userChoice == "q") {
        welcomePrompt();
        return;
    }        
    
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

    while (password != confirmPassword) {
        std::cout << "Passwords do not match. Please try again" << std::endl;
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
    }

    if (password == confirmPassword) {
        std::cout << "Account created successfully!" << std::endl;
    } 

    std::cout << "Please enter a couple words, titles, or genres you may be interested in. Type Q to dismiss this prompt. Click ENTER after each word entry." << std::endl;
    string userInterestInput;
    vector<string> userInterests;
    getline(cin, userInterestInput);
    if (!(userInterestInput == "Q" || userInterestInput == "q")) {
            userInterests.push_back(userInterestInput);
    }
    while(userInterestInput != "Q" && userInterestInput != "q") {
        getline(cin, userInterestInput);
        if (!(userInterestInput == "Q" || userInterestInput == "q")) {
            userInterests.push_back(userInterestInput);
        }
    }

    //create password hash
    string userHash = sha256(password);
    //create user
    currentUser = new User(username, userHash);
    currentUser->setFine(0.0);
    currentUser->setInterestKeywords(userInterests);
    //add to JSON
    jsonManager::write(currentUser);
    //display menu
    mainMenuPrompt();
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
    currentUser = new User();
    currentUser->setUsername(username);
    string foundUser = jsonManager::loadUser(currentUser);
    currentUser->setHash(foundUser);
    if (foundUser == "false") {
        std::cout << "This username does not exist in our system. We will redirect you to the sign up page where you can create an account." << std::endl;
        signUpPrompt();
    }
    else {
        string userChoice;
        std::cout << "Password: ";
        setStdInEcho(false);
        std::getline(std::cin, password);
        setStdInEcho(true);
        std::cout << std::endl;

        if (sha256(password) != foundUser) {
            std::cout << "The password you have entered is incorrect." << std::endl;
            std::cout << "Enter C to get 3 tries to get the correct password. If all three tries are incorrect, you will be directed to the sign up page. Any other input will direct you to the sign up page to create a new account." << std::endl;
            std::getline(std::cin, userChoice);
            if (userChoice == "C" || userChoice == "c") {
                bool successLog = false;
                for (int iter = 0; iter < 3; iter++) {
                    std::cout << "Password: ";
                    setStdInEcho(false);
                    std::getline(std::cin, password);
                    setStdInEcho(true);
                    if (sha256(password) == foundUser) {
                        successLog = true;
                        break;
                    }
                }
                if (!successLog) {
                    std::cout << "You will be directed to the signup page to create a new account." << std::endl;
                    signUpPrompt();
                }
                else {
                    mainMenuPrompt();
                }
            }
            else {
                signUpPrompt();
            }
        }
        else {
            mainMenuPrompt();
        }
    }
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
            checkoutCart();
        } else if (input == "4") {
            returnPrompt();
        } else if (input == "5") {
            // renew a book
        } else if (input == "6") {
            browsePrompt();
        } else if (input == "7") {
            displayUserDetails();
        } else if (input == "8") {
            // get book recommendations
        } else if (input == "9") {
            jsonManager::updateJSON(currentUser);
            return;
        } else {
            std::cout << "Invalid input. Please try again" << std::endl;
            mainMenuPrompt();
        }
    } else {
        if (input == "1") {
            checkoutCart();
        } else if (input == "2") {
            returnPrompt();
        } else if (input == "3") {
            // renew a book
        } else if (input == "4") {
            browsePrompt();
        } else if (input == "5") {
            displayUserDetails();
        } else if (input == "6") {
            // get book recommendations
        } else if (input == "7") {
            jsonManager::updateJSON(currentUser);
            exit(0);
        } else {
            std::cout << "Invalid input. Please try again" << std::endl;
            mainMenuPrompt();
        }
    }

    mainMenuPrompt();
}

// switch case version of main menu prompt, keeping in case we need it later
// void LMS::mainMenuPrompt() {
//     currentUser->displayMenu();

//     bool adminStatus = currentUser->getAdminStatus();

//     int input;
//     std::cin >> input;

//     if (adminStatus) {
//         switch (input) {
//             case 1:
//                 // manage books in system
//                 break;
//             case 2:
//                 // add lower level admin
//                 break;
//             case 3:
//                 checkoutCart();
//                 break;
//             case 4:
//                 // return a book
//                 break;
//             case 5:
//                 // renew a book
//                 break;
//             case 6:
//                 browsePrompt();
//                 break;
//             case 7:
//                 displayUserDetails();
//                 break;
//             case 8:
//                 // get book recommendations
//                 break;
//             case 9:
//                 jsonManager::updateJSON(currentUser);
//                 return;
//             default:
//                 std::cout << "Invalid input. Please try again" << std::endl;
//                 mainMenuPrompt();
//                 break;
//         }
//     } else {
//         switch (input) {
//             case 1:
//                 checkoutCart();
//                 break;
//             case 2:
//                 // return a book
//                 break;
//             case 3:
//                 // renew a book
//                 break;
//             case 4:
//                 browsePrompt();
//                 break;
//             case 5:
//                 displayUserDetails();
//                 break;
//             case 6:
//                 // get book recommendations
//                 break;
//             case 7:
//                 jsonManager::updateJSON(currentUser);
//                 return;
//             default:
//                 std::cout << "Invalid input. Please try again" << std::endl;
//                 mainMenuPrompt();
//                 break;
//         }
//     }
// }

void LMS::browsePrompt() {
    std::cout << std::endl;
    std::cout << "What criterion would you like to browse by?" << std::endl;
    std::cout << "1. Browse by Genre" << std::endl;
    std::cout << "2. Browse by Title" << std::endl;
    std::cout << "3. Browse by Author" << std::endl;
    std::cout << "4. Browse by ISBN" << std::endl;
    std::cout << "5. Exit" << std::endl;
    int option = 0;
    std::cin >> option;
    std::list<Book> results; 
    switch(option) {
        case 1:
            results = browseByGenre();
            break;
        case 2:
            results = browseByTitle();
            break;
        case 3:
            results = browseByAuthor();
            break;
        default:
            return;
    }
    //BELOW IS PART OF A PROTOTYPE/EXAMPLE
    
    int searchOption = 0;
    while(searchOption != 2) {
        std::cout << std::endl;
        std::cout << "Results:" << std::endl;
        auto it = results.begin();
        for(unsigned i = 0; i < results.size(); ++i) {
            std::cout << (i+1) << ". " << it->getTitle() << std::endl;
            ++it;
        }
        std::cout << std::endl;
        std::cout << "Options: " << std::endl;
        std::cout << "1. Add to cart" << std::endl;
        std::cout << "2. Return to Main Menu" << std::endl;
        std::cin >> searchOption;
        switch(searchOption) {
            case 1:
                std::cout << "Enter the numerical result of the book to add: " << std::endl;
                {
                    int bookOption = 0;
                    std::cin >> bookOption;
                    auto it = results.begin();
                    for(unsigned i = 0; i < bookOption-1; ++i) {
                        ++it;
                    }
                    cart.push_back(*it);
                }
                std::cout << "Current cart: " << std::endl;
                for(auto it : cart) {
                    std::cout << it.getTitle() << ", ";
                }
                std::cout << std::endl;
                break;
            case 2:
                mainMenuPrompt();
                break;
            default:
                mainMenuPrompt();
                break;
        }
    }
}

list<Book> LMS::browseByGenre() {
    string genreInput = "";
    std::cout << "What genre of book are you looking for?" << std::endl;
    string userInput = "";
    cin.get();
    getline(cin, userInput);
    //TODO: search by actual genre input
    auto resultEntries = searchBase.searchByGenre(Book::Genre::FICTION); //Hardcoded for now
    return bookEntriesToBooks(resultEntries);
}

list<Book> LMS::browseByTitle() {
    string userInput = "";
    std::cout << "What is the title of the book you are looking for?" << std::endl;
    return browseByStringInput();
}

list<Book> LMS::browseByAuthor() {
    std::cout << "Who is the author of the book(s) you are looking for?" << std::endl;
    return browseByStringInput();
}

list<Book> LMS::browseByStringInput() {
    string userInput = "";
    cin.get();
    getline(cin, userInput);
    auto resultEntries = searchBase.searchByTerms(userInput); //Results are currently iterators
    return bookEntriesToBooks(resultEntries); //Convert from iterator list to pure books
}

list<Book> LMS::bookEntriesToBooks(const list<list<Book>::iterator> &entries) {
    list<Book> rawBooks;
    for(auto it : entries) {
        rawBooks.push_back(*it);
    }
    return rawBooks;
}

void LMS::checkoutCart() {
    for(auto it : cart) {
        currentUser->addBook(it);
        std::cout << "Checked out " << it.getTitle() << std::endl;
    }
    std::cout << std::endl;
    cart.clear();
    mainMenuPrompt();
}

void LMS::logoutPrompt() {

}

void LMS::displayUserDetails() {
    std::cout << std::endl;
    std::cout << "Details for " << currentUser->getUsername() << std::endl;
    std::cout << "Fines: " << currentUser->getFine() << std::endl;
    std::cout << "Books currently checked out: ";
    for(auto it : currentUser->getBooks()) {
        std::cout << it.getTitle() << ", ";
    }
    std::cout << std::endl;
    mainMenuPrompt();
}

// main menu prompts

void LMS::checkoutPrompt() {

}

void LMS::returnPrompt() {
    // Get the user's checked out books
    const list<Book>& checkedOutBooks = currentUser->getBooks();

    // Check if the user has any books checked out
    if (checkedOutBooks.empty()) {
        cout << "You don't have any books checked out." << endl;
        return;
    }

    // Display the user's checked out books
    cout << "You have the following books checked out:" << endl;
    int i = 1;
    for (const Book& book : checkedOutBooks) {
        cout << i << ". " << book.getTitle() << " by " << book.getAuthor() << endl;
        i++;
    }

    // Prompt the user to select a book to return
    cout << "Enter the number of the book you want to return (or 0 to return all books): ";
    int bookIndex;
    cin >> bookIndex;

    // Return the selected book or all books
    if (bookIndex == 0) {
        // Return all books
        for (const Book& book : checkedOutBooks) {
            currentUser->removeBook(book);
        }
        cout << "All books have been returned." << endl;
    } else if (bookIndex > 0 && bookIndex <= checkedOutBooks.size()) {
        // Return the selected book
        auto it = checkedOutBooks.begin();
        advance(it, bookIndex - 1);
        const Book& book = *it;
        string title = book.getTitle();
        currentUser->removeBook(book);
        cout << "The book \"" << title << "\" has been returned." << endl;
    } else {
        cout << "Invalid book number." << endl;
    }
}

void LMS::renewPrompt() {

}

void LMS::getRecommendationsPrompt() {

}

void LMS::viewAccountPrompt(const User &user) {

}

// admin prompts

void LMS::manageBooksPrompt() {

}

void LMS::addAdminPrompt() {
    std::cout   << "\t\tAdd Admin" << std::endl
                << "Enter the username of the user you would like to make an admin. Enter \"quit\" to go back" << std::endl
                << "Username: ";
    std::string username;
    std::getline(std::cin, username);

    if (username == "quit") {
        mainMenuPrompt();
    }

    std::string userFile = jsonManager::findUserFile(username);
    if (userFile == "") {
        std::cout << "User " << username << " does not exist. Please try again" << std::endl;
        addAdminPrompt();
    }
    std::ifstream userFileStream(userFile);
    json userJson = json::parse(userFileStream);

    userJson["AdminStatus"] = true;
    // TODO: add admin priority once it gets implemented

    std::ofstream userFileOutStream(userFile);
    userFileOutStream << userJson.dump(4) << std::endl;

    std::cout << "User " << username << " is now an admin." << std::endl;
    mainMenuPrompt();
}