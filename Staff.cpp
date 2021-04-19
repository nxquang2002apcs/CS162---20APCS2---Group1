#include "DataStructure.h"


void View_list_of_year();
bool isExisted_year(int start_year, int end_year);					//Hàm kiểm tra xem năm đó đã tồn tại hay chưa
bool delete_a_schoolyear(int startYear);
bool go_to_detail_of_a_student(string studentID);
bool go_to_detail_of_a_class(string className);
bool go_to_detail_of_a_course(string courseID);
bool go_to_detail_of_a_semester(int semester_n);
bool go_to_detail_of_a_year(int startYear);
//void view_a_student_profile(Student* ListStudent, string studentID);


/// <summary>
/// Cái đống này của Nhật Quang
/// </summary>
/// <param name="start_year"></param>
/// <param name="end_year"></param>
void create_a_new_school_year(int start_year, int end_year) 		// Hàm tạo năm học mới với start_year là năm bắt đầu, end_year là năm kết thúc.
{
	if (HeadYear == nullptr)										// Nếu chưa có năm học nào
	{
		HeadYear = new SchoolYear;									// thì tạo mới
		CurrentYear = HeadYear;
		CurrentYear->pPrev = nullptr;
	}
	else															// Nếu có rồi
	{
		CurrentYear->pNext = new SchoolYear;						// tạo năm học mới nối đuôi với năm trước đó
		CurrentYear->pNext->pPrev = CurrentYear;
		CurrentYear = CurrentYear->pNext;							// năm được tạo mới là năm hiện tại
	}

	CurrentYear->startYear = start_year;
	CurrentYear->endYear = end_year;

	CurrentYear->HeadClass = nullptr;								// Năm học mới chưa tạo danh sách lớp

	// --- Năm học mới chưa tạo học kỳ ---------
	CurrentYear->semester1.isAvailable = false;
	CurrentYear->semester2.isAvailable = false;
	CurrentYear->semester3.isAvailable = false;
	//-------------------------------------------

	CurrentSemester = nullptr;
	CurrentYear->pNext = nullptr;
}

void input_school_year()					// Hàm để staff nhập năm học mới
{
	int start_year, end_year;
	cout << "Enter a school year: " << endl;
	cout << "Start year: ";  	cin >> start_year;
	cout << "End year: ";		cin >> end_year;
	while (end_year < start_year) {
		cout << "End year must be greater than start year! Please enter again!" << endl;
		cout << "Start year: ";  	cin >> start_year;
		cout << "End year: ";		cin >> end_year;
	}
	if (isExisted_year(start_year, end_year) == false) {
		create_a_new_school_year(start_year, end_year);
	}
	else {
		cout << "Year is existed! Cannot create again!" << endl;
		system("pause");
	}
}

void input_classes_for_current_year()		// Hàm tạo danh sách các lớp học cho năm hiện tại
{
	Class* pCur_class = nullptr;

	int stop_condition = 1; // 1: tiếp tục nhập,  2: dừng nhập.

	while (stop_condition == 1)
	{
		pCur_class = CurrentYear->HeadClass;
		while (pCur_class != nullptr && pCur_class->pNext != nullptr)
			pCur_class = pCur_class->pNext;

		if (CurrentYear->HeadClass == nullptr)			// Nếu chưa có lớp nào
		{
			CurrentYear->HeadClass = new Class;			// thì tạo lớp mới, ListClass làm vai trò như pHead cho danh sách các lớp
			pCur_class = CurrentYear->HeadClass;
			pCur_class->pPrev = nullptr;
		}
		else
		{
			pCur_class->pNext = new Class;
			pCur_class->pNext->pPrev = pCur_class;
			pCur_class = pCur_class->pNext;
		}

		cin.get();
		cout << "Please enter the class's name: ";			getline(cin, pCur_class->className);
		cout << "Please enter the class's number of students: ";	cin >> pCur_class->classSize;
		cin.get();
		cout << "Please enter the class's form teacher name: ";		getline(cin, pCur_class->formTeacherName);

		pCur_class->HeadStudent = nullptr;				// Lớp mới tạo chưa có danh sách học sinh

		pCur_class->pNext = nullptr;

		cout << "Do you want to add more class?" << endl;
		cout << "1. Yes				2.No" << endl;
		cout << "Your choice: ";
		cin >> stop_condition;
	}
}

void create_a_semester_for_year(SchoolYear*& Year, DateTime start_date, DateTime end_date, int semester_n)
{
	switch (semester_n)												                          	// Thêm học kỳ mấy?
	{
	case 1:		// Học kỳ 1
	{
		Year->semester1.isAvailable = true;
		Year->semester1.startDate = start_date;						                // ngày bắt đầu	
		Year->semester1.endDate = end_date;							                // ngày kết thúc
		Year->semester1.HeadCourse = nullptr;							            // Học kỳ mới chưa tạo danh sách các môn học
		break;
	}
	case 2:		// Học kỳ 2
	{
		Year->semester2.isAvailable = true;
		Year->semester2.startDate = start_date;
		Year->semester2.endDate = end_date;
		Year->semester2.HeadCourse = nullptr;
		break;
	}
	case 3:		// Học kỳ 3
	{
		Year->semester3.isAvailable = true;
		Year->semester3.startDate = start_date;
		Year->semester3.endDate = end_date;
		Year->semester3.HeadCourse = nullptr;
		break;
	}
}
		
}

