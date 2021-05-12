#include "DataStructure.h"

void create_a_new_school_year(int start_year, int end_year) 		// Hàm tạo năm học mới với start_year là năm bắt đầu, end_year là năm kết thúc.
{
	if (HeadYear == nullptr)					// Nếu chưa có năm học nào
	{
		HeadYear = new SchoolYear;				// thì tạo mới
		CurrentYear = HeadYear;
		CurrentYear->pPrev = nullptr;
	}
	else								// Nếu có rồi
	{
		CurrentYear->pNext = new SchoolYear;			// tạo năm học mới nối đuôi với năm trước đó
		CurrentYear->pNext->pPrev = CurrentYear;
		CurrentYear = CurrentYear->pNext;			// năm được tạo mới là năm hiện tại
	}

	CurrentYear->startYear = start_year;
	CurrentYear->endYear = end_year;

	CurrentYear->HeadClass = nullptr;				// Năm học mới chưa tạo danh sách lớp

	// --- Năm học mới chưa tạo học kỳ ---------
	CurrentYear->semester1.isAvailable = false;
	CurrentYear->semester2.isAvailable = false;
	CurrentYear->semester3.isAvailable = false;
	//-------------------------------------------

	CurrentSemester = nullptr;
	CurrentYear->pNext = nullptr;
}


void input_school_year ( )		// Hàm để staff nhập năm học mới
{
	int start_year, end_year;			

	cout << "Enter a school year: " << endl;
	cout << "start year: ";  	cin >> start_year;		cout << endl;
	cout << "end year: ";		cin >> end_year;		cout << endl;
	create_a_new_school_year ( start_year, end_year );		
}

void input_classes_for_current_year ( )		// Hàm tạo danh sách các lớp học cho năm hiện tại
{
	Class* pCur_class = nullptr;

	int stop_condition = 1; // 1: tiếp tục nhập,  2: dừng nhập.

	while ( stop_condition == 1 )
	{
		if ( CurrentYear -> HeadClass == nullptr )			// Nếu chưa có lớp nào
		{
			CurrentYear -> HeadClass = new Class;			// thì tạo lớp mới, ListClass làm vai trò như pHead cho danh sách các lớp
			pCur_class = CurrentYear -> HeadClass;
			pCur_class -> pPrev = nullptr;
		}
		else
		{
			pCur_class -> pNext = new Class;								
			pCur_class -> pNext -> pPrev = pCur_class;
			pCur_class = pCur_class -> pNext; 
		}

		cin.get();
		cout << "Please enter the class's name: ";			getline ( cin, pCur_class -> className );	
		cout << "Please enter the class's number of students: ";	cin >> pCur_class -> classSize;
		cin.get();
		cout << "Please enter the class's form teacher name: ";		getline ( cin, pCur_class -> formTeacherName );

		pCur_class -> HeadStudent = nullptr;				// Lớp mới tạo chưa có danh sách học sinh

		pCur_class -> pNext = nullptr;

		cout << "Do you want to add more class?" << endl;
		cout << "1. Yes				2.No" << endl;
		cout << "Your choice: ";
		cin >> stop_condition;
	}
}

void create_a_semester_for_year ( DateTime start_date, DateTime end_date, int semester_n )
{
	switch ( semester_n )												                          
	{
		case 1:		// Học kỳ 1
		{
			CurrentYear -> semester1.startDate = start_date;	// ngày bắt đầu	
			CurrentYear -> semester1.endDate = end_date;		// ngày kết thúc
			CurrentYear -> semester1.HeadCourse = nullptr;		// Học kỳ mới chưa tạo danh sách các môn học
            		CurrentYear -> semester1.isAvailable = true;        	// Học kỳ mới tạo được gọi là có sẵn
            		CurrentSemester = & ( CurrentYear -> semester1 );       // Học kỳ mới tạo là học kì hiện tại
			CurrentSemester -> HeadCourse = nullptr;
			break;
		}
		case 2:		// Học kỳ 2
		{
			CurrentYear -> semester2.startDate = start_date;
			CurrentYear -> semester2.endDate = end_date;
			CurrentYear -> semester2.HeadCourse = nullptr;
            		CurrentYear -> semester2.isAvailable = true;
            		CurrentSemester = & ( CurrentYear -> semester2 );
			CurrentSemester -> HeadCourse = nullptr;
			break;
		}
		case 3:		// Học kỳ 3
		{
			CurrentYear -> semester3.startDate = start_date;
			CurrentYear -> semester3.endDate = end_date;
			CurrentYear -> semester3.HeadCourse = nullptr;
            		CurrentYear -> semester3.isAvailable = true;
            		CurrentSemester = & ( CurrentYear -> semester3 );
			CurrentSemester -> HeadCourse = nullptr;
			break;
		}
	}
}

