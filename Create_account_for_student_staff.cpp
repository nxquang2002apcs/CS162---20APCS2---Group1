#include "DataStructure.h"

// Hàm tạo tài khoản cho sinh viên
// Hàm này tự lấy thông tin trong danh sách sinh viên để tạo tài khoản cho sinh viên

void create_account_for_student(ofstream& out, Student* ListStudent)
{
	string path;
	
	while (ListStudent)
	{
		path = "data\\" + ListStudent->SID + ".txt";

		out.open(path);
		if (!out.is_open())
			cout << "Can not create file for account " << ListStudent->SID << endl;
		else
		{
			out << ListStudent->SID << endl;
			out << setfill('0') << setw(2) << ListStudent->DateOfBirth.day;
			out << setfill('0') << setw(2) << ListStudent->DateOfBirth.month;
			out << ListStudent->DateOfBirth.year << endl;
			out.close();
		}

		ListStudent = ListStudent->pNext;
	}
}


// Hàm chuyển chữ hoa về chữ thường và xóa dấu cách giữa các chữ, thêm "admin" để tạo 1 username đúng quy ước cho staff

void make_a_valid_username(string& name)
{
	for (int i = 0; i < name.length(); ++i)
		if (name[i] == ' ')
		{
			for (int j = i; j < name.length() - 1; ++j)
				name[j] = name[j + 1];

			--i;
			name.resize(name.length() - 1);
		}
	
	for (int i = 0; name[i]; ++i)
		if (name[i] >= 'A' && name[i] <= 'Z')
			name[i] += 32;

	name = "admin" + name;
}


// Hàm tạo tài khoản cho staff
// Hàm này để cho người quản lý hệ thống tạo tài khoản cho staff, người này sẽ nhập tên và password theo quy ước để lưu cho staff 

void create_account_for_staff(ofstream& out)
{
	string staffName, password;
	string path;

	while (1)
	{
		cout << "Enter staff's name: ";
		getline(cin, staffName);
		cout << "Enter password: ";
		getline(cin, password);

		make_a_valid_username(staffName);

		path = "data\\" + staffName + ".txt";

		out.open(path);
		if (!out.is_open())
			cout << "Can not create file for staff " << staffName << endl;
		else
		{
			out << staffName << endl;
			out << password << endl;
			out.close();
		}

		int choice;
		cout << "Are you done ?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		do
		{
			cout << "Your choice (enter 1 or 2): ";
			cin >> choice;
		} while (choice != 1 && choice != 2);

		if (choice == 1)
			break;		
	}
}