void enter_a_semester()			// Hàm để staff nhập ngày, tháng, năm bắt đầu và kết thúc học kỳ
{
	int semester_n;

	cout << "Choose a semester: " << endl;
	cout << "1. Semester 1." << endl;
	cout << "2. Semester 2." << endl;
	cout << "3. Semester 3." << endl;
	cout << "User: ";
	cin >> semester_n;
	switch (semester_n) {
	case 1:
		if (CurrentYear->semester1.isAvailable == true) {
			cout << "Semester 1 has been created. Cannot create again!" << endl;
			system("pause");
			return;
		}
		CurrentSemester = &CurrentYear->semester1;
		break;
	case 2:
		if (CurrentYear->semester2.isAvailable == true) {
			cout << "Semester 2 has been created. Cannot create again!" << endl;
			system("pause");
			return;
		}
		if (CurrentYear->semester1.isAvailable == false) {
			cout << "Semester 1 is unavailble. Cannot initialize semester 2!" << endl;
			system("pause");
			return;
		}
		CurrentSemester = &CurrentYear->semester2;
		break;
	case 3:
		if (CurrentYear->semester3.isAvailable == true) {
			cout << "Semester 3 has been created. Cannot create again!" << endl;
			system("pause");
			return;
		}
		if (CurrentYear->semester1.isAvailable == false) {
			cout << "Semester 1 is unavailble. Cannot initialize semester 3!" << endl;
			system("pause");
			return;
		}
		if (CurrentYear->semester2.isAvailable == false) {
			cout << "Semester 2 is unavailble. Cannot initialize semester 3!" << endl;
			system("pause");
			return;
		}
		CurrentSemester = &CurrentYear->semester3;
		break;
	default:
		cout << "Invalid input!" << endl;
		system("pause");
		return;
	}
	DateTime start_date, end_date;

	cout << "Enter the semester's start date: " << endl;
	cout << "Day: ";			cin >> start_date.day;	
	cout << "Month: ";			cin >> start_date.month;
	cout << "Year: ";			cin >> start_date.year;

	cout << "Enter the semester's end date: " << endl;
	cout << "Day: ";			cin >> end_date.day;		
	cout << "Month: ";			cin >> end_date.month;			
	cout << "Year: ";			cin >> end_date.year;	

	create_a_semester_for_year(CurrentYear, start_date, end_date, semester_n);
}

void delete_year_and_class()
{
	SchoolYear* year_delete = nullptr;
	Class* class_delete = nullptr;

	SchoolYear* pCur_year = HeadYear;
	Class* pCur_class = pCur_year->HeadClass;

	while (pCur_year != nullptr)
	{
		while (pCur_class != nullptr)
		{
			class_delete = pCur_class;
			pCur_class = pCur_class->pNext;
			delete class_delete;
		}

		year_delete = pCur_year;
		pCur_year = pCur_year->pNext;
		delete year_delete;
	}
}

//In ds các năm
void display_school_year_list()
{
	if (HeadYear == nullptr) {
		cout << "No existed year!" << endl;
	}
	else {
		SchoolYear* pCur = HeadYear;
		while (pCur != nullptr)
		{
			//cout << "This is the list of school year: " << endl;
			cout << pCur->startYear << "-" << pCur->endYear << endl;
			pCur = pCur->pNext;
		}
		cout << endl;
	}
}

void display_classes_list_of_school_year()
{
	cout << "List of classes: " << endl;
	if (ThisYear->HeadClass == nullptr) {
		cout << "No existed class!" << endl;         //Nếu chưa có lớp thì thông báo chưa có lớp tồn tại
	}
	else {
		Class* pCur_class = ThisYear->HeadClass;
		int index = 1;
		while (pCur_class != nullptr)
		{
			cout << index++ << ". " << pCur_class->className << endl;
			pCur_class = pCur_class->pNext;
		}
		cout << endl;
	}
}	

void display_semesters_of_school_year()
{
	if (ThisYear->semester1.isAvailable == true) {
		cout << "Semester 1: ";
		cout << ThisYear->semester1.startDate.day << "/" << ThisYear->semester1.startDate.month << "/" << ThisYear->semester1.startDate.year;
		cout << " - ";
		cout << ThisYear->semester1.endDate.day << "/" << ThisYear->semester1.endDate.month << "/" << ThisYear->semester1.endDate.year;
		cout << endl;
	}
	else {
		cout << "Semester 1: unavailable" << endl;
	}
	

	if (ThisYear->semester2.isAvailable == true) {
		cout << "Semester 2: ";
		cout << ThisYear->semester2.startDate.day << "/" << ThisYear->semester2.startDate.month << "/" << ThisYear->semester2.startDate.year;
		cout << " - ";
		cout << ThisYear->semester2.endDate.day << "/" << ThisYear->semester2.endDate.month << "/" << ThisYear->semester2.endDate.year;
		cout << endl;
	}
	else {
		cout << "Semester 2: unavailable" << endl;
	}

	if (ThisYear->semester3.isAvailable == true) {
		cout << "Semester 3: ";
		cout << ThisYear->semester3.startDate.day << "/" << ThisYear->semester3.startDate.month << "/" << ThisYear->semester3.startDate.year;
		cout << " - ";
		cout << ThisYear->semester3.endDate.day << "/" << ThisYear->semester3.endDate.month << "/" << ThisYear->semester3.endDate.year;
		cout << endl;
	}
	else {
		cout << "Semester 3: unavailable" << endl;
	}
}