void enter_a_semester ()			// Hàm để staff nhập ngày, tháng, năm bắt đầu và kết thúc học kỳ
{
	int semester_n;

	cout << "Choose a semester: " << endl;
	cout << "1. Semester 1." << endl;
	cout << "2. Semester 2." << endl;
	cout << "3. Semester 3." << endl;
	cin >> semester_n;

	DateTime start_date, end_date;

	cout << "Enter the semester's start date: " << endl;
	cout << "Day: ";			cin >> start_date.day;			cout << endl;	
	cout << "Month: ";			cin >> start_date.month;		cout << endl;
	cout << "Year: ";			cin >> start_date.year;			cout << endl;

	cout << "Enter the semester's end date: " << endl;
	cout << "Day: ";			cin >> end_date.day;			cout << endl;	
	cout << "Month: ";			cin >> end_date.month;			cout << endl;
	cout << "Year: ";			cin >> end_date.year;			cout << endl;

	create_a_semester_for_year ( start_date, end_date, semester_n );
}

void delete_everything ()
{
	SchoolYear* pCur_year = HeadYear;
	while ( pCur_year != nullptr )
	{
//------------ DELETE NHÁNH CLASS CỦA SCHOOLYEAR --------------

		Class* pCur_class = pCur_year -> HeadClass;
		while ( pCur_class != nullptr )
		{
			Student* pCur_student = pCur_class -> HeadStudent;	// delete student trong class
			while ( pCur_student != nullptr )	
			{
				CourseForEachStudent* pCur_enrolled_course = pCur_student -> Head_of_enrolled_course;	// delete enrolled course của student
				while ( pCur_enrolled_course != nullptr )	
				{
					CourseForEachStudent* delete_enrolled_course = pCur_enrolled_course;
					pCur_enrolled_course = pCur_enrolled_course -> pNext;
					delete delete_enrolled_course;
				}

				Student* delete_student = pCur_student;
				pCur_student = pCur_student -> pNext;
				delete delete_student;
			}

			Class* delete_class = pCur_class;
			pCur_class = pCur_class -> pNext;
			delete delete_class;
		}

//---------------------------------------------------------

//--------- DELETE NHÁNH SEMESTER CỦA SCHOOLYEAR -----------

		CourseDetail* pCur_course = pCur_year -> semester1.HeadCourse;  // Xóa các course của học kỳ 1
		while ( pCur_course != nullptr )
		{
			Student_CourseScores* pCur_Student_CourseScores = pCur_course -> HeadStudent;	// Xóa danh sách điểm của course này
			while ( pCur_Student_CourseScores != nullptr )
			{
				Student_CourseScores* delete_Student_CourseScores = pCur_Student_CourseScores;
				pCur_Student_CourseScores = pCur_Student_CourseScores -> pNext;
				delete delete_Student_CourseScores;
			}

			CourseDetail* delete_course = pCur_course;
			pCur_course = pCur_course -> pNext;
			delete delete_course;
		}

		pCur_course = pCur_year -> semester2.HeadCourse;	// Của học kỳ 2, copy-paste
		while ( pCur_course != nullptr )	
		{
			Student_CourseScores* pCur_Student_CourseScores = pCur_course -> HeadStudent;
			while ( pCur_Student_CourseScores != nullptr )
			{
				Student_CourseScores* delete_Student_CourseScores = pCur_Student_CourseScores;
				pCur_Student_CourseScores = pCur_Student_CourseScores -> pNext;
				delete delete_Student_CourseScores;
			}

			CourseDetail* delete_course = pCur_course;
			pCur_course = pCur_course -> pNext;
			delete delete_course;
		}

		pCur_course = pCur_year -> semester3.HeadCourse;	// Và học kỳ 3
		while ( pCur_course != nullptr )
		{
			Student_CourseScores* pCur_Student_CourseScores = pCur_course -> HeadStudent;
			while ( pCur_Student_CourseScores != nullptr )
			{
				Student_CourseScores* delete_Student_CourseScores = pCur_Student_CourseScores;
				pCur_Student_CourseScores = pCur_Student_CourseScores -> pNext;
				delete delete_Student_CourseScores;
			}

			CourseDetail* delete_course = pCur_course;
			pCur_course = pCur_course -> pNext;
			delete delete_course;
		}
	
	SchoolYear* delete_year = pCur_year;
	pCur_year = pCur_year -> pNext;
	delete delete_year;

	}
}

