#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_
#pragma warning(disable : 4996)
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//Kiểu dữ liệu ngày tháng (ngày sinh, ngày kết thúc học kỳ,...)
struct DateTime {
	int day, month, year;
};

//Đối tượng sinh viên
struct Student {
	int no;					//Số thứ tự trong lớp
	string SID;				//MSSV
	string firstName, lastName;
	string gender;
	string socialID;				//Số CMND
	string DateOfBirth;
};

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

struct Class {
	string className;			//Tên lớp, ví dụ 20CTT2
	int classSize;				//Số sinh viên
	string formTeacherName;			//Tên giảng viên chủ nhiệm
	Student* ListStudent;			//Danh sách sinh viên trong lớp
	Class* pNext;
	Class* pPrev;
};

struct Semester {
	DateTime startDate;			//Ngày bắt đầu học kỳ
	DateTime endDate;			//Ngày kết thúc				
	CourseDetail* ListCourse;       	//Danh sách môn học trong học kỳ này
};

struct SchoolYear {
	int schoolYear;
	Semester semester1, semester2, semester3;
	Class* ListClass;               	//Danh sách các lớp
	SchoolYear* pPrev;
	SchoolYear* pNext;
};


static SchoolYear* CurrentYear = nullptr;                 	//Pointer để đánh dấu năm học hiện tại
static Semester CurrentSemester;			//Học kỳ hiện tại
static SchoolYear* HeadYear = nullptr;			// Vai trò như pHead cho list các năm học


//Hàm đọc file CSV
void inputCSV(string path, Student* ListStudent, int& size);

//Các hàm làm khởi tạo năm học và học kỳ
void create_a_new_school_year(int start_year, int end_year);		// Hàm tạo năm học mới
void input_school_year();						// Hàm để staff nhập năm học mới
void input_classes_for_current_year();				// Hàm tạo lớp cho năm học hiện tại
void create_a_semester_for_year(int start_year, int end_year, DateTime start_date, DateTime end_date, int semester_n);	// Hàm tạo học kỳ cho năm học (start_year - end_year)
void enter_a_semester();						// Hàm để staff nhập học kỳ mới
void delete_year_and_class();						// Hàm xóa danh sách năm học và danh sách các lớp
void display_school_year_list();					// Hàm hiển thị danh sách các năm học
void display_classes_list_of_school_year(int start_year, int end_year);	// Hàm hiển thị danh sách các lớp học của năm học (start_year - end_year)

#endif