void create_a_list_of_courses_for_Semester()
{
	int want_more = 1;
	CourseDetail* pCur = nullptr;
	cout << endl;
	while (want_more == 1)
	{
		string check_id;	// Dùng để lưu tạm ID được nhập vào, nếu không trùng ID nào thì đưa vào Linked List sau

		cout << "Enter the course's ID: ";
		cin.get();
		getline(cin, check_id);

		// ------ Check xem có trùng ID của Course nào không:

		CourseDetail* pCur_check_id = ThisSemester->HeadCourse;

		while (pCur_check_id != nullptr && pCur_check_id->courseID != check_id)	// Tìm xem có ID nào trùng check_id không
			pCur_check_id = pCur_check_id->pNext;

		if (pCur_check_id != nullptr && pCur_check_id->courseID == check_id)	// Nếu tìm thấy
		{
			cout << "The ID already exits. Enter again?" << endl;
			cout << "1. Yes			2.No" << endl;
			cout << "User: ";
			cin >> want_more;
			continue;
		}

		//-----------------------------------------

		//--- Không trùng mới đọc tới dòng dưới --
		pCur = ThisSemester->HeadCourse;
		while (pCur != nullptr && pCur->pNext != nullptr)
			pCur = pCur->pNext;

		if (ThisSemester->HeadCourse == nullptr)
		{
			ThisSemester->HeadCourse = new CourseDetail;
			pCur = ThisSemester->HeadCourse;
			pCur->pPrev = nullptr;
		}
		else
		{
			pCur->pNext = new CourseDetail;
			pCur->pNext->pPrev = pCur;
			pCur = pCur->pNext;
		}

		pCur->pNext = nullptr;

		pCur->ListStudent = nullptr;		// Môn học mới tạo chưa có người đăng ký
		pCur->enrolledStudent = 0;

		pCur->courseID = check_id;
		cout << "Enter the course's name: ";							getline(cin, pCur->courseName);
		cout << "Enter the course's teacher name: ";					getline(cin, pCur->teacherName);
		cout << "Enter the course's credits: ";							cin >> pCur->credits;		
		cout << "Enter the course's maximum number of students: ";		cin >> pCur->numberStudent;		
		cin.get();
		cout << "Enter the course's 1st session: ";						getline(cin, pCur->session1);
		cout << "Enter the course's 2nd session: ";						getline(cin, pCur->session2);

		cout << "Add one more course?		1. Yes		2.No	\n";
		cout << "User: ";		cin >> want_more;
	}
	return;
}

void delete_everything()
{
	SchoolYear* pCur_year = HeadYear;
	while (pCur_year != nullptr)
	{
		//------------ DELETE NHÁNH CLASS CỦA SCHOOLYEAR --------------

		Class* pCur_class = pCur_year->HeadClass;
		while (pCur_class != nullptr)
		{
			Student* pCur_student = pCur_class->HeadStudent;	// delete student trong class
			while (pCur_student != nullptr)
			{
				CourseForEachStudent* pCur_enrolled_course = pCur_student->Head_of_enrolled_course;	// delete enrolled course của student
				while (pCur_enrolled_course != nullptr)
				{
					CourseForEachStudent* delete_enrolled_course = pCur_enrolled_course;
					pCur_enrolled_course = pCur_enrolled_course->pNext;
					delete delete_enrolled_course;
				}

				Student* delete_student = pCur_student;
				pCur_student = pCur_student->pNext;
				delete delete_student;
			}

			Class* delete_class = pCur_class;
			pCur_class = pCur_class->pNext;
			delete delete_class;
		}

		//---------------------------------------------------------

		//--------- DELETE NHÁNH SEMESTER CỦA SCHOOLYEAR -----------

		CourseDetail* pCur_course = pCur_year->semester1.HeadCourse;  // Xóa các course của học kỳ 1
		while (pCur_course != nullptr)
		{
			Student* pCur_enrolled_student = pCur_course->ListStudent;	// Xóa danh sách student đã đăng ký course này
			while (pCur_enrolled_student != nullptr)
			{
				Student* delete_enrolled_student = pCur_enrolled_student;
				pCur_enrolled_student = pCur_enrolled_student->pNext;
				delete delete_enrolled_student;
			}

			CourseDetail* delete_course = pCur_course;
			pCur_course = pCur_course->pNext;
			delete delete_course;
		}

		pCur_course = pCur_year->semester2.HeadCourse;	// Của học kỳ 2, copy-paste
		while (pCur_course != nullptr)
		{
			Student* pCur_enrolled_student = pCur_course->ListStudent;
			while (pCur_enrolled_student != nullptr)
			{
				Student* delete_enrolled_student = pCur_enrolled_student;
				pCur_enrolled_student = pCur_enrolled_student->pNext;
				delete delete_enrolled_student;
			}

			CourseDetail* delete_course = pCur_course;
			pCur_course = pCur_course->pNext;
			delete delete_course;
		}

		pCur_course = pCur_year->semester3.HeadCourse;	// Và học kỳ 3
		while (pCur_course != nullptr)	//
		{
			Student* pCur_enrolled_student = pCur_course->ListStudent;
			while (pCur_enrolled_student != nullptr)
			{
				Student* delete_enrolled_student = pCur_enrolled_student;
				pCur_enrolled_student = pCur_enrolled_student->pNext;
				delete delete_enrolled_student;
			}

			CourseDetail* delete_course = pCur_course;
			pCur_course = pCur_course->pNext;
			delete delete_course;
		}

		SchoolYear* delete_year = pCur_year;
		pCur_year = pCur_year->pNext;
		delete delete_year;
	}
}

