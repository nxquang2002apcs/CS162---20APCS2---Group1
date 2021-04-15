#include "DataStructure.h"

void create_a_list_of_courses_for_currentSemester ()	
{
	int want_more = 1;
	CourseDetail* pCur  = nullptr;

	while ( want_more == 1 )
	{
		if ( CurrentSemester -> HeadCourse == nullptr )
		{
			CurrentSemester -> HeadCourse = new CourseDetail;
			pCur = CurrentSemester -> HeadCourse;
			pCur -> pPrev = nullptr;
		}
		else 
		{
			pCur -> pNext = new CourseDetail;
			pCur -> pNext -> pPrev = pCur;
			pCur = pCur -> pNext;
		}

		pCur -> pNext = nullptr;

		pCur -> ListStudent = nullptr;		// Môn học mới tạo chưa có người đăng ký
		pCur -> enrolledStudent = 0;

		cin.get();
		cout << "Enter the course's ID: ";				getline ( cin, pCur -> courseID );		cout << endl;
		cout << "Enter the course's name: ";				getline ( cin, pCur -> courseName );		cout << endl;
		cout << "Enter the course's teacher name: ";			getline ( cin, pCur -> teacherName );		cout << endl;
		cout << "Enter the course's credits: ";				cin >> pCur -> credits;				cout << endl;
		cout << "Enter the course's maximum number of students: ";	cin >> pCur -> numberStudent;			cout << endl;
										cin.get();
		cout << "Enter the course's 1st session: ";			getline ( cin, pCur -> session1 );		cout << endl;
		cout << "Enter the course's 2nd session: ";			getline ( cin, pCur -> session2 );		cout << endl;

		cout << "Add one more course?		1. Yes		2.No	\n";
		cout << "Your choice: ";			cin >> want_more;
	}
}
