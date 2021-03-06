#include "DataStructure.h"

//bool Available_register;
bool Available_all_scoreboard;

void View_list_of_year();
bool isExisted_year(int start_year, int end_year);					//Hàm kiểm tra xem năm đó đã tồn tại hay chưa
bool delete_a_schoolyear(int startYear);
bool go_to_detail_of_a_student(Student*& HeadStudent, string studentID);
bool go_to_detail_of_a_class(string className);
bool go_to_detail_of_a_course(string courseID);
bool go_to_detail_of_a_semester(int semester_n);
bool go_to_detail_of_a_year(int startYear);
void View_list_of_Enrolled_student(CourseDetail* course);
void delete_a_student(Student*& HeadStudent, int& classSize);
bool Check_all_scoreboard_available();								//Hàm check xem tất cả các môn đều đã có bảng điểm hết hay chưa
//void View_list_of_courses_by_XQ();
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
		Update_automatically();
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
		cout << "Please enter the class's form teacher name: ";		getline(cin, pCur_class->formTeacherName);
		pCur_class->classSize = 0;						//Lớp mới tạo chưa có sv

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
		Year->semester1.numberOfCourse = 0;											//Số môn học sẽ bằng 0
		break;
	}
	case 2:		// Học kỳ 2
	{
		Year->semester2.isAvailable = true;
		Year->semester2.startDate = start_date;
		Year->semester2.endDate = end_date;
		Year->semester2.HeadCourse = nullptr;
		Year->semester2.numberOfCourse = 0;
		break;
	}
	case 3:		// Học kỳ 3
	{
		Year->semester3.isAvailable = true;
		Year->semester3.startDate = start_date;
		Year->semester3.endDate = end_date;
		Year->semester3.HeadCourse = nullptr;
		Year->semester3.numberOfCourse = 0;
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
	Available_all_scoreboard = false;
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

		cout << char(218);
		for (int i = 0; i < 26; ++i)
			cout << char(196);
		cout << char(191) << endl;

		cout << char(179) << "   List of school years   " << char(179) << endl;

		cout << char(195);
		for (int i = 0; i < 26; ++i)
			cout << char(196);
		cout << char(180) << endl;

		int index = 1;
		SchoolYear* pCur = HeadYear;
		while (pCur != nullptr)
		{
			cout << char(179);
			cout << setw(5) << left << index;
			cout << "    " << pCur->startYear << "-" << pCur->endYear << setw(8) << " " << char(179) << endl;
			pCur = pCur->pNext;
			++index;
		}

		cout << char(192);
		for (int i = 0; i < 26; ++i)
			cout << char(196);
		cout << char(217) << endl;

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

		pCur->HeadStudent = nullptr;		// Môn học mới tạo chưa có người đăng ký
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
			Student_CourseScores* pCur_Student_CourseScores = pCur_course->HeadStudent;	// Xóa danh sách điểm của course này
			while (pCur_Student_CourseScores != nullptr)
			{
				Student_CourseScores* delete_Student_CourseScores = pCur_Student_CourseScores;
				pCur_Student_CourseScores = pCur_Student_CourseScores->pNext;
				delete delete_Student_CourseScores;
			}

			CourseDetail* delete_course = pCur_course;
			pCur_course = pCur_course->pNext;
			delete delete_course;
		}

		pCur_course = pCur_year->semester2.HeadCourse;	// Của học kỳ 2, copy-paste
		while (pCur_course != nullptr)
		{


			Student_CourseScores* pCur_Student_CourseScores = pCur_course->HeadStudent;
			while (pCur_Student_CourseScores != nullptr)
			{
				Student_CourseScores* delete_Student_CourseScores = pCur_Student_CourseScores;
				pCur_Student_CourseScores = pCur_Student_CourseScores->pNext;
				delete delete_Student_CourseScores;
			}

			CourseDetail* delete_course = pCur_course;
			pCur_course = pCur_course->pNext;
			delete delete_course;
		}

		pCur_course = pCur_year->semester3.HeadCourse;	// Và học kỳ 3
		while (pCur_course != nullptr)
		{

			Student_CourseScores* pCur_Student_CourseScores = pCur_course->HeadStudent;
			while (pCur_Student_CourseScores != nullptr)
			{
				Student_CourseScores* delete_Student_CourseScores = pCur_Student_CourseScores;
				pCur_Student_CourseScores = pCur_Student_CourseScores->pNext;
				delete delete_Student_CourseScores;
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
		system("pause");
		return;
	}

	// Searching course
	CourseDetail* pCur = HeadCourse;
	while (pCur != nullptr && pCur->courseID != courseID)
		pCur = pCur->pNext;
	if (pCur == nullptr) {
		cout << "Course is unavailable! Cannot update!";
		_getch();
		return;
	}

	cout << "*------------------------------------------------------------*\n";
	cout << "\t\tWHAT WOULD YOU LIKE TO UPDATE?\n";
	cout << "*------------------------------------------------------------*\n";
	cout << "\t0. Cancle update" << endl;
	cout << "\t1. Course ID\t\t" << "2. Course's name\n";
	cout << "\t3. Teacher's name\t" << "4. Credit\n";
	cout << "\t5. Session 1\t\t" << "6. Session 2\n";
	cout << "\t\t7. Number of student\n";

	while (check == 1) {
		// Choose something to update
		int choose;
		do {
			cout << "User: ";
			cin >> choose;
			cin.get();
			if (choose == 0) {
				cout << "CANCLE UPDATE!";
				_getch();
				return;
			}
			if (choose < 1 || choose > 7) cout << "Invalid input. Please try again\n";
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
		cout << "Do you want to update anything more?\n";
		cout << " 1. YES            2. NO" << endl;
		do {
			cout << "User: ";
			cin >> check;
			if (check != 2 && check != 1) cout << "Invalid input! Please try again...\n";
		} while (check != 2 && check != 1);
	}

}
//Delete the course		  
void delete_a_course_in_the_list(CourseDetail*& HeadCourse, string courseID) {
	int check = 1;
	if (HeadCourse == nullptr) {
		cout << "No existed course! Cannot delete! " << endl;
		system("pause");
		return;
	}
	while (check == 1) {
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

		int sure_delete = 1;
		cout << "Are you sure delete the course?" << endl;
		cout << "1. YES			2.NO" << endl;
		cout << "User: ";
		cin >> sure_delete;
		while (sure_delete != 1 && sure_delete != 2) {
			cout << "Invalid input! Please try again!" << endl;
			cout << "User: ";
			cin >> sure_delete;
		}
		if (sure_delete == 1) {
			if (pCur->pNext) pCur->pNext->pPrev = pCur->pPrev;
			if (pCur->pPrev) pCur->pPrev->pNext = pCur->pNext;
			else HeadCourse = pCur->pNext;
			delete pCur;
			cout << "DELETE SUCCESSFULLY\n";

			// Ask user wants to delete more
			do {
				cout << "Do you want to delete any course more?\n";
				cout << "1. YES\t\t" << "2. NO\n";
				cout << "Choose: ";
				cin >> check;
				if (check != 0 && check != 1) cout << "Invalid input! Please try again!\n";
			} while (check != 0 && check != 1);
		}
		else {
			cout << "CANCLE DELETE!";
			_getch();
			return;
		}
	}
}
//Input list of student
void inputListOfStudent(Class*& cls) {
	int size = 0;
	cout << "Enter the number of students: ";    //Khởi tạo số lượng học sinh
	cin >> size;
	if (size == 0)								//Nếu số sv nhập vào là 0 thì không cần thực thi làm gì
		return;
	while (size < 0) {
		cout << "Invalid input! Please try again!" << endl;
		cout << "Enter the number of students: ";
		cin >> size;
	}
	cls->classSize += size;						 //Số sv trong lớp được tăng thêm size đơn vị

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
		pCur->FirstYear = CurrentYear->startYear;	//Năm nhập học của sinh viên sẽ là năm sinh viên được thêm vào danh sách
		pCur->gpa = 0;
	}
	return;
}
//Lấy điểm từ file CSV vào hệ thống
bool import_course_score_from_CSV(string path, Student_CourseScores*& head_Course_Score) {

	ifstream imfile;
	imfile.open(path);
	if (!imfile.is_open()) {
		cout << "Could not open the file\n";
		_getch();
		return false;	
	}

	//Tạo các học sinh trong CourseScore
	Student_CourseScores* pCur_Course_Score = head_Course_Score;
	string headLine;
	string no, courseGPA, final, midterm, otherMark, SID, firstName, lastName, gender, className;
	getline(imfile, headLine);
	while (!imfile.eof() && pCur_Course_Score != nullptr) {
		// //-----DÙNG ĐỂ TEST(KHI KHÔNG CÓ DỮ LIỆU TRƯỚC)----
		// if(head_Course_Score == nullptr){
		//     head_Course_Score = new Student_CourseScores;
		//     pCur_Course_Score = head_Course_Score;
		//     pCur_Course_Score->pPrev = nullptr;
		// }else{
		//     pCur_Course_Score->pNext = new Student_CourseScores;
		//     pCur_Course_Score->pNext->pPrev = pCur_Course_Score;
		//     pCur_Course_Score = pCur_Course_Score->pNext;
		// }
		// pCur_Course_Score->pNext = nullptr;

		// //------------------------------------------------
		
		getline(imfile, no, ',');           //Lưu vào chỗ khác do không cần thiết               
		getline(imfile, SID, ',');          //Lưu vào chỗ khác do không cần thiết
		getline(imfile, firstName, ',');    //Lưu vào chỗ khác do không cần thiết
		getline(imfile, lastName, ',');     //Lưu vào chỗ khác do không cần thiết
		getline(imfile, gender, ',');
		getline(imfile, className, ',');    //Lưu vào chỗ khác do không cần thiết
	

		getline(imfile, midterm, ',');                      //Import midterm
		pCur_Course_Score->midterm = stof(midterm);
		pCur_Course_Score->point_to_an_enrolled_course_of_a_student_in_a_class->midterm = pCur_Course_Score->midterm;  //Lưu ở 2 đầu
		//cout << "midterm" << pCur_Course_Score->midterm << endl;

		getline(imfile, final, ',');                        //Import final 
		pCur_Course_Score->final = stof(final);
		pCur_Course_Score->point_to_an_enrolled_course_of_a_student_in_a_class->final = stof(final);	//Lưu ở 2 đầu
		//cout << "Final " << pCur_Course_Score->final << endl;

		getline(imfile, otherMark, ',');                    //Import othrmark
		pCur_Course_Score->otherMark = stof(otherMark);
		pCur_Course_Score->point_to_an_enrolled_course_of_a_student_in_a_class->otherMark = stof(otherMark);	//Lưu ở 2 đầu
		//cout << "Other mark " << pCur_Course_Score->otherMark << endl;

		pCur_Course_Score = pCur_Course_Score->pNext;
	}

	imfile.close();
	return true;
};
//Xuất điểm 1 môn từ hệ thống qua file CSV
bool export_course_score_to_CSV(string path, Student_CourseScores* head_Course_Score) {
	Student_CourseScores* pCur_Course_Score = head_Course_Score;
	ofstream exfile;
	exfile.open(path);

	if (!exfile.is_open()) {
		cout << "Could not open the file\n";
		return false;
	}

	//Truyền data vào file CSV
	exfile << "No,Student ID,Student First Name,Student Last Name,Gender,Class Name,Midterm Mark,Final Mark,Other Mark\n";
	while (pCur_Course_Score) {

		exfile << pCur_Course_Score->no << "," << pCur_Course_Score->SID << "," << pCur_Course_Score->firstName << "," << pCur_Course_Score->lastName << "," << pCur_Course_Score->gender << ",";
		exfile << pCur_Course_Score->className << "," << pCur_Course_Score->midterm << "," << pCur_Course_Score->final << "," << pCur_Course_Score->otherMark << "\n";

		pCur_Course_Score = pCur_Course_Score->pNext;
	}

	exfile.close();
	return true;
}
//Thay đổi thông tin của sv
void update_student_profile(Student*& HeadStudent, Student*& student) {
	int check = 1;
	string studentID;
	cout << "*------------------------------------------------------------*\n";
	cout << "\t\tWHAT WOULD YOU LIKE TO UPDATE?\n";
	cout << "*------------------------------------------------------------*\n";
	cout << "\t0. Cancle update" << endl;
	cout << "\t1. Student's ID\t\t" << "2. First name\n";
	cout << "\t3. Last name\t\t" << "4. Gender\n";
	cout << "\t5. Social ID\t\t" << "6. Date of birth\n";
	while (check == 1) {

		int staff;
		cout << "User: ";
		cin >> staff;
		if (staff == 0) {
			cout << "CANCLE UPDATE!";
			_getch();
			return;
		}
		while (staff < 1 || staff > 10) {
			cout << "Invalid input! Please try again!" << endl;
			cout << "User: ";
			cin >> staff;
		}

		Student* Cur = HeadStudent;
		string data;
		switch (staff) {
			  //Student ID
		case 1: 
			do {
				Cur = HeadStudent;
				cin.get();
				cout << "New student ID: ";
				getline(cin, data);
				//fflush(stdin);
				while (Cur != nullptr && Cur->SID != data) {
					Cur = Cur->pNext;
				}
				if (Cur != nullptr) cout << "This new one is duplicated. Please try again!\n";
				else student->SID = data;
			} while (Cur);

			cout << "CHANGE SUCCESSFULLY!\n";
			break;
			  // Firstname
		case 2: 
			cin.get();
			cout << "New first name: ";
			getline(cin, data);
			//fflush(stdin);
			student->firstName = data;
			cout << "CHANGE SUCCESSFULLY!\n";
			break;
			  // Lastname
		case 3: 
			cin.get();
			cout << "New last name: ";
			getline(cin, data);
			//fflush(stdin);
			student->lastName = data;

			cout << "CHANGE SUCCESSFULLY!\n";
			break;
			  // Gender
		case 4:
			cin.get();
			cout << "New gender: ";
			getline(cin, data);
			while (data != "male" || data != "female" || data != "MALE" || data != "FEMALE") {
				cout << "Invalid input! Please try again!" << endl;
				cout << "New gender: ";
				getline(cin, data);
			}
			//fflush(stdin);
			student->gender = data;
			cout << "CHANGE SUCCESSFULLY!\n";
			break;
			  // Social ID
		case 5:
			cin.get();
			cout << "New social ID: ";
			getline(cin, data);
			//fflush(stdin);
			student->socialID = data;

			cout << "CHANGE SUCCESSFULLY!\n";
			break;
			  // Date of birth 
		case 6: 
		{
			cin.get();
			int day, month, year;
			cout << "New day of birth: ";
			cout << "Day: ";     cin >> day;
			while (day < 1 || day > 31) {
				cout << "Invalid input! Please try again!" << endl;
				cout << "Day: "; cin >> day;
			}
			cout << "Month: ";   cin >> month;
			while (month < 1 || month > 12) {
				cout << "Invalid input! Please try again!" << endl;
				cout << "Month: "; cin >> month;
			}
			cout << "Year: ";    cin >> year;
			while (year < 1900) {
				cout << "Invalid input! Please try again!" << endl;
				cout << "Year: "; cin >> year;
			}

			student->DateOfBirth.day = day;
			student->DateOfBirth.month = month;
			student->DateOfBirth.year = year;

			cout << "CHANGE SUCCESSFULLY!\n";
			break;
		}
		}


		// User wants to update more?
		cout << "Do you want to update anything more?\n";
		cout << " 1. YES           2.NO" << endl;
		do {
			cout << "User: ";
			cin >> check;
			if (check != 2 && check != 1)
				cout << "Invalid input. Please try again\n";
		} while (check != 2 && check != 1);

	}

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

	cout << char(218);
	for (int i = 0; i < 78; ++i)
		cout << char(196);
	cout << char(191) << endl;

	cout << char(179);
	cout << setw(5) << left << "No";
	cout << setw(12) << left << "Student ID";
	cout << setw(12) << left << "First name";
	cout << setw(17) << left << "Last name";
	cout << setw(8) << left << "Gender";
	cout << setw(15) << left << "Date of Birth";
	cout << setw(9) << left << "Social ID" << char(179) << endl;

	cout << char(195);
	for (int i = 0; i < 78; ++i)
		cout << char(196);
	cout << char(180) << endl;

	while (pHead)
	{
		cout << char(179);
		cout << setw(5) << left << pHead->no;
		cout << setw(12) << left << pHead->SID;
		cout << setw(12) << left << pHead->firstName;
		cout << setw(17) << left << pHead->lastName;
		cout << setw(8) << left << pHead->gender;
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.day << "/";
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.month << "/";
		cout << setfill('0') << setw(2) << right << pHead->DateOfBirth.year;
		cout << setfill(' ') << setw(5) << right << " ";
		cout << setw(9) << left << pHead->socialID;
		cout << char(179) << endl;

		pHead = pHead->pNext;
	}

	cout << char(192);
	for (int i = 0; i < 78; ++i)
		cout << char(196);
	cout << char(217) << endl;
	return;
}
// Hàm cho staff xem danh sách các môn học trong 1 học kỳ
void view_list_of_courses(Semester* semester)
{
	CourseDetail* pHead = semester->HeadCourse;

	cout << char(218);
	for (int i = 0; i < 184; ++i)
		cout << char(196);
	cout << char(191) << endl;

	cout << char(179);
	cout << setw(5) << left << "No";
	cout << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Lecturer Name";
	cout << "Number of credits   ";
	cout << "Maximum number of students in the course   ";
	cout << "Number of students enrolled  ";
	cout << "Session 1  ";
	cout << "Session 2" << char(179) << endl;

	int i = 1; // Số thứ tự

	cout << char(195);
	for (int i = 0; i < 184; ++i)
		cout << char(196);
	cout << char(180) << endl;

	while (pHead)
	{
		cout << char(179);
		cout << setw(5) << left << i;
		cout << setw(12) << left << pHead->courseID;
		cout << setw(35) << left << pHead->courseName;
		cout << setw(17) << left << pHead->teacherName;
		cout << setw(13) << right << pHead->credits;
		cout << setw(32) << right << pHead->numberStudent;
		cout << setw(36) << right << pHead->enrolledStudent;
		cout << setw(21) << right << pHead->session1;
		cout << setw(11) << right << pHead->session2;
		cout << "  " << char(179) << endl;

		pHead = pHead->pNext;
		++i;
	}

	cout << char(192);
	for (int i = 0; i < 184; ++i)
		cout << char(196);
	cout << char(217) << endl;
}

