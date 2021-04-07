#include "DataStructure.h"

//hàm check có bị trùng lịch học không
bool check(Student* student, string ses1, string ses2) {

	if (!student->Head_of_enrolled_course)
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
	//node chạy course system
	CourseDetail* tmpCourse = enrolledCourse;	

	//Node chạy danh sách sinh viên khóa học
	Student* tmpCourseList = enrolledCourse->ListStudent;

	//Node chạy của course mỗi sinh viên
	CourseForEachStudent* tmpEach = student->Head_of_enrolled_course;

	//Hiển thị danh sách khóa học cho sinh viên đăng kí
	while (tmpCourse) {
		cout << "Course ID: " << tmpCourse->courseID << endl;
		cout << "Course Name: " << tmpCourse->courseName << endl;
		cout << "Teacher Name: " << tmpCourse->teacherName << endl;
		cout << "Number of Credits: " << tmpCourse->credits << endl;
		cout << "Number of Students: " << tmpCourse->numberStudent << endl;
		cout << "Number of Enrolled Students: " << tmpCourse->enrolledStudent << endl;
		cout << "Session : " << tmpCourse->session1 << endl << tmpCourse->session2 << endl;
	}

	int id;
	do {
		cout << "Please enter Course ID to enroll: ";
		cin >> id;
		tmpCourse = enrolledCourse;

		

		while (tmpCourse) {

			//check có trùng ID không
			if (tmpCourse->courseID == id) {

				//check course còn slot không
				if (tmpCourse->enrolledStudent < tmpCourse->numberStudent) {
					
					//check có bị trùng ca học không
					if (check(student, tmpCourse->session1, tmpCourse->session2)) {

						if (student->Head_of_enrolled_course == nullptr) {

							student->Head_of_enrolled_course = new CourseForEachStudent;
							tmpEach = student->Head_of_enrolled_course;
							tmpEach->pPrev = nullptr;

						}
						else {
							//đảm bảo đang ở node cuối
							while (tmpEach->pNext)
								tmpEach = tmpEach->pNext;

							tmpEach->pNext = new CourseForEachStudent;
							tmpEach->pNext->pPrev = tmpEach;
							tmpEach = tmpEach->pNext;
						}

						//thêm khóa học cho sinh viên
						tmpEach->detail.courseID = tmpCourse->courseID;
						tmpEach->detail.courseName = tmpCourse->courseName;
						tmpEach->detail.credits = tmpCourse->credits;
						tmpEach->detail.session1 = tmpCourse->session1;
						tmpEach->detail.session2 = tmpCourse->session2;
						tmpEach->numberCourse++;
						tmpEach->final = 0;
						tmpEach->midterm = 0;
						tmpEach->otherMark = 0;
						tmpEach->total = 0;

						//tăng số lượng sinh viên đã enrol thành công khóa học
						tmpCourse->enrolledStudent++;

						

						//thêm danh sách sinh viên tham gia khóa học
						if (tmpCourse->ListStudent == nullptr) {
							tmpCourse->ListStudent = new Student;
							tmpCourseList = tmpCourse->ListStudent;
							tmpCourseList->pPrev = nullptr;
						}
						else {
							//đảm bảo đang ở node cuối
							while (tmpCourseList->pNext)
								tmpCourseList = tmpCourseList->pNext;

							tmpCourseList->pNext = new Student;
							tmpCourseList->pNext->pPrev = tmpCourseList;
							tmpCourseList = tmpCourseList->pNext;
						}

						tmpCourseList->no++;
						tmpCourseList->firstName = student->firstName;
						tmpCourseList->lastName = student->lastName;
						tmpCourseList->gender = student->gender;
						tmpCourseList->SID = student->SID;
						tmpCourseList->DateOfBirth = student->DateOfBirth;
						tmpCourseList->pNext = nullptr;


						tmpEach->pNext = nullptr;

						cout << "Enroll Successfully." << endl;
						continue;
					}
					else {
						cout << "Session conflicted! Try Again!" << endl;
						continue;
					}
				}
				else {
					cout << "The course is full. Try other course!" << endl;
					continue;
				}
			}
			tmpCourse = tmpCourse->pNext;
		}
	} while (tmpEach->numberCourse <= 5);
	cout << "You have already enrolled in 5 courses." << endl;
}