#include "DataStructure.h"

void create_a_list_of_courses_for_currentSemester ()	
{
	int want_more = 1;
	CourseDetail* pCur = CurrentSemester -> HeadCourse;

	while ( want_more == 1 )
	{
		if ( pCur == nullptr )
		{
			pCur = new CourseDetail;
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

		cout << "Enter the course's ID: ";					cin >> pCur -> courseID;		cout << endl;
		cout << "Enter the course's name: ";					cin >> pCur -> courseName;		cout << endl;
		cout << "Enter the course's teacher name: ";				cin >> pCur -> teacherName;		cout << endl;
		cout << "Enter the course's credits: ";					cin >> pCur -> credits;			cout << endl;
		cout << "Enter the course's maximum number of students: ";		cin >> pCur -> numberStudent;		cout << endl;
		cout << "Enter the course's 1st session: ";				cin >> pCur -> session1;		cout << endl;
		cout << "Enter the course's 2nd session: ";				cin >> pCur -> session2;		cout << endl;

		cout << "Add one more course?		1. Yes		2.No	\n";
		cout << "Your choice: ";			
                cin >> want_more;
	}
}
