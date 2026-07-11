#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
using namespace std;

struct SemesterRecord {
    int semesterNumber;
    double gpa;
    double percentage;
    string grade;
};

class Student {
private:
    string studentID;
    string fullName;
    string gender;
    string dob;
    string fatherName;
    string motherName;
    string department;
    string course;
    int currentSemester;
    string phoneNumber;
    string email;
    double attendancePercentage;

    vector<SemesterRecord> academicHistory;

public:
    Student();
    Student(string id, string name, string gender, string dob, string father, string mother,
            string dept, string course, int sem, string phone, string email, double attendance);

    string getStudentID() const;
    string getFullName() const;
    string getGender() const;
    string getDOB() const;
    string getFatherName() const;
    string getMotherName() const;
    string getDepartment() const;
    string getCourse() const;
    int getCurrentSemester() const;
    string getPhoneNumber() const;
    string getEmail() const;
    double getAttendance() const;
    vector<SemesterRecord>& getAcademicHistory();

    void setStudentID(string id);
    void setFullName(string name);
    void setGender(string g);
    void setDOB(string d);
    void setFatherName(string f);
    void setMotherName(string m);
    void setDepartment(string d);
    void setCourse(string c);
    void setCurrentSemester(int sem);
    void setPhoneNumber(string p);
    void setEmail(string e);
    void setAttendance(double a);

    void addSemesterRecord(const SemesterRecord& record);
    double calculateCGPA() const;

    void displayShort() const;
    void displayDetailed() const;

    string toFileString() const;
    static Student fromFileString(const string& line);
};

#endif
