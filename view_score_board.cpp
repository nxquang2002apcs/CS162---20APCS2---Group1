#include "DataStructure.h"

void view_class_scoreboard(Class* cls)
{
	if (cls->HeadStudent == nullptr)
	{
		cout << "There are no students in the class." << endl;
		return;
	}

	Student* headstudent = cls->HeadStudent;
	CourseForEachStudent* headcourse;
	CourseForEachStudent* pCur;
	int numberOfCourse;                                           // Biến số lượng số môn học 1 sinh viên đã học
														
	cout << "No  ";										       
	cout << "First name  ";								    
	cout << setw(18) << left << "Last name";
	cout << setw(14) << left << "Student ID";
	cout << "Number of courses  ";
	cout << "Overall GPA  ";
	cout << "Course ID  ";
	cout << "Final  ";
	cout << "Course GPA  " << endl;

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
		
		cout << setw(4) << left << headstudent->no;
		cout << setw(12) << left << headstudent->firstName;
		cout << setw(18) << left << headstudent->lastName;
		cout << setw(14) << left << headstudent->SID;
		cout << setw(9) << right << numberOfCourse;
		cout << setw(14) << " "; print(headstudent->gpa);

		if (numberOfCourse != 0)
		{
	
			cout << setw(5) << right << " " << setw(11) << left << headcourse->detail.courseID;
			cout << " "; print(headcourse->final);
			cout << setw(7) << right << " "; print(headcourse->courseGPA);
			cout << endl;
		
			headcourse = headcourse->pNext;
			while (headcourse != nullptr)
			{
				cout << setw(80) << right << " " << setw(11) << left << headcourse->detail.courseID;
				cout << " "; print(headcourse->final);
				cout << setw(7) << right << " "; print(headcourse->courseGPA);
				cout << endl;

				headcourse = headcourse->pNext;
			}
		}

		headstudent = headstudent->pNext;
		cout << endl << endl;
	}
}

