#include "StudentManager.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

StudentManager::StudentManager(string filename) {
    dataFile = filename;
    nextIDNumber = 1;
}

void StudentManager::loadRecords() {
    FileManager::loadStudents(students, dataFile);

    for (size_t i = 0; i < students.size(); i++) {
        string id = students[i].getStudentID();
        if (id.size() > 2) {
            int num = stoi(id.substr(2));
            if (num >= nextIDNumber) nextIDNumber = num + 1;
        }
    }
    cout << "[Info] " << students.size() << " student record(s) loaded from " << dataFile << ".\n";
}

void StudentManager::saveRecords() {
    FileManager::saveStudents(students, dataFile);
    cout << "[Info] Records saved to " << dataFile << ".\n";
}

string StudentManager::generateNextID() {
    stringstream ss;
    ss << "ST" << setfill('0') << setw(4) << nextIDNumber;
    nextIDNumber++;
    return ss.str();
}

void StudentManager::addStudent() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name, gender, dob, father, mother, dept, course, phone, email;
    int sem;
    double attendance;

    cout << "\n----- Add New Student -----\n";
    cout << "Full Name          : "; getline(cin, name);
    cout << "Gender             : "; getline(cin, gender);
    cout << "Date of Birth (DD-MM-YYYY): "; getline(cin, dob);
    cout << "Father's Name      : "; getline(cin, father);
    cout << "Mother's Name      : "; getline(cin, mother);
    cout << "Department         : "; getline(cin, dept);
    cout << "Course             : "; getline(cin, course);
    cout << "Current Semester   : "; cin >> sem;
    cout << "Phone Number       : "; cin >> phone;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Email              : "; getline(cin, email);
    cout << "Attendance %       : "; cin >> attendance;

    string newID = generateNextID();
    Student newStudent(newID, name, gender, dob, father, mother, dept, course, sem, phone, email, attendance);

    cout << "\nDo you want to enter semester-wise GPA history now? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        for (int s = 1; s <= sem; s++) {
            SemesterRecord rec;
            rec.semesterNumber = s;
            cout << "  Semester " << s << " GPA        : "; cin >> rec.gpa;
            cout << "  Semester " << s << " Percentage : "; cin >> rec.percentage;
            cout << "  Semester " << s << " Grade      : "; cin >> rec.grade;
            newStudent.addSemesterRecord(rec);
        }
    }

    students.push_back(newStudent);
    saveRecords();

    cout << "\nStudent added successfully with ID: " << newID << endl;
}

void StudentManager::updateStudent() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string id;
    cout << "\nEnter Student ID to update: ";
    getline(cin, id);

    int index = -1;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getStudentID() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Student ID not found.\n";
        return;
    }

    Student& s = students[index];
    cout << "Leave blank and press Enter to keep the current value.\n";

    cout << "Full Name [" << s.getFullName() << "]: ";
    string temp;
    getline(cin, temp);
    if (!temp.empty()) s.setFullName(temp);

    cout << "Department [" << s.getDepartment() << "]: ";
    getline(cin, temp);
    if (!temp.empty()) s.setDepartment(temp);

    cout << "Current Semester [" << s.getCurrentSemester() << "]: ";
    getline(cin, temp);
    if (!temp.empty()) s.setCurrentSemester(stoi(temp));

    cout << "Phone Number [" << s.getPhoneNumber() << "]: ";
    getline(cin, temp);
    if (!temp.empty()) s.setPhoneNumber(temp);

    cout << "Email [" << s.getEmail() << "]: ";
    getline(cin, temp);
    if (!temp.empty()) s.setEmail(temp);

    cout << "Attendance % [" << s.getAttendance() << "]: ";
    getline(cin, temp);
    if (!temp.empty()) s.setAttendance(stod(temp));

    cout << "Add a new semester GPA record? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        SemesterRecord rec;
        cout << "  Semester Number : "; cin >> rec.semesterNumber;
        cout << "  GPA             : "; cin >> rec.gpa;
        cout << "  Percentage      : "; cin >> rec.percentage;
        cout << "  Grade           : "; cin >> rec.grade;
        s.addSemesterRecord(rec);
    }

    saveRecords();
    cout << "Student record updated successfully.\n";
}

void StudentManager::deleteStudent() {
    string id;
    cout << "\nEnter Student ID to delete: ";
    cin >> id;

    int index = -1;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getStudentID() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Student ID not found.\n";
        return;
    }

    cout << "Are you sure you want to delete " << students[index].getFullName() << "? (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        students.erase(students.begin() + index);
        saveRecords();
        cout << "Student record deleted successfully.\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

