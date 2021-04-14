#include "DataStructure.h"

void View_list_of_year();
bool go_to_detail_of_a_year(int startYear);
bool delete_a_schoolyear(int startYear);


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
	CurrentYear->semester1.isAvailable = false;
	CurrentYear->semester2.isAvailable = false;
	CurrentYear->semester2.isAvailable = false;
	CurrentYear->semester3.isAvailable = false;
	CurrentYear->semester3.isAvailable = false;
	//-------------------------------------------

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
	create_a_new_school_year(start_year, end_year);
}

void input_classes_for_current_year()		// Hàm tạo danh sách các lớp học cho năm hiện tại
{
	Class* pCur = nullptr;
	string class_name_temp;

	cout << "PLease enter the class name (0 to stop): ";
	cin >> class_name_temp;

	while (class_name_temp != "0")
	{
		if (CurrentYear->HeadClass == nullptr)					// Nếu chưa có lớp nào
		{
			CurrentYear->HeadClass = new Class;					    // thì tạo lớp mới, ListClass làm vai trò như pHead cho danh sách các lớp
			pCur = CurrentYear->HeadClass;
			pCur->pPrev = nullptr;
		}
		else
		{
			pCur->pNext = new Class;
			pCur->pNext->pPrev = pCur;
			pCur = pCur->pNext;
		}

		pCur->className = class_name_temp;						    // Tên của lớp
		pCur->HeadStudent = nullptr;								      // Lớp mới tạo chưa có danh sách học sinh

		pCur->pNext = nullptr;

		cout << "PLease enter the class name (0 to stop): ";
		cin >> class_name_temp;
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
	cin >> semester_n;
	switch (semester_n) {
	case 1:
		if (CurrentYear->semester1.isAvailable == true) {
			cout << "Semester 1 has been created. Cannot create again!" << endl;
			return;
		}
		break;
	case 2:
		if (CurrentYear->semester2.isAvailable == true) {
			cout << "Semester 2 has been created. Cannot create again!" << endl;
			return;
		}
		if (CurrentYear->semester1.isAvailable == false) {
			cout << "Semester 1 is unavailble. Cannot initialize semester 2" << endl;
			return;
		}
		break;
	case 3:
		if (CurrentYear->semester3.isAvailable == true) {
			cout << "Semester 3 has been created. Cannot create again!" << endl;
			return;
		}
		if (CurrentYear->semester1.isAvailable == false) {
			cout << "Semester 1 is unavailble. Cannot initialize semester 3" << endl;
			return;
		}
		if (CurrentYear->semester2.isAvailable == false) {
			cout << "Semester 2 is unavailble. Cannot initialize semester 3" << endl;
			return;
		}
		break;
	default:
		cout << "Invalid input!" << endl;
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
		while (pCur_class != nullptr)
		{
			cout << pCur_class->className << endl;
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

//Hiển thị thông tin của một học kỳ
bool go_to_detail_of_a_semester(int semester_n) {
	Semester tempSemester;
	//Xác định học kỳ mà người dùng đang muốn truy cập
	switch (semester_n) {
	case 1:
		tempSemester = ThisYear->semester1;
		break;
	case 2:
		tempSemester = ThisYear->semester2;
		break;
	case 3:
		tempSemester = ThisYear->semester3;
		break;
	}
	if (tempSemester.isAvailable == false) {
		return false;
	}
	else {
		system("cls");
		cout << ThisYear->startYear << "-" << ThisYear->endYear << " >> Semester " << semester_n << endl;
		//Ngày bắt đầu, kết thúc học kỳ
		cout << "Start date: " << tempSemester.startDate.day << "/" << tempSemester.startDate.month << "/" << tempSemester.startDate.year << endl;
		cout << "End date: " << tempSemester.endDate.day << "/" << tempSemester.endDate.month << "/" << tempSemester.endDate.year << endl;
		cout << endl;
		//In ra danh sách môn học
		cout << "List of courses: " << endl;
		if (tempSemester.HeadCourse == nullptr) {
			cout << "No existed course!" << endl;		//Chưa có môn học nào được khởi tạo
		}
		else {

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
			cout << tempYear->startYear << " ";
			tempYear = tempYear->pNext;
		}
		if (tempYear == nullptr) {
			cout << "Year is unavailable! Cannot access!" << endl;
			return false;
		}
		else {
			while (true) {
				system("cls");
				ThisYear = tempYear;
				int startYear = tempYear->startYear;
				int endYear = tempYear->endYear;
				cout << "    " << startYear << "-" << endYear << endl;
				cout << "  " << "--------------" << endl;
				display_semesters_of_school_year();
				display_classes_list_of_school_year();

				int choice = 0;
				cout << "0. Back" << endl
					<< "1. Go to a semester" << endl
					<< "2. Create a semester" << endl
					<< "3. Go to a class" << endl
					<< "4. Create a new class" << endl
					<< "User: ";
				cin >> choice;
				switch (choice) {
				case 0:
					return true;
				case 1:
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
					}
					system("pause");
					break;
				case 2:
					enter_a_semester();
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
		cout << "2. Activate coure registration system" << endl;
		cout << "3. Close course registration system" << endl;
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
		}
	}
}

