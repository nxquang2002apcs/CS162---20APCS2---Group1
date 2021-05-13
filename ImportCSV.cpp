#include "DataStructure.h"


void input_list_of_students_from_CSV(string path, Student*& ListStudent, int& size) {
    
    ifstream in;
    in.open(path);
    if (!in.is_open()) {
        cout << "Could not open file";
        return;
    }
    else {
        int i = 0;
        while (!in.eof()) {
            ListStudent[i].no = i + 1;
            size++;
            getline(in, ListStudent[i].firstName, ',');
            getline(in, ListStudent[i].lastName, ',');
            getline(in, ListStudent[i].SID, ',');
            getline(in, ListStudent[i].className, ',');
            getline(in, ListStudent[i].gender, ',');
            getline(in, ListStudent[i].socialID, ',');
            string data;
            getline(in, data, '/');
            ListStudent[i].DateOfBirth.day = stoi(data);
            getline(in, data, '/');
            ListStudent[i].DateOfBirth.month = stoi(data);
            getline(in, data, ',');
            ListStudent[i].DateOfBirth.year = stoi(data);
            getline(in, data, ',');
            ListStudent[i].FirstYear = stoi(data);
            getline(in, data, '\n');
            ListStudent[i].gpa = stof(data);
            i++;
        }
        in.close();
    }
    size -= 1;
};

void input_list_of_course_from_CSV(string path, Semester curSemester) {
    ifstream in;
    in.open(path);
    if (!in.is_open()) {
        cout << "Cannot open file!" << endl;
        return;
    }
    else {

    }
}