// Hàm cho staff xem danh sách các lớp trong 1 năm
void view_list_of_class(SchoolYear* year)
{
	if (year->HeadClass == nullptr) {
		cout << "No existed class!" << endl;
		return;
	}

	cout << char(218);
	for (int i = 0; i < 66; ++i)
		cout << char(196);
	cout << char(191) << endl;

	cout << char(179);
	cout << setw(5) << left << "No";
	cout << setw(15) << left << "Class Name";
	cout << setw(21) << left << "Number of students";
	cout << setw(25) << left << "Form teacher" << char(179) << endl;

	Class* pHead = year->HeadClass;

	int i = 1; // Số thứ tự

	cout << char(195);
	for (int i = 0; i < 66; ++i)
		cout << char(196);
	cout << char(180) << endl;

	while (pHead)
	{
		cout << char(179);
		cout << setw(5) << left << i;
		cout << setw(15) << left << pHead->className;
		cout << setw(10) << right << pHead->classSize;
		cout << setw(11) << right << " ";
		cout << setw(25) << left << pHead->formTeacherName;  // Truong Thuy Tuong Khanh
		cout << char(179) << endl;

		pHead = pHead->pNext;
		++i;
	}

	cout << char(192);
	for (int i = 0; i < 66; ++i)
		cout << char(196);
	cout << char(217) << endl;
}

