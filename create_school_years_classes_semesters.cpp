#include "DataStructure.h"

void create_a_new_school_year ( int start_year, int end_year )		// Hàm tạo năm học mới với start_year là năm bắt đầu, end_year là năm kết thúc.
{
	if ( HeadYear == nullptr )					// Nếu chưa có năm học nào
	{
		HeadYear = new SchoolYear;				// thì tạo mới
		CurrentYear = HeadYear;										
		CurrentYear -> pPrev = nullptr;								
	}
	else								// Nếu có rồi
	{
		CurrentYear -> pNext = new SchoolYear;			// tạo năm học mới nối đuôi với năm trước đó
		CurrentYear -> pNext -> pPrev = CurrentYear;
		CurrentYear = CurrentYear -> pNext;			// năm được tạo mới là năm hiện tại
	}

	CurrentYear -> startYear = start_year;
    	CurrentYear -> endYear = end_year;

	CurrentYear -> HeadClass = nullptr;				// Năm học mới chưa tạo danh sách lớp

	// --- Năm học mới chưa tạo học kỳ ---------
	CurrentYear -> semester1.startDate = {};						
	CurrentYear -> semester1.endDate = {};
    	CurrentYear -> semester1.isAvailable = 0;
	CurrentYear -> semester1.HeadCourse = nullptr;

	CurrentYear -> semester2.startDate = {};
	CurrentYear -> semester2.endDate = {};
    	CurrentYear -> semester2.isAvailable = 0;
	CurrentYear -> semester2.HeadCourse = nullptr;

	CurrentYear -> semester3.startDate = {};
	CurrentYear -> semester3.endDate = {};
    	CurrentYear -> semester3.isAvailable = 0;
	CurrentYear -> semester3.HeadCourse = nullptr;
	//-------------------------------------------

	CurrentYear -> pNext = nullptr;
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
