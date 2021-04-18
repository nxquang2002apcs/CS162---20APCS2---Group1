#include "DataStructure.h"


//toList
void readListStudentCourse(string path, Student* HeadStudent) {
	ifstream fin;
	string data;
	fin.open(path);
	if (!fin.is_open()) {
		cout << "Couldn't open file" << endl;
	}
	else {
		Student* CurrentStudent = nullptr;
		getline(fin, data);
		if (data != "") {
			while (!fin.eof()) {
				if (HeadStudent == nullptr) {
					HeadStudent = new Student;
					CurrentStudent = HeadStudent;
				}
				else {
					CurrentStudent->pNext = new Student;
					CurrentStudent->pPrev = new Student;
					CurrentStudent->pPrev->pNext = CurrentStudent;
					CurrentStudent = CurrentStudent->pNext;
				}
				CurrentStudent->no = stoi(data);
				getline(fin, data);
				CurrentStudent->firstName = data;
				getline(fin, data);
				CurrentStudent->lastName = data;
				getline(fin, data);
				CurrentStudent->gender = data;
				getline(fin, data);
				CurrentStudent->SID = stoi(data);
				getline(fin, data);
				CurrentStudent->DateOfBirth.day = stoi(data);
				getline(fin, data);
				CurrentStudent->DateOfBirth.month = stoi(data);
				getline(fin, data);
				CurrentStudent->DateOfBirth.year = stoi(data);
				CurrentStudent->pNext = nullptr;
			}
		}
	}
}

//tocourseinfo
void readCourseInfo(string path, CourseDetail* CurrentCourse) {
	ifstream in;
	string data;
	in.open(path);
	if (!in.is_open())
		cout << "Couldn't open file" << endl;
	else {
		getline(in, data);
		if (data != "") {
			CurrentCourse->courseID = data;
			getline(in, data);
			CurrentCourse->courseName = data;
			getline(in, data);
			CurrentCourse->credits = stoi(data);
			getline(in, data);
			CurrentCourse->numberStudent = stoi(data);
			getline(in, data);
			CurrentCourse->enrolledStudent = stoi(data);
			getline(in, data);
			CurrentCourse->session1 = data;
			getline(in, data);
			CurrentCourse->session2 = data;
		}
	}

}
//tocal1
void readCourse(string path, string course, Semester sem) {
	ifstream f;
	f.open(path + course + ".txt");
	string data;
	string info = "Course Information";
	if (!f.is_open())
		cout << "Couldn't open file" << endl;
	else{
		CourseDetail* CurrentCourse = nullptr;
		while (!f.eof()) {
			if (sem.HeadCourse == nullptr) {
				sem.HeadCourse = new CourseDetail;
				CurrentCourse = sem.HeadCourse;
				CurrentCourse->pPrev = nullptr;
			}
			else {
				CurrentCourse->pNext = nullptr;
				CurrentCourse->pPrev = new CourseDetail;
				CurrentCourse->pPrev->pNext = CurrentCourse;
				CurrentCourse = CurrentCourse->pNext;
			}
			getline(f, data);
			readCourseInfo(path + data + "\\" + data + ".txt", CurrentCourse);
			getline(f, data);
			readListStudentCourse(path + data + "\\" + data + ".txt", CurrentCourse->ListStudent);
			CurrentCourse->pNext = nullptr;
		}
	}
};
//tosemester
void readSemester(string path, Semester sem) {
	ifstream fin;
	string course;
	fin.open(path + "Semester.txt");
	if (!fin.is_open()) {
		cout << "Couldn't open file" << endl;
	}
	else {
		while (!fin.eof()) {
			getline(fin, course);
			readCourse(path + course + "\\", course, sem);
		}
	}
	fin.close();
}
//to20202021
void readYear(string path, SchoolYear* CurrentYear) {
	ifstream in;
	string num;
	in.open(path);
	if (!in.is_open())
		cout << "Couldn't open file" << endl;
	else {
		getline(in, num);
		if (num != "") {
			CurrentYear->startYear = stoi(num);
			getline(in, num);
			CurrentYear->endYear = stoi(num);

			if (!in.eof()) {
				CurrentYear->semester1.isAvailable = true;
				getline(in, num);
				CurrentYear->semester1.startDate.day = stoi(num);
				getline(in, num);
				CurrentYear->semester1.startDate.month = stoi(num);
				getline(in, num);
				CurrentYear->semester1.startDate.year = stoi(num);
				getline(in, num);
				CurrentYear->semester1.endDate.day = stoi(num);
				getline(in, num);
				CurrentYear->semester1.endDate.month = stoi(num);
				getline(in, num);
				CurrentYear->semester1.endDate.year = stoi(num);
			}
			if (!in.eof()) {
				CurrentSemester->isAvailable = true;
				getline(in, num);
				CurrentYear->semester2.startDate.day = stoi(num);
				getline(in, num);
				CurrentYear->semester2.startDate.month = stoi(num);
				getline(in, num);
				CurrentYear->semester2.startDate.year = stoi(num);
				getline(in, num);
				CurrentYear->semester2.endDate.day = stoi(num);
				getline(in, num);
				CurrentYear->semester2.endDate.month = stoi(num);
				getline(in, num);
				CurrentYear->semester2.endDate.year = stoi(num);
			}
			if (!in.eof()) {
				CurrentSemester->isAvailable = true;
				getline(in, num);
				CurrentYear->semester3.startDate.day = stoi(num);
				getline(in, num);
				CurrentYear->semester3.startDate.month = stoi(num);
				getline(in, num);
				CurrentYear->semester3.startDate.year = stoi(num);
				getline(in, num);
				CurrentYear->semester3.endDate.day = stoi(num);
				getline(in, num);
				CurrentYear->semester3.endDate.month = stoi(num);
				getline(in, num);
				CurrentYear->semester3.endDate.year = stoi(num);

			}
		}
	}
	in.close();
}


void readAll() {
	ifstream f;
	string path = "C:\\Users\\Administrator\\source\\repos\\Schoolyear\\";
	string schoolyear;
	
	f.open(path + "Schoolyear.txt");
	if (!f.is_open())
		cout << "Could't open file" << endl;
	else {
		while (!f.eof()) {
			if (HeadYear == nullptr) {
				HeadYear = new SchoolYear;
				CurrentYear = HeadYear;
				CurrentYear->pPrev = nullptr;
			}
			else {
				CurrentYear->pNext = new SchoolYear;
				CurrentYear->pPrev = new SchoolYear;
				CurrentYear->pPrev->pNext = CurrentYear;
				CurrentYear = CurrentYear->pNext;
			}
			getline(f, schoolyear);
			readYear(path + schoolyear + "\\" + schoolyear + ".txt", CurrentYear);
			if (CurrentYear->semester1.isAvailable) {
				readSemester(path + schoolyear + "\\" + "Semester 1\\" , CurrentYear->semester1);
			}
			if (CurrentYear->semester2.isAvailable) {
				readSemester(path + schoolyear + "\\" + "Semester 2\\" , CurrentYear->semester2);
			}
			if (CurrentYear->semester3.isAvailable) {
				readSemester(path + schoolyear + "\\" + "Semester 3\\" , CurrentYear->semester3);
			}
			CurrentYear->pNext = nullptr;
		}
		
	}
	f.close();
}