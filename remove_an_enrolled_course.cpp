#include "DataStructure.h"

//Hàm cho phép sinh viên xóa một môn mình đã đăng ký
void remove_an_enrolled_course(CourseForEachStudent*& HeadCourse, string courseID, string studentID, Semester*& CurrentSemester){
    //1.Tìm ra course(tìm id trong course detail) cần xóa trong course for each student
    CourseForEachStudent* pCur_course_each_student = HeadCourse;
    while(pCur_course_each_student != nullptr && pCur_course_each_student->detail.courseID != courseID ){
        pCur_course_each_student = pCur_course_each_student->pNext;
    }
    if(pCur_course_each_student == nullptr) cout <<"This course does not exist. Please try again\n";   return;

    //Xóa course trong CourseForEachStudent
    if(pCur_course_each_student->pPrev != nullptr) pCur_course_each_student->pPrev->pNext = pCur_course_each_student->pNext;
    else HeadCourse = pCur_course_each_student-> pNext;
    if(pCur_course_each_student->pNext != nullptr) pCur_course_each_student->pNext->pPrev = pCur_course_each_student->pPrev;
    delete pCur_course_each_student;

    //--------------------------------------------------------------------------------------
    //Xóa student trong course của current semester

    //Tìm course trong semester
    CourseDetail* pCur_course_in_semester = CurrentSemester->HeadCourse;
    while(pCur_course_in_semester != nullptr && pCur_course_in_semester->courseID != courseID){
        pCur_course_in_semester = pCur_course_in_semester->pNext;
    }

    if(pCur_course_in_semester == nullptr) cout << "This course does not exist. Please try again\n";   return;
    
    //Tìm student trong course score
    Student_CourseScores* pCur_student_in_course_of_semester = pCur_course_in_semester->HeadStudent;
    while(pCur_student_in_course_of_semester != nullptr && pCur_student_in_course_of_semester->SID != studentID){
        pCur_student_in_course_of_semester = pCur_student_in_course_of_semester -> pNext;
    }

    //Xóa student
    if(pCur_student_in_course_of_semester->pPrev != nullptr) pCur_student_in_course_of_semester->pPrev->pNext = pCur_student_in_course_of_semester->pNext;
    else pCur_course_in_semester->HeadStudent = pCur_student_in_course_of_semester-> pNext;
    if(pCur_student_in_course_of_semester->pNext != nullptr) pCur_student_in_course_of_semester->pNext->pPrev = pCur_student_in_course_of_semester->pPrev;
    delete pCur_student_in_course_of_semester;
    
    //Giảm số lượng học sinh đăng kí môn đó trong curentsemester 
}