/// <summary>
/// Cái đống này của Hoàng Huy
/// </summary>
/// <param name="HeadCourse"></param>
/// <param name="courseID"></param>
// Update course detail   
void update_course_detail(CourseDetail*& HeadCourse, string courseID) {
	int check = 1;  //check whether user wants to update more ?
	if (HeadCourse == nullptr) {
		cout << "No existed course! Cannot update!" << endl;
		return;
	}
	while (check) {
		// Searching course
		CourseDetail* pCur;
		do {
			pCur = HeadCourse;
			fflush(stdin);
			while (pCur && pCur->courseID != courseID)
				pCur = pCur->pNext;
			if (!pCur) {
				cout << "Sorry, we can not find this course. Please try again\n";
				check = false;
			}
		} while (!pCur);

		cout << "*------------------------------------------------------------*\n";
		cout << "\t\tWHAT WOULD YOU LIKE TO UPDATE?\n";
		cout << "*------------------------------------------------------------*\n";
		cout << "\t1. Course ID\t\t" << "2. Course's name\n";
		cout << "\t3. Teacher's name\t" << "4. Credit\n";
		cout << "\t5. Session 1\t\t" << "6. Session 2\n";
		cout << "\t\t7. Number of student\n";

		// Choose something to update
		int choose;
		do {
			cout << "Choose: ";
			cin >> choose;
			cin.get();
			if (choose < 1 || choose > 7) cout << "Error. Please try again\n";
		} while (choose < 1 || choose > 7);

		CourseDetail* Cur = HeadCourse;
		switch (choose) {
		case 1: {    // Course ID 
			do {
				Cur = HeadCourse;
				string courseId;
				fflush(stdin);
				cout << "New course ID: ";
				getline(cin, courseId);
				fflush(stdin);
				while (Cur != nullptr && Cur->courseID != courseId) {
					Cur = Cur->pNext;
				}
				if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
				else pCur->courseID = courseId;
			} while (Cur);
			cout << "CHANGE SUCCESSFULLY\n";
			break;
		}

		case 2: {    // Course's name
			do {
				Cur = HeadCourse;
				string courseName;
				cout << "New course name: ";
				fflush(stdin);
				getline(cin, courseName);
				fflush(stdin);
				while (Cur != nullptr && Cur->courseName != courseName) {
					Cur = Cur->pNext;
				}
				if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
				else pCur->courseName = courseName;
			} while (Cur);
			cout << "CHANGE SUCCESSFULLY\n";
			break;
		}

		case 3: {    // Teacher's name
			do {
				Cur = HeadCourse;
				string teacherName;
				fflush(stdin);
				cout << "New teacher name: ";
				getline(cin, teacherName);
				fflush(stdin);
				while (Cur != nullptr && Cur->teacherName != teacherName) {
					Cur = Cur->pNext;
				}
				if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
				else pCur->teacherName = teacherName;
			} while (Cur);
			cout << "CHANGE SUCCESSFULLY\n";
			break;
		}

		case 4: {    // session1
			do {
				Cur = HeadCourse;
				int credits;
				cout << "New credit: ";
				cin >> credits;
				while (Cur != nullptr && Cur->credits != credits) {
					Cur = Cur->pNext;
				}
				if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
				else pCur->teacherName = credits;
			} while (Cur);
			cout << "CHANGE SUCCESSFULLY\n";
			break;
		}

		case 5: {    // session1
			do {
				Cur = HeadCourse;
				string session1;
				fflush(stdin);
				cout << "New session1: ";
				getline(cin, session1);
				fflush(stdin);
				while (Cur != nullptr && Cur->session1 != session1) {
					Cur = Cur->pNext;
				}
				if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
				else pCur->session1 = session1;
			} while (Cur);
			cout << "CHANGE SUCCESSFULLY\n";
			break;
		}

		case 6: {    // session2
			do {
				Cur = HeadCourse;
				string session2;
				fflush(stdin);
				cout << "New session2: ";
				getline(cin, session2);
				fflush(stdin);
				while (Cur != nullptr && Cur->session2 != session2) {
					Cur = Cur->pNext;
				}
				if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
				else pCur->session2 = session2;
			} while (Cur);
			cout << "CHANGE SUCCESSFULLY\n";
			break;
		}

		case 7: {    // numberStudent  
			do {
				Cur = HeadCourse;
				int numberStudent;
				cout << "New number of student: ";
				cin >> numberStudent;
				while (Cur != nullptr && Cur->numberStudent != numberStudent) {
					Cur = Cur->pNext;
				}
				if (Cur != nullptr) cout << "This new one is duplicated. Please try again\n";
				else pCur->session2 = numberStudent;
			} while (Cur);
			cout << "CHANGE SUCCESSFULLY\n";
			break;
		}

		}
		// User wants to update more?
		do {
			cout << "Do you want to update anything more?\n";
			cout << "0. NO\t\t" << "1. YES\n";
			cout << "Choose: ";
			cin >> check;
			if (check != 0 && check != 1) cout << "Unidentified. Please try again...\n";
		} while (check != 0 && check != 1);
	}

}

//Delete the course		  
void delete_a_course_in_the_list(CourseDetail*& HeadCourse, string courseID) {
	int check = 1;
	if (HeadCourse == nullptr) {
		cout << "No existed course! Cannot delete! " << endl;
		return;
	}
	while (check) {
		// Searching course
		CourseDetail* pCur;
		do {
			pCur = HeadCourse;
			fflush(stdin);
			cout << "Enter a course ID you want to delete: ";
			getline(cin, courseID);
			fflush(stdin);
			while (pCur && pCur->courseID != courseID)
				pCur = pCur->pNext;
			if (!pCur) cout << "Sorry, we can not find this course. Please try again\n";
		} while (!pCur);

		// Delete course
		if (!pCur) return;
		if (pCur->pNext) pCur->pNext->pPrev = pCur->pPrev;
		if (pCur->pPrev) pCur->pPrev->pNext = pCur->pNext;
		else HeadCourse = pCur->pNext;
		delete pCur;
		cout << "DELETE SUCCESSFULLY\n";

		// Ask user wants to delete more
		do {
			cout << "Do you want to delete any course more?\n";
			cout << "0. NO\t\t" << "1. YES\n";
			cout << "Choose: ";
			cin >> check;
			if (check != 0 && check != 1) cout << "Unidentified. Please try again\n";
		} while (check != 0 && check != 1);
	}
}

