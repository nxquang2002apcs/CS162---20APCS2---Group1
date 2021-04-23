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
		pCur -> Head_Student_CourseScores = nullptr;	// Danh sách điểm chưa có

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

void create_course_scores_list (  )	
{
	CourseDetail* pCur_semester_courses = CurrentSemester -> HeadCourse;
	while ( pCur_semester_courses != nullptr )
	{
		Student* pCur_Student = pCur_semester_courses -> ListStudent;
		Student_CourseScores* pCur_Student_CourseScores = nullptr;

		while ( pCur_Student != nullptr )	// Duyệt qua từng sinh viên trong CourseDetail -> ListStudent để tạo từng Student_CourseScores mới tương ứng
		{
			// ---- Bắt đầu tạo -----
			if ( pCur_semester_courses -> HeadStudent == nullptr )
			{
				pCur_semester_courses -> HeadStudent = new Student_CourseScores;
				pCur_Student_CourseScores = pCur_semester_courses -> HeadStudent;
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
			pCur_Student_CourseScores -> className		=	pCur_Student -> className;
			// --------------------- Đã copy xong -----------------------------------

			// --- Mặc định các điểm là bằng 0 ---
			pCur_Student_CourseScores -> midterm = 0;
			pCur_Student_CourseScores -> final = 0;
			pCur_Student_CourseScores -> otherMark = 0;
			pCur_Student_CourseScores -> total = 0;
			// -----------------------------------

			// --- Tìm Course này của Student trong nhánh Class của SchoolYear ---

			Class* pCur_find_class = CurrentYear -> HeadClass;	// Tìm lớp
			while ( pCur_find_class -> className != pCur_Student_CourseScores -> className )
				pCur_find_class = pCur_find_class -> pNext;

			Student* pCur_find_student_ID = pCur_find_class -> HeadStudent;	// Tìm sinh viên
			while ( pCur_find_student_ID -> SID != pCur_Student_CourseScores -> SID )
				pCur_find_student_ID = pCur_find_student_ID -> pNext;

			CourseForEachStudent* pCur_student_enrolled_course = pCur_find_student_ID -> Head_of_enrolled_course;	// Tìm trong danh sách khóa học sinh viên đó đăng kí
			while ( pCur_student_enrolled_course -> detail.courseID != pCur_semester_courses -> courseID )
				pCur_student_enrolled_course = pCur_student_enrolled_course -> pNext;

			// pCur_Student_CourseScores -> point_to_an_enrolled_course_of_a_student_in_a_class = pCur_student_enrolled_course;

			pCur_Student = pCur_Student -> pNext;
		}

		pCur_semester_courses = pCur_semester_courses -> pNext;
	}
}

void connect_course_scores_to_student ( )
{
	CourseDetail* pCur_semester_courses = CurrentSemester -> HeadCourse;	// Chạy từ đầu danh sách khóa học của học kỳ hiện tại
	while ( pCur_semester_courses != nullptr )
	{
		Student_CourseScores* pCur_CourseScores = pCur_semester_courses -> HeadStudent;	// Chạy từ đầu danh sách điểm trong khóa học đó
		while ( pCur_CourseScores != nullptr )
		{
			Class* pCur_find_class = CurrentYear -> HeadClass;	// Tìm lớp sinh viên này đang học, bắt đầu từ đầu danh sách các lớp học của CurrentYear
			
			while (pCur_find_class != nullptr && pCur_find_class -> className != pCur_CourseScores -> className ) // bằng cách so sánh className
				pCur_find_class = pCur_find_class -> pNext;

			if ( pCur_find_class != nullptr ) // Nếu tìm thấy lớp
			{
				Student* pCur_find_student = pCur_find_class -> HeadStudent;	
				while ( pCur_find_student != nullptr && pCur_find_student -> SID != pCur_CourseScores -> SID )	// thì so sánh từng SID trong lớp đó
					pCur_find_student = pCur_find_student -> pNext;

				if ( pCur_find_student != nullptr ) // Nếu tìm thấy sinh viên
				{
					CourseForEachStudent* pCur_enrolled_courses = pCur_find_student -> Head_of_enrolled_course; // thì tìm trong danh sách khóa học sinh viên đã đăng ký
					while ( pCur_enrolled_courses != nullptr && pCur_enrolled_courses -> detail.courseID != pCur_semester_courses -> courseID ) // bằng cách so sánh courseID
						pCur_enrolled_courses = pCur_enrolled_courses -> pNext;

					if ( pCur_enrolled_courses != nullptr )	// Nếu tìm thấy
					{
						pCur_CourseScores -> point_to_an_enrolled_course_of_a_student_in_a_class = pCur_enrolled_courses;	// Nối pointer từ danh sách điểm của khóa học sang khóa học của sinh viên
						
						// --- Sao chép điểm qua ---    Để tiện khi sinh viên xem điểm của mình
						pCur_enrolled_courses -> midterm 	= 	pCur_CourseScores -> midterm;
						pCur_enrolled_courses -> final	 	= 	pCur_CourseScores -> final;
						pCur_enrolled_courses -> otherMark	= 	pCur_CourseScores -> otherMark;
						pCur_enrolled_courses -> total 		= 	pCur_CourseScores -> total;
						// --------------------------------------------------------------------
					}
				}
			}

			pCur_CourseScores = pCur_CourseScores -> pNext;
		}

		pCur_semester_courses = pCur_semester_courses -> pNext;
	}
}

void create_connection ( CourseDetail* &course, string StudentID, string className )	//	Hàm tạo liên kết một Student_CourseScores của một môn với một Student
{
	Class* pCur_class = CurrentYear -> HeadClass;	// Tìm lớp của sinh viên này đang học
	while ( pCur_class != nullptr && pCur_class -> className != className )	// bằng cách so sánh className
		pCur_class = pCur_class -> pNext;

	if ( pCur_class != nullptr )	// Nếu tìm thấy lớp
	{
		Student* pCur_student = pCur_class -> HeadStudent;	// thì tìm sinh viên này trong lớp mới tìm được
		while ( pCur_student != nullptr && pCur_student -> SID != StudentID )	// bằng cách so sánh ID sinh viên
			pCur_student = pCur_student -> pNext;

		if ( pCur_student != nullptr )	// Nếu tìm thấy sinh viên
		{
			CourseForEachStudent* pCur_enrolled_course = pCur_student -> Head_of_enrolled_course;	// thì tìm khóa học cần tạo liên kết trong danh sách khóa học sinh viên này đã đăng kí
			while ( pCur_enrolled_course != nullptr && pCur_enrolled_course -> detail.courseID != course -> courseID )	// bằng cách so sánh ID khóa học
				pCur_enrolled_course = pCur_enrolled_course -> pNext;

			if ( pCur_enrolled_course != nullptr )	// Nếu tìm thấy
			{
				cout << "found" << endl;
				Student_CourseScores* pCur_Student_CourseScores = course -> HeadStudent;	// thì tìm bảng điểm cần liên kết trong danh sách điểm của khóa học
				while ( pCur_Student_CourseScores != nullptr && pCur_Student_CourseScores -> SID != pCur_student -> SID )	// bằng cách so sánh ID sinh viên
					pCur_Student_CourseScores = pCur_Student_CourseScores -> pNext;

				if ( pCur_Student_CourseScores != nullptr )	// Nếu tìm thấy
				{
					pCur_Student_CourseScores -> point_to_an_enrolled_course_of_a_student_in_a_class = pCur_enrolled_course;	// thì tạo liên kết

					// --- Sao chép từ bảng điểm qua ----
					pCur_enrolled_course -> midterm 	=	 pCur_Student_CourseScores -> midterm;
					pCur_enrolled_course -> final		= 	 pCur_Student_CourseScores -> final;
					pCur_enrolled_course -> otherMark	= 	 pCur_Student_CourseScores -> otherMark;
					pCur_enrolled_course -> total		= 	 pCur_Student_CourseScores -> total;
					// ----------------------------------
				}
			}
		}
	}
}
