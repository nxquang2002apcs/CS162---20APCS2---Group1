#include "DataStructure.h"

// Input a list of students's info
void inputListOfStudent(int& sizeOfStudent, Student*& student){
    cout <<"Please input the number of students: ";    //Create the number of students
    cin >> sizeOfStudent;                              

    Student* pCur = nullptr;
    for(int i = 1; i <= sizeOfStudent; ++i) {
        if(!student){
            student = new Student;
            pCur = student;
            pCur->pPrev = nullptr;
        }else{
            pCur->pNext = new Student;
            pCur->pNext->pPrev = pCur;
            pCur = pCur->pNext;
        }

        // Enter the infomation:
        cout <<"Student "<<i<<": " <<endl;

        cout <<"Please input your number in class: ";  //No
        cin >> pCur->no;
        fflush(stdin);

        cout <<"Please input your Student ID: ";       //SID
        getline(cin, pCur->SID);
        fflush(stdin);
        
        cout <<"Please input your First name: ";       //Firstname 
        getline(cin, pCur->firstName);
        fflush(stdin);

        cout <<"Please input your Last name: ";        //Lastname
        getline(cin, pCur->lastName);
        fflush(stdin);

        cout <<"Please input your Gender: ";           //Gender 
        getline(cin, pCur->gender);
        fflush(stdin);

        cout <<"Please input your Date of Birth: ";    //DateOfBirth
        cout <<"Day:";      cin >> pCur->DateOfBirth.day;
        cout <<"Month: ";   cin >> pCur->DateOfBirth.month;
        cout <<"Year: ";    cin >> pCur->DateOfBirth.year;

        cout <<"Please input your Social ID: ";        //socialID
        getline(cin, pCur->socialID);
        fflush(stdin);

        pCur->pNext = nullptr;                                                     
    }
}


