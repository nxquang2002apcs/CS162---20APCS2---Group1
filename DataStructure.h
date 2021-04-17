#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_
#pragma warning(disable : 4996)
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

struct CourseForEachStudent;
struct CourseDetail;
struct Student;
struct Class;
struct Semester;
struct SchoolYear;

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
	DateTime DateOfBirth;

	CourseForEachStudent* Head_of_enrolled_course;   //Linked List

	Student* pNext;
	Student* pPrev;
};

//Thông tin về môn học
struct CourseDetail {
	string courseID;
	string courseName, teacherName;
	int credits;
	int numberStudent;
	int enrolledStudent;
	/// 2 tiết mỗi tuần
	/// MON / TUE / WED / THU / FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)
	string session1, session2;		//Ví dụ: MONS1 - Monday 7h30

	Student* ListStudent;			//Danh sách sinh viên đã đăng ký môn học

	CourseDetail* pNext;
	CourseDetail* pPrev;

};


struct CourseForEachStudent {
	CourseDetail detail;
	int numberCourse;
	float midterm, final, total, otherMark;  //Điểm số

	CourseForEachStudent* pNext;
	CourseForEachStudent* pPrev;
};

struct Class {
	string className;				//Tên lớp, ví dụ 20CTT2
	int classSize;					//Số sinh viên
	string formTeacherName;			//Tên giảng viên chủ nhiệm
	Student* HeadStudent;			//pHead trong Linked List student

	Class* pNext;
	Class* pPrev;
};

struct Semester {
	bool isAvailable;				//Nếu học kỳ chưa được tạo thì isAvailable = false, ngược lại thì true
	DateTime startDate;				//Ngày bắt đầu học kỳ
	DateTime endDate;				//Ngày kết thúc				
	CourseDetail* HeadCourse;       //pHead cảu danh sách môn học trong học kỳ này
};

struct SchoolYear {
	int startYear, endYear;			//2019-2020. startYear = 2019, endYear = 2020.
	Semester semester1, semester2, semester3;
	Class* HeadClass;               //Danh sách các lớp, HeadClass là pHead trong danh sách

	SchoolYear* pPrev;
	SchoolYear* pNext;
};

static SchoolYear* CurrentYear = nullptr;		//Pointer để đánh dấu năm học hiện tại, tiện cho việc truy xuất thông tin
static Semester* CurrentSemester = nullptr;		//Học kỳ hiện tại
static SchoolYear* HeadYear = nullptr;			// Vai trò như pHead cho list các năm học
static SchoolYear* ThisYear = nullptr;			//Năm học mà người dùng đang truy cập đến, khác với CurrentYear
static Semester* ThisSemester = nullptr;		//Học kỳ mà người dùng đang truy cập đến	
//static Student* CurrentStudent = nullptr;		//Nếu người dùng là học sinh thì biến này sẽ đánh dấu học sinh đó

/// <summary>
/// Đăng nhập/Đăng ký, đăng xuất, đổi mật khẩu
/// </summary>
void Read_Name_Pass(ifstream& in, string& username, string& password, string& userfile, string& passfile);
void login(ifstream& in, int& role);
void signup(ifstream& in, ofstream& out, int& role);  //Role là biến quản lý vai trò người dùng: 1. student; 2. staff
void changePassword(ifstream& in, ofstream& out);


/// <summary>
/// Làm việc với file CSV
/// </summary>
void inputCSV(string path, Student* ListStudent, int& size);		//Nhập ds sinh viên bằng cách đọc file CSV

/// <summary>
/// Các hàm khởi tạo và đọc dữ liệu người dùng
/// </summary>
void create_a_new_school_year(int start_year, int end_year);		// Hàm tạo năm học mới
void input_school_year();							// Hàm để staff nhập năm học mới
void input_classes_for_current_year();				// Hàm tạo lớp cho năm học hiện tại
void create_a_semester_for_year(SchoolYear*& Year, DateTime start_date, DateTime end_date, int semester_n);	// Hàm tạo học kỳ cho năm học (start_year - end_year)
void enter_a_semester();							// Hàm để staff nhập học kỳ mới
void delete_year_and_class();						// Hàm xóa danh sách năm học và danh sách các lớp
void display_school_year_list();					// Hàm hiển thị danh sách các năm học
void display_classes_list_of_school_year();	// Hàm hiển thị danh sách các lớp học của năm học (start_year - end_year)
void inputListOfStudent(int& sizeOfStudent, Student*& student);      //Hàm nhập thủ công danh sách sinh viên trong một lớp

/// <summary>
/// Dự định
/// </summary>
//Nhật Quang
void create_a_list_of_courses_for_currentSemester();
void input_course_detail(CourseDetail*& HeadCourse);					//Input là nhập cả ds course, HeadCourse là pHead của list

//Hoàng Huy
void update_course_detail(CourseDetail*& HeadCourse, int courseID);		//HeadCourse là pHead, yêu cầu đổi thông tin của course có ID cần đổi
void delete_a_course_in_the_list(CourseDetail*& HeadCourse, CourseDetail*& deletedCourse); //deletedCourse là node muốn xóa khỏi danh sách

//Băng Trinh
void enroll_a_course(Student*& student, CourseDetail*& enrolledCourse);  //Thêm Course vào ds môn học của sinh viên (student), set các loại điểm về 0
bool check(Student* student, string ses1, string ses2);

//Gia Khánh
void view_list_of_enrolled_course(Student* student);					//In ra danh sách môn học của student: student->Head_of_enrolled_course->courseDetail
void remove_an_enrolled_course(CourseForEachStudent*& Head_of_enrolled_course, int courseID);  //Truyền vào Danh sách môn học, courseID là ID của môn muốn xóa.

//Xuân Quang
void StaffInterface();     //Giao diện làm việc của staff.
	


//Gia Khánh
void view_list_of_student_course(Student* student);
void view_list_of_students_in_class(Class* Cls);
void view_list_of_courses(Semester* semester);
void view_list_of_student_in_course(CourseDetail* course);
void view_list_of_class(SchoolYear* year);


#endif