//Hàm cho student xem danh sách các môn học họ sẽ học trong học kỳ
void view_list_of_student_course(Student* student)
{
	if (student->Head_of_enrolled_course == nullptr) {
		cout << "No course existed!" << endl;
		return;
	}

	cout << char(218);
	for (int i = 0; i < 182; ++i)
		cout << char(196);
	cout << char(191) << endl;

	cout << char(179);
	cout << "   " << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Lecturer Name";
	cout << "Number of credits   ";
	cout << "Maximum number of students in the course   ";
	cout << "Number of students enrolled  ";
	cout << "Session 1  ";
	cout << "Session 2" << char(179) << endl;

	cout << char(195);
	for (int i = 0; i < 182; ++i)
		cout << char(196);
	cout << char(180) << endl;

	CourseForEachStudent* Head_course = student->Head_of_enrolled_course;

	while (Head_course)
	{
		cout << char(179);
		cout << Head_course->numberCourse << ". ";
		cout << setw(12) << left << Head_course->detail.courseID;
		cout << setw(35) << left << Head_course->detail.courseName;
		cout << setw(17) << left << Head_course->detail.teacherName;
		cout << setw(13) << right << Head_course->detail.credits;
		cout << setw(32) << right << Head_course->detail.numberStudent;
		cout << setw(36) << right << Head_course->detail.enrolledStudent;
		cout << setw(21) << right << Head_course->detail.session1;
		cout << setw(11) << right << Head_course->detail.session2;
		cout << "  " << char(179) << endl;

		Head_course = Head_course->pNext;
	}

	cout << char(192);
	for (int i = 0; i < 182; ++i)
		cout << char(196);
	cout << char(217) << endl;
}

