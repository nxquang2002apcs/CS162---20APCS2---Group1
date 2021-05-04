#include "DataStructure.h"

//to20125001
void writeStudentCourse(string path, Student_CourseScores*& CurrentStudent) {
	ofstream out;
	out.open(path);
	
	out << CurrentStudent->firstName << endl;
	out << CurrentStudent->lastName << endl;
	out << CurrentStudent->gender << endl;
	out << CurrentStudent->SID << endl;
	out << CurrentStudent->className << endl;
	out << CurrentStudent->midterm << endl;
	out << CurrentStudent->final << endl;
	out << CurrentStudent->otherMark << endl;
	out << CurrentStudent->courseGPA;
	
	out.close();
}

//toListStu
void writeListStudentCourse(string path, string list, Student_CourseScores*& HeadStudent) {
	ofstream out;
	out.open(path + list + ".txt");
	Student_CourseScores* CurrentStudent = HeadStudent;
	while (CurrentStudent != nullptr) {
		if (CurrentStudent->pNext == nullptr)
			out << CurrentStudent->SID;
		else
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
	string data;

	data = "Course Info";
	out << data << endl;
	writeCourseInfo(path + data + ".txt", CurrentCourse);
	data = "List Student";
	out << data;
	writeListStudentCourse(path + data + "\\", data, CurrentCourse->HeadStudent);
	out.close();
};
//toLisofCourses
void writeSemester(string path, Semester& sem) {
	ofstream out;
	out.open(path + "ListOfCourses.txt");
	CourseDetail* CurrentCourse = sem.HeadCourse;
	while (CurrentCourse != nullptr) {
		string tmpPATH = path;
		if (CurrentCourse->pNext == nullptr)
			out << CurrentCourse->courseID;
		else
			out << CurrentCourse->courseID << endl;
		tmpPATH += CurrentCourse->courseID;
		const char* dir = tmpPATH.c_str();
		_mkdir(dir);
		writeCourse(tmpPATH + "\\", CurrentCourse->courseID, CurrentCourse);
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
		out << CurrentYear->semester1.endDate.day << "/" << CurrentYear->semester1.endDate.month << "/" << CurrentYear->semester1.endDate.year;
	}
	if (CurrentYear->semester2.isAvailable == true) {
		out << endl << CurrentYear->semester2.startDate.day << "/" << CurrentYear->semester2.startDate.month << "/" << CurrentYear->semester2.startDate.year << " - ";
		out << CurrentYear->semester2.endDate.day << "/" << CurrentYear->semester2.endDate.month << "/" << CurrentYear->semester2.endDate.year;
	}
	if (CurrentYear->semester3.isAvailable == true) {
		out << endl << CurrentYear->semester3.startDate.day << "/" << CurrentYear->semester3.startDate.month << "/" << CurrentYear->semester3.startDate.year << " - ";
		out << CurrentYear->semester3.endDate.day << "/" << CurrentYear->semester3.endDate.month << "/" << CurrentYear->semester3.endDate.year;
	}
	out.close();
}
//toClassInfo
void writeClassInfo(string path, Class*& CurrentClass) {
	ofstream out;
	out.open(path);

	out << CurrentClass->className << endl;
	out << CurrentClass->formTeacherName << endl;
	out << CurrentClass->classSize << endl;
	
	out.close();
}
//toCS161
void writeEnrolledCourse(string path, CourseForEachStudent*& CurrentCourse) {
	ofstream out;
	out.open(path);

	out << CurrentCourse->detail.courseID << endl;
	out << CurrentCourse->detail.courseName << endl;
	out << CurrentCourse->detail.teacherName << endl;
	out << CurrentCourse->detail.credits << endl;
	out << CurrentCourse->detail.session1 << endl;
	out << CurrentCourse->detail.session2 << endl;
	out << CurrentCourse->midterm << endl;
	out << CurrentCourse->final << endl;
	out << CurrentCourse->otherMark << endl;
	out << CurrentCourse->courseGPA;
	
	out.close();
}
//toListofEnrolledCourse
void writeListEnrolledCourse(string path, string s, Student*& CurrentStudent, CourseForEachStudent*& HeadCourse) {
	ofstream out;
	out.open(path + s + ".txt");
	CourseForEachStudent* CurrentCourse = HeadCourse;
	while (CurrentCourse != nullptr) {
		if (CurrentCourse->pNext == nullptr)
			out << CurrentCourse->detail.courseID;
		else
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
	
	out << CurrentStudent->firstName << endl;
	out << CurrentStudent->lastName << endl;
	out << CurrentStudent->SID << endl;
	out << CurrentStudent->className << endl;
	out << CurrentStudent->gender << endl;
	out << CurrentStudent->socialID << endl;
	out << CurrentStudent->DateOfBirth.day << "/" << CurrentStudent->DateOfBirth.month << "/" << CurrentStudent->DateOfBirth.year;
	out << endl << CurrentStudent->FirstYear << endl;
	out << CurrentStudent->gpa;
		
};
//to20125001
void writeStudent(string path, string s, Student*& CurrentStudent) {
	ofstream out;
	out.open(path + s + ".txt");
	string data;

	data = "List Of Enrolled Course";
	out << data << endl;
	writeListEnrolledCourse(path + data + "\\", data, CurrentStudent, CurrentStudent->Head_of_enrolled_course);
	data = "Student Information";
	out << data;
	writeStudentInfo(path + data + ".txt", CurrentStudent);
	out.close();
}
//toListStudentClass
void writeListStudentClass(string path, string s, Student*& HeadStudent) {
	ofstream out;
	out.open(path + s + ".txt");
	Student* CurrentStudent = HeadStudent;
	while (CurrentStudent != nullptr) {
		string tmpPATH = path;
		if (CurrentStudent->pNext == nullptr)
			out << CurrentStudent->SID;
		else
			out << CurrentStudent->SID << endl;
		tmpPATH += CurrentStudent->SID;
		const char* dir = tmpPATH.c_str();
		_mkdir(dir);
		writeStudent(tmpPATH + "\\", CurrentStudent->SID, CurrentStudent);
		CurrentStudent = CurrentStudent->pNext;
	}
	out.close();
}
//to20CTT1
void writeClass(string path, string s, Class*& CurrentClass) {
	ofstream out;
	out.open(path + s + ".txt");
	string data;
	data = "Class Information";
	out << data << endl;
	writeClassInfo(path + data + ".txt", CurrentClass);
	data = "List Student";
	out << data;
	writeListStudentClass(path + data + "\\", data, CurrentClass->HeadStudent);
	
	out.close();
}
//toListofClass
void writeListClass(string path, string s, Class*& HeadClass) {
	ofstream out;
	out.open(path + s + ".txt");

	Class* CurrentClass = HeadClass;
	while (CurrentClass!=nullptr){
		string tmpPATH = path;
		if (CurrentClass->pNext == nullptr)
			out << CurrentClass->className;
		else
			out << CurrentClass->className << endl;
		tmpPATH += CurrentClass->className;
		const char* dir = tmpPATH.c_str();
		_mkdir(dir);
		writeClass(tmpPATH + "\\", CurrentClass->className, CurrentClass);
		CurrentClass = CurrentClass->pNext;
	}
	
	out.close();
}

void writeAll(SchoolYear* &HeadYear)
{
	ofstream out;
	string path = "C:\\Users\\User\\source\\repos\\Enroll\\Data\\Schoolyear\\";
	string schoolyear;
	out.open(path + "Schoolyear.txt");

	SchoolYear* CurrentYear = HeadYear;
	while (CurrentYear != nullptr){
		string tmpPATH = path;
		schoolyear = to_string(CurrentYear->startYear) + to_string(CurrentYear->endYear);
		if (CurrentYear->pNext == nullptr)
			out << schoolyear;
		else
			out << schoolyear << endl;

		tmpPATH += schoolyear;
		const char* dir0 = tmpPATH.c_str();
		_mkdir(dir0);
		writeYear(tmpPATH + "\\" + schoolyear + ".txt", CurrentYear);
		
		if (CurrentYear->semester1.isAvailable) {
			string tmp1 = tmpPATH + "\\" + "Semester 1";
			const char* dir1 = tmp1.c_str();
			_mkdir(dir1);
			writeSemester(tmp1 + "\\", CurrentYear->semester1);
			CurrentSemester = &CurrentYear->semester1;
		}
		
		if (CurrentYear->semester2.isAvailable) {
			string tmp2 = tmpPATH + "\\" + "Semester 2";
			const char* dir2 = tmp2.c_str();
			_mkdir(dir2);
			writeSemester(tmp2 + "\\", CurrentYear->semester2);
			CurrentSemester = &CurrentYear->semester2;
		}
		
		if (CurrentYear->semester3.isAvailable) {
			string tmp3 = tmpPATH + "\\" + "Semester 3";
			const char* dir3 = tmp3.c_str();
			_mkdir(dir3);
			writeSemester(tmp3 + "\\", CurrentYear->semester3);
			CurrentSemester = &CurrentYear->semester3;
		}
		
		writeListClass(tmpPATH + "\\" + "ListOfClasses\\", "ListOfClasses", CurrentYear->HeadClass);

		CurrentYear = CurrentYear->pNext;
	}
		
	out.close();
}