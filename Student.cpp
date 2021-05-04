#include "DataStructure.h"


void view_my_profile(Student*& student);
// Đi tới danh sách những môn đã đăng ký
void go_to_my_enrolled_course(Student*& student);
// Hàm xem scoreboard của student
void view_scoreboard_of_student(Student* student)
{
	if (student->Head_of_enrolled_course == nullptr) {
		cout << "No enrolled course!" << endl;
		return;
	}

	cout << "   " << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Lecturer Name";
	cout << "Number of credits   ";
	cout << setw(15) << "Session 1  ";
	cout << setw(12) << "Session 2";
	cout << setw(9) << left << "Midterm";
	cout << setw(7) << left << "Final";
	cout << setw(12) << left << "Other mark";
	cout << "Course's GPA" << endl;

	CourseForEachStudent* Head_course = student->Head_of_enrolled_course;

	while (Head_course)
	{
		cout << Head_course->numberCourse << ". ";
		cout << setw(12) << left << Head_course->detail.courseID;
		cout << setw(35) << left << Head_course->detail.courseName;
		cout << setw(17) << left << Head_course->detail.teacherName;
		cout << setw(13) << right << Head_course->detail.credits;
		cout << setw(15) << right << Head_course->detail.session1;
		cout << setw(15) << right << Head_course->detail.session2;
		cout << setw(9) << right << " ";  print(Head_course->midterm);
		cout << setw(5) << right << " "; print(Head_course->final);
		cout << setw(6) << right << " "; print(Head_course->otherMark);
		cout << setw(11) << left << " "; print(Head_course->courseGPA);

		Head_course = Head_course->pNext;

		cout << endl;
	}
}

//Tìm đến sinh viên có ID trùng với mật khẩu đăng nhập
Student* findStudent(string studentID) {
	Class* tempClass = CurrentYear->HeadClass;
	Student* tempStudent = nullptr;
	while (tempClass != nullptr) {
		tempStudent = tempClass->HeadStudent;
		while (tempStudent != nullptr && tempStudent->SID != studentID)
			tempStudent = tempStudent->pNext;

		if (tempStudent == nullptr) {
			tempClass = tempClass->pNext;
		}
		else return tempStudent;
	}
	return nullptr;
}

void StudentInterface(string studentID) {

	Student* user = findStudent(studentID);            //Người dùng là sv có SID trùng với mật khẩu đăng nhập
	if (user == nullptr) {
		cout << "Your profile is not available in database!" << endl;
		return;
	}

	int choice = 0;
	while (true) {
		system("cls");
		cout << user->className << " >> " << user->firstName << " " << user->lastName << endl;
		cout << "-----------------------------" << endl;
		cout << endl;
		if (Available_register == true) {
			cout << "***NOTFICATION***" << endl;
			cout << "Course registration is active now! You can enroll new courses by choosing OPTION 3." << endl;
			cout << endl;
		}
		if (Available_all_scoreboard == true) {
			cout << "***NOTFICATION***" << endl;
			cout << "Scoreboard is available now! You can view your scoreboard by choosing OPTION 3." << endl;
			cout << endl;
		}

		cout << "1. View my profile" << endl;
		cout << "2. My list of courses" << endl;
		if (Available_register == true) {
			cout << "3. Enroll new courses" << endl;
		}
		else if(Available_all_scoreboard == true)
			cout << "3. View my scoreboard" << endl;
		cout << "4. Change password" << endl;
		cout << "5. Log out" << endl;
		cout << "6. Exit program" << endl;
		cout << "User: ";
		cin >> choice;

		switch (choice) {
		case 1:
			view_my_profile(user);
			break;
		case 2:
			go_to_my_enrolled_course(user);
			break;
		case 3:
			if (Available_register == true) {
				system("cls");
				enroll_a_course(user, CurrentSemester->HeadCourse);
			}
			else if (Available_all_scoreboard == true) {
				view_scoreboard_of_student(user);
			}
			break;
		case 4:
			
			break;
		case 5:
			cin.get();
			return;
		case 6:
			cout << endl;
			cout << "THANK YOU FOR USING OUR PROGRAM!" << endl;
			_getch();
			delete_everything();
			exit(0);
		default: 
			cout << "Invalid input! Please try again!";
			_getch();
			break;
		}
	}
}