//Input list of student
void inputListOfStudent(Class*& cls) {
	int size = 0;
	cout << "Enter the number of students: ";    //Khởi tạo số lượng học sinh
	cin >> size;
	while (size > cls->classSize) {
		cout << "Class size is" << cls->classSize << ". Cannot exceed this size!" << endl;
		cout << "Enter the number of student: ";
		cin >> size;
	}

	int index = 1;
	Student* pCur = cls->HeadStudent;
	while (pCur != nullptr && pCur->pNext != nullptr) {
		pCur = pCur->pNext;
		index++;
	}
		
	cin.get();
	for (int i = 0; i < size; ++i) {
		if (cls->HeadStudent == nullptr) {
			cls->HeadStudent = new Student;
			pCur = cls->HeadStudent;
			pCur->pPrev = nullptr;
			index = 0;
		}
		else {
			pCur->pNext = new Student;
			pCur->pNext->pPrev = pCur;
			pCur = pCur->pNext;
		}
		pCur->pNext = nullptr;

		cout << "-------------------------" << endl;
		cout << "Student " << index + 1 << ": " << endl;        //Thứ tự nhập
		pCur->no = index + 1;
		pCur->className = cls->className;
		
		cout << "Enter Student ID: ";       //Nhập MSSV
		getline(cin, pCur->SID);
		fflush(stdin);

		cout << "Enter student's first name: ";       //Nhập firstname 
		getline(cin, pCur->firstName);
		fflush(stdin);

		cout << "Enter student's last name: ";        //Nhập lastname
		getline(cin, pCur->lastName);
		fflush(stdin);

		cout << "Gender: ";           //Nhập giới tính
		getline(cin, pCur->gender);
		fflush(stdin);

		cout << "Enter student's date of Birth: " << endl;    //Nhập ngày sinh
		cout << "Day: ";
		cin >> pCur->DateOfBirth.day;
		cout << "Month: ";
		cin >> pCur->DateOfBirth.month;
		cout << "Year: ";
		cin >> pCur->DateOfBirth.year;
		fflush(stdin);

		cin.get();
		cout << "Enter student's social ID: ";        //Nhập CMND
		getline(cin, pCur->socialID);

	}
	return;
}

/*
//Đọc ds năm học từ file và in ra màn hình
void display_List_of_schoolYear() {
	ifstream in;
	string path = "Data\\School Year\\List of school year.txt";
	in.open(path);
	if (!in.is_open()) {
		cout << "Cannot display" << endl;
	}
	else {
		cout << "-List of school years-" << endl;
		string year;
		int index = 1;
		while (!in.eof()) {
			getline(in, year);
			cout<< index << ". " << year << endl;
			index++;
		}
		cout << endl;
	}
	in.close();
}*/

/// <summary>
/// Cái đống này của Gia Khánh
/// </summary>
/// <param name="cls"></param>
/// Hàm cho staff xem danh sách học sinh trong 1 lớp
void view_list_of_students_in_class(Class* cls)
{
	if (cls->HeadStudent == nullptr) {
		cout << "No student in class!" << endl;
		//system("pause");
		return;
	}
	Student* pHead = cls->HeadStudent;

	cout << setw(5) << left << "No";
	cout << setw(12) << left << "Student ID";
	cout << setw(12) << left << "First name";
	cout << setw(17) << left << "Last name";
	cout << setw(8) << left << "Gender";
	cout << setw(15) << left << "Date of Birth";
	cout << "Social ID" << endl;

	while (pHead)
	{
		cout << setw(5) << left << pHead->no;
		cout << setw(12) << left << pHead->SID;
		cout << setw(12) << left << pHead->firstName;
		cout << setw(17) << left << pHead->lastName;
		cout << setw(8) << left << pHead->gender;
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.day << "/";
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.month << "/";
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.year;
		cout << setfill(' ') << setw(5) << right << " ";
		cout << pHead->socialID << endl;

		pHead = pHead->pNext;
	}
	return;
}
// Hàm xem danh sách các courses đã đăng ký
void view_list_of_enrolled_course(Student* student)
{
	if (student->Head_of_enrolled_course == nullptr) {
		cout << "No enrolled course!" << endl;
		return;
	}

	cout << "   " << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Teacher Name";
	cout << "Number of credits   ";
	cout << "Maximum number of students in the course   ";
	cout << "Number of students enrolled  ";
	cout << "Session 1  ";
	cout << "Session 2" << endl;

	CourseForEachStudent* Head_course = student->Head_of_enrolled_course;

	while (Head_course)
	{
		cout << Head_course->numberCourse << ". ";
		cout << setw(12) << left << Head_course->detail.courseID;
		cout << setw(35) << left << Head_course->detail.courseName;
		cout << setw(17) << left << Head_course->detail.teacherName;
		cout << setw(13) << right << Head_course->detail.credits;
		cout << setw(32) << right << Head_course->detail.numberStudent;
		cout << setw(36) << right << Head_course->detail.enrolledStudent;
		cout << setw(21) << right << Head_course->detail.session1;
		cout << setw(11) << right << Head_course->detail.session2 << endl;

		Head_course = Head_course->pNext;

		cout << endl;
	}
}
// Hàm cho staff xem danh sách các môn học trong 1 học kỳ
void view_list_of_courses(Semester* semester)
{
	CourseDetail* pHead = semester->HeadCourse;

	cout << "   " << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Lecturer Name";
	cout << "Number of credits   ";
	cout << "Maximum number of students in the course   ";
	cout << "Number of students enrolled  ";
	cout << "Session 1  ";
	cout << "Session 2" << endl;

	int i = 1; // Số thứ tự

	while (pHead)
	{
		cout << i << ". ";
		cout << setw(12) << left << pHead->courseID;
		cout << setw(35) << left << pHead->courseName;
		cout << setw(17) << left << pHead->teacherName;
		cout << setw(13) << right << pHead->credits;
		cout << setw(32) << right << pHead->numberStudent;
		cout << setw(36) << right << pHead->enrolledStudent;
		cout << setw(21) << right << pHead->session1;
		cout << setw(11) << right << pHead->session2 << endl;

		pHead = pHead->pNext;
		++i;

		cout << endl;
	}
}
// Hàm cho staff xem danh sách các lớp trong 1 năm
void view_list_of_class(SchoolYear* year)
{
	if (year->HeadClass == nullptr) {
		cout << "No existed class!" << endl;
		return;
	}
	cout << setw(15) << left << "   Class Name";
	cout << setw(21) << left << "Number of students";
	cout << "Form teacher" << endl;

	Class* pHead = year->HeadClass;

	int i = 1; // Số thứ tự

	while (pHead)
	{
		cout << i << ". ";
		cout << setw(12) << left << pHead->className;
		cout << setw(10) << right << pHead->classSize;
		cout << setw(11) << right << " ";
		cout << pHead->formTeacherName << endl;

		pHead = pHead->pNext;
		++i;
	}
}
//Hàm cho student xem danh sách các môn học họ sẽ học trong học kỳ
void view_list_of_student_course(Student* student)
{
	if (student->Head_of_enrolled_course == nullptr) {
		cout << "No course existed!" << endl;
		return;
	}

	cout << "   " << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Lecturer Name";
	cout << "Number of credits   ";
	cout << "Maximum number of students in the course   ";
	cout << "Number of students enrolled  ";
	cout << "Session 1  ";
	cout << "Session 2" << endl;

	CourseForEachStudent* Head_course = student->Head_of_enrolled_course;

	while (Head_course)
	{
		cout << Head_course->numberCourse << ". ";
		cout << setw(12) << left << Head_course->detail.courseID;
		cout << setw(35) << left << Head_course->detail.courseName;
		cout << setw(17) << left << Head_course->detail.teacherName;
		cout << setw(13) << right << Head_course->detail.credits;
		cout << setw(32) << right << Head_course->detail.numberStudent;
		cout << setw(36) << right << Head_course->detail.enrolledStudent;
		cout << setw(21) << right << Head_course->detail.session1;
		cout << setw(11) << right << Head_course->detail.session2 << endl;

		Head_course = Head_course->pNext;

		cout << endl;
	}
}


