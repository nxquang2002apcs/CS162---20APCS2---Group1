#include "DataStructure.h"
bool check(Student* student, string ses1, string ses2) {

	if (student->Head_of_enrolled_course == nullptr)
		return true;

	CourseForEachStudent* tmp = student->Head_of_enrolled_course;

	while (tmp) {
		//so sánh string
		if (tmp->detail.session1.compare(ses1) == 0 || tmp->detail.session2.compare(ses2) == 0)
			return false;
		tmp = tmp->pNext;
	}
	return true;
}

void enroll_a_course(Student*& student, CourseDetail*& enrolledCourse) {

	int numberDefaultCourse = 5;
	//node chạy course system
	CourseDetail* tmpCourse = enrolledCourse;

	//Node chạy danh sách sinh viên khóa học
	Student_CourseScores* tmpCourseList = enrolledCourse->HeadStudent;

	//Node chạy của course mỗi sinh viên
	CourseForEachStudent* tmpEach = student->Head_of_enrolled_course;

	//Hiển thị danh sách khóa học cho sinh viên đăng kí
	/*
	while (tmpCourse) {
		cout << "Course ID: " << tmpCourse->courseID << endl;
		cout << "Course Name: " << tmpCourse->courseName << endl;
		cout << "Teacher Name: " << tmpCourse->teacherName << endl;
		cout << "Number of Credits: " << tmpCourse->credits << endl;
		cout << "Number of Students: " << tmpCourse->numberStudent << endl;
		cout << "Number of Enrolled Students: " << tmpCourse->enrolledStudent << endl;
		cout << "Session : " << tmpCourse->session1 << endl << tmpCourse->session2 << endl << endl << endl;
		tmpCourse = tmpCourse->pNext;
	}*/
	view_list_of_courses(CurrentSemester);

	int i = 0;
	do {
		char c;

		//Check có muốn đăng kí tiếp khóa học không
		cout << "You want to enroll a course? (YES/NO): ";
		cout << "	1. YES			2. NO";
		cin >> c;
		if (c == 2)
			break;

		else if (c == 1) {
			cout << "Please enter Course ID to enroll: ";
			string id;
			cin.ignore();
			getline(cin, id);

			tmpCourse = enrolledCourse;

			while (tmpCourse) {

				//check có trùng ID không
				if (tmpCourse->courseID.compare(id) == 0) {

					//check course còn slot không
					if (tmpCourse->enrolledStudent < tmpCourse->numberStudent) {

						//check có bị trùng ca học không
						if (check(student, tmpCourse->session1, tmpCourse->session2)) {

							if (student->Head_of_enrolled_course == nullptr) {

								student->Head_of_enrolled_course = new CourseForEachStudent;
								tmpEach = student->Head_of_enrolled_course;
								tmpEach->numberCourse = 1;
								tmpEach->pPrev = nullptr;

							}
							else {
								tmpEach->pNext = new CourseForEachStudent;
								tmpEach->pNext->pPrev = tmpEach;
								tmpEach = tmpEach->pNext;
								tmpEach->numberCourse++;
							}

							//thêm khóa học cho sinh viên
							tmpEach->detail.courseID = tmpCourse->courseID;
							tmpEach->detail.courseName = tmpCourse->courseName;
							tmpEach->detail.credits = tmpCourse->credits;
							tmpEach->detail.session1 = tmpCourse->session1;
							tmpEach->detail.session2 = tmpCourse->session2;

							/*tmpEach->final = 0;
							tmpEach->midterm = 0;
							tmpEach->otherMark = 0;
							tmpEach->total = 0;
							*/

							//tăng số lượng sinh viên đã enrol thành công khóa học
							tmpCourse->enrolledStudent++;

							//thêm danh sách sinh viên tham gia khóa học
							if (tmpCourse->HeadStudent == nullptr) {
								tmpCourse->HeadStudent = new Student_CourseScores;
								tmpCourseList = tmpCourse->HeadStudent;
								tmpCourseList->no = 1;
								tmpCourseList->pPrev = nullptr;
							}
							else {
								tmpCourseList->pNext = new Student_CourseScores;
								tmpCourseList->pNext->pPrev = tmpCourseList;
								tmpCourseList->no++;
								tmpCourseList = tmpCourseList->pNext;
							}

							tmpCourseList->firstName = student->firstName;
							tmpCourseList->lastName = student->lastName;
							tmpCourseList->gender = student->gender;
							tmpCourseList->SID = student->SID;
							tmpCourseList->pNext = nullptr;
							tmpCourseList->midterm = 0;
							tmpCourseList->final = 0;
							tmpCourseList->otherMark = 0;
							tmpCourseList->courseGPA = 0;

							//Node chay lien ket diem cua student_courseScore voi CourseForEach
							CourseForEachStudent* tmp = tmpCourseList->point_to_an_enrolled_course_of_a_student_in_a_class;
							while (tmp->detail.courseID != id)
								tmp = tmp->pNext;

							tmp->midterm = 0;
							tmp->final = 0;
							tmp->otherMark = 0;
							tmp->courseGPA = 0;


							tmpEach->pNext = nullptr;

							cout << "Enroll Successfully." << endl;
							cout << "You have enrolled in " << tmpEach->numberCourse << " course(s)." << endl;
							i++;
							break;
						}
						else {
							cout << "Session conflicted! Try Again!" << endl;
							break;
						}
					}
					else {
						cout << "The course is full. Try other course!" << endl;
						break;
					}
				}
				tmpCourse = tmpCourse->pNext;
			}
		}

		//Nếu nhập sai thì hỏi lại
		else
			continue;
	} while (i < numberDefaultCourse);

}