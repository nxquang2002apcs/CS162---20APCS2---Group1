#include "DataStructure.h"

void create_a_list_of_courses_for_currentSemester ()	
{
	int want_more = 1;
	CourseDetail* pCur  = nullptr;

	while ( want_more == 1 )
	{
		string check_id;	// Dùng để lưu tạm ID được nhập vào, nếu không trùng ID nào thì đưa vào Linked List sau

		cin.get();
		cout << "Enter the course's ID: ";							
		getline ( cin, check_id );
		cout << endl;

		// ------ Check xem có trùng ID của Course nào không:

		CourseDetail* pCur_check_id = CurrentSemester -> HeadCourse;
		
		while ( pCur_check_id != nullptr && pCur_check_id -> courseID != check_id )	// Tìm xem có ID nào trùng check_id không
			pCur_check_id = pCur_check_id -> pNext;

		if ( pCur_check_id != nullptr && pCur_check_id -> courseID == check_id )	// Nếu tìm thấy
		{
			cout << "The ID already exits. Enter again?" << endl;
			cout << "1. Yes			2.No" << endl;
			cout << "Your choice: ";
			cin >> want_more;
			continue;
		}
		
		//-----------------------------------------
		
		//--- Không trùng mới đọc tới dòng dưới --

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

		pCur -> courseID = check_id;
		cout << "Enter the course's name: ";					getline ( cin, pCur -> courseName );		cout << endl;
		cout << "Enter the course's teacher name: ";				getline ( cin, pCur -> teacherName );		cout << endl;
		cout << "Enter the course's credits: ";					cin >> pCur -> credits;				cout << endl;
		cout << "Enter the course's maximum number of students: ";		cin >> pCur -> numberStudent;			cout << endl;
											cin.get();
		cout << "Enter the course's 1st session: ";				getline ( cin, pCur -> session1 );		cout << endl;
		cout << "Enter the course's 2nd session: ";				getline ( cin, pCur -> session2 );		cout << endl;

		cout << "Add one more course?		1. Yes		2.No	\n";
		cout << "Your choice: ";		cin >> want_more;
	}
}


// NÈ COI ĐI ÔNG.

void create_course_scores_list ( CourseDetail* & Course )	// Tạm thời hàm chỉ dùng cho 1 course, nếu cần tạo cho nhiều môn thì phải gọi nhiều lần 
{
	Student* pCur_Student = Course -> ListStudent;
	Student_CourseScores* pCur_Student_CourseScores = nullptr;

	while ( pCur_Student != nullptr )	// Duyệt qua từng sinh viên trong CourseDetail -> ListStudent để tạo từng Student_CourseScores mới tương ứng
	{
		// ---- Bắt đầu tạo -----
		if ( Course -> Head_Student_CourseScores == nullptr )
		{
			Course -> Head_Student_CourseScores = new Student_CourseScores;
			pCur_Student_CourseScores = Course -> Head_Student_CourseScores;
			pCur_Student_CourseScores -> pPrev = nullptr;
		}
		else
		{
			pCur_Student_CourseScores -> pNext = new Student_CourseScores;
			pCur_Student_CourseScores -> pNext -> pPrev = pCur_Student_CourseScores;
			pCur_Student_CourseScores = pCur_Student_CourseScores -> pNext;
		}

		pCur_Student_CourseScores -> pNext = nullptr;
		// --- Đã tạo xong -----

		// --- Bắt đầu copy các Basic info từ Student vào Student_CourseScores ---
		pCur_Student_CourseScores -> no 		= 	pCur_Student -> no;
		pCur_Student_CourseScores -> SID 		= 	pCur_Student -> SID;
		pCur_Student_CourseScores -> firstName 		= 	pCur_Student -> firstName;
		pCur_Student_CourseScores -> lastName 		=	pCur_Student -> lastName;
		pCur_Student_CourseScores -> gender 		= 	pCur_Student -> gender;
		pCur_Student_CourseScores -> socialID		= 	pCur_Student -> socialID;
		pCur_Student_CourseScores -> DateOfBirth 	= 	pCur_Student -> DateOfBirth;
		// --------------------- Đã copy xong -----------------------------------

		// --- Mặc định các điểm là bằng 0 ---
		pCur_Student_CourseScores -> midterm = 0;
		pCur_Student_CourseScores -> final = 0;
		pCur_Student_CourseScores -> otherMark = 0;
		pCur_Student_CourseScores -> total = 0;
		// -----------------------------------

		// --- Tìm Course này của Student trong nhánh Class của SchoolYear ---

		int we_found_it = 0;

		SchoolYear* pCur_year = HeadYear;;
		while ( pCur_year != nullptr ) // Vào từng năm
		{
			Class* pCur_Class = pCur_year -> HeadClass;	
			while ( pCur_Class != nullptr )	// Vào từng lớp
			{
				Student* pCur_find_student_ID = pCur_Class -> HeadStudent;
				if ( pCur_find_student_ID -> SID == pCur_Student_CourseScores -> SID )	/// Nếu thấy khớp ID
				{
					CourseForEachStudent* pCur_find_courseID = pCur_find_student_ID -> Head_of_enrolled_course; // Thì tìm trong danh sách enrolled course của Student đó

					while ( pCur_find_courseID -> detail.courseID != Course -> courseID )	// Chắc chắn phải tìm được, vì Student này đã enroll
							pCur_find_courseID = pCur_find_courseID -> pNext;

					pCur_Student_CourseScores -> point_to_an_enrolled_course_of_a_student_in_a_class = pCur_find_courseID;
					we_found_it = 1;
					break;
				}

				pCur_Class = pCur_Class -> pNext;
			}

			if ( we_found_it == 1 )
				break;

			pCur_year = pCur_year -> pNext;
		} 
	}
}

