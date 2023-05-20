#ifndef ADMIN_HPP
#define ADMIN_HPP
#include "user.hpp"

class Admin: public User {
    private:
        unsigned int priority;
    public:
        Admin();
        Admin(int);
        unsigned int getPriority();
        void displayMenu();
};
#endif