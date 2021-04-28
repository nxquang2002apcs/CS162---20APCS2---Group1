#include "DataStructure.h"

SchoolYear* CurrentYear = nullptr;		//Pointer để đánh dấu năm học hiện tại, tiện cho việc truy xuất thông tin
Semester* CurrentSemester = nullptr;		//Học kỳ hiện tại
SchoolYear* HeadYear = nullptr;			// Vai trò như pHead cho list các năm học
SchoolYear* ThisYear = nullptr;			//Năm học mà người dùng đang truy cập đến, khác với CurrentYear
Semester* ThisSemester = nullptr;		//Học kỳ mà người dùng đang truy cập đến	
Student* CurrentStudent = nullptr;		//Nếu người dùng là học sinh thì biến này sẽ đánh dấu học sinh đó

//to20125001
void writeStudentCourse(string path, Student_CourseScores*& CurrentStudent) {
	ofstream out;
	out.open(path);
	
	out << CurrentStudent->firstName << endl;
	out << CurrentStudent->lastName << endl;
	out << CurrentStudent->gender;
	out << CurrentStudent->SID;
	out << CurrentStudent->className;
	out << CurrentStudent->midterm;
	out << CurrentStudent->final;
	out << CurrentStudent->otherMark;
	out << CurrentStudent->courseGPA;
	
	out.close();
}