void view_my_profile(Student*& student) {
	int choice = 0;
	while (true) {
		system("cls");
		
		cout << student->className << " >> " << student->SID << " " << student->firstName << " " << student->lastName << endl;
		cout << "---------------------------------" << endl;
		cout << "Full name: " << student->firstName << " " << student->lastName << endl;
		cout << "SID: " << student->SID << endl;
		cout << "Class: " << student->className << endl;
		cout << "School Year: " << CurrentYear->startYear << "-" << CurrentYear->endYear << endl;
		cout << "Gender: " << student->gender << endl;
		cout << "Date of Birth: " << student->DateOfBirth.day << "/" << student->DateOfBirth.month << "/" << student->DateOfBirth.year << endl;
		cout << "Social ID: " << student->socialID << endl;
		cout << "---------------------------------" << endl;

		cout << endl;
		cout << "0. Return menu" << endl;
		cout << "User: ";
		cin >> choice;
		while (choice != 0) {
			cout << "Invalid input! Please try again!" << endl;
			cout << "User: ";
			cin >> choice;
		}
		return;
	}
}

void go_to_my_enrolled_course(Student*& student) {
	int choice = 0;
	while (true) {
		system("cls");
		cout << student->className << " >> " << student->SID << " >> " << "My enrolled courses" << endl;
		cout << "------------------------------------------" << endl;
		cout << "List of courses: " << endl;
		view_list_of_enrolled_course(student);
		cout << endl;
		
		if (Available_register == true) {
			cout << "***NOTIFICATION***" << endl;
			cout << "Course registration is available now! You can enroll new courses by choose option 1" << endl;
			cout << endl;
		}

		cout << "0. Return menu" << endl;
		if (Available_register) {
			cout << "1. Enroll new courses" << endl;
			cout << "2. Remove courses" << endl;
		}
		cout << "User: ";
		cin >> choice;

		switch (choice) {
		case 0:
			return;
		case 1:
			if (Available_register) {
				system("cls");
				enroll_a_course(student, CurrentSemester->HeadCourse);
			}
			break;
		case 2:
			if (Available_register) {

			}
			break;
		}
	}
}



//hàm check có bị trùng lịch học không
bool check(Student* student, string ses1, string ses2) {

	if (student->Head_of_enrolled_course == nullptr)
		return true;

	CourseForEachStudent* tmp = student->Head_of_enrolled_course;

	while (tmp) {
		//so sánh string
		if (tmp->detail.session1.compare(ses1) == 0 || tmp->detail.session2.compare(ses2) == 0)
			return false;
		tmp = tmp->pNext;
	}
	return true;
}