// Update course detail
void update_course_detail(CourseDetail*& HeadCourse, string courseID){
    int check = 1;  //check whether user wants to update more ?
    while(check){
        // Searching course
        CourseDetail* pCur;
        do {
            pCur = HeadCourse;
            fflush(stdin);
            cout << "Enter a course ID you want to update: ";
            getline(cin, courseID);
            fflush(stdin);
            while(pCur && pCur->courseID != courseID)
                pCur = pCur->pNext;
            if(!pCur) cout <<"Sorry, we can not find this course. Please try again\n";
        } while (!pCur);

        cout <<"*------------------------------------------------------------*\n";
        cout <<"\t\tWHAT WOULD YOU LIKE TO UPDATE?\n";
        cout <<"*------------------------------------------------------------*\n";
        cout <<"\t1. Course ID\t\t" << "2. Course's name\n";
        cout <<"\t3. Teacher's name\t" << "4. Credit\n";
        cout <<"\t5. Session 1\t\t" << "6. Session 2\n";
        cout <<"\t\t7. Number of student\n";

        // Choose something to update
        int choose;
        do {
            cout <<"Choose: ";
            cin >> choose;
            if(choose < 1 || choose > 7) cout <<"Error. Please try again\n";
        } while (choose < 1 || choose > 7);
        
        CourseDetail* Cur = HeadCourse;
        switch (choose){
            case 1:{    // Course ID 
                do{
                    Cur = HeadCourse;
                    string courseId;
                    fflush(stdin);
                    cout <<"New course ID: ";
                    getline(cin, courseId);
                    fflush(stdin);
                    while(Cur != nullptr && Cur->courseID != courseId){
                        Cur = Cur->pNext;
                    }
                    if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                    else pCur->courseID = courseId;
                } while(Cur);
                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            case 2:{    // Course's name
                do{
                    Cur = HeadCourse;
                    string courseName;
                    fflush(stdin);
                    cout <<"New course name: ";
                    getline(cin,courseName);
                    fflush(stdin);
                    while(Cur != nullptr && Cur->courseName != courseName){
                        Cur = Cur->pNext;
                    }
                    if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                    else pCur->courseName = courseName;
                } while(Cur);
                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            case 3:{    // Teacher's name
                do{
                    Cur = HeadCourse;
                    string teacherName;
                    fflush(stdin);
                    cout <<"New teacher name: ";
                    getline(cin, teacherName);
                    fflush(stdin);
                    while(Cur != nullptr && Cur->teacherName != teacherName){
                        Cur = Cur->pNext;
                    }
                    if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                    else pCur->teacherName = teacherName;
                } while(Cur);
                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            case 4:{    // session1
                do{
                    Cur = HeadCourse;
                    int credits;
                    cout <<"New credit: ";
                    cin >> credits;
                    while(Cur != nullptr && Cur->credits != credits){
                        Cur = Cur->pNext;
                    }
                    if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                    else pCur->teacherName = credits;
                } while(Cur);
                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            case 5:{    // session1
                do{
                    Cur = HeadCourse;
                    string session1;
                    fflush(stdin);
                    cout <<"New session1: ";
                    getline(cin, session1);
                    fflush(stdin);
                    while(Cur != nullptr && Cur->session1 != session1){
                        Cur = Cur->pNext;
                    }
                    if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                    else pCur->session1 = session1;
                } while(Cur);
                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            case 6:{    // session2
                do{
                    Cur = HeadCourse;
                    string session2;
                    fflush(stdin);
                    cout <<"New session2: ";
                    getline(cin, session2);
                    fflush(stdin);
                    while(Cur != nullptr && Cur->session2 != session2){
                        Cur = Cur->pNext;
                    }
                    if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                    else pCur->session2 = session2;
                } while(Cur);
                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            case 7:{    // numberStudent  
                do{
                    Cur = HeadCourse;
                    int numberStudent;
                    cout <<"New number of student: ";
                    cin >> numberStudent;
                    while(Cur != nullptr && Cur->numberStudent != numberStudent){
                        Cur = Cur->pNext;
                    }
                    if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                    else pCur->session2 = numberStudent;
                } while(Cur);
                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

        }
        // User wants to update more?
        do {
            cout <<"Do you want to update anything more?\n";
            cout <<"0. NO\t\t" <<"1. YES\n";
            cout <<"Choose: ";
            cin >> check;
            if(check != 0 && check != 1) cout <<"Unidentified. Please try again\n";
        } while(check != 0 && check != 1);
    }
    
}		

//Delete the course
void delete_a_course_in_the_list(CourseDetail*& HeadCourse, string courseID){
    int check = 1;
    while(check){
        // Searching course
        CourseDetail* pCur;
        do {
            pCur = HeadCourse;
            fflush(stdin);
            cout << "Enter a course ID you want to delete: ";
            getline(cin, courseID);
            fflush(stdin);
            while(pCur && pCur->courseID != courseID)
                pCur = pCur->pNext;
            if(!pCur) cout <<"Sorry, we can not find this course. Please try again\n";
        } while (!pCur);
        
        // Delete course
        if(!pCur) return; 
        if(pCur->pNext) pCur->pNext->pPrev = pCur->pPrev;
        if(pCur->pPrev) pCur->pPrev->pNext = pCur->pNext;
        else HeadCourse = pCur->pNext;
        delete pCur;
        cout <<"DELETE SUCCESSFULLY\n";

        // Ask user wants to delete more
        do {
            cout <<"Do you want to delete any course more?\n";
            cout <<"0. NO\t\t" <<"1. YES\n";
            cout <<"Choose: ";
            cin >> check;
            if(check != 0 && check != 1) cout <<"Unidentified. Please try again\n";
        } while(check != 0 && check != 1);    
    }
}




//----------------------------- USE TO TEST ---------------------------------------------

// void inputListOfCourse(int& size, CourseDetail* &HeadCourse){
//     cout <<"Please input the number of courses: ";    //Create the number of students
//     cin >> size;                              

//     CourseDetail* pCur = nullptr;
//     for(int i = 1; i <= size; ++i) {
//         if(!HeadCourse){
//             HeadCourse = new CourseDetail;
//             pCur = HeadCourse;
//             pCur->pPrev = nullptr;
//         }else{
//             pCur->pNext = new CourseDetail;
//             pCur->pNext->pPrev = pCur;
//             pCur = pCur->pNext;
//         }

//         // Enter the infomation:
//         cout <<"Course "<<i<<": " <<endl;

//         fflush(stdin);
//         cout <<"Please input courseID: ";  //No
//         getline(cin, pCur->courseID);
//         fflush(stdin);

//         cout <<"Please input courseName: ";       //SID
//         getline(cin, pCur->courseName);
//         fflush(stdin);
        
//         cout <<"Please input teacherName: ";       //Firstname 
//         getline(cin, pCur->teacherName);
//         fflush(stdin);

//         cout <<"Please input credits: ";        //Lastname
//         cin >> pCur->credits;
//         fflush(stdin);

//         cout <<"Please input session1: ";           //Gender 
//         getline(cin, pCur->session1);
//         fflush(stdin);

//         cout <<"Please input session2: ";    //DateOfBirth
//         getline(cin, pCur->session2);
//         fflush(stdin);

//         cout <<"Please input Number of student: ";    //DateOfBirth
//         cin >> pCur->numberStudent;
//         fflush(stdin);

//         cout <<"Please input Enrolled student: ";    //enrolledStudent
//         cin >> pCur->enrolledStudent;
        
//         pCur->pNext = nullptr;                                                     
//     }
// }

// int main(){
//     CourseDetail* HeadCourse = nullptr;
//     int size;
//     inputListOfCourse(size, HeadCourse);

//     string courseID;
//     delete_a_course_in_the_list(HeadCourse, courseID);
//     update_course_detail(HeadCourse, courseID);

//     return 0;
// }