/// <summary>
/// Cái đống này của Xuân Quang
/// </summary>
/// <param name="semester_n"></param>
/// <returns></returns>
/// //Hiển thị thông tin của một khóa học
bool go_to_detail_of_a_course(string courseID) {
	if (ThisSemester->HeadCourse == nullptr) {
		cout << "No existed course! Cannot access!" << endl;
		return false;
	}
	else {
		CourseDetail* tempCourse = ThisSemester->HeadCourse;
		while (tempCourse != nullptr && tempCourse->courseID != courseID) {
			tempCourse = tempCourse->pNext;
		}

		if (tempCourse == nullptr) {
			cout << "Course is unavailable! Cannot access!" << endl;
			return false;
		}
		else {
			int choice = 0;
			while (true) {
				system("cls");
				cout << tempCourse->courseName << endl;
				cout << "------------------------" << endl;
				cout << "Course ID: " << tempCourse->courseID << endl;
				cout << "Lecturer: " << tempCourse->teacherName << endl;
				cout << "Credits: " << tempCourse->credits << endl;
				cout << "Maximum slots: " << tempCourse->numberStudent << endl;
				cout << "The number of enrolled students: " << tempCourse->enrolledStudent << endl;
				cout << "Session 1: " << tempCourse->session1 << endl;
				cout << "Session 2: " << tempCourse->session2 << endl;
				cout << "------------------------" << endl;
				cout << endl;
				cout << "List of enrolled students: " << endl;
				if (tempCourse->ListStudent == nullptr) {
					cout << "No student has enrolled this course!" << endl;
				}
				else {

				}

				cout << endl;
				cout << "0. Back" << endl;
				cout << "1. View a student's profile " << endl;
				cout << "2. Export list of enrolled students to .CSV" << endl;
				cout << "3. Import scoreboard of course" << endl;
				cout << "4. View scoreboard (if scoreboard is available)" << endl;
				cout << "User: ";
				cin >> choice;
				switch (choice) {
				case 0:
					return true;
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				}

			}
			return true;
		}
	}
}
//Hiển thị thông tin của một học kỳ
bool go_to_detail_of_a_semester(int semester_n) {
	//Xác định học kỳ mà người dùng đang muốn truy cập
	switch (semester_n) {
	case 1:
		ThisSemester = &ThisYear->semester1;
		break;
	case 2:
		ThisSemester = &ThisYear->semester2;
		break;
	case 3:
		ThisSemester = &ThisYear->semester3;
		break;
	}
	if (ThisSemester->isAvailable == false || ThisSemester == nullptr) {
		return false;
	}
	else {
		while (true) {
			system("cls");
			cout << ThisYear->startYear << "-" << ThisYear->endYear << " >> Semester " << semester_n << endl;
			cout << "----------------------------" << endl;
			//Ngày bắt đầu, kết thúc học kỳ
			cout << "Start date: " << '\t' << ThisSemester->startDate.day << "/" << ThisSemester->startDate.month << "/" << ThisSemester->startDate.year << endl;
			cout << "End date: " << '\t' << ThisSemester->endDate.day << "/" << ThisSemester->endDate.month << "/" << ThisSemester->endDate.year << endl;
			cout << "----------------------------" << endl;
			cout << endl;
			//In ra danh sách môn học
			cout << "List of courses: " << endl;
			//View_list_of_courses_by_XQ();
			view_list_of_courses(ThisSemester);

			int choice = 0;
			cout << endl;
			cout << "0. Back" << endl;
			cout << "1. Go to a course" << endl;
			if (ThisSemester == CurrentSemester) {
				cout << "2. Add one/list of new course" << endl;
				cout << "3. Update a course's detail" << endl;
				cout << "4. Delete a course" << endl;
				cout << "5. Activate course registration system" << endl;
			}
			cout << "User: ";
			cin >> choice;
			string courseID;
			switch (choice) {
			case 0:
				return true;
			case 1:
				cout << "Enter a course's ID (0 to cancle): ";
				cin.get();
				getline(cin, courseID);
				if (courseID == "0") break;
				else go_to_detail_of_a_course(courseID);
				break;
			case 2:
				if(ThisSemester == CurrentSemester)
					create_a_list_of_courses_for_Semester();
				break;
			case 3:
				if (ThisSemester == CurrentSemester) {
					cout << "Enter course's ID to update (0 to cancle): ";
					cin.get();
					getline(cin, courseID);
					if (courseID == "0") break;
					else update_course_detail(ThisSemester->HeadCourse, courseID);
				}
				break;
			case 4:
				if (ThisSemester == CurrentSemester) {
					cout << "Enter course's ID to delete (0 to cancle): ";
					cin.get();
					getline(cin, courseID);
					delete_a_course_in_the_list(ThisSemester->HeadCourse, courseID);
				}
				break;
			case 5:
				break;
			}
		}
		return true;
	}
}
//Hiển thị thông tin của một học sinh trong lớp
bool go_to_detail_of_a_student(Student* HeadStudent, string studentID) {
	if (HeadStudent == nullptr) {
		cout << "No student in class! Cannot access!" << endl;
		system("pause");
		return false;
	}

	Student* tempStudent = HeadStudent;
	while (tempStudent != nullptr && tempStudent->SID != studentID)
		tempStudent = tempStudent->pNext;

	if (tempStudent == nullptr) {
		cout << "Student is unavailable! Cannot access!" << endl;
		system("pause");
		return false;
	}
	else {
		int choice = 0;
		while (true) {
			system("cls");
			cout << "Class " << tempStudent->className << " >> " << studentID << endl;
			cout << "-------------------------------" << endl;
			cout << "Full name: " << tempStudent->firstName << " " << tempStudent->lastName << endl;
			cout << "SID: " << tempStudent->SID << endl;
			cout << "Class: " << tempStudent->className << endl;
			cout << "Gender: " << tempStudent->gender << endl;
			cout << "Date of Birth: " << tempStudent->DateOfBirth.day << "/" << tempStudent->DateOfBirth.month << "/" << tempStudent->DateOfBirth.year << endl;
			cout << "Social ID: " << tempStudent->socialID << endl;
			cout << "-------------------------------" << endl;
			cout << "GPA in this semester: " << tempStudent->GPA << endl;
			cout << "-------------------------------" << endl;
			cout << "Enrolled course: ";
			view_list_of_enrolled_course(tempStudent);

			cout << endl;
			cout << "0. Back" << endl;
			if (ThisYear == CurrentYear && ThisSemester == CurrentSemester) {
				cout << "1. Update student's profile" << endl;
			}
			cout << "User: ";
			cin >> choice;
			switch (choice) {
			case 0:
				return true;
			case 1:
				if (ThisYear == CurrentYear && ThisSemester == CurrentSemester) {

				}
			}
		}
	}
}
//Hiển thị thông tin của một lớp 
bool go_to_detail_of_a_class(string className)   {
	if (ThisYear->HeadClass == nullptr) {
		cout << "No existed class! Cannot access!" << endl;
		system("pause");
		return false;
	}
	Class* tempClass = ThisYear->HeadClass;
	while (tempClass != nullptr && tempClass->className != className)
		tempClass = tempClass->pNext;

	if (tempClass == nullptr) {
		cout << "Class is not available! Cannot access" << endl;
		system("pause");
		return false;
	}
	else {
		int choice = 0;
		while (true) {
			system("cls");
			cout << "Class " << tempClass->className << endl;
			cout << "--------------------------" << endl;
			cout << "Form teacher: " << tempClass->formTeacherName << endl;
			cout << "Students: " << tempClass->classSize << endl;
			cout << "--------------------------" << endl;
			cout << "List of student: " << endl;
			view_list_of_students_in_class(tempClass);

			cout << endl;
			cout << "0. Back" << endl;
			cout << "1. View a student" << endl;
			if (ThisYear == CurrentYear) {
				cout << "2. Add student" << endl;
				cout << "3. Delete a student" << endl;
			}
			cout << "User: ";
			cin >> choice;

			string studentID;
			switch (choice) {
			case 0:
				return true;
			case 1:
				cout << "Enter student ID (0 to cancle): ";
				cin.get();
				getline(cin, studentID);
				if (studentID == "0") break;
				go_to_detail_of_a_student(tempClass->HeadStudent, studentID);
				break;
			case 2:
				if (ThisYear == CurrentYear)
					inputListOfStudent(tempClass);
				break;
			case 3:
				break;
			default:
				cout << "Invalid input! Please try again!" << endl;
				break;
			}
		}
		return true;
	}
}
//Hiển thị thông tin của một năm học	
bool go_to_detail_of_a_year(int startYear) {
	if (HeadYear == nullptr) {			//Nếu chưa có năm học nào cả thì không thể in ra
		cout << "No available school year! Cannot access!" << endl;
		return false;
	}
	else {
		SchoolYear* tempYear = HeadYear;
		while (tempYear != nullptr && tempYear->startYear != startYear) {
			tempYear = tempYear->pNext;
		}
		if (tempYear == nullptr) {
			cout << "Year is unavailable! Cannot access!" << endl;
			return false;
		}
		else {
			string className;
			int choice = 0;
			while (true) {
				system("cls");
				ThisYear = tempYear;
				int startYear = tempYear->startYear;
				int endYear = tempYear->endYear;
				cout << "      " << startYear << "-" << endYear << endl;
				cout << "-------------------------" << endl;
				display_semesters_of_school_year();
				cout << "-------------------------" << endl;
				cout << "List of classes: " << endl;
				//display_classes_list_of_school_year();
				view_list_of_class(ThisYear);

				cout << endl;
				cout << "0. Back" << endl
					<< "1. Go to a class" << endl
					<< "2. Go to a semester" << endl;
				if (ThisYear == CurrentYear) {						//Chỉ được phép tạo học kỳ mới và lớp mới trong năm học hiện tại
					cout << "3. Go to current semester" << endl
						<< "4. Create a new class" << endl
						<< "5. Create a semester" << endl;
				}
				cout << "User: ";
				cin >> choice;
				switch (choice) {
				case 0:
					return true;
				case 1:
					cout << "Enter class name (0 to cancle): ";
					cin.get();
					getline(cin, className);
					if (className == "0") break;
					go_to_detail_of_a_class(className);
					break;
				case 2:
					int semester_n;
					cout << "Enter semester (0 to cancle): ";
					cin >> semester_n;
					if (semester_n == 0) break;											//Nếu người dùng nhập 0 thì dừng
					while (semester_n < 0 || semester_n > 4) {							//Nếu nhập sai thì bắt buộc phải nhập lại
						cout << "Invalid input! Please enter again (0 to cancle): ";
						cin >> semester_n;
					}
					if (!go_to_detail_of_a_semester(semester_n)) {
						cout << endl << "Semester is unavailable! Cannot access!" << endl;
						system("pause");
					}
					break;
				case 3:
					if (ThisYear == CurrentYear) {
						if (CurrentSemester == &CurrentYear->semester1) {
							go_to_detail_of_a_semester(1);
						}
						else if (CurrentSemester == &CurrentYear->semester2) {
							go_to_detail_of_a_semester(2);
						}
						else if (CurrentSemester == &CurrentYear->semester3) {
							go_to_detail_of_a_semester(3);
						}
						else {
							cout << "No available semester! Cannot access!" << endl;
							system("pause");
						}
					}
					break;
				case 4:
					if(ThisYear == CurrentYear) input_classes_for_current_year();	
					break;
				case 5:
					if (ThisYear == CurrentYear) enter_a_semester();				//Nếu không phải năm học hiện tại thì không cho tạo học kỳ
					break;
				default: 
					cout << "Invalid input!" << endl;
					break;
				}
			}
			return true;
		}
	}
}

