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

        cout <<"Please input your class name: ";   // Class name
        getline(cin, pCur->className);
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

        cout <<"Please input your Date of Birth: \n";    //DateOfBirth
        cout <<"Day:";      cin >> pCur->DateOfBirth.day;
        cout <<"Month: ";   cin >> pCur->DateOfBirth.month;
        cout <<"Year: ";    cin >> pCur->DateOfBirth.year;

        fflush(stdin);
        cout <<"Please input your Social ID: ";        //socialID
        getline(cin, pCur->socialID);
        fflush(stdin);

        pCur->pNext = nullptr;                                                     
    }
}


// ---------------------------------Update course detail------------------------------------------
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

//-----------------------------Delete the course-------------------------------------------
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

//--------------------------------Display student ( chỉ dùng để test )-------------------------------------------------
void display_student(Student* student){
    while(student){
        cout <<"*-------------------------------------------*\n";
        cout <<"No:"<< student->no <<endl;
        cout <<"SID:"<< student->SID <<endl;
        cout <<"classname:"<< student->className <<endl;
        cout <<"firstname:"<< student-> firstName <<endl;
        cout <<"lastname:"<< student->lastName <<endl;
        cout <<"gender: "<< student->gender << endl;
        cout <<"social id: "<< student->socialID <<endl;
        cout <<"date:"<<student->DateOfBirth.day <<"/"<< student->DateOfBirth.month <<"/"<< student->DateOfBirth.year <<endl;
        student = student->pNext;
        cout <<"*-------------------------------------------*\n";
    }
}

//--------------------------------Update student profile--------------------------------------
void update_student_profile(Student*& student, string studentID){
    int check = 1;
    while(check){
        if(!student) cout <<"No student existed\n";

        //Tìm học sinh:
        Student* pCur;
        do {
            pCur = student;
            fflush(stdin);
            cout << "Enter a student ID you want to update: ";
            getline(cin, studentID);
            fflush(stdin);
            while(pCur && pCur->SID != studentID)
                pCur = pCur->pNext;
            if(!pCur) cout <<"Sorry, we can not find this student. Please try again\n";
        } while (!pCur);

        //If student exists, then show menu update
        cout <<"*------------------------------------------------------------*\n";
        cout <<"\t\tWHAT WOULD YOU LIKE TO UPDATE?\n";
        cout <<"*------------------------------------------------------------*\n";
        cout <<"\t1. No\t\t\t" << "2. Student's ID\n";
        cout <<"\t3. Class name\t\t" << "4. First name\n";
        cout <<"\t5. Last name\t\t" << "6. Gender\n";
        cout <<"\t7. Social ID\t\t" << "8. Date of birth\n";

        
        int staff;
        do {
            cout <<"Staff: ";
            cin >> staff;
            if(staff < 1 || staff > 10) cout <<"Error. Please try again\n";
        } while (staff < 1 || staff > 10);

        Student* Cur = student;
        switch (staff){
            // No
            case 1:{ 
                do{
                    Cur = student;
                    int No;
                    cout <<"New number in class: ";
                    cin >> No;
                    while(Cur != nullptr && Cur->no != No){
                        Cur = Cur->pNext;
                    }
                    if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                    else pCur->no = No;
                } while(Cur);

                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            //Student ID
            case 2:{    
                do{
                Cur = student;
                string SID;
                fflush(stdin);
                cout <<"New student ID: ";
                getline(cin, SID);
                fflush(stdin);
                while(Cur != nullptr && Cur->SID != SID){
                    Cur = Cur->pNext;
                }
                if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                else pCur->SID = SID;
                } while(Cur);

                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            //Class name:
            case 3:{    
                do{
                Cur = student;
                string className;
                fflush(stdin);
                cout <<"New class name: ";
                getline(cin, className);
                fflush(stdin);
                while(Cur != nullptr && Cur->className != className){
                    Cur = Cur->pNext;
                }
                if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                else pCur->className = className;
                } while(Cur);

                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }   

            // Firstname
            case 4:{    
                do{
                Cur = student;
                string firstName;
                fflush(stdin);
                cout <<"New first name: ";
                getline(cin, firstName);
                fflush(stdin);
                while(Cur != nullptr && Cur->firstName != firstName){
                    Cur = Cur->pNext;
                }
                if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                else pCur->firstName = firstName;
                } while(Cur);

                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            // Lastname
            case 5:{    
                do{
                Cur = student;
                string lastName;
                fflush(stdin);
                cout <<"New last name: ";
                getline(cin, lastName);
                fflush(stdin);
                while(Cur != nullptr && Cur->lastName != lastName){
                    Cur = Cur->pNext;
                }
                if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                else pCur->lastName = lastName;
                } while(Cur);

                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            // Gender
            case 6:{    
                do{
                Cur = student;
                string gender;
                fflush(stdin);
                cout <<"New gender: ";
                getline(cin, gender);
                fflush(stdin);
                while(Cur != nullptr && Cur->gender != gender){
                    Cur = Cur->pNext;
                }
                if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                else pCur->gender = gender;
                } while(Cur);

                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            // Social ID
            case 7:{    
                do{
                Cur = student;
                string socialID;
                fflush(stdin);
                cout <<"New social ID: ";
                getline(cin, socialID);
                fflush(stdin);
                while(Cur != nullptr && Cur->socialID != socialID){
                    Cur = Cur->pNext;
                }
                if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                else pCur->socialID = socialID;
                } while(Cur);

                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

            // Date of birth 
            case 8:{    
                do{
                Cur = student;
                int day, month, year;
                cout <<"New day of birth: ";
                cout <<"Day: ";     cin >> day;
                cout <<"Month: ";   cin >> month;
                cout <<"Year: ";    cin >> year;
                while(Cur != nullptr && (Cur->DateOfBirth.day != day || Cur->DateOfBirth.month != month || Cur->DateOfBirth.year != year)){
                    Cur = Cur->pNext;
                }
                if(Cur != nullptr) cout <<"This new one is duplicated. Please try again\n";
                else{
                    pCur->DateOfBirth.day = day;
                    pCur->DateOfBirth.month = month;
                    pCur->DateOfBirth.year = year;

                }
                } while(Cur);

                cout <<"CHANGE SUCCESSFULLY\n";
                break;
            }

        }

        //--------- Chỉ dùng để test ------
        display_student(student);
        //---------------------------------

        // User wants to update more?
        do {
            cout <<"Do you want to update anything more?\n";
            cout <<"0. NO\t\t" <<"1. YES\n";
            cout <<"Staff: ";
            cin >> check;
            if(check != 0 && check != 1) cout <<"Unidentified. Please try again\n";
        } while(check != 0 && check != 1);

    }

}

//----------------------------- USE TO TEST ( Cũ )---------------------------------------------

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


int main(){
    Student* student = nullptr;
    int size;
    inputListOfStudent(size, student);
    string courseID;
    update_student_profile(student, courseID);

    return 0;
}