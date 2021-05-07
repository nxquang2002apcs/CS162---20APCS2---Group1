#include "DataStructure.h"

void GPAStudentInCourse(Student_CourseScores*& HeadStudent) {
	Student_CourseScores* CurrentStudent = HeadStudent;
	while (CurrentStudent != nullptr) {
		CurrentStudent->courseGPA = CurrentStudent->midterm * 0.4 + CurrentStudent->final * 0.5 + CurrentStudent->otherMark * 0.1;
		CurrentStudent->point_to_an_enrolled_course_of_a_student_in_a_class->courseGPA = CurrentStudent->courseGPA;
		CurrentStudent = CurrentStudent->pNext;
	}
}

void GPASemesterOfStudent(Student*& HeadStudent) {
	Student* CurrentStudent = HeadStudent;
	while (CurrentStudent != nullptr) {
		float total = 0;
		int credits = 0;
		CourseForEachStudent* CurrentCourse = CurrentStudent->Head_of_enrolled_course;
		while (CurrentCourse != nullptr) {
			credits += CurrentCourse->detail.credits;
			total += CurrentCourse->courseGPA * CurrentCourse->detail.credits;
			CurrentCourse = CurrentCourse->pNext;
		}
		CurrentStudent->gpa = (float) (total / credits);
		CurrentStudent = CurrentStudent->pNext;
	}
}
