#include "../header/admin.hpp"

Admin::Admin() : User(), priority(0) {}

Admin::Admin(const string& username, const string& password, int _priority) : User(username, password), priority(_priority) {}

unsigned int Admin::getPriority() {
    return priority;
}

void Admin::displayMenu() {
    std::cout << "Welcome to the Admin Menu!" << std::endl;
    std::cout << "1. Manage Books in System" << std::endl;
    std::cout << "2. Add Lower Level Admin" << std::endl;
    std::cout << "3. Checkout books in cart" << std::endl;
    std::cout << "4. Return a book" << std::endl;
    std::cout << "5. Browse/Search for Books/Add books to cart" << std::endl;
    std::cout << "6. View Books on Account & Fees" << std::endl;
    std::cout << "7. Get book recommendations" << std::endl;
    std::cout << "8. Save and Logout" << std::endl;
}