void display_school_year_list ()
{
	SchoolYear* pCur = HeadYear;
	while ( pCur != nullptr )
	{
		cout << "This is the list of school year: " << endl;
		cout << pCur -> startYear << "-" << pCur -> endYear << ", ";
		pCur = pCur -> pNext;
	}
	cout << endl;
}

void display_classes_list_of_school_year ( int start_year, int end_year )
{
	SchoolYear* pCur_year = HeadYear;

	while ( pCur_year != nullptr && pCur_year -> startYear != start_year )
		pCur_year = pCur_year -> pNext;

	if ( pCur_year -> startYear == start_year )
	{
		cout << "This is the classes list of " << start_year << "-" << end_year << " school year:" << endl;
		Class* pCur_class = pCur_year -> HeadClass;
		while ( pCur_class != nullptr )
		{
			cout << pCur_class -> className << ", ";
			pCur_class = pCur_class -> pNext;
		}
		cout << endl;
	}

	else cout << "Year is not found." << endl;
}

void display_semesters_of_school_year ( int start_year, int end_year )
{
	SchoolYear* pCur_year = HeadYear;

	while ( pCur_year != nullptr && pCur_year -> startYear != start_year )
		pCur_year = pCur_year -> pNext;

	if ( pCur_year -> startYear == start_year )
	{
		cout << "Semester 1:" << endl;
		cout << pCur_year -> semester1.startDate.day << " / " << pCur_year -> semester1.startDate.month << " / " << pCur_year -> semester1.startDate.year;
		cout << " - ";
		cout << pCur_year -> semester1.endDate.day << " / " << pCur_year -> semester1.endDate.month << " / " << pCur_year -> semester1.endDate.year;
		cout << endl;

		cout << "Semester 2:" << endl;
		cout << pCur_year -> semester2.startDate.day << " / " << pCur_year -> semester2.startDate.month << " / " << pCur_year -> semester2.startDate.year;
		cout << " - ";
		cout << pCur_year -> semester2.endDate.day << " / " << pCur_year -> semester2.endDate.month << " / " << pCur_year -> semester2.endDate.year;
		cout << endl;

		cout << "Semester 3:" << endl;
		cout << pCur_year -> semester3.startDate.day << " / " << pCur_year -> semester3.startDate.month << " / " << pCur_year -> semester3.startDate.year;
		cout << " - ";
		cout << pCur_year -> semester3.endDate.day << " / " << pCur_year -> semester3.endDate.month << " / " << pCur_year -> semester3.endDate.year;

		cout << endl;
	}
	else cout << "Year is not found." << endl;
}