//Xóa một năm học trong list các năm
bool delete_a_schoolyear(int startYear) {
	if (HeadYear == nullptr) {
		return false;
	}									//DS năm trống thì không thể xóa, báo lỗi
	else {
		SchoolYear* tempYear = HeadYear;						
		while (tempYear != nullptr && tempYear->startYear != startYear)					// Tìm đến năm muốn xóa
			tempYear = tempYear->pNext;

		if (tempYear == nullptr) {							//Không có năm đó thì không cần xóa
			return false;
		}
		else {
			if (tempYear == HeadYear) {
				HeadYear = HeadYear->pNext;
				if(HeadYear != nullptr)
					HeadYear->pPrev = nullptr;
				tempYear->pNext = nullptr;
				delete tempYear;
			}
			else if (tempYear->pNext == nullptr) {
				tempYear->pPrev->pNext = nullptr;
				CurrentYear = CurrentYear->pPrev;
				delete tempYear;
			}
			else {
				tempYear->pPrev->pNext = tempYear->pNext;
				tempYear->pNext->pPrev = tempYear->pPrev;
				delete tempYear;
			}
			return true;
		}
	}
}

//Kiểm tra xem năm học đã được tạo hay chưa
bool isExisted_year(int start_year, int end_year) {
	if (HeadYear == nullptr)						//List null thì nghĩa là chưa có năm nào tồn tại
		return false;
	SchoolYear* tempYear = HeadYear;
	while (tempYear != nullptr && (tempYear->startYear != start_year || tempYear->endYear != end_year))
		tempYear = tempYear->pNext;
	if (tempYear == nullptr)						//Năm học chưa từng tồn tại
		return false;
	return true;									//Năm học đã được tạo rồi
}

