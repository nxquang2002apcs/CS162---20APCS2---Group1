#include "DataStructure.h"

void inputCSV(string path, Student** ListStudent) {
    ifstream in;
    in.open(path);
    if (!in.is_open())
        cout << "Could not open file";
    char line[1000];
    in.getline(line, 1000);
    int i = 1;
    while (in) {
        ListStudent[i - 1] = new Student;
        ListStudent[i-1]->no = i;
        ListStudent[i-1]->SID = strtok(line, ",");
        ListStudent[i-1]->firstName = strtok(NULL, ",");
        ListStudent[i-1]->lastName = strtok(NULL, ",");
        ListStudent[i-1]->gender = strtok(NULL, ",");
        ListStudent[i-1]->socialID = strtok(NULL, ",");
        ListStudent[i-1]->DateOfBirth = strtok(NULL, ",");
        in.getline(line, 1000);
        i++;
    }
    in.close();

};