//Hàm cho staff xem scoreboard của môn
void print(float n)
{
	for (int i = 0; i < 10; ++i)
		if (abs(n - (int)n - (float)i / 10) < 0.00001)
		{

			cout << setw(4) << left << setprecision(1) << fixed << n;
			return;
		}

	cout << setw(4) << left << setprecision(2) << fixed << n;
}
void View_scoreboard_of_a_course(CourseDetail* course) {
	system("cls");
	int semester_n;
	if (CurrentSemester == &CurrentYear->semester1) semester_n = 1;
	else if (CurrentSemester == &CurrentYear->semester2) semester_n = 2;
	else semester_n = 3;

	cout << CurrentYear->startYear << "-" << CurrentYear->endYear << " >> Semester " << semester_n << " >> " << course->courseName << " >> Scoreboard " << endl;
	cout << "------------------------------------------------------------------------------" << endl;

	if (course->HeadStudent == nullptr) {
		cout << "No student!" << endl;
		return;
	}
	Student_CourseScores* pCur = course->HeadStudent;

	cout << char(218);
	for (int i = 0; i < 96; ++i)
		cout << char(196);
	cout << char(191) << endl;

	cout << char(179);
	cout << setw(5) << left << "No";
	cout << setw(12) << left << "Student ID";
	cout << setw(12) << left << "First name";
	cout << setw(17) << left << "Last name";
	cout << setw(10) << left << "Class";
	cout << setw(9) << left << "Midterm";
	cout << setw(7) << left << "Final";
	cout << setw(12) << left << "Other mark";
	cout << "Course's GPA" << char(179) << endl;

	cout << char(195);
	for (int i = 0; i < 96; ++i)
		cout << char(196);
	cout << char(180) << endl;

	while (pCur != nullptr) {
		cout << char(179);
		cout << setw(5) << left << pCur->no;
		cout << setw(12) << left << pCur->SID;
		cout << setw(12) << left << pCur->firstName;
		cout << setw(17) << left << pCur->lastName;
		cout << setw(10) << left << pCur->className;
		cout << setw(2) << right << " ";  print(pCur->midterm);
		cout << setw(4) << right << " "; print(pCur->final);
		cout << setw(5) << right << " "; print(pCur->otherMark);
		cout << setw(9) << left << " "; print(pCur->courseGPA);
		cout << "    " << char(179) << endl;

		pCur = pCur->pNext;
	}

	cout << char(192);
	for (int i = 0; i < 96; ++i)
		cout << char(196);
	cout << char(217) << endl;
	cout << endl; 

	int choice = 0;
	cout << "0. Return" << endl;
	cout << "User: ";
	cin >> choice;

	while (choice != 0) {
		cout << "Invalid input! Please try again!" << endl;
		cout << "User: ";
		cin >> choice;
	}

	return;
}
//Hiển thị danh sách những sinh viên đã đăng ký môn
void View_list_of_Enrolled_student(CourseDetail* course) {
	if (course->HeadStudent == nullptr) {
		cout << "No student!" << endl;
		return;
	}
	Student_CourseScores* pCur = course->HeadStudent;

	cout << char(218);
	for (int i = 0; i < 96; ++i)
		cout << char(196);
	cout << char(191) << endl;

	cout << char(179);
	cout << setw(5) << left << "No";
	cout << setw(12) << left << "Student ID";
	cout << setw(12) << left << "First name";
	cout << setw(17) << left << "Last name";
	cout << setw(10) << left << "Class";
	cout << setw(9) << left << "Midterm";
	cout << setw(7) << left << "Final";
	cout << setw(12) << left << "Other mark";
	cout << "Course's GPA" << char(179) << endl;

	cout << char(195);
	for (int i = 0; i < 96; ++i)
		cout << char(196);
	cout << char(180) << endl;

	while (pCur != nullptr) {
		cout << char(179);
		cout << setw(5) << left << pCur->no;
		cout << setw(12) << left << pCur->SID;
		cout << setw(12) << left << pCur->firstName;
		cout << setw(17) << left << pCur->lastName;
		cout << setw(10) << left << pCur->className;
		cout << setw(2) << right << " ";  print(pCur->midterm);
		cout << setw(4) << right << " "; print(pCur->final);
		cout << setw(5) << right << " "; print(pCur->otherMark);
		cout << setw(9) << left << " "; print(pCur->courseGPA);
		cout << "    " << char(179) << endl;

		pCur = pCur->pNext;
	}

	cout << char(192);
	for (int i = 0; i < 96; ++i)
		cout << char(196);
	cout << char(217) << endl;
}

