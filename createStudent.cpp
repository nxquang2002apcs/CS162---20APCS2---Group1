#include "DataStructure.h"

void inputListOfStudent(int &sizeOfStudent, Student* &student){
    cout <<"Pls input your number of student: ";    //Khởi tạo số lượng học sinh
    cin >> sizeOfStudent;                              

    student = new Student[sizeOfStudent];           //Khởi tạo mảng động

    for(int i = 0; i < sizeOfStudent; ++i){

        cout <<"Student "<<i+1<<": " <<endl;        //Thứ tự nhập

        cout <<"Pls input your number in class: ";  //Nhập số thứ tự 
        cin >> student[i].no;
        fflush(stdin);

        cout <<"Pls input your Student ID: ";       //Nhập MSSV
        getline(cin, student[i].SID);
        fflush(stdin);
        
        cout <<"Pls input your First name: ";       //Nhập firstname 
        getline(cin, student[i].firstName);
        fflush(stdin);

        cout <<"Pls input your Last name: ";        //Nhập lastname
        getline(cin, student[i].lastName);
        fflush(stdin);

        cout <<"Pls input your Gender: ";           //Nhập giới tính
        getline(cin, student[i].gender);
        fflush(stdin);

        cout <<"Pls input your Date of Birth: ";    //Nhập ngày sinh
        getline(cin, student[i].DateOfBirth);
        fflush(stdin);

        cout <<"Pls input your Social ID: ";        //Nhập CMND
        getline(cin, student[i].socialID);
        fflush(stdin);

    }

    delete [] student;
}


