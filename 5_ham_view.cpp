#include "DataStructure.h"

// 1. Hàm cho student xem danh sách các môn học họ sẽ học trong học kỳ

void view_list_of_student_course(Student* student)
{
	cout << "   " << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Teacher Name";
	cout << "Number of credits   ";
	cout << "Maximum number of students in the course   ";
	cout << "Number of students enrolled  ";
	cout << "Session 1  ";
	cout << "Session 2" << endl;

	CourseForEachStudent* Head_course = student->Head_of_enrolled_course;

	while (Head_course)
	{
		cout << Head_course->numberCourse << ". ";
		cout << setw(12) << left << Head_course->detail.courseID;
		cout << setw(35) << left << Head_course->detail.courseName;
		cout << setw(17) << left << Head_course->detail.teacherName;
		cout << setw(13) << right << Head_course->detail.credits;
		cout << setw(32) << right << Head_course->detail.numberStudent;
		cout << setw(36) << right << Head_course->detail.enrolledStudent;
		cout << setw(21) << right << Head_course->detail.session1;
		cout << setw(11) << right << Head_course->detail.session2 << endl;

		Head_course = Head_course->pNext;

		cout << endl;
	}
}

// 2. Hàm cho staff xem danh sách học sinh trong 1 lớp

void view_list_of_students_in_class(Class* cls)
{
	Student* pHead = cls->HeadStudent;

	cout << setw(5) << left << "No";
	cout << setw(12) << left << "Student ID";
	cout << setw(12) << left << "First name";
	cout << setw(17) << left << "Last name";
	cout << setw(8) << left << "Gender";
	cout << setw(15) << left << "Date of Birth";
	cout << "Social ID" << endl;
	
	while (pHead)
	{
		cout << setw(5) << left << pHead->no;
		cout << setw(12) << left << pHead->SID;
		cout << setw(12) << left << pHead->firstName;
		cout << setw(17) << left << pHead->lastName;
		cout << setw(8) << left << pHead->gender;
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.day << "/";
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.month << "/";
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.year;
		cout << setfill(' ') << setw(5) << right << " ";
		cout << pHead->socialID << endl;

		pHead = pHead->pNext;
	}
}

// 3. Hàm cho staff xem danh sách các môn học trong 1 học kỳ

void view_list_of_courses(Semester* semester)
{
	CourseDetail* pHead = semester->HeadCourse;

	cout << "   " << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Teacher Name";
	cout << "Number of credits   ";
	cout << "Maximum number of students in the course   ";
	cout << "Number of students enrolled  ";
	cout << "Session 1  ";
	cout << "Session 2" << endl;

	int i = 1; // Số thứ tự

	while (pHead)
	{
		cout << i << ". ";
		cout << setw(12) << left << pHead->courseID;
		cout << setw(35) << left << pHead->courseName;
		cout << setw(17) << left << pHead->teacherName;
		cout << setw(13) << right << pHead->credits;
		cout << setw(32) << right << pHead->numberStudent;
		cout << setw(36) << right << pHead->enrolledStudent;
		cout << setw(21) << right << pHead->session1;
		cout << setw(11) << right << pHead->session2 << endl;

		pHead = pHead->pNext;
		++i;

		cout << endl;
	}
}

// 4. Hàm cho staff xem danh sách học sinh trong 1 môn học

void view_list_of_student_in_course(CourseDetail* course)
{
	Student* pHead = course->ListStudent;

	cout << setw(5) << left << "No";
	cout << setw(12) << left << "Student ID";
	cout << setw(12) << left << "First name";
	cout << setw(21) << left << "Last name";
	cout << setw(8) << left << "Gender";
	cout << setw(15) << left << "Date of Birth";
	cout << "Social ID" << endl;

	while (pHead)
	{
		cout << setw(5) << left << pHead->no;
		cout << setw(12) << left << pHead->SID;
		cout << setw(12) << left << pHead->firstName;
		cout << setw(17) << left << pHead->lastName;
		cout << setw(8) << left << pHead->gender;
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.day << "/";
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.month << "/";
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.year;
		cout << setfill(' ') << setw(5) << right << " ";
		cout << pHead->socialID << endl;

		pHead = pHead->pNext;
	}
}

// 5. Hàm cho staff xem danh sách các lớp trong 1 năm

void view_list_of_class(SchoolYear* year)
{
	cout << setw(15) << left << "   Class Name";
	cout << setw(21) << left << "Number of students";
	cout << "Form teacher" << endl;

	Class* pHead = year->HeadClass;

	int i = 1; // Số thứ tự

	while (pHead)
	{
		cout << i << ". ";
		cout << setw(12) << left << pHead->className;
		cout << setw(10) << right << pHead->classSize;
		cout << setw(11) << right << " ";
		cout << pHead->formTeacherName << endl;

		pHead = pHead->pNext;
		++i;
	}
}

