STUDENT RECORD MANAGEMENT SYSTEM
=================================
DSA Course Project | Team of 5 | B.Tech CSE, 5th Semester

HOW TO COMPILE
--------------
Open a terminal in this folder and run:

    g++ -std=c++17 -o srms main.cpp Student.cpp StudentManager.cpp Authentication.cpp FileManager.cpp

HOW TO RUN
----------
    ./srms        (Linux/Mac)
    srms.exe      (Windows)

FIRST RUN
---------
On the very first run, the program automatically creates login.txt
with a default admin account:
    Username: admin
    Password: admin123

students.txt is also created automatically as soon as you add your
first student record. Both files live in the same folder as the
program and are loaded automatically every time you start it.

FILES
-----
Student.h / Student.cpp             -> Student class (Member 1)
StudentManager.h / StudentManager.cpp -> Add/Search/Sort/Dashboard (Members 1-4)
Authentication.h / Authentication.cpp -> Login system (Member 5)
FileManager.h / FileManager.cpp       -> File I/O (Member 5)
main.cpp                              -> Menu integration (Member 5)
