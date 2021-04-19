#include "DataStructure.h"


//to20125001
bool readStudentCourse(string path, Student_CourseScores* CurrentStudent) {
	ifstream fin;
	string data;
	fin.open(path);
	if (!fin.is_open()) {
		cout << "Couldn't open file" << endl;
	}
	else {
		getline(fin, data);
		if (data != "") {
			CurrentStudent->firstName = data;
			getline(fin, data);
			CurrentStudent->lastName = data;
			getline(fin, data);
			CurrentStudent->gender = data;
			getline(fin, data);
			CurrentStudent->SID = data;
			getline(fin, data);
			CurrentStudent->className = data;
			getline(fin, data);
			CurrentStudent->DateOfBirth = data;
			getline(fin, data);
			CurrentStudent->midterm = stof(data);
			getline(fin, data);
			CurrentStudent->final = stof(data);
			getline(fin, data);
			CurrentStudent->otherMark = stof(data);
			getline(fin, data);
			CurrentStudent->total = stof(data);
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

//toListStu
void readListStudentCourse(string path, string list, Student_CourseScores*& HeadStudent) {
	ifstream in;
	in.open(path + list + ".txt");
	string data;
	if (!in.is_open()) {
		cout << "Couldn't open file" << endl;
	}
	else {
		Student_CourseScores* CurrentStudent = nullptr;
		
		int i = 0;
		while (!in.eof()) {
			getline(in, data);
			if (data != "") {

				if (HeadStudent == nullptr) {
					HeadStudent = new Student_CourseScores;
					CurrentStudent = HeadStudent;
					CurrentStudent->pPrev = nullptr;
				}
				else {
					CurrentStudent->pNext = new Student_CourseScores;
					CurrentStudent->pPrev = new Student_CourseScores;
					CurrentStudent->pPrev->pNext = CurrentStudent;
					CurrentStudent = CurrentStudent->pNext;
				}

				if (readStudentCourse(path + data + ".txt", CurrentStudent)){
					i++;
					CurrentStudent->no = i;
				}	
				CurrentStudent->pNext = nullptr;
				
			}
		}
	}
	in.close();
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
	in.close();

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
			readCourseInfo(path + data + ".txt", CurrentCourse);
			getline(f, data);
			readListStudentCourse(path + data + "\\", data, CurrentCourse->HeadStudent);
		}
	}
	f.close();
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
		getline(in, data);
		if (data != "") {
			CurrentClass->className = data;
			getline(in, data);
			CurrentClass->formTeacherName = data;
			getline(in, data);
			CurrentClass->classSize = stoi(data);
		}
	}
	in.close();
}
//toCS161
bool readEnrolledCourse(string path, CourseForEachStudent* CurrentCourse) {
	ifstream fin;
	fin.open(path);
	string data;
	if (!fin.is_open())
		cout << "Couldn't open file\n";
	else {
		getline(fin, data);
		if (data != "") {
			CurrentCourse->detail.courseID = data;
			getline(fin, data);
			CurrentCourse->detail.courseName = data;
			getline(fin, data);
			CurrentCourse->detail.teacherName = data;
			getline(fin, data);
			CurrentCourse->detail.credits = stoi(data);
			getline(fin, data);
			CurrentCourse->detail.session1 = data;
			getline(fin, data);
			CurrentCourse->detail.session2 = data;
			getline(fin, data);
			CurrentCourse->midterm = stof(data);
			getline(fin, data);
			CurrentCourse->final = stof(data);
			getline(fin, data);
			CurrentCourse->otherMark = stof(data);
			getline(fin, data);
			CurrentCourse->total = stof(data);
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}
//toListofEnrolledCourse
void readListEnrolledCourse(string path, string s, CourseForEachStudent*& HeadCourse) {
	ifstream f;
	f.open(path + s + ".txt");
	string data;
	if (!f.is_open())
		cout << "Couldn't open file" << endl;
	else {
		CourseForEachStudent* CurrentCourse = nullptr;
		int i = 0;
		while (!f.eof()) {
			getline(f, data);
			if (data != "") {
				if (HeadCourse == nullptr) {
					HeadCourse = new CourseForEachStudent;
					CurrentCourse = HeadCourse;
					CurrentCourse->pPrev = nullptr;
				}
				else {
					CurrentCourse->pNext = new CourseForEachStudent;
					CurrentCourse->pPrev = new CourseForEachStudent;
					CurrentCourse->pPrev->pNext = CurrentCourse;
					CurrentCourse = CurrentCourse->pNext;
				}
				
				if (readEnrolledCourse(path + data + ".txt", CurrentCourse)) {
					i++;
					CurrentCourse->numberCourse = i;
				}
				CurrentCourse->pNext = nullptr;
			}
		}
	}
	f.close();
}
//toStudentInformation
void readStudentInfo(string path, Student* CurrentStudent) {
	ifstream f;
	f.open(path);
	string data;
	if (!f.is_open())
		cout << "Couldn't open file\n";
	else {
		getline(f, data);
		if (data != "") {
			CurrentStudent->firstName = data;
			getline(f, data);
			CurrentStudent->lastName = data;
			getline(f, data);
			CurrentStudent->SID = data;
			getline(f, data);
			CurrentStudent->className = data;
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
			CurrentStudent->gpa = stof(data);
		}
	}
};
//to20125001
bool readStudent(string path, string s, Student* CurrentStudent) {
	ifstream in;
	string data;
	in.open(path + s + ".txt");
	if (!in.is_open())
		cout << "Couldn't open file" << endl;
	else {
		getline(in, data);
		if (data != "") {
			readListEnrolledCourse(path + data + "\\", data, CurrentStudent->Head_of_enrolled_course);
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
void readListStudentClass(string path, string s, Student*& HeadStudent) {
	ifstream fin;
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
					CurrentStudent->pPrev = new Student;
					CurrentStudent->pPrev->pNext = CurrentStudent;
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
void readClass(string path, string s, Class* CurrentClass) {
	ifstream f;
	string data;
	f.open(path + s + ".txt");
	if (!f.is_open())
		cout << "Couldn't open file" << endl;
	else {
		getline(f, data);
		if (data != "") {
			readClassInfo(path + data + ".txt", CurrentClass);
			getline(f, data);
			readListStudentClass(path + data + "\\",data, CurrentClass->HeadStudent);
		}
	}
	f.close();
}
//toListofClass
void readListClass(string path, string s, Class*& HeadClass) {
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
				if (HeadClass == nullptr) {
					HeadClass = new Class;
					CurrentClass = HeadClass;
					CurrentClass->pPrev = nullptr;
				}
				else {
					CurrentClass->pNext = new Class;
					CurrentClass->pPrev = new Class;
					CurrentClass->pPrev->pNext = CurrentClass;
					CurrentClass = CurrentClass->pNext;
				}
				readClass(path + data + "\\", data, CurrentClass);
				CurrentClass->pNext = nullptr;
			}
		}
	}
	fin.close();
}

void readAll(SchoolYear* &HeadYear) {
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
				readListClass(path + schoolyear + "\\" + "ListOfClasses\\", "ListOfClasses", CurrentYear->HeadClass);

				CurrentYear->pNext = nullptr;
			}
		}
	}
	f.close();
}