void deleteYear ( int startYear )	// Hàm dùng để delete một năm học với startYear biết sẵn
{
	SchoolYear* findYear = HeadYear;	// pointer findYear dùng để tìm đến năm cần delete, bắt đầu tìm từ HeadYear
	while ( findYear != nullptr && findYear -> startYear != startYear )	// Tìm bằng cách so sánh startYear
		findYear = findYear -> pNext;	// Nếu chưa tìm thấy, tiếp tục di chuyển tới năm tiếp theo
	
	if ( findYear != nullptr )	// Nếu tìm thấy
	{
		// ---------------- Delete trong nhánh Class -------------------
		Class* pCurClass = findYear -> HeadClass;	// Truy cập từng lớp
		while ( pCurClass != nullptr )
		{
			Student* pCurStudent = pCurClass -> HeadStudent;	// Truy cập từng sinh viên trong lớp đó
			while ( pCurStudent != nullptr )
			{
				CourseForEachStudent* pCurEnrolledCourse = pCurStudent -> Head_of_enrolled_course;	// Truy cập danh sách khóa học sinh viên đã đăng ký
				while ( pCurEnrolledCourse != nullptr )
				{
					CourseForEachStudent* deleteEnrolledCourse = pCurEnrolledCourse;
					pCurEnrolledCourse = pCurEnrolledCourse -> pNext;
					delete deleteEnrolledCourse;							// Delete từng khóa học trong danh sách đó
				}

				Student* deleteStudent = pCurStudent;
				pCurStudent = pCurStudent -> pNext;						
				delete deleteStudent;									// Delete từng sinh viên trong lớp
				//cout << "Student deleted." << endl;
			}

			Class* deleteClass = pCurClass;
			pCurClass = pCurClass -> pNext;
			delete deleteClass;										// Và delete từng lớp trong năm
		}
		// -------------------------------------------------------------

		// --------------- Delete trong nhánh Semester -----------------
		CourseDetail* pCurCourse = findYear -> semester1.HeadCourse;	// Truy cập từng Course của semester 1
		while ( pCurCourse != nullptr )
		{
			Student_CourseScores* pCur_CourseScores = pCurCourse -> HeadStudent;	// Truy cập vào Student_CourseScores của Course đó 
			while ( pCur_CourseScores != nullptr )
			{
				Student_CourseScores* deleteCourseScores = pCur_CourseScores;
				pCur_CourseScores = pCur_CourseScores -> pNext;
				delete deleteCourseScores; 					// Delete từng Student_CourseScores
			}

			CourseDetail* deleteCourse = pCurCourse;
			pCurCourse = pCurCourse -> pNext;
			delete deleteCourse;							// Delete từng Course
		}

		// Tương tự với semester 2
		pCurCourse = findYear -> semester2.HeadCourse;	
		while ( pCurCourse != nullptr )
		{
			Student_CourseScores* pCur_CourseScores = pCurCourse -> HeadStudent; 
			while ( pCur_CourseScores != nullptr )
			{
				Student_CourseScores* deleteCourseScores = pCur_CourseScores;
				pCur_CourseScores = pCur_CourseScores -> pNext;
				delete deleteCourseScores; 										
			}

			CourseDetail* deleteCourse = pCurCourse;
			pCurCourse = pCurCourse -> pNext;
			delete deleteCourse;						
		}

		// Và semester 3... chỉ là copy paste thôi
		pCurCourse = findYear -> semester3.HeadCourse;	
		while ( pCurCourse != nullptr )
		{
			Student_CourseScores* pCur_CourseScores = pCurCourse -> HeadStudent;	 
			while ( pCur_CourseScores != nullptr )
			{
				Student_CourseScores* deleteCourseScores = pCur_CourseScores;
				pCur_CourseScores = pCur_CourseScores -> pNext;
				delete deleteCourseScores; 										
			}

			CourseDetail* deleteCourse = pCurCourse;
			pCurCourse = pCurCourse -> pNext;
			delete deleteCourse;					
		}
		// --------------------------------------------------------
	}

	else	// Nếu không tìm thấy năm cần delete, return
	{
		cout << "School year not found. Cannot delete." << endl;
		return;
	}
	
	//------------------ Delete node SchoolYear --------------------
	if ( findYear -> pNext == nullptr && findYear -> pPrev == nullptr )	// Trường hợp chỉ có một SchoolYear duy nhất trong list
	{
		HeadYear = nullptr;
		delete findYear;
		return;
	}

	if ( findYear -> pPrev == nullptr )	// Trường hợp delete HeadYear
	{
		HeadYear = HeadYear -> pNext;	// Gán HeadYear tới năm kế sau nó. HeadYear là NULL nếu không có năm kế sau
		HeadYear -> pPrev = nullptr;
		delete findYear;
	}
	else if ( findYear -> pNext == nullptr ) // Trường hợp delete SchoolYear đứng cuối list ( CurrentYear )
	{
		CurrentYear = CurrentYear -> pPrev;	// Gán CurrentYear tới năm kế trước nó
		CurrentYear -> pNext = nullptr;
		delete findYear;
	}
	else	// Trường hợp delete ở giữa list
	{
		findYear -> pPrev -> pNext = findYear -> pNext;
		findYear -> pNext -> pPrev = findYear -> pPrev;
		delete findYear;
	}
	// --------------------------------------------------------------
}

