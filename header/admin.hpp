#ifndef ADMIN_HPP
#define ADMIN_HPP
#include "user.hpp"

class Admin: public User {
    private:
        unsigned int priority;
    public:
        Admin();
        Admin(const string&, const string&, int);
        unsigned int getPriority();
        void displayMenu();
};
#endif