#include "DataStructure.h"

void create_a_new_school_year ( int start_year, int end_year )		// Hàm tạo năm học mới với start_year là năm bắt đầu, end_year là năm kết thúc.
{
	if ( HeadYear == nullptr )										// Nếu chưa có năm học nào
	{
		HeadYear = new SchoolYear;									// thì tạo mới
		CurrentYear = HeadYear;										
		CurrentYear -> pPrev = nullptr;								
	}
	else															// Nếu có rồi
	{
		CurrentYear -> pNext = new SchoolYear;						// tạo năm học mới nối đuôi với năm trước đó
		CurrentYear -> pNext -> pPrev = CurrentYear;
		CurrentYear = CurrentYear -> pNext;							// năm được tạo mới là năm hiện tại
	}

	CurrentYear -> schoolYear = start_year + end_year;

	CurrentYear -> ListClass = nullptr;								// Năm học mới chưa tạo danh sách lớp

	// --- Năm học mới chưa tạo học kỳ ---------
	CurrentYear -> semester1.startDate = {};						
	CurrentYear -> semester1.endDate = {};
	CurrentYear -> semester2.startDate = {};
	CurrentYear -> semester2.endDate = {};
	CurrentYear -> semester3.startDate = {};
	CurrentYear -> semester3.endDate = {};
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
	Class* pCur = nullptr;
	string class_name_temp;

	cout << "PLease enter the class name (0 to stop): ";
	cin >> class_name_temp;

	while ( class_name_temp != "0" )						
	{
		if ( CurrentYear -> ListClass == nullptr )					// Nếu chưa có lớp nào
		{
			CurrentYear -> ListClass = new Class;					    // thì tạo lớp mới, ListClass làm vai trò như pHead cho danh sách các lớp
			pCur = CurrentYear -> ListClass;						
			pCur -> pPrev = nullptr;
		}
		else 													
		{
			pCur -> pNext = new Class;								
			pCur -> pNext -> pPrev = pCur;
			pCur = pCur -> pNext; 
		}

		pCur -> className = class_name_temp;						    // Tên của lớp
		pCur -> ListStudent = nullptr;								      // Lớp mới tạo chưa có danh sách học sinh

		pCur -> pNext = nullptr;

		cout << "PLease enter the class name (0 to stop): ";
		cin >> class_name_temp;
	}
}

void create_a_semester_for_year ( int start_year, int end_year, DateTime start_date, DateTime end_date, int semester_n )
{
	SchoolYear* pCur = HeadYear;

	while ( pCur != nullptr && pCur -> schoolYear != start_year + end_year )	// Tìm đến năm học cần thêm học kỳ
		pCur = pCur -> pNext;

	if ( pCur -> schoolYear == start_year + end_year )							          // Nếu tìm thấy
	{
		switch ( semester_n )												                          	// Thêm học kỳ mấy?
		{
			case 1:		// Học kỳ 1
			{
				pCur -> semester1.startDate = start_date;						                // ngày bắt đầu	
				pCur -> semester1.endDate = end_date;							                  // ngày kết thúc
				pCur -> semester1.ListCourse = nullptr;							                // Học kỳ mới chưa tạo danh sách các môn học
				break;
			}
			case 2:		// Học kỳ 2
			{
				pCur -> semester2.startDate = start_date;
				pCur -> semester2.endDate = end_date;
				pCur -> semester2.ListCourse = nullptr;
				break;
			}
			case 3:		// Học kỳ 3
			{
				pCur -> semester3.startDate = start_date;
				pCur -> semester3.endDate = end_date;
				pCur -> semester3.ListCourse = nullptr;
				break;
			}
		}
	}
}

void enter_a_semester ()			// Hàm để staff nhập ngày, tháng, năm bắt đầu và kết thúc học kỳ
{
	int start_year, end_year;
	int semester_n;

	cout << "Enter school year which this semester belongs to: " << endl;
	cout << "start year: "; 	cin >> start_year;		cout << endl;
	cout << "end year: ";		cin >> end_year;		cout << endl;

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

	create_a_semester_for_year ( start_year, end_year, start_date, end_date, semester_n );
}

void delete_year_and_class ()
{
	SchoolYear* year_delete = nullptr;
	Class* class_delete = nullptr;

	SchoolYear* pCur_year = HeadYear;
	Class* pCur_class = pCur_year -> ListClass;

	while ( pCur_year != nullptr )
	{
		while ( pCur_class != nullptr )
		{
			class_delete = pCur_class;
			pCur_class = pCur_class -> pNext;
			delete class_delete;
		}

		year_delete = pCur_year;
		pCur_year = pCur_year -> pNext;
		delete year_delete;
	}
}

void display_school_year_list ()
{
	SchoolYear* pCur = HeadYear;
	while ( pCur != nullptr )
	{
		cout << "This is the list of school year: " << endl;
		cout << pCur -> schoolYear / 2 << "-" << pCur -> schoolYear / 2 + 1 << ", ";
		pCur = pCur -> pNext;
	}
	cout << endl;
}

void display_classes_list_of_school_year ( int start_year, int end_year )
{
	SchoolYear* pCur_year = HeadYear;

	while ( pCur_year != nullptr && pCur_year -> schoolYear != start_year + end_year )
		pCur_year = pCur_year -> pNext;

	if ( pCur_year -> schoolYear == start_year + end_year )
	{
		cout << "This is the classes list of " << start_year << "-" << end_year << " school year:" << endl;
		Class* pCur_class = pCur_year -> ListClass;
		while ( pCur_class != nullptr )
		{
			cout << pCur_class -> className << ", ";
			pCur_class = pCur_class -> pNext;
		}
		cout << endl;
	}
	else cout << "Year is not found" << endl;
}

void display_semesters_of_school_year ( int start_year, int end_year )
{
	SchoolYear* pCur_year = HeadYear;

	while ( pCur_year != nullptr && pCur_year -> schoolYear != start_year + end_year )
		pCur_year = pCur_year -> pNext;

	if ( pCur_year -> schoolYear == start_year + end_year )
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
