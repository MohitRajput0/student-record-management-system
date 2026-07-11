#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
using namespace std;

class Authentication {
private:
    string filename;
    string loggedInUser;

    void createDefaultCredentialsIfMissing();

public:
    Authentication(string filename = "login.txt");

    bool login();
    void logout();
};

#endif
