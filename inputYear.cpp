#include "DataStructure.h"

SchoolYear* CurrentYear = nullptr;		//Pointer để đánh dấu năm học hiện tại, tiện cho việc truy xuất thông tin
Semester* CurrentSemester = nullptr;		//Học kỳ hiện tại
SchoolYear* HeadYear = nullptr;			// Vai trò như pHead cho list các năm học
SchoolYear* ThisYear = nullptr;			//Năm học mà người dùng đang truy cập đến, khác với CurrentYear
Semester* ThisSemester = nullptr;		//Học kỳ mà người dùng đang truy cập đến	
Student* CurrentStudent = nullptr;		//Nếu người dùng là học sinh thì biến này sẽ đánh dấu học sinh đó


void connect_course_scores_to_student()
{
	CourseDetail* pCur_semester_courses = CurrentSemester->HeadCourse;	// Chạy từ đầu danh sách khóa học của học kỳ hiện tại
	while (pCur_semester_courses != nullptr)
	{
		Student_CourseScores* pCur_CourseScores = pCur_semester_courses->HeadStudent;	// Chạy từ đầu danh sách điểm trong khóa học đó
		while (pCur_CourseScores != nullptr)
		{
			Class* pCur_find_class = CurrentYear->HeadClass;	// Tìm lớp sinh viên này đang học, bắt đầu từ đầu danh sách các lớp học của CurrentYear

			while (pCur_find_class != nullptr && pCur_find_class->className != pCur_CourseScores->className) // bằng cách so sánh className
				pCur_find_class = pCur_find_class->pNext;

			if (pCur_find_class != nullptr) // Nếu tìm thấy lớp
			{
				Student* pCur_find_student = pCur_find_class->HeadStudent;
				while (pCur_find_student != nullptr && pCur_find_student->SID != pCur_CourseScores->SID)	// thì so sánh từng SID trong lớp đó
					pCur_find_student = pCur_find_student->pNext;

				if (pCur_find_student != nullptr) // Nếu tìm thấy sinh viên
				{
					CourseForEachStudent* pCur_enrolled_courses = pCur_find_student->Head_of_enrolled_course; // thì tìm trong danh sách khóa học sinh viên đã đăng ký
					while (pCur_enrolled_courses != nullptr && pCur_enrolled_courses->detail.courseID != pCur_semester_courses->courseID) // bằng cách so sánh courseID
						pCur_enrolled_courses = pCur_enrolled_courses->pNext;

					if (pCur_enrolled_courses != nullptr)	// Nếu tìm thấy
					{
						pCur_CourseScores->point_to_an_enrolled_course_of_a_student_in_a_class = pCur_enrolled_courses;	// Nối pointer từ danh sách điểm của khóa học sang khóa học của sinh viên

						
						// --- Sao chép điểm qua ---    Để tiện khi sinh viên xem điểm của mình
						pCur_enrolled_courses->midterm = pCur_CourseScores->midterm;
						pCur_enrolled_courses->final = pCur_CourseScores->final;
						pCur_enrolled_courses->otherMark = pCur_CourseScores->otherMark;
						pCur_enrolled_courses->courseGPA = pCur_CourseScores->courseGPA;
						// --------------------------------------------------------------------
						
					}
				}
			}

			pCur_CourseScores = pCur_CourseScores->pNext;
		}

		pCur_semester_courses = pCur_semester_courses->pNext;
	}
}


//to20125001 in Course
bool readStudentCourse(string path, Student_CourseScores*& CurrentStudent) {
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
			CurrentStudent->midterm = stof(data);
			getline(fin, data);
			CurrentStudent->final = stof(data);
			getline(fin, data);
			CurrentStudent->otherMark = stof(data);
			getline(fin, data);
			CurrentStudent->courseGPA = stof(data);
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

//toListStudent in Course
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
					CurrentStudent->pNext->pPrev = CurrentStudent;
					CurrentStudent = CurrentStudent->pNext;
				}

				if (readStudentCourse(path + data + ".txt", CurrentStudent)) {
					i++;
					CurrentStudent->no = i;
				}
				CurrentStudent->pNext = nullptr;

			}
		}
	}
	in.close();
};
//tocourseinfo in semester
void readCourseInfo(string path, CourseDetail*& CurrentCourse) {
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
//toCS161 in semester
void readCourse(string path, string course, CourseDetail*& CurrentCourse) {
	ifstream f;
	f.open(path + course + ".txt");
	string data;
	if (!f.is_open())
		cout << "Couldn't open file" << endl;
	else {
		getline(f, data);
		if (data != "") {
			readCourseInfo(path + data + ".txt", CurrentCourse);
			getline(f, data);
			readListStudentCourse(path + data + "\\", data, CurrentCourse->HeadStudent);
		}
	}
	f.close();
};
//toLisofCourses in semester
void readSemester(string path, Semester& sem) {
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
					CurrentCourse->pNext->pPrev = CurrentCourse;
					CurrentCourse = CurrentCourse->pNext;
				}
				readCourse(path + course + "\\", course, CurrentCourse);
				CurrentCourse->pNext = nullptr;
			}
		}
	}
	fin.close();
}
//to20202021 in data
void readYear(string path, SchoolYear*& CurrentYear) {
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
//toClassInfo in list Class
void readClassInfo(string path, Class*& CurrentClass) {
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
//toCS161 in student in class
bool readEnrolledCourse(string path, CourseForEachStudent*& CurrentCourse) {
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
			CurrentCourse->courseGPA = stof(data);
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}
//toListofEnrolledCourse in student in class
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
					CurrentCourse->pNext->pPrev = CurrentCourse;
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
//toStudentInformation in student in class
void readStudentInfo(string path, Student*& CurrentStudent) {
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
			CurrentStudent->FirstYear = stoi(data);
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
//to20125001 in student in class
bool readStudent(string path, string s, Student*& CurrentStudent) {
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
//toListStudentClass in class
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
//to20CTT1 in list class
void readClass(string path, string s, Class*& CurrentClass) {
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
			readListStudentClass(path + data + "\\", data, CurrentClass->HeadStudent);
		}
	}
	f.close();
}
//toListofClass in schoolyear
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

void readAll()
{
	ifstream f;
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
	connect_course_scores_to_student();
}



