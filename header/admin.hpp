#ifndef ADMIN_HPP
#define ADMIN_HPP
#include "user.hpp"

class Admin: public User {
    private:
        unsigned int priority;
    public:
        Admin();
        unsigned int getPriority();
        void displayMenu();
};
#endif