void deleteClass ( int startYear, string className )	// Hàm delete một Class với className và startYear biết sẵn
{
	SchoolYear* findYear = HeadYear; // pointer findYear dùng để tìm đến năm mà lớp cần delete đang nằm
	while ( findYear != nullptr && findYear -> startYear != startYear )	// Tìm bằng cách so sánh startYear
		findYear = findYear -> pNext;	// Nếu chưa tìm thấy, tiếp tục di chuyển tới năm tiếp theo

	if ( findYear != nullptr )	// Nếu tìm thấy năm học
	{
		Class* findClass = findYear -> HeadClass;	// Tìm đến lớp cần delete trong năm học đó
		while ( findClass != nullptr && findClass -> className != className )	// Bằng cách so sánh className
			findClass = findClass -> pNext;
		
		if ( findClass != nullptr )	// Nếu tìm thấy lớp cần delete
		{
			//------------ Delete mọi thứ bên trong Class --------------
			Student* pCurStudent = findClass -> HeadStudent;	// Truy cập từng sinh viên trong lớp dó
			while ( pCurStudent != nullptr )
			{
				CourseForEachStudent* pCurEnrolledCourse = pCurStudent -> Head_of_enrolled_course; // Truy cập danh sách khóa học sinh viên đã đăng kí
				while ( pCurEnrolledCourse != nullptr)
				{
					CourseForEachStudent* deleteEnrolledCourse = pCurEnrolledCourse;
					pCurEnrolledCourse = pCurEnrolledCourse -> pNext;
					delete deleteEnrolledCourse;					// Delete từng khóa học sinh viên đã đăng kí
				}

				Student* deleteStudent = pCurStudent;
				pCurStudent = pCurStudent -> pNext;
				delete deleteStudent;						// Delete từng sinh viên trong lớp đó
			}
			// ---------------------------------------------------------

			// ------------------ Delete node Class --------------------
			if ( findClass -> pNext == nullptr && findClass -> pPrev == nullptr )	// Trường hợp chỉ có một lớp duy nhất trong SchoolYear
			{
				findYear -> HeadClass = nullptr;
				delete findClass;
				return;
			}

			if ( findClass -> pPrev == nullptr )	// Trường hợp xóa HeadClass
			{
				findYear -> HeadClass = findClass -> pNext;	// Lớp kế sau nó được gán là HeadClass
				findYear -> HeadClass -> pPrev = nullptr;
				delete findClass;
			}
			else if ( findClass -> pNext == nullptr )	// Trường hợp delete Class đứng cuối list
			{
				findClass -> pPrev -> pNext = nullptr;
				delete findClass;
			}
			else	// Trường hợp Class đứng giữa
			{
				findClass -> pNext -> pPrev = findClass -> pPrev;
				findClass -> pPrev -> pNext = findClass -> pNext;
				delete findClass;
			}
			// -----------------------------------------------------------

		}
		else	// Nếu không tìm thấy Class cần delete, return
		{
			cout << "Class not found. Cannot delete." << endl;
			return;
		}
	}
	else
	{
		cout << "Class not found. Cannot delete." << endl;
		return;
	}
}

void deleteStudent ( Class* & tmpClass, string SID )	// Hàm delete một Student với SID biết sẵn, tmpClass là lớp mà sinh viên đang học
{
	Student* findStudent = tmpClass -> HeadStudent;	// pointer findStudent dùng để tìm đến Student cần xóa
	while ( findStudent != nullptr && findStudent -> SID != SID )	// bằng cách so sánh SID
		findStudent = findStudent -> pNext;

	if ( findStudent != nullptr )	// Nếu tìm thấy
	{
		CourseForEachStudent* pCurEnrolledCourse = findStudent -> Head_of_enrolled_course;	// Truy cập vào danh sách khóa học sinh viên đã đăng kí
		while ( pCurEnrolledCourse != nullptr )
		{
			CourseForEachStudent* deleteEnrolledCourse = pCurEnrolledCourse;
			pCurEnrolledCourse = pCurEnrolledCourse -> pNext;
			delete deleteEnrolledCourse;	// Xóa từng khóa học đã đăng kí
		}

		// ------------------- Delete node Student -----------------------
		if ( findStudent -> pPrev == nullptr && findStudent -> pNext == nullptr )	// Trường hợp chỉ có một Student duy nhất trong Class
		{
			tmpClass -> HeadStudent = nullptr;
			delete findStudent;
			return;
		}

		if ( findStudent -> pPrev == nullptr )	// Trường hợp xóa HeadStudent
		{
			tmpClass -> HeadStudent = findStudent -> pNext;	// HeadStudent được gán cho Student kế sau
			tmpClass -> HeadStudent -> pPrev = nullptr;
			delete findStudent;
		}
		else if ( findStudent -> pNext == nullptr )	// Trường hợp xóa Student đứng cuối list
		{
			findStudent -> pPrev -> pNext = nullptr;
			delete findStudent;
		}
		else	// Trường hợp Student đứng giữa list
		{
			findStudent -> pPrev -> pNext = findStudent -> pNext;
			findStudent -> pNext -> pPrev = findStudent -> pPrev;
			delete findStudent;
		}
		// -----------------------------------------------------------------
	}
	else // Nếu không tìm thấy Student
	{
		cout << "Student not found. Cannot delete." << endl;
		return;
	}
}

