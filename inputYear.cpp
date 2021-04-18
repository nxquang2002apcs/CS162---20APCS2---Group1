#include "DataStructure.h"


//to20125051
bool readInfoStudentCourse(string path, string mssv, Student* CurrentStudent) {
	ifstream fin;
	string data;
	fin.open(path + mssv + ".txt");
	if (!fin.is_open()) {
		cout << "Couldn't open file" << endl;
	}
	else {
		getline(fin, data,',');
		if (data != "") {
			CurrentStudent->firstName = data;
			getline(fin, data, ',');
			CurrentStudent->lastName = data;
			getline(fin, data, ',');
			CurrentStudent->gender = data;
			getline(fin, data, ',');
			CurrentStudent->SID = stoi(data);
			getline(fin, data, '/');
			CurrentStudent->DateOfBirth.day = stoi(data);
			getline(fin, data, '/');
			CurrentStudent->DateOfBirth.month = stoi(data);
			getline(fin, data, '\n');
			CurrentStudent->DateOfBirth.year = stoi(data);
			return true;
		}
	}
	return false;
}

//toListStu
void readListStudentCourse(string path, string list, Student* HeadStudent) {
	ifstream in;
	in.open(path + list + ".txt");
	string data;
	if (!in.is_open()) {
		cout << "Couldn't open file" << endl;
	}
	else {
		Student* CurrentStudent = nullptr;
		
		int i = 0;
		while (!in.eof()) {
			getline(in, data);
			if (data != "") {
				if (HeadStudent == nullptr) {
					HeadStudent = new Student;
					CurrentStudent = HeadStudent;
					CurrentStudent->pPrev = nullptr;
				}
				else {
					CurrentStudent->pNext = new Student;
					CurrentStudent->pPrev = new Student;
					CurrentStudent->pPrev->pNext = CurrentStudent;
					CurrentStudent = CurrentStudent->pNext;
				}

				if (readInfoStudentCourse(path + data + "\\", data, CurrentStudent)) {
					i++;
					CurrentStudent->no = i;
				};
				CurrentStudent->pNext = nullptr;
				getline(in, data);
			}
		}
	}
};
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
			CurrentCourse->teacherName = data;
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
//toCS161
void readCourse(string path, string course, CourseDetail* CurrentCourse) {
	ifstream f;
	f.open(path + course + ".txt");
	string data;
	if (!f.is_open())
		cout << "Couldn't open file" << endl;
	else{
		getline(f, data);
		if (data!="") {
			readCourseInfo(path + data + "\\" + data + ".txt", CurrentCourse);
			getline(f, data);
			readListStudentCourse(path + data + "\\", data, CurrentCourse->ListStudent);
		}
	}
};
//toLisofCourses
void readSemester(string path, Semester sem) {
	ifstream fin;
	string course;
	fin.open(path + "ListOfCourses.txt");
	if (!fin.is_open()) {
		cout << "Couldn't open file" << endl;
	}
	else {
		CourseDetail* CurrentCourse = nullptr;
		
		while (!fin.eof()) {
			getline(fin, course);
			if (course != "") {
				if (sem.HeadCourse == nullptr) {
					sem.HeadCourse = new CourseDetail;
					CurrentCourse = sem.HeadCourse;
					CurrentCourse->pPrev = nullptr;
				}
				else {
					CurrentCourse->pNext = new CourseDetail;
					CurrentCourse->pPrev = new CourseDetail;
					CurrentCourse->pPrev->pNext = CurrentCourse;
					CurrentCourse = CurrentCourse->pNext;
				}
				readCourse(path + course + "\\", course, CurrentCourse);
				CurrentCourse->pNext = nullptr;
			}
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
				getline(in, num, '/');
				CurrentYear->semester1.startDate.day = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester1.startDate.month = stoi(num);
				getline(in, num, '-');
				CurrentYear->semester1.startDate.year = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester1.endDate.day = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester1.endDate.month = stoi(num);
				getline(in, num, '\n');
				CurrentYear->semester1.endDate.year = stoi(num);
			}
			if (!in.eof()) {
				CurrentYear->semester2.isAvailable = true;
				getline(in, num, '/');
				CurrentYear->semester2.startDate.day = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester2.startDate.month = stoi(num);
				getline(in, num, '-');
				CurrentYear->semester2.startDate.year = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester2.endDate.day = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester2.endDate.month = stoi(num);
				getline(in, num, '\n');
				CurrentYear->semester2.endDate.year = stoi(num);
			}
			if (!in.eof()) {
				CurrentYear->semester3.isAvailable = true;
				getline(in, num, '/');
				CurrentYear->semester3.startDate.day = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester3.startDate.month = stoi(num);
				getline(in, num, '-');
				CurrentYear->semester3.startDate.year = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester3.endDate.day = stoi(num);
				getline(in, num, '/');
				CurrentYear->semester3.endDate.month = stoi(num);
				getline(in, num, '\n');
				CurrentYear->semester3.endDate.year = stoi(num);

			}
		}
	}
	in.close();
}
//toClassInfo
void readClassInfo(string path, Class* CurrentClass) {
	ifstream in;
	string data;
	in.open(path);
	if (!in.is_open())
		cout << "Couldn't open file";
	else {
		while (!in.eof()) {
			getline(in, data);
			if (data != "") {
				CurrentClass->className = data;
				getline(in, data);
				CurrentClass->formTeacherName = data;
				getline(in, data);
				CurrentClass->classSize = stoi(data);
			}
		}
		
	}
}
//toListStudentClass
void readListStudentClass(string path, string s, Student* HeadStudent) {
	ifstream fin;
	string data;
	fin.open(path + s + ".txt");
	if (!fin.is_open())
		cout << "Couldn't open file" << endl;
}
//to20CTT1
void readClass(string path, string s, Class* CurrentClass) {
	ifstream f;
	string data;
	f.open(path + s + ".txt");
	if (!f.is_open())
		cout << "Couldn't open file" << endl;
	else {
		getline(f, data);
		if (data != "") {
			readClassInfo(path + path + ".txt", CurrentClass);
			getline(f, data);
			readListStudentClass(path, data, CurrentClass->HeadStudent);
		}
	}
}
//toListofClass
void readListClass(string path, string s, Class* HeadClass) {
	ifstream fin;
	string data;
	fin.open(path + s + ".txt");
	if (!fin.is_open())
		cout << "Couldn't open file" << endl;
	else {
		Class* CurrentClass = nullptr;
		while (!fin.eof()) {
			getline(fin, data);
			if (data != "") {
				if (HeadClass = nullptr) {
					HeadClass = new Class;
					CurrentClass = HeadClass;
					CurrentClass->pPrev = nullptr;
				}
				else {
					CurrentClass->pNext = new Class;
					CurrentClass->pPrev = new Class;
					CurrentClass->pPrev->pNext = CurrentClass;
				}
				readClass(path + data + "\\", data, CurrentClass);
				CurrentClass->pNext = nullptr;
			}
		}
	}
}

void readAll() {
	ifstream f;
	string path = "C:\\Users\\Administrator\\source\\repos\\Data\\Schoolyear\\";
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
					CurrentYear->pPrev = new SchoolYear;
					CurrentYear->pPrev->pNext = CurrentYear;
					CurrentYear = CurrentYear->pNext;
				}

				readYear(path + schoolyear + "\\" + schoolyear + ".txt", CurrentYear);
				if (CurrentYear->semester1.isAvailable) {
					readSemester(path + schoolyear + "\\" + "Semester 1\\", CurrentYear->semester1);
				}
				if (CurrentYear->semester2.isAvailable) {
					readSemester(path + schoolyear + "\\" + "Semester 2\\", CurrentYear->semester2);
				}
				if (CurrentYear->semester3.isAvailable) {
					readSemester(path + schoolyear + "\\" + "Semester 3\\", CurrentYear->semester3);
				}
				readListClass(path + "ListOfClasses\\", "ListOfClasses", CurrentYear->HeadClass);
				getline(f, schoolyear);
				CurrentYear->pNext = nullptr;
			}
		}
	}
	f.close();
}