void StudentManager::searchByID() {
    string id;
    cout << "\nEnter Student ID: ";
    cin >> id;

    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getStudentID() == id) {
            students[i].displayDetailed();
            return;
        }
    }
    cout << "No student found with ID " << id << ".\n";
}

void StudentManager::searchByName() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    cout << "\nEnter Student Name: ";
    getline(cin, name);

    bool found = false;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getFullName() == name) {
            students[i].displayDetailed();
            found = true;
        }
    }
    if (!found) cout << "No student found with name \"" << name << "\".\n";
}

void StudentManager::searchByDOB() {
    string dob;
    cout << "\nEnter Date of Birth (DD-MM-YYYY): ";
    cin >> dob;

    bool found = false;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getDOB() == dob) {
            students[i].displayDetailed();
            found = true;
        }
    }
    if (!found) cout << "No student found with DOB " << dob << ".\n";
}

void StudentManager::binarySearchByID() {
    if (students.empty()) {
        cout << "No records to search.\n";
        return;
    }

    mergeSort(students, 0, students.size() - 1,
              [](const Student& a, const Student& b) { return a.getStudentID() < b.getStudentID(); });

    string id;
    cout << "\nEnter Student ID: ";
    cin >> id;

    int low = 0, high = students.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        string midID = students[mid].getStudentID();

        if (midID == id) {
            students[mid].displayDetailed();
            return;
        } else if (midID < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << "No student found with ID " << id << ".\n";
}

void StudentManager::displayAll() {
    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n" << left << setw(10) << "ID" << setw(22) << "Name"
         << setw(10) << "Dept" << setw(6) << "Sem" << setw(10) << "CGPA" << endl;
    cout << string(58, '-') << endl;

    for (size_t i = 0; i < students.size(); i++) {
        students[i].displayShort();
    }
    cout << "\nTotal Students: " << students.size() << endl;
}

void StudentManager::merge(vector<Student>& arr, int left, int mid, int right,
                           const function<bool(const Student&, const Student&)>& comesBefore) {
    vector<Student> leftPart(arr.begin() + left, arr.begin() + mid + 1);
    vector<Student> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < leftPart.size() && j < rightPart.size()) {
        if (!comesBefore(rightPart[j], leftPart[i])) {
            arr[k++] = leftPart[i++];
        } else {
            arr[k++] = rightPart[j++];
        }
    }
    while (i < leftPart.size()) arr[k++] = leftPart[i++];
    while (j < rightPart.size()) arr[k++] = rightPart[j++];
}

void StudentManager::mergeSort(vector<Student>& arr, int left, int right,
                               const function<bool(const Student&, const Student&)>& comesBefore) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, comesBefore);
    mergeSort(arr, mid + 1, right, comesBefore);
    merge(arr, left, mid, right, comesBefore);
}

void StudentManager::sortMenu() {
    if (students.empty()) {
        cout << "No records to sort.\n";
        return;
    }

    cout << "\n----- Sort Students -----\n";
    cout << "1. Sort by Student ID\n";
    cout << "2. Sort by Name\n";
    cout << "3. Sort by CGPA (Highest first)\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            mergeSort(students, 0, students.size() - 1,
                      [](const Student& a, const Student& b) { return a.getStudentID() < b.getStudentID(); });
            cout << "Sorted by Student ID.\n";
            break;
        case 2:
            mergeSort(students, 0, students.size() - 1,
                      [](const Student& a, const Student& b) { return a.getFullName() < b.getFullName(); });
            cout << "Sorted by Name.\n";
            break;
        case 3:
            mergeSort(students, 0, students.size() - 1,
                      [](const Student& a, const Student& b) { return a.calculateCGPA() > b.calculateCGPA(); });
            cout << "Sorted by CGPA (highest first).\n";
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    saveRecords();
    displayAll();
}

void StudentManager::showDashboard() {
    if (students.empty()) {
        cout << "\nNo data available for dashboard.\n";
        return;
    }

    double highest = students[0].calculateCGPA();
    double lowest = students[0].calculateCGPA();
    double total = 0.0;

    for (size_t i = 0; i < students.size(); i++) {
        double cgpa = students[i].calculateCGPA();
        total += cgpa;
        if (cgpa > highest) highest = cgpa;
        if (cgpa < lowest) lowest = cgpa;
    }

    double average = total / students.size();

    cout << "\n============ DASHBOARD ============\n";
    cout << "Total Students   : " << students.size() << endl;
    cout << fixed << setprecision(2);
    cout << "Highest CGPA     : " << highest << endl;
    cout << "Lowest CGPA      : " << lowest << endl;
    cout << "Average CGPA     : " << average << endl;
    cout << "====================================\n";
}

int StudentManager::getTotalStudents() const {
    return students.size();
}
