#include "FileManager.h"
#include <fstream>
#include <iostream>
using namespace std;

void FileManager::loadStudents(vector<Student>& students, const string& filename) {
    ifstream file(filename);
    if (!file) {
        return;
    }

    students.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Student s = Student::fromFileString(line);
        if (!s.getStudentID().empty()) {
            students.push_back(s);
        }
    }
    file.close();
}

void FileManager::saveStudents(const vector<Student>& students, const string& filename) {
    ofstream file(filename, ios::trunc);
    if (!file) {
        cout << "Error: Unable to open " << filename << " for saving.\n";
        return;
    }

    for (size_t i = 0; i < students.size(); i++) {
        file << students[i].toFileString() << endl;
    }
    file.close();
}
