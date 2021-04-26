#include "Header.h"

//Hàm xóa sinh viên ra khỏi danh sách và đổi thứ tự
void delete_a_student(Student*& HeadStudent) {
	if (HeadStudent == nullptr) {
		cout << "No existed student! Cannot delete!";
		_getch();
		return;
	}
	int delete_more = 1;
	while (delete_more == 1) {
		string studentID;
		cout << "Enter student ID you want to delete (0 to cancle): ";
		getline(cin, studentID);

		Student* tempStudent = HeadStudent;
		while (tempStudent != nullptr && tempStudent->SID != studentID)
			tempStudent = tempStudent->pNext;

		if (tempStudent == nullptr) {
			cout << "Student is not available! Cannot delete!";
			_getch();
			return;
		}
		else {

			Student* pTmp;

			if (tempStudent == HeadStudent) {
				HeadStudent = HeadStudent->pNext;
				if (HeadStudent != nullptr)
					HeadStudent->pPrev = nullptr;
			}
			else {
				tempStudent->pPrev->pNext = tempStudent->pNext;
				if (tempStudent->pNext != nullptr)
					tempStudent->pNext->pPrev = tempStudent->pPrev;
			}

			pTmp = tempStudent->pNext;
			delete tempStudent;

			while (pTmp != nullptr)
			{
				--(pTmp->no);
				pTmp = pTmp->pNext;
			}

			cout << "DELETE SUCCESSFULLY!" << endl;
		}
		cout << "You want to delete more? " << endl;
		cout << "1. YES			2. NO" << endl;
		cout << "User: ";
		cin >> delete_more;
		cin.get();
	}
}
