#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <vector>
#include <string>
#include <functional>
#include "Student.h"
using namespace std;

class StudentManager {
private:
    vector<Student> students;
    string dataFile;
    int nextIDNumber;

    string generateNextID();

    void mergeSort(vector<Student>& arr, int left, int right,
                   const function<bool(const Student&, const Student&)>& comesBefore);
    void merge(vector<Student>& arr, int left, int mid, int right,
               const function<bool(const Student&, const Student&)>& comesBefore);

public:
    StudentManager(string filename = "students.txt");

    void loadRecords();
    void saveRecords();

    void addStudent();

    void updateStudent();
    void deleteStudent();

    void searchByID();
    void searchByName();
    void searchByDOB();
    void binarySearchByID();
    void displayAll();

    void sortMenu();
    void showDashboard();

    int getTotalStudents() const;
};

#endif