//toListStu
void writeListStudentCourse(string path, string list, Student_CourseScores*& HeadStudent) {
	ofstream out;
	out.open(path + list + ".txt");
	Student_CourseScores* CurrentStudent = nullptr;

	Student_CourseScores* CurrentStudent_CourseScores = HeadStudent;
	while (CurrentStudent != nullptr) {
		out << CurrentStudent->SID << endl;
		writeStudentCourse(path + CurrentStudent->SID + ".txt", CurrentStudent);
		CurrentStudent = CurrentStudent->pNext;
	}

	out.close();
};
//tocourseinfo
void writeCourseInfo(string path, CourseDetail*& CurrentCourse) {
	ofstream out;
	out.open(path);

	out << CurrentCourse->courseID << endl;
	out << CurrentCourse->courseName << endl;
	out << CurrentCourse->teacherName << endl;
	out << CurrentCourse->credits << endl;
	out << CurrentCourse->numberStudent << endl;
	out << CurrentCourse->enrolledStudent << endl;
	out << CurrentCourse->session1 << endl;
	out << CurrentCourse->session2 << endl;
	if (CurrentCourse->Available_scoreboard == false)
		out << 0;
	else out << 1;
	
	out.close();

}
//toCS161
void writeCourse(string path, string course, CourseDetail*& CurrentCourse) {
	ofstream out;
	out.open(path + course + ".txt");
	out << "Course Info\n";
	writeCourseInfo(path + "Course Info" + ".txt", CurrentCourse);
	out << "List Student";
	writeListStudentCourse(path + "List Student" + "\\", "List Student", CurrentCourse->HeadStudent);
	out.close();
};
//toLisofCourses
void writeSemester(string path, Semester& sem) {
	ofstream out;
	out.open(path + "ListOfCourses.txt");
	CourseDetail* CurrentCourse = sem.HeadCourse;
	while (CurrentCourse != nullptr) {
		out << CurrentCourse->courseID << endl;
		writeCourse(path + CurrentCourse->courseID + "\\", CurrentCourse->courseID, CurrentCourse);
		CurrentCourse = CurrentCourse->pNext;
	}
	out.close();
}
//to20202021
void writeYear(string path, SchoolYear*& CurrentYear) {
	ofstream out;
	string num;
	out.open(path);

	out << CurrentYear->startYear << endl;
	out << CurrentYear->endYear << endl;

	if (CurrentYear->semester1.isAvailable == true) {
		out << CurrentYear->semester1.startDate.day << "/" << CurrentYear->semester1.startDate.month << "/" << CurrentYear->semester1.startDate.year << " - ";
		out << CurrentYear->semester1.endDate.day << "/" << CurrentYear->semester1.endDate.month << "/" << CurrentYear->semester1.endDate.year << endl;
	}
	if (CurrentYear->semester2.isAvailable == true) {
		out << CurrentYear->semester2.startDate.day << "/" << CurrentYear->semester2.startDate.month << "/" << CurrentYear->semester2.startDate.year << " - ";
		out << CurrentYear->semester2.endDate.day << "/" << CurrentYear->semester2.endDate.month << "/" << CurrentYear->semester2.endDate.year << endl;
	}
	if (CurrentYear->semester3.isAvailable == true) {
		out << CurrentYear->semester3.startDate.day << "/" << CurrentYear->semester3.startDate.month << "/" << CurrentYear->semester3.startDate.year << " - ";
		out << CurrentYear->semester3.endDate.day << "/" << CurrentYear->semester3.endDate.month << "/" << CurrentYear->semester3.endDate.year << endl;
	}
	out.close();
}
//toClassInfo
void writeClassInfo(string path, Class*& CurrentClass) {
	ofstream out;
	string data;
	out.open(path);

	out << CurrentClass->className;
	out << CurrentClass->formTeacherName;
	out << CurrentClass->classSize;
	
	out.close();
}
//toCS161
void writeEnrolledCourse(string path, CourseForEachStudent*& CurrentCourse) {
	ofstream out;
	out.open(path);

	out << CurrentCourse->detail.courseID;
	out << CurrentCourse->detail.courseName;
	out << CurrentCourse->detail.teacherName;
	out << CurrentCourse->detail.credits;
	out << CurrentCourse->detail.session1;
	out << CurrentCourse->detail.session2;
	out << CurrentCourse->midterm;
	out << CurrentCourse->final;
	out << CurrentCourse->otherMark;
	out << CurrentCourse->courseGPA;
	
	out.close();
}
//toListofEnrolledCourse
void writeListEnrolledCourse(string path, string s, Student*& CurrentStudent, CourseForEachStudent*& HeadCourse) {
	ofstream out;
	out.open(path + s + ".txt");
	CourseForEachStudent* CurrentCourse = HeadCourse;
	while (CurrentCourse != nullptr) {
		out << CurrentCourse->detail.courseID << endl;
		writeEnrolledCourse(path + CurrentCourse->detail.courseID + ".txt", CurrentCourse);
		CurrentCourse = CurrentCourse->pNext;
	}		
	out.close();
}
//toStudentInformation
void writeStudentInfo(string path, Student*& CurrentStudent) {
	ofstream out;
	out.open(path);
	
	out << CurrentStudent->firstName;
	out << CurrentStudent->lastName;
	out << CurrentStudent->SID;
	out << CurrentStudent->className;
			getline(f, data);
			CurrentStudent->gender = data;
			getline(f, data);
			CurrentStudent->socialID = data;
			getline(f, data, '/');
			CurrentStudent->DateOfBirth.day = stoi(data);
			getline(f, data, '/');
			CurrentStudent->DateOfBirth.month = stoi(data);
			getline(f, data);
			CurrentStudent->DateOfBirth.year = stoi(data);
			getline(f, data);
			CurrentStudent->FirstYear = stoi(data);
			getline(f, data);
			CurrentStudent->gpa = stof(data);
		}
};
//to20125001
bool writeStudent(string path, string s, Student*& CurrentStudent) {
	ofstream in;
	string data;
	in.open(path + s + ".txt");
	if (!in.is_open())
		cout << "Couldn't open file" << endl;
	else {
		getline(in, data);
		if (data != "") {
			readListEnrolledCourse(path + data + "\\", data, CurrentStudent, CurrentStudent->Head_of_enrolled_course);
			getline(in, data);
			readStudentInfo(path + data + ".txt", CurrentStudent);
			in.close();
			return true;
		}
	}
	in.close();
	return false;
}
//toListStudentClass
void writeListStudentClass(string path, string s, Student*& HeadStudent) {
	ofstream fin;
	string data;
	fin.open(path + s + ".txt");
	if (!fin.is_open())
		cout << "Couldn't open file" << endl;
	else {
		Student* CurrentStudent = nullptr;
		int i = 0;
		while (!fin.eof()) {
			getline(fin, data);
			if (data != "") {

				if (HeadStudent == nullptr) {
					HeadStudent = new Student;
					CurrentStudent = HeadStudent;
					CurrentStudent->pPrev = nullptr;
				}
				else {
					CurrentStudent->pNext = new Student;
					CurrentStudent->pNext->pPrev = CurrentStudent;
					CurrentStudent = CurrentStudent->pNext;
				}
				if (readStudent(path + data + "\\", data, CurrentStudent)) {
					i++;
					CurrentStudent->no = i;
				}
				CurrentStudent->pNext = nullptr;
			}
		}
	}
	fin.close();
}
//to20CTT1
void writeClass(string path, string s, Class*& CurrentClass) {
	ofstream f;
	string data;
	f.open(path + s + ".txt");
	if (!f.is_open())
		cout << "Couldn't open file" << endl;
	else {
		getline(f, data);
		if (data != "") {
			readClassInfo(path + data + ".txt", CurrentClass);
			getline(f, data);
			readListStudentClass(path + data + "\\", data, CurrentClass->HeadStudent);
		}
	}
	f.close();
}
//toListofClass
void writeListClass(string path, string s, Class*& HeadClass) {
	ofstream fin;
	string data;
	fin.open(path + s + ".txt");
	if (!fin.is_open())
		cout << "Couldn't open file" << endl;
	else {
		Class* CurrentClass = nullptr;
		while (!fin.eof()) {
			getline(fin, data);
			if (data != "") {
				if (HeadClass == nullptr) {
					HeadClass = new Class;
					CurrentClass = HeadClass;
					CurrentClass->pPrev = nullptr;
				}
				else {
					CurrentClass->pNext = new Class;
					CurrentClass->pNext->pPrev = CurrentClass;
					CurrentClass = CurrentClass->pNext;
				}
				readClass(path + data + "\\", data, CurrentClass);
				CurrentClass->pNext = nullptr;
			}
		}
	}
	fin.close();
}