void deleteEnrolledCourse ( Student* & student, string courseID )
{
	CourseDetail* pCurCourse = CurrentSemester -> HeadCourse;
	while ( pCurCourse -> courseID != courseID && pCurCourse != nullptr )	// Tìm đến Course cần delete
		pCurCourse = pCurCourse -> pNext;

	if ( pCurCourse == nullptr )	// Nếu không tìm thấy
	{
		cout << "Course not found. Cannot delete." << endl;
		return;
	}
	else	// Nếu tìm thấy
	{
		Student_CourseScores* pCurStudent = pCurCourse -> HeadStudent;
		while ( pCurStudent -> SID != student -> SID && pCurStudent != nullptr )	// Tìm đến Student_CourseScores của sinh viên trong Course vừa tìm được
			pCurStudent = pCurStudent -> pNext;

		if ( pCurStudent == nullptr )	// Nếu không tìm thấy, có thể sinh viên chưa đăng ký môn này
		{
			cout << "The student may not has enrolled this course. Delete failed." << endl;
			return;
		}
		else	// Nếu tìm thấy, bắt đầu delete
		{
			CourseForEachStudent* deleteEnrolled = pCurStudent -> point_to_an_enrolled_course_of_a_student_in_a_class;	// Delete CourseForEachStudent của sinh viên
			if ( deleteEnrolled -> pPrev == nullptr )	// Trường hợp delete Head_of_enrolled_course
			{
				student -> Head_of_enrolled_course = deleteEnrolled -> pNext;	// Chuyển Head_of_enrolled_course sang node kế tiếp

				if ( student -> Head_of_enrolled_course != nullptr )	// Nếu node kế tiếp tồn tại
					student -> Head_of_enrolled_course -> pPrev = nullptr;	// Set pPrev của node đó về nullptr

				delete deleteEnrolled;
			}
			else	// Trường hợp đứng giữa hoặc cuối
			{
				deleteEnrolled -> pPrev -> pNext = deleteEnrolled -> pNext;	// Nối lại các node

				if ( deleteEnrolled -> pNext != nullptr )	// Nếu không phải là node cuối cùng
					deleteEnrolled -> pNext -> pPrev = deleteEnrolled -> pPrev;

				delete deleteEnrolled;
			}

			// Delete Student_CourseScores

			if ( pCurStudent -> pPrev == nullptr )	// Trường hợp delete HeadStudent
			{
				pCurCourse -> HeadStudent = pCurStudent -> pNext;	// Chuyển HeadStudent sang node kế tiếp

				if ( pCurCourse -> HeadStudent != nullptr )	// Nếu node kế tiếp tồn tại
					pCurCourse -> HeadStudent -> pPrev = nullptr;	// Set pPrev của node đó về nullpter

				delete pCurStudent;
				return;
			}
			else	// Trường hợp đứng giữa hoặc đứng cuối
			{
				pCurStudent -> pPrev -> pNext = pCurStudent -> pNext;	// Nối lại các node

				if ( pCurStudent -> pNext != nullptr )	// Nếu không phải là node cuối cùng
					pCurStudent -> pNext -> pPrev = pCurStudent -> pPrev;

				delete pCurStudent;
				return;
			}
		}
	}
} 
