#include "DataStructure.h"


void inputCSV(string path, Student* ListStudent, int& size) {
    
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
            getline(in, ListStudent[i].SID, ',');
            getline(in, ListStudent[i].firstName, ',');
            getline(in, ListStudent[i].lastName, ',');
            getline(in, ListStudent[i].gender, ',');
            getline(in, ListStudent[i].socialID, ',');
            getline(in, ListStudent[i].DateOfBirth, '\n');
            i++;
        }
        in.close();
    }
    size -= 1;
};
