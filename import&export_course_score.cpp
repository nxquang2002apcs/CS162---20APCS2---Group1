#include "DataStructure.h"

// 1 DANH SÁCH ĐIỂM BAO GỒM:
//No, Student ID, Student First Name, Student Last Name, Gender, Class Name, Midterm Mark, Final Mark
//Other Mark, GPA;

// Nhập điểm từ file CSV vào trong hệ thống
void import_course_score_from_CSV(string path, Student_CourseScores* &head_Course_Score){

    ifstream imfile;
    imfile.open(path);
    if (!imfile.is_open()) {
        cout << "Could not open the file\n";
        return;
    }
    
    //Tạo các học sinh trong CourseScore
    Student_CourseScores* pCur_Course_Score = nullptr;
    while (!imfile.eof()) {
        // //-----DÙNG ĐỂ TEST(KHI KHÔNG CÓ DỮ LIỆU TRƯỚC)----
        // if(head_Course_Score == nullptr){
        //     head_Course_Score = new Student_CourseScores;
        //     pCur_Course_Score = head_Course_Score;
        //     pCur_Course_Score->pPrev = nullptr;
        // }else{
        //     pCur_Course_Score->pNext = new Student_CourseScores;
        //     pCur_Course_Score->pNext->pPrev = pCur_Course_Score;
        //     pCur_Course_Score = pCur_Course_Score->pNext;
        // }
        // pCur_Course_Score->pNext = nullptr;

        // //------------------------------------------------
        string no, courseGPA, final, midterm, otherMark, SID, firstName, lastName, gender, className;
        getline(imfile, no, ',');           //Lưu vào chỗ khác do không cần thiết               

        getline(imfile, SID, ',');          //Lưu vào chỗ khác do không cần thiết
        getline(imfile, firstName, ',');    //Lưu vào chỗ khác do không cần thiết
        getline(imfile, lastName, ',');     //Lưu vào chỗ khác do không cần thiết
        getline(imfile, gender, ',');       //Lưu vào chỗ khác do không cần thiết
        getline(imfile, className, ',');    //Lưu vào chỗ khác do không cần thiết

        getline(imfile, midterm, ',');                      //Import midterm
        pCur_Course_Score->midterm = stof(midterm);     

        getline(imfile, final, ',');                        //Import final 
        pCur_Course_Score->final = stof(final);

        getline(imfile, otherMark, ',');                    //Import othrmark
        pCur_Course_Score->otherMark = stof(otherMark);

        getline(imfile, courseGPA, '\n');                   //Import courseGpa  
        pCur_Course_Score->courseGPA = stof(courseGPA);
        
        pCur_Course_Score = pCur_Course_Score -> pNext;
    }

    imfile.close();

};

//Xuất điểm 1 môn từ hệ thống qua file CSV
bool export_course_score_to_CSV(string path, Student_CourseScores* head_Course_Score){
    Student_CourseScores* pCur_Course_Score = head_Course_Score; 
    ofstream exfile;
    exfile.open(path);

    if (!exfile.is_open()) {
        cout << "Could not open the file\n";
        return false;
    }
    
    //Truyền data vào file CSV
    exfile <<"No,Student ID,Student First Name,Student Last Name,Gender,Class Name,Midterm Mark,Final Mark,Other Mark,GPA\n";
    while(pCur_Course_Score){

        exfile << pCur_Course_Score->no <<","<< pCur_Course_Score->SID <<","<<  pCur_Course_Score->firstName<<","<< pCur_Course_Score->lastName <<","<<pCur_Course_Score->gender<<",";
        exfile << pCur_Course_Score->className<<","<<pCur_Course_Score->midterm <<","<< pCur_Course_Score->final <<","<<  pCur_Course_Score->otherMark <<","<< pCur_Course_Score->courseGPA <<"\n";

        pCur_Course_Score = pCur_Course_Score->pNext;
    }

    exfile.close();
}

// void display_Course_Score(Student_CourseScores* head_Course_Score){
//     Student_CourseScores* pCur = head_Course_Score;
//     while(pCur != nullptr){
//         cout <<pCur->no<<endl;
//         cout <<pCur->SID<<endl;
//         cout <<pCur->firstName<<endl;
//         cout <<pCur->lastName<<endl;
//         cout <<pCur->midterm<<endl;
//         cout <<pCur->final<<endl;
//         cout <<pCur->otherMark<<endl;
//         cout <<pCur->courseGPA<<endl;

//         pCur = pCur->pNext;
//         cout <<"--------------------\n";
//     }
// }

// void delete_course_score(Student_CourseScores* &head_Course_Score){
//     while(head_Course_Score){
//         Student_CourseScores* pCur = head_Course_Score;
//         head_Course_Score = head_Course_Score->pNext;
//         delete pCur;
//     }
// }

// int main(){
//     Student_CourseScores* head_Course_Score = nullptr;
//     import_course_score_from_CSV("import_course_score.csv", head_Course_Score);
//     display_Course_Score(head_Course_Score);
//     export_course_score_to_CSV("export_course_score.csv", head_Course_Score);
//     delete_course_score(head_Course_Score);
//     return 0;
// }