void writeAll()
{
	ofstream f;
	string path = "Data\\Schoolyear\\";
	string schoolyear;

	f.open(path + "Schoolyear.txt");
	if (!f.is_open())
		cout << "Could't open file" << endl;
	else {
		while (!f.eof()) {
			getline(f, schoolyear);
			if (schoolyear != "") {
				if (HeadYear == nullptr) {
					HeadYear = new SchoolYear;
					CurrentYear = HeadYear;
					CurrentYear->pPrev = nullptr;
				}
				else {
					CurrentYear->pNext = new SchoolYear;
					CurrentYear->pNext->pPrev = CurrentYear;
					CurrentYear = CurrentYear->pNext;
				}

				readYear(path + schoolyear + "\\" + schoolyear + ".txt", CurrentYear);
				if (CurrentYear->semester1.isAvailable) {
					readSemester(path + schoolyear + "\\" + "Semester 1\\", CurrentYear->semester1);
					CurrentSemester = &CurrentYear->semester1;
				}
				if (CurrentYear->semester2.isAvailable) {
					readSemester(path + schoolyear + "\\" + "Semester 2\\", CurrentYear->semester2);
					CurrentSemester = &CurrentYear->semester2;
				}
				if (CurrentYear->semester3.isAvailable) {
					readSemester(path + schoolyear + "\\" + "Semester 3\\", CurrentYear->semester3);
					CurrentSemester = &CurrentYear->semester3;
				}
				readListClass(path + schoolyear + "\\" + "ListOfClasses\\", "ListOfClasses", CurrentYear->HeadClass);

				CurrentYear->pNext = nullptr;
			}
		}
	}
	f.close();
}