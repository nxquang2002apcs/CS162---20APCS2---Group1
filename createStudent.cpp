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
//Thay d?i thông tin c?a sv
void update_student_profile(Student*& HeadStudent, Student*& student) {
	int check = 1;
	string studentID;
	cout << "*------------------------------------------------------------*\n";
	cout << "\t\tWHAT WOULD YOU LIKE TO UPDATE?\n";
	cout << "*------------------------------------------------------------*\n";
	cout << "\t1. Student's ID" << "2. First name\n";
	cout << "\t3. Last name\t\t" << "4. Gender\n";
	cout << "\t5. Social ID\t\t" << "6. Date of birth\n";
	while (check) {

		int staff;
		cout << "User: ";
		cin >> staff;
		while (staff < 1 || staff > 10) {
			cout << "Invalid input! Please try again!" << endl;
			cout << "User: ";
			cin >> staff;
		}

		Student* Cur = HeadStudent;
		string data;
		switch (staff) {

			//Student ID
            case 1:
                do {
                    Cur = HeadStudent;
                    cin.get();
                    cout <<"The student ID before: " << student->SID<<endl;
                    cin.get();
                    cout << "New student ID: ";
                    getline(cin, data);
                    //fflush(stdin);
                    while (Cur != nullptr && Cur->SID != data) {
                        Cur = Cur->pNext;
                    }
                    if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
                    else{
                        int sure = 1;
                        cout <<"Are you sure?(1: sure, 0: not sure)\n";
                        cout <<"User: ";    cin >> sure;

                        if(sure){
                            student->SID = data;
                            cout << "CHANGE SUCCESSFULLY\n";
                        }
                    }
                } while (Cur);

                break;

            // Firstname
            case 2: 
                cin.get();
                cout <<"The first name before: " << student->firstName <<endl;
                cin.get();
                cout << "New first name: ";
                getline(cin, data);
                
                int sure = 1;
                cout <<"Are you sure?(1: sure, 0: not sure)\n";
                cout <<"User: ";    cin >> sure;

                if(sure){
                    student->firstName = data;
                    cout << "CHANGE SUCCESSFULLY\n";
                }
                break;

            // Lastname
            case 3: 
                cin.get();
                cout <<"The last name before: " << student->lastName <<endl;
                cin.get();
                cout << "New last name: ";
                getline(cin, data);
                
                int sure = 1;
                cout <<"Are you sure?(1: sure, 0: not sure)\n";
                cout <<"User: ";    cin >> sure;

                if(sure){
                    student->firstName = data;
                    cout << "CHANGE SUCCESSFULLY\n";
                }
                break;
            
            // Gender
            case 4:
                cin.get();
                cout <<"The gender before: " << student->gender <<endl;
                cin.get();
                cout << "New gender: ";
                getline(cin, data);
                
                int sure = 1;
                cout <<"Are you sure?(1: sure, 0: not sure)\n";
                cout <<"User: ";    cin >> sure;

                if(sure){
                    student->firstName = data;
                    cout << "CHANGE SUCCESSFULLY\n";
                }
                break;

            
            // Social ID
            case 5:
                cin.get();
                cout <<"The social ID: " << student->socialID <<endl;
                cin.get();
                cout << "New social ID: ";
                getline(cin, data);

                int sure = 1;
                cout <<"Are you sure?(1: sure, 0: not sure)\n";
                cout <<"User: ";    cin >> sure;

                if(sure){
                    student->firstName = data;
                    cout << "CHANGE SUCCESSFULLY\n";
                }
                break;
            
            // Date of birth 
            case 6: 
            {
                cin.get();
                cout <<"The day of birth before: " <<student->DateOfBirth.day<<"/"<<student->DateOfBirth.month<<"/"<<student->DateOfBirth.year<<endl;
                cin.get();
                int day, month, year;
                cout << "New day of birth: ";
                cout << "Day: ";     cin >> day;
                cout << "Month: ";   cin >> month;
                cout << "Year: ";    cin >> year;

                int sure = 1;
                cout <<"Are you sure?(1: sure, 0: not sure)\n";
                cout <<"User: ";    cin >> sure;

                if(sure){
                    student->DateOfBirth.day = day;
                    student->DateOfBirth.month = month;
                    student->DateOfBirth.year = year;

                    cout << "CHANGE SUCCESSFULLY\n";
                }
                break;
            }

		}


		// User wants to update more?
		do {
			cout << "Do you want to update anything more?\n";
			cout << "0. NO\t\t" << "1. YES\n";
			cout << "Staff: ";
			cin >> check;
			if (check != 0 && check != 1) cout << "Invalid input. Please try again\n";
		} while (check != 0 && check != 1);

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
void update_student_profile(Student*& HeadStudent, Student*& student) {
    int check = 1;
    string studentID;
    cout << "*------------------------------------------------------------*\n";
    cout << "\t\tWHAT WOULD YOU LIKE TO UPDATE?\n";
    cout << "*------------------------------------------------------------*\n";
    cout << "\t1. Student's ID" << "2. First name\n";
    cout << "\t3. Last name\t\t" << "4. Gender\n";
    cout << "\t5. Social ID\t\t" << "6. Date of birth\n";
    while (check) {

        int staff;
        cout << "User: ";
        cin >> staff;
        while (staff < 1 || staff > 10) {
            cout << "Invalid input! Please try again!" << endl;
            cout << "User: ";
            cin >> staff;
        }

        Student* Cur = HeadStudent;
        string data;
        switch (staff) {
            //Student ID
            case 1:
                do {
                    Cur = HeadStudent;
                    cin.get();
                    cout << "New student ID: ";
                    getline(cin, data);
                    //fflush(stdin);
                    while (Cur != nullptr && Cur->SID != data) {
                        Cur = Cur->pNext;
                    }
                    if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
                    else student->SID = data;
                } while (Cur);

                cout << "CHANGE SUCCESSFULLY\n";
                break;
            // Firstname
            case 2:
                cin.get();
                cout << "New first name: ";
                getline(cin, data);
                //fflush(stdin);

                student->firstName = data;

                cout << "CHANGE SUCCESSFULLY\n";
                break;
            // Lastname
            case 3:
                cin.get();
                cout << "New last name: ";
                getline(cin, data);
                //fflush(stdin);
                student->lastName = data;

                cout << "CHANGE SUCCESSFULLY\n";
                break;
            // Gender
            case 4:
                cin.get();
                cout << "New gender: ";
                getline(cin, data);
                //fflush(stdin);
                student->gender = data;
                cout << "CHANGE SUCCESSFULLY\n";
                break;
            // Social ID
            case 5:
                cin.get();
                cout << "New social ID: ";
                getline(cin, data);
                //fflush(stdin);
                student->socialID = data;

                cout << "CHANGE SUCCESSFULLY\n";
                break;
            // Date of birth 
            case 6:
            {
                cin.get();
                int day, month, year;
                cout << "New day of birth: ";
                cout << "Day: ";     cin >> day;
                cout << "Month: ";   cin >> month;
                cout << "Year: ";    cin >> year;

                student->DateOfBirth.day = day;
                student->DateOfBirth.month = month;
                student->DateOfBirth.year = year;

                cout << "CHANGE SUCCESSFULLY\n";
                break;
            }
        }


        // User wants to update more?
        do {
            cout << "Do you want to update anything more?\n";
            cout << "0. NO\t\t" << "1. YES\n";
            cout << "Staff: ";
            cin >> check;
            if (check != 0 && check != 1) cout << "Invalid input. Please try again\n";
        } while (check != 0 && check != 1);

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


// int main(){
//     Student* student = nullptr;
//     int size;
//     inputListOfStudent(size, student);
//     string courseID;
//     update_student_profile(student, student);

//     return 0;
// }