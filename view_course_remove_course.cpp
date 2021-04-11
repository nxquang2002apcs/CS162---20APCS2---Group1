#include "DataStructure.h"


// Hàm xem danh sách các courses đã đăng ký

void view_list_of_enrolled_course(Student* student)
{
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


// Hàm xóa 1 course với ID là courseID trong danh sách các courses đã đăng ký

void remove_an_enrolled_course(CourseForEachStudent*& Head_of_enrolled_course, string courseID)
{
	// Kiểm tra đã đăng ký course nào chưa

	if (Head_of_enrolled_course == nullptr)
	{
		cout << "There is no course in your enrolled course list." << endl;
		return;
	}

	CourseForEachStudent* pCur = Head_of_enrolled_course;

	while (pCur && pCur->detail.courseID != courseID)
		pCur = pCur->pNext;

	// Đây là khi trong list course của student không có course đó

	if (pCur == nullptr)
	{
		cout << "That course does not exist in your list of enrolled courses" << endl;
		return;
	}

	CourseForEachStudent* pTmp = pCur;

	if (pCur->pPrev)
		pCur->pPrev->pNext = pCur->pNext;
	else
		Head_of_enrolled_course = pCur->pNext;

	if (pCur->pNext) pCur->pNext->pPrev = pCur->pPrev;
	pCur = pCur->pNext;
	delete pTmp;

	// Sửa đổi thứ tự của các course sau khi đã xóa 1 course

	while (pCur)
	{
		--(pCur->numberCourse);
		pCur = pCur->pNext;
	}
}