void View_list_of_year() {
	while (true) {
		system("cls");

		display_school_year_list();
		int choice = 0;
		cout << "What you want to do?" << endl;
		cout << "0. Back" << endl;
		cout << "1. Go to detail of a school year" << endl;
		cout << "2. Go to current year" << endl;
		cout << "3. Create new school year" << endl;
		cout << "4. Delete a school year" << endl;
		cout << "User: ";
		cin >> choice;
		int schoolYear;
		switch (choice) {
		case 0:			 //Trở về giao diện chính
			return;
		case 1:			//Đi tới thông tin chi tiết của một năm học
			cout << "Enter school year (start year) (0 to cancel): ";
			cin >> schoolYear;
			while (!go_to_detail_of_a_year(schoolYear) && schoolYear != 0) {  //Lặp cho đến khi tìm được năm đã tồn tại
				cout << "Enter school year (start year): ";
				cin >> schoolYear;
			}
			break;
		case 2:
			if (CurrentYear == nullptr) {
				cout << "No existed year! Cannot access!" << endl;
				system("pause");
			}
			else go_to_detail_of_a_year(CurrentYear->startYear);
			break;
		case 3:			// Tạo năm học mới
			input_school_year();
			break;
		case 4:			//Xóa một năm học trong danh sách các năm.
			cout << "Enter school year you want to delete (start year): ";
			cin >> schoolYear;
			if (!delete_a_schoolyear(schoolYear)) {
				cout << "Something wrong! Cannot delete this year!" << endl;
				system("pause");
			}
			break;

		}
	}
}


//Giao diện khi staff khởi động chương trình
void StaffInterface() {
	while (true) {
		system("cls");

		int choice = 0;
		cout << "1. View list of years" << endl;
		cout << "2. Go to current year" << endl;
		cout << "3. Go to current semester" << endl;
		cout << "4. Exit program" << endl;
		cout << "User: ";
		cin >> choice;
		if (choice == 4)
			break;
		switch (choice) {
		case 1:
			View_list_of_year();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			return;
		}
	}
}

