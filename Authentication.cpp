#include "Authentication.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Authentication::Authentication(string filename) {
    this->filename = filename;
    this->loggedInUser = "";
    createDefaultCredentialsIfMissing();
}

void Authentication::createDefaultCredentialsIfMissing() {
    ifstream checkFile(filename);
    if (!checkFile) {
        ofstream newFile(filename);
        newFile << "admin|admin123" << endl;
        newFile.close();
        cout << "[Setup] Default admin account created -> username: admin, password: admin123\n";
    }
    checkFile.close();
}

bool Authentication::login() {
    string enteredUser, enteredPass;

    cout << "\n========== ADMIN LOGIN ==========\n";
    cout << "Username : ";
    cin >> enteredUser;
    cout << "Password : ";
    cin >> enteredPass;

    ifstream file(filename);
    if (!file) {
        cout << "Error: login.txt not found.\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string storedUser, storedPass;
        getline(ss, storedUser, '|');
        getline(ss, storedPass, '|');

        if (storedUser == enteredUser && storedPass == enteredPass) {
            loggedInUser = storedUser;
            cout << "\nLogin successful. Welcome, " << loggedInUser << "!\n";
            return true;
        }
    }

    cout << "\nInvalid username or password.\n";
    return false;
}

void Authentication::logout() {
    cout << "\nUser '" << loggedInUser << "' logged out successfully.\n";
    loggedInUser = "";
}
