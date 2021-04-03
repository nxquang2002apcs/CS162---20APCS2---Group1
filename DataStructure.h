#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//Thông tin về môn học
struct CourseDetail {
	int courseID;
	string courseName, teacherName;
	int credits;

	/// 2 tiết mỗi tuần
	/// MON / TUE / WED / THU / FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)
	string session1, session2;		//Ví dụ: MONS1 - Monday 7h30

	Student* ListStudent;			//Danh sách sinh viên đã đăng ký môn học
};


struct CourseForEachStudent {
	CourseDetail detail;
	float midterm, final, total, otherMark;  //Điểm số
};

//Đối tượng sinh viên
struct Student {
	int no;							//Số thứ tự trong lớp
	int SID;						//MSSV
	string firstName, lastName;
	enum gender { male, female };
	int socialID;					//Số CMND
	struct DateOfBirth {
		int day, month, year;
	};
};


struct Class {
	string className;				//Tên lớp, ví dụ 20CTT2
	string formTeacherName;			//Tên giảng viên chủ nhiệm
	Student* ListStudent;			//Danh sách sinh viên trong lớp
};

struct Semeseter {
	struct startDate {
		int day, month, year;
	};								//Ngày bắt đầu học kỳ
	struct endDate {
		int day, month, year;
	};								//Ngày kết thúc
	int schoolYear;					
	CourseDetail* ListCourse;       //Danh sách môn học trong học kỳ này
};

struct SchoolYear {
	Semeseter semester1, semester2, semester3;
	Class* ListClass;               //Danh sách các lớp 
};

SchoolYear CurrentYear;                 //Biến để đánh dấu năm học hiện tại
Semester CurrentSemester;		//Học kỳ hiện tại
#endif
