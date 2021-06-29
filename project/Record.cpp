#include "Record.h"
#include "menu.h"

using namespace std;

istream& operator>>(istream& is, Record& e)
{
	int course;
	int group;
	string fio;
	int number;
	string discipline;
	int mark;
	string field;
	menu* check = new menu();

	if (typeid(is) == typeid(ifstream))
	{
		is >> field;
		if ((course = check->CheckChoise(field, 1, 4)) == -1)
		{
			system("pause");
			e = Record();
			return is;
		}
		is >> field;
		if ((group = check->CheckChoise(field, 1, 10)) == -1)
		{
			system("pause");
			e = Record();
			return is;
		}
		is >> fio;
		is >> field;
		if ((number = check->CheckChoise(field, 1, 1000000)) == -1)
		{
			system("pause");
			e = Record();
			return is;
		}
		is >> discipline;
		is >> field;
		if ((mark = check->CheckChoise(field, 1, 5)) == -1)
		{
			system("pause");
			e = Record();
			return is;
		}
	}
	else
	{
		do
		{
			cout << "������� ���������� � ��������: " << endl;
			cout << "����: ";
			is >> field;
			if ((course = check->CheckChoise(field, 1, 5)) == -1)
			{
				system("pause");
				system("cls");
				cout << "������� ���������� � ��������: " << endl;
			}
		} while (course == -1);
		do
		{
			cout << "������: ";
			is >> field;
			if ((group = check->CheckChoise(field, 1, 10)) == -1)
			{
				system("pause");
				system("cls");
				cout << "������� ���������� � ��������: " << endl;
			}
		} while (group == -1);
		cout << "������� ��� � �������� ��������: "; is >> fio;
		do
		{
			cout << "����� �������� ������: ";
			is >> field;
			if ((number = check->CheckChoise(field, 1, 1000000)) == -1)
			{
				system("pause");
				system("cls");
				cout << "������� ���������� � ��������: " << endl;
			}
		} while (number == -1);
		cout << "����������: "; is >> discipline;
		do
		{
			cout << "������: ";
			is >> field;
			if ((mark = check->CheckChoise(field, 1, 5)) == -1)
			{
				system("pause");
				system("cls");
				cout << "������� ���������� � ��������: " << endl;
			}
		} while (mark == -1);
	}
	delete check;
	e = Record(course, group, fio, number, discipline, mark);
	return is;
}

ostream& operator<<(ostream& os, const Record& e)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << e._course << '\t';
		os << e._group << '\t';
		os << e._fio << "\t\t\t\t";
		os << e._number << "\t\t";
		os << e._discipline << "\t\t";
		os << e._mark;
	}
	else
	{
		os << "���������� � ��������: " << endl;
		os << "����: " << e._course << endl;
		os << "������: " << e._group << endl;
		os << "������� ��� � ��������: " << e._fio << endl;
		os << "����� �������: " << e._number << endl;
		os << "����������: " << e._discipline << endl;
		os << "������: " << e._mark << endl;
	}
	//os << endl;
	return os;
}