void enroll_a_course(Student*& student, CourseDetail*& enrolledCourse) {

	int numberDefaultCourse = 5;
	//node chạy course system
	CourseDetail* tmpCourse = enrolledCourse;

	//Node chạy danh sách sinh viên khóa học
	Student_CourseScores* tmpCourseList = enrolledCourse->HeadStudent;

	//Node chạy của course mỗi sinh viên
	CourseForEachStudent* tmpEach = student->Head_of_enrolled_course;

	//Hiển thị danh sách khóa học cho sinh viên đăng kí
	view_list_of_courses(CurrentSemester);

	int i = 0;
	do {
		int c;
		//Check có muốn đăng kí tiếp khóa học không
		cout << "You want to enroll a course? (YES/NO): " << endl;
		cout << "  1. YES			2. NO" << endl;;
		cout << "User: ";
		cin >> c;
		while (c != 1 && c != 2) {
			cout << "Invalid input!" << endl;
			cout << "User: ";
			cin >> c;
		}
		if (c == 2)
			break;
		else if (c == 1) {
			cout << "Please enter Course ID to enroll: ";
			string id;
			cin.ignore();
			getline(cin, id);

			tmpCourse = enrolledCourse;

			while (tmpCourse) {

				//check có trùng ID không
				if (tmpCourse->courseID.compare(id) == 0) {

					//check course còn slot không
					if (tmpCourse->enrolledStudent < tmpCourse->numberStudent) {

						//check có bị trùng ca học không
						if (check(student, tmpCourse->session1, tmpCourse->session2)) {
							while (tmpEach->pNext != nullptr)
								tmpEach = tmpEach->pNext;

							if (student->Head_of_enrolled_course == nullptr) {

								student->Head_of_enrolled_course = new CourseForEachStudent;
								tmpEach = student->Head_of_enrolled_course;
								tmpEach->numberCourse = 1;
								tmpEach->pPrev = nullptr;

							}
							else {
								tmpEach->pNext = new CourseForEachStudent;
								tmpEach->pNext->pPrev = tmpEach;
								tmpEach = tmpEach->pNext;
								tmpEach->numberCourse = tmpEach->pPrev->numberCourse + 1;
								student->numberOfCourse++;
							}

							//thêm khóa học cho sinh viên
							tmpEach->detail.courseID = tmpCourse->courseID;
							tmpEach->detail.courseName = tmpCourse->courseName;
							tmpEach->detail.teacherName = tmpCourse->teacherName;
							tmpEach->detail.credits = tmpCourse->credits;
							tmpEach->detail.session1 = tmpCourse->session1;
							tmpEach->detail.session2 = tmpCourse->session2;

							/*tmpEach->final = 0;
							tmpEach->midterm = 0;
							tmpEach->otherMark = 0;
							tmpEach->total = 0;
							*/

							//tăng số lượng sinh viên đã enrol thành công khóa học
							tmpCourse->enrolledStudent++;

							//thêm danh sách sinh viên tham gia khóa học
							while (tmpCourseList->pNext != nullptr) {
								tmpCourseList = tmpCourseList->pNext;
							}
							if (tmpCourse->HeadStudent == nullptr) {
								tmpCourse->HeadStudent = new Student_CourseScores;
								tmpCourseList = tmpCourse->HeadStudent;
								tmpCourseList->no = 1;
								tmpCourseList->pPrev = nullptr;
							}
							else {
								tmpCourseList->pNext = new Student_CourseScores;
								tmpCourseList->pNext->pPrev = tmpCourseList;
								tmpCourseList->no++;
								tmpCourseList = tmpCourseList->pNext;
							}

							tmpCourseList->firstName = student->firstName;
							tmpCourseList->lastName = student->lastName;
							tmpCourseList->className = student->className;
							tmpCourseList->gender = student->gender;
							tmpCourseList->SID = student->SID;
							tmpCourseList->pNext = nullptr;
							tmpCourseList->midterm = 0;
							tmpCourseList->final = 0;
							tmpCourseList->otherMark = 0;
							tmpCourseList->courseGPA = 0;

							/*
							//Node chay lien ket diem cua student_courseScore voi CourseForEach
							CourseForEachStudent* tmp = tmpCourseList->point_to_an_enrolled_course_of_a_student_in_a_class;
							while (tmp->detail.courseID != id)
								tmp = tmp->pNext;

							tmp->midterm = tmpCourseList->midterm;
							tmp->final = tmpCourseList->final;
							tmp->otherMark = tmpCourseList->otherMark;
							tmp->courseGPA = tmpCourseList->courseGPA;
							*/

							tmpCourseList->point_to_an_enrolled_course_of_a_student_in_a_class = tmpEach;

							tmpEach->pNext = nullptr;

							cout << "Enroll Successfully." << endl;
							cout << "You have enrolled in " << tmpEach->detail.courseName << endl;
							i++;
							break;
						}
						else {
							cout << "Session conflicted! Try Again!" << endl;
							break;
						}
					}
					else {
						cout << "The course is full. Try other course!" << endl;
						break;
					}
				}
				tmpCourse = tmpCourse->pNext;
			}
		}

		//Nếu nhập sai thì hỏi lại
		else
			continue;
	} while (i < numberDefaultCourse);

}