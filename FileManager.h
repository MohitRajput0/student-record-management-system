#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "Student.h"
using namespace std;

class FileManager {
public:
    static void loadStudents(vector<Student>& students, const string& filename);

    static void saveStudents(const vector<Student>& students, const string& filename);
};

#endif