// Hàm in danh sách các courses student đã đăng ký
void view_list_of_enrolled_course(Student* student)
{
	if (student->Head_of_enrolled_course == nullptr) {
		cout << "No enrolled course!" << endl;
		return;
	}

	cout << char(218);
	for (int i = 0; i < 114; ++i)
		cout << char(196);
	cout << char(191) << endl;

	cout << char(179);
	cout << "   " << setw(12) << left << "Course ID";
	cout << setw(35) << "Course Name";
	cout << setw(20) << left << "Lecturer Name";
	cout << "Number of credits   ";
	cout << setw(15) << "Session 1  ";
	cout << setw(8) << "Session 2" << char(179) << endl;

	cout << char(195);
	for (int i = 0; i < 114; ++i)
		cout << char(196);
	cout << char(180) << endl;

	CourseForEachStudent* Head_course = student->Head_of_enrolled_course;

	while (Head_course)
	{
		cout << char(179);
		cout << Head_course->numberCourse << ". ";
		cout << setw(12) << left << Head_course->detail.courseID;
		cout << setw(35) << left << Head_course->detail.courseName;
		cout << setw(17) << left << Head_course->detail.teacherName;
		cout << setw(13) << right << Head_course->detail.credits;
		cout << setw(17) << right << Head_course->detail.session1;
		cout << setw(15) << right << Head_course->detail.session2;
		cout << "  " << char(179) << endl;

		Head_course = Head_course->pNext;
	}

	cout << char(192);
	for (int i = 0; i < 114; ++i)
		cout << char(196);
	cout << char(217) << endl;
}

