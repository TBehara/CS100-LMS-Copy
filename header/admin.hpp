#ifndef ADMIN_HPP
#define ADMIN_HPP
#include "user.hpp"

class Admin: public User {
    private:
        unsigned int priority;
    public:
        Admin();
        Admin(const string&, const string&, int);
        Admin(User*, int);
        unsigned int getPriority();
        void displayMenu();
        bool getAdminStatus();
        void setPriority(unsigned int priority);
};
#endif