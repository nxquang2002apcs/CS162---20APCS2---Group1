#include "DataStructure.h"

//Sao chép thông tin của 1 sinh viên từ năm cũ sang năm mới
void copyStudentInfo(Student* prevStudent, Student*& curStudent) {
	curStudent->className = prevStudent->className;
	curStudent->firstName = prevStudent->firstName;
	curStudent->lastName = prevStudent->lastName;
	curStudent->gender = prevStudent->gender;
	curStudent->no = prevStudent->no;
	curStudent->SID = prevStudent->SID;
	curStudent->socialID = prevStudent->socialID;
	curStudent->DateOfBirth.day = prevStudent->DateOfBirth.day;
	curStudent->DateOfBirth.month = prevStudent->DateOfBirth.month;
	curStudent->DateOfBirth.year = prevStudent->DateOfBirth.year;
	curStudent->FirstYear = prevStudent->FirstYear;

	curStudent->gpa = 0;
	curStudent->Head_of_enrolled_course = nullptr;					//Ban đầu sv vẫn chưa đăng ký môn
	curStudent->numberOfCourse = 0;
	curStudent->pNext = nullptr;
}

//Sao chép thông tin của 1 lớp từ năm cũ sang năm mới
void copyClassInfo(Class* prevClass, Class*& curClass) {
	curClass->className = prevClass->className;
	curClass->classSize = prevClass->classSize;
	curClass->formTeacherName = prevClass->formTeacherName;

	Student* tempStudent_cur = curClass->HeadStudent;
	Student* tempStudent_prev = prevClass->HeadStudent;

	while (tempStudent_prev != nullptr) {							//Copy danh sách sinh viên năm 2,3,4 trong lớp đó
		if (curClass->HeadStudent == nullptr) {
			curClass->HeadStudent = new Student;
			tempStudent_cur = curClass->HeadStudent;
			tempStudent_cur->pPrev = nullptr;
		}
		else {
			tempStudent_cur->pNext = new Student;
			tempStudent_cur->pNext->pPrev = tempStudent_cur;
			tempStudent_cur = tempStudent_cur->pNext;
		}

		tempStudent_cur->pNext = nullptr;
		copyStudentInfo(tempStudent_prev, tempStudent_cur);			//Copy thông tin của một sinh viên

		tempStudent_prev = tempStudent_prev->pNext;
	}


	curClass->pNext = nullptr;
}


void Update_automatically() {
	SchoolYear* prevYear = CurrentYear->pPrev;
	if (prevYear == nullptr)
		return;

	Class* prevClass = prevYear->HeadClass;												//Biến duyệt danh sách năm cũ
	Class* curClass = CurrentYear->HeadClass;											//Biến duyệt ds năm mới
	if (prevClass == nullptr) return;

	while (prevClass != nullptr) {
		if (prevClass->HeadStudent->FirstYear - CurrentYear->startYear < 4) {			//Nếu năm hiện tại trừ năm nhập học nhỏ hơn 4 thì nghĩa là sv chưa tốt nghiệp
			if (CurrentYear->HeadClass == nullptr) {
				CurrentYear->HeadClass = new Class;
				curClass = CurrentYear->HeadClass;
				curClass->pPrev = nullptr;
			}
			else {
				curClass->pNext = new Class;
				curClass->pNext->pPrev = curClass;
				curClass = curClass->pNext;
			}

			curClass->pNext = nullptr;
			copyClassInfo(prevClass, curClass);											//Copy thông tin của lớp đó ở năm rồi sang năm mới
		}
		
		prevClass = prevClass->pNext;
	}
}