//Hàm in bảng điểm của cả lớp
void view_class_scoreboard(Class* cls)
{
	system("cls");
	cout << CurrentYear->startYear << "-" << CurrentYear->endYear << " >> Class " << cls->className << " >> " << "Class scoreboard" << endl;
	cout << "---------------------------------------------" << endl;

	if (cls->HeadStudent == nullptr)
	{
		cout << "There are no students in the class." << endl;
		return;
	}

	Student* headstudent = cls->HeadStudent;
	CourseForEachStudent* headcourse;
	CourseForEachStudent* pCur;
	int numberOfCourse;                                           // Biến số lượng số môn học 1 sinh viên đã học

	cout << char(218);
	for (int i = 0; i < 108; ++i)
		cout << char(196);
	cout << char(191) << endl;

	cout << char(179);
	cout << "No  ";
	cout << "First name  ";
	cout << setw(18) << left << "Last name";
	cout << setw(14) << left << "Student ID";
	cout << "Number of courses  ";
	cout << "Overall GPA  ";
	cout << "Course ID  ";
	cout << "Final  ";
	cout << "Course GPA" << char(179) << endl;

	cout << char(195);
	for (int i = 0; i < 108; ++i)
		cout << char(196);
	cout << char(180) << endl;

	while (headstudent != nullptr)
	{
		headcourse = headstudent->Head_of_enrolled_course;
		pCur = headcourse;

		while (pCur != nullptr && pCur->pNext != nullptr)
			pCur = pCur->pNext;

		if (pCur == nullptr)
			numberOfCourse = 0;
		else
			numberOfCourse = pCur->numberCourse;

		cout << char(179);
		cout << setw(4) << left << headstudent->no;
		cout << setw(12) << left << headstudent->firstName;
		cout << setw(18) << left << headstudent->lastName;
		cout << setw(14) << left << headstudent->SID;
		cout << setw(9) << right << numberOfCourse;
		cout << setw(14) << " "; print(headstudent->gpa);

		if (numberOfCourse == 0)
			cout << setw(33) << right << " " << char(179) << endl;

		else
		{
			cout << setw(5) << right << " " << setw(11) << left << headcourse->detail.courseID;
			cout << " "; print(headcourse->final);
			cout << setw(7) << right << " "; print(headcourse->courseGPA);
			cout << " " << char(179) << endl;

			headcourse = headcourse->pNext;
			while (headcourse != nullptr)
			{
				cout << char(179);
				cout << setw(80) << right << " " << setw(11) << left << headcourse->detail.courseID;
				cout << " "; print(headcourse->final);
				cout << setw(7) << right << " "; print(headcourse->courseGPA);
				cout << " " << char(179) << endl;

				headcourse = headcourse->pNext;
			}
		}

		headstudent = headstudent->pNext;
		if (headstudent != nullptr)
		{
			cout << char(179) << setw(108) << right << " " << char(179) << endl;
			cout << char(179) << setw(108) << right << " " << char(179) << endl;
		}
	}

	cout << char(192);
	for (int i = 0; i < 108; ++i)
		cout << char(196);
	cout << char(217) << endl;

	int user;
	cout << "0. Return" << endl;
	cout << "User: ";
	cin >> user;
	while (user != 0) {
		cout << "Invalid input! Please try again!" << endl;
		cout << "User: ";
		cin >> user;
	}

	return;
}



