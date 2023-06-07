#include "../header/admin.hpp"

Admin::Admin() : User(), priority(0) {}

Admin::Admin(const string& username, const string& password, int _priority) : User(username, password), priority(_priority) {}

Admin::Admin(User* user, int _priority) : User(user->getUsername(), user->hashPassword()), priority(_priority) {
    this->setCheckedOutBooks(user->getCheckedOutBooks());
    this->setFine(user->getFine());
    this->setPrevBookNames(user->getPrevBookNames());
    this->setInterestKeywords(user->getInterestKeywords());
}

unsigned int Admin::getPriority() {
    return priority;
}

void Admin::displayMenu() {
    User::displayMenu();
    std::cout << std::endl;
    std::cout << "Additional Admin Controls" << std::endl;
    std::cout << "8. Manage Books in System" << std::endl;
    std::cout << "9. Add Lower Level Admin" << std::endl;    
}

bool Admin::getAdminStatus() {
    return true;
}

void Admin::setPriority(unsigned int priorityNum) {
    this->priority = priorityNum;
}

