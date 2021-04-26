#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_
#pragma warning(disable : 4996)
#include<string>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>

#include "Console.h"
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

struct Student_CourseScores {	// Dùng để lưu, cập nhật, in điểm của một Student trong một Course
	int no;			// Số thứ tự trong lớp
	string SID;		// MSSV
	string firstName, lastName;
	string gender;
	string className;

	float midterm, final, otherMark, courseGPA = 0;

	Student_CourseScores* pNext;
	Student_CourseScores* pPrev;

	CourseForEachStudent* point_to_an_enrolled_course_of_a_student_in_a_class;	// Trỏ tới và cập nhật điểm của một trong các course của CourseForEachStudent của một Student trong một Class.
};


//Đối tượng sinh viên
struct Student {
	int no;					//Số thứ tự trong lớp
	string SID;				//MSSV
	string className;			//Lớp học mà sv đó đang học
	int FirstYear;				//Năm học mà sv bắt đầu nhập học
	string firstName, lastName;
	string gender;
	string socialID;	//Số CMND
	float gpa;
	DateTime DateOfBirth;
	int numberOfCourse = 0;		//Số môn học sv đã đăng ký

	CourseForEachStudent* Head_of_enrolled_course = nullptr;   //Linked List

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
	
	bool Available_scoreboard;     				//Nếu môn học đã có điểm thì set về true, không thì false.
	
	//Student* ListStudent = nullptr;			//Danh sách sinh viên đã đăng ký môn học
	Student_CourseScores* HeadStudent = nullptr;
	CourseDetail* pNext;
	CourseDetail* pPrev;

};


struct CourseForEachStudent {
	CourseDetail detail;
	int numberCourse;
	float midterm, final, otherMark, courseGPA;  //Điểm số

	CourseForEachStudent* pNext;
	CourseForEachStudent* pPrev;
};

struct Class {
	string className;				//Tên lớp, ví dụ 20CTT2
	int classSize;					//Số sinh viên
	string formTeacherName;			//Tên giảng viên chủ nhiệm
	Student* HeadStudent = nullptr;			//pHead trong Linked List student


	Class* pNext;
	Class* pPrev;
};

struct Semester {
	bool isAvailable = false;				//Nếu học kỳ chưa được tạo thì isAvailable = false, ngược lại thì true
	DateTime startDate;				//Ngày bắt đầu học kỳ
	DateTime endDate;				//Ngày kết thúc				
	CourseDetail* HeadCourse = nullptr;       //pHead cảu danh sách môn học trong học kỳ này
	
	int numberOfCourse = 0;			//Biến đếm số môn học trong học kỳ này
};

struct SchoolYear {
	int startYear, endYear;			//2019-2020. startYear = 2019, endYear = 2020.
	Semester semester1, semester2, semester3;
	Class* HeadClass = nullptr;               //Danh sách các lớp, HeadClass là pHead trong danh sách

	SchoolYear* pPrev;
	SchoolYear* pNext;
};

extern SchoolYear* CurrentYear;				//Pointer để đánh dấu năm học hiện tại, tiện cho việc truy xuất thông tin
extern Semester* CurrentSemester;			//Học kỳ hiện tại
extern SchoolYear* HeadYear;				// Vai trò như pHead cho list các năm học
extern SchoolYear* ThisYear;				//Năm học mà người dùng đang truy cập đến, khác với CurrentYear
extern Semester* ThisSemester;				//Học kỳ mà người dùng đang truy cập đến	
extern Student* CurrentStudent;				//Nếu người dùng là học sinh thì biến này sẽ đánh dấu học sinh đó

extern bool Available_register;		//Biến lưu trạng thái đóng mở của hệ thống đăng ký môn, true thì hệ thống mở, sv được đk môn.
extern bool Available_all_scoreboard;	//Nếu tất cả các môn đều đã có điểm, biến này trả về true, cho phép học sinh được xem scoreboard

/// <summary>
/// Đăng nhập/Đăng ký, đăng xuất, đổi mật khẩu
/// </summary>
void Read_Name_Pass(ifstream& in, string& username, string& password, string& userfile, string& passfile);
bool login(ifstream& in, int& role, string& studentID);
void signup(ifstream& in, ofstream& out, int& role);  //Role là biến quản lý vai trò người dùng: 1. student; 2. staff
void changePassword(ifstream& in, ofstream& out);


/// <summary>
/// Làm việc với file CSV
/// </summary>
void inputCSV(string path, Student* ListStudent, int& size);		//Nhập ds sinh viên bằng cách đọc file CSV

//Băng Trinh
void readCourseInfo(string path, CourseDetail*& CurrentCourse);
void readCourse(string path, string course, CourseDetail*& CurrentCourse);
void readSemester(string path, Semester& sem);
void readYear(string path, SchoolYear*& CurrentYear);
void readClassInfo(string path, Class*& CurrentClass);
void readListStudentClass(string path, string s, Student*& HeadStudent);
void readClass(string path, string s, Class*& CurrentClass);
void readListClass(string path, string s, Class*& HeadClass);
bool readStudentCourse(string path, Student_CourseScores*& CurrentStudent);
void readListStudentCourse(string path, string list, Student_CourseScores*& HeadStudent);
bool readEnrolledCourse(string path, CourseForEachStudent*& CurrentCourse);
void readListEnrolledCourse(string path, string s, Student*& CurrentStudent, CourseForEachStudent*& HeadCourse);
void readStudentInfo(string path, Student*& CurrentStudent);
bool readStudent(string path, string s, Student*& CurrentStudent);
void readAll();

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
void delete_everything();

//Hoàng Huy
void update_course_detail(CourseDetail*& HeadCourse, string courseID);		//HeadCourse là pHead, yêu cầu đổi thông tin của course có ID cần đổi
void delete_a_course_in_the_list(CourseDetail*& HeadCourse, string courseID); //deletedCourse là node muốn xóa khỏi danh sách
bool export_course_score_to_CSV(string path, Student_CourseScores* head_Course_Score);
void import_course_score_from_CSV(string path, Student_CourseScores*& head_Course_Score);

//Băng Trinh
void enroll_a_course(Student*& student, CourseDetail*& enrolledCourse);  //Thêm Course vào ds môn học của sinh viên (student), set các loại điểm về 0
bool check(Student* student, string ses1, string ses2);

//Gia Khánh
void view_list_of_enrolled_course(Student* student);			//Staff xem thì có thêm các loại điểm
void view_list_of_enrolled_course(Student* student);			//In ra danh sách môn học của student, không có các loại điểm
void remove_an_enrolled_course(CourseForEachStudent*& Head_of_enrolled_course, int courseID);  //Truyền vào Danh sách môn học, courseID là ID của môn muốn xóa.
void view_list_of_student_course(Student* student);
void view_list_of_students_in_class(Class* Cls);
void view_list_of_courses(Semester* semester);
void view_list_of_student_in_course(CourseDetail* course);
void view_list_of_class(SchoolYear* year);
void print(float n);


//Xuân Quang
void StaffInterface();     //Giao diện làm việc của staff.
void StudentInterface(string studentID);	//Giao diện làm việc của student

#endif

