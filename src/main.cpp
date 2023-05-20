#include "../header/jsonManager.hpp"
#include "../header/user.hpp"
//using namespace std;

int main() {
    User x;
    jsonManager ex;
    x.setUsername("tbeha001");
    ex.write(x);
    return 0;
}