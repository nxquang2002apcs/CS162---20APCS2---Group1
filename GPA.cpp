#include "DataStructure.h"

void GPAStudent(Student_CourseScores*& HeadStudent) {
	Student_CourseScores* CurrentStudent = HeadStudent;
	while (CurrentStudent != nullptr) {
		CurrentStudent->courseGPA = CurrentStudent->midterm * 0.4 + CurrentStudent->final * 0.5 + CurrentStudent->otherMark * 0.1;
		CurrentStudent->point_to_an_enrolled_course_of_a_student_in_a_class->courseGPA = CurrentStudent->courseGPA;
		CurrentStudent = CurrentStudent->pNext;
	}
}