/// <summary>
/// Cái đống này của Xuân Quang
/// </summary>
/// <param name="semester_n"></param>
/// <returns></returns>
/// //Hiển thị thông tin của một khóa học
bool go_to_detail_of_a_course(string courseID) {
	if (ThisSemester->HeadCourse == nullptr) {
		cout << "No existed course! Cannot access!";
		_getch();
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
				cout << "--------------------------------" << endl;
				cout << "Course ID: " << tempCourse->courseID << endl;
				cout << "Lecturer: " << tempCourse->teacherName << endl;
				cout << "Credits: " << tempCourse->credits << endl;
				cout << "Maximum slots: " << tempCourse->numberStudent << endl;
				cout << "The number of enrolled students: " << tempCourse->enrolledStudent << endl;
				cout << "Session 1: " << tempCourse->session1 << endl;
				cout << "Session 2: " << tempCourse->session2 << endl;
				cout << "--------------------------------" << endl;
				cout << "List of enrolled students: " << endl;
				View_list_of_Enrolled_student(tempCourse);

				if (tempCourse->Available_scoreboard == true) {
					cout << endl;
					cout << "*** NOTIFICATION ***" << endl;
					cout << "Course's scoreboard is available now. To view scoreboard, choose OPTION 3." << endl;
				}

				cout << endl;
				cout << "0. Back" << endl;
				cout << "1. Export list of enrolled students to .CSV" << endl;
				cout << "2. Import scoreboard of course" << endl;
				if (tempCourse->Available_scoreboard == true)
					cout << "3. View scoreboard" << endl;
				cout << "User: ";
				cin >> choice;
				string path;
				switch (choice) {
				case 0:
					return true;
					break;
				case 1:
					path = "Data\\" + tempCourse->courseName + ".csv";
					if (export_course_score_to_CSV(path, tempCourse->HeadStudent)) {
						cout << "Exports successfully!";
						_getch();
					}
					break;
				case 2:
					path = "Data\\" + tempCourse->courseName + ".csv";
					if (import_course_score_from_CSV(path, tempCourse->HeadStudent)) {
						tempCourse->Available_scoreboard = true;
						GPAStudentInCourse(tempCourse->HeadStudent);
						cout << "Import successfully! Course's scoreboard is available now!" << endl;
						if (Check_all_scoreboard_available() == true) {
							Available_all_scoreboard = true;
							Class* CurClass = CurrentYear->HeadClass;
							while (CurClass != nullptr) {
								GPASemesterOfStudent(CurClass->HeadStudent);
								CurClass = CurClass->pNext;
							}
						}
						_getch();
					}
					break;
				case 3:
					if (tempCourse->Available_scoreboard == true) {
						View_scoreboard_of_a_course(tempCourse);
					}
					break;
				default:
					cout << "Invalid input!" << endl;
					cout << "User: ";
					cin >> choice;
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

			if (Available_all_scoreboard) {
				cout << endl;
				cout << "*** NOTIFICATION ***" << endl;
				cout << "All scoreboards are available now! Now you can view class's scoreboard, course's scoreboard and student's scoreboard." << endl;
			}

			int choice = 0;
			cout << endl;
			cout << "0. Back" << endl;
			cout << "1. Go to a course" << endl;
			if (ThisSemester == CurrentSemester) {
				cout << "2. Add one/list of new course" << endl;
				cout << "3. Update a course's detail" << endl;
				cout << "4. Delete a course" << endl;
				if (Available_register == false) {
					cout << "5. Activate course registration system" << endl;
				}
				else cout << "5. Close course registration system" << endl;
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
				if (ThisSemester == CurrentSemester && ThisYear == CurrentYear) {
					if (Available_register == false) {
						Available_register = true;
						cout << endl;
						cout << "Course registration session is ACTIVE now!";
						_getch();
					}
					else {
						Available_register = false;
						cout << endl;
						cout << "Course registration session is CLOSE now!";
						_getch();
					}
				}
				break;
			}
		}
		return true;
	}
}
//Hiển thị thông tin của một học sinh trong lớp
bool go_to_detail_of_a_student(Student*& HeadStudent, string studentID) {
	if (HeadStudent == nullptr) {
		cout << "No student in class! Cannot access!";
		_getch();
		return false;
	}

	Student* tempStudent = HeadStudent;
	while (tempStudent != nullptr && tempStudent->SID != studentID)
		tempStudent = tempStudent->pNext;

	if (tempStudent == nullptr) {
		cout << "Student is unavailable! Cannot access!";
		_getch();
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
			cout << "GPA in this semester: " << tempStudent->gpa << endl;
			cout << "-------------------------------" << endl;
			cout << "Enrolled course: " << endl;
			view_list_of_enrolled_course(tempStudent);

			cout << endl;
			cout << "0. Back" << endl;
			if (ThisYear == CurrentYear) {
				cout << "1. Update student's profile" << endl;
			}
			if (Available_all_scoreboard == true) {
				cout << "2. View student's scoreboard" << endl;
			}
			cout << "User: ";
			cin >> choice;
			switch (choice) {
			case 0:
				return true;
			case 1:
				if (ThisYear == CurrentYear) {
					update_student_profile(HeadStudent, tempStudent);
				}
				break;
			case 2: 
				/*
				if (Available_all_scoreboard) {
					view_scoreboard_of_student(tempStudent);
				}*/
				view_scoreboard_of_student(tempStudent);
				break;
			default: 
				cout << "Invalid input! Please try again!";
				break;
			}
		}
	}
}
//Hiển thị thông tin của một lớp 
bool go_to_detail_of_a_class(string className)   {
	if (ThisYear->HeadClass == nullptr) {
		cout << "No existed class! Cannot access!";
		_getch();
		return false;
	}
	Class* tempClass = ThisYear->HeadClass;
	while (tempClass != nullptr && tempClass->className != className)
		tempClass = tempClass->pNext;

	if (tempClass == nullptr) {
		cout << "Class is not available! Cannot access";
		_getch();
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

			if (Available_all_scoreboard) {
				cout << endl;
				cout << "*** NOTIFICATION ***" << endl;
				cout << "Class scoreboard is available now. To view, choose OPTION 4" << endl;
			}

			cout << endl;
			cout << "0. Back" << endl;
			cout << "1. View a student" << endl;
			if (ThisYear == CurrentYear) {
				cout << "2. Add student" << endl;
				cout << "3. Delete a student" << endl;
			}
			if (Available_all_scoreboard == true) {
				cout << "4. View class's scoreboard" << endl;
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
				if (ThisYear == CurrentYear) {
					int way = 1;
					cout << "0. Cancle" << endl;
					cout << "1. Input from keyboard" << endl;
					cout << "2. Import from .csv file" << endl;
					cout << "User: ";
					cin >> way;
					while (way < 0 || way > 2) {
						cout << "Invalid input. Please try again!" << endl;
						cout << "User: ";
						cin >> way;
					}
					if (way == 0) {
						cout << "CANCLE ADDITION!";
						_getch();
						break;
					}
					else if (way == 1) {						//Nhập tay
						inputListOfStudent(tempClass);
					}
					else {										//Nhập từ CSV
						string path;
						cout << "Please enter file name: ";
						cin.get();
						getline(cin, path);
						if (input_list_of_students_from_CSV("Data\\" + path + ".csv", tempClass->HeadStudent, tempClass->classSize)) {
							cout << "IMPORT SUCCESSFULLY!";
							_getch();
						}
					}
					
				}
					
				break;
			case 3:
				delete_a_student(tempClass->HeadStudent, tempClass->classSize);
				break;
			case 4:
				if (Available_all_scoreboard == true) {
					view_class_scoreboard(tempClass);
				}
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
				cout << "    School Year: " << startYear << "-" << endYear << endl;
				cout << "-----------------------------------" << endl;
				display_semesters_of_school_year();
				cout << "-----------------------------------" << endl;
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
						cout << endl << "Semester is unavailable! Cannot access!";
						_getch();
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
							cout << "No available semester! Cannot access!";
							_getch();
						}
					}
					break;
				case 4:
					if(ThisYear == CurrentYear) 
						input_classes_for_current_year();	
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

//Hàm xóa sinh viên ra khỏi danh sách
void delete_a_student(Student*& HeadStudent, int& classSize) {
	if (HeadStudent == nullptr) {
		cout << "No existed student! Cannot delete!";
		_getch();
		return;
	}
	int delete_more = 1;
	while (delete_more == 1) {
		string studentID;
		cout << "Enter student ID you want to delete (0 to cancle): ";
		cin.get();
		getline(cin, studentID);

		Student* tempStudent = HeadStudent;
		while (tempStudent != nullptr && tempStudent->SID != studentID)
			tempStudent = tempStudent->pNext;

		if (tempStudent == nullptr) {
			cout << "Student is not available! Cannot delete!";
			_getch();
			return;
		}
		else {
			int sure_delete = 1;
			cout << "Are you sure delete the student?" << endl;
			cout << "1. YES			2.NO" << endl;
			cout << "User: ";
			cin >> sure_delete;
			while (sure_delete  != 1 && sure_delete != 2) {
				cout << "Invalid input! Please try again!" << endl;
				cout << "User: ";
				cin >> sure_delete;
			}
			if (sure_delete == 1) {
				if (tempStudent == HeadStudent) {
					HeadStudent = HeadStudent->pNext;
					if (HeadStudent != nullptr)
						HeadStudent->pPrev = nullptr;
					delete tempStudent;
				}
				else {
					tempStudent->pPrev->pNext = tempStudent->pNext;
					if (tempStudent->pNext != nullptr)
						tempStudent->pNext->pPrev = tempStudent->pPrev;
					delete tempStudent;
				}
				classSize--;
				cout << "DELETE SUCCESSFULLY!" << endl;

				cout << "You want to delete more? " << endl;
				cout << "1. YES			2. NO" << endl;
				cout << "User: ";
				cin >> delete_more;
				while (delete_more != 1 && delete_more != 2) {
					cout << "Invalid input! Please try again!" << endl;
					cout << "User: ";
					cin >> delete_more;
				}
			}
			else {
				cout << "CANCLE DELETE!";
				_getch();
				return;
			}
			
		}
		
	}
}


/*
void view_a_student_profile(Student* ListStudent,string studentID) {
	if (ListStudent == nullptr) {
		cout << "No student has enrolled this course! Cannot access!" << endl;
		return;
	}

	Student* tempStudent = ListStudent;
	while (tempStudent != nullptr && tempStudent->SID != studentID)
		tempStudent = tempStudent->pNext;

	if (tempStudent == nullptr) {
		cout << "Student is not available! Cannot access!" << endl;
		return;
	}
	else {
		while (true) {
			system("cls");
			cout << "Full name: " << tempStudent->firstName + tempStudent->firstName << endl;
			cout << "SID: " << tempStudent->SID << endl;
			cout << "Class: " << tempStudent->Class << endl;
			cout << "Gender: " << tempStudent->gender << endl;
		}
	}
}
*/
void View_list_of_courses_by_XQ() {
	if (ThisSemester->HeadCourse == nullptr) {
		cout << "No existed course!" << endl;							//Trường hợp chưa có môn học nào được khởi tạo
		return;
	}
	else {
		int i = 1;
		CourseDetail* tempCourse = ThisSemester->HeadCourse;
		while (tempCourse != nullptr) {
			cout << i++ << ". " << tempCourse->courseName << endl;
			cout << "Course ID: " << tempCourse->courseID << endl;
			cout << "Lecturer: " << tempCourse->teacherName << endl;
			cout << "--------------------" << endl;
			tempCourse = tempCourse->pNext;
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
			int sure_delete = 1;
			cout << "Are you sure delete the school year?" << endl;
			cout << "1. YES			2.NO" << endl;
			cout << "User: ";
			cin >> sure_delete;
			while (sure_delete != 1 && sure_delete != 2) {
				cout << "Invalid input! Please try again!" << endl;
				cout << "User: ";
				cin >> sure_delete;
			}

			if (sure_delete == 1) {
				if (tempYear == HeadYear) {
					HeadYear = HeadYear->pNext;
					if (HeadYear != nullptr)
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

				cout << "DELETE SUCCESSFULLY!";
				_getch();
			}
			else {
				cout << "CANCLE DELETE!";
				_getch();
			}
			return true;
		}
	}
}

//Kiểm tra xem
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
//Hàm check xem tất cả các môn đều đã có bảng điểm hết hay chưa	
bool Check_all_scoreboard_available() {
	if (CurrentSemester->HeadCourse == nullptr)
		return false;
	CourseDetail* CurCourse = CurrentSemester->HeadCourse;

	while (CurCourse != nullptr) {
		if (CurCourse->Available_scoreboard == false)
			return false;

		CurCourse = CurCourse->pNext;
	}
	if (CurCourse == nullptr)
		return true;
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
				cout << "No existed year! Cannot access!";
				_getch();
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
				cout << "Something wrong! Cannot delete this year!";
				_getch();
			}
			break;

		}
	}
}


//Giao diện khi staff khởi động chương trình
void StaffInterface() {
	int choice = 0;
	while (true) {
		system("cls");

		cout << "1. View list of years" << endl;
		cout << "2. Go to current year" << endl;
		cout << "3. Log out" << endl;
		cout << "4. Exit program" << endl;
		cout << "User: ";
		cin >> choice;
		switch (choice) {
		case 1:
			View_list_of_year();
			break;
		case 2:
			go_to_detail_of_a_year(CurrentYear->startYear);
			break;
		case 3:
			cin.get();
			return;
		case 4:
			cout << endl;
			cout << "THANK YOU FOR USING OUR PROGRAM!";
			_getch();
			writeAll(HeadYear);
			delete_everything();
			exit(0);
		default:
			cout << "Invalid input! Please try again!";
			_getch();
		}
	}
}

//Hàm cho phép sinh viên xóa một môn mình đã đăng ký
void remove_an_enrolled_course(CourseForEachStudent*& HeadCourse, string courseID);
//HeadCourse là danh sách môn mà sv đã đăng ký, courseID là ID của môn cần xóa, không cần yêu cầu nhập vào nữa

