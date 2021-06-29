#include "functions.h"
#include "help.h"

void AddDiscipline(disciplines& dis)
{
	string discipline;
	bool ok;
	do
	{
		cout << "������� ����������: ";
		getline(cin, discipline);
		if (!(ok = dis.Add(discipline)))
		{
			cout << endl << "������ ���������� ��� ���� ��������� �����" << endl;
			system("pause");
		}
		system("cls");
	} while (!ok);
}

void ChangeDiscipline(disciplines& dis)
{
	menu* list_dis = new menu;
	list_dis = dis.getList();
	list_dis->Print();
	int choice = list_dis->Choice("�������� ����������");
	system("cls");
	bool ok;
	string discipline;
	do
	{
		cout << "������� ����������: ";
		getline(cin, discipline);
		if (!(ok = dis.Change(dis[choice - 1], discipline)))
		{
			cout << endl << "������ ���������� ��� ����������� � ������" << endl;
			system("pause");
			system("cls");
		}
	} while (!ok);
	system("cls");
	delete list_dis;
}

void DeleteDiscipline(disciplines& dis)
{
	menu* list_dis = new menu;
	list_dis = dis.getList();
	list_dis->Print();
	int choice = list_dis->Choice("�������� ����������");
	system("cls");
	dis.Remove(dis[choice - 1]);
	system("cls");
	delete list_dis;
}

void PrintDiscipline(disciplines dis)
{
	menu* disciplines = new menu;
	disciplines = dis.getList();
	disciplines->Print();
	system("pause");
	delete disciplines;
}

void CorrectDisciplines(disciplines& dis)
{
	menu* menu_disciplines = new menu;
	menu_disciplines = getmenuDis(dis.size());
	menu_disciplines->Print();
	int choise = menu_disciplines->Choice("");
	system("cls");
	switch (choise)
	{
	case 1:
		AddDiscipline(dis);
		break;
	case 2:
		ChangeDiscipline(dis);
		break;
	case 3:
		DeleteDiscipline(dis);
		break;
	case 4:
		PrintDiscipline(dis);
		break;
	}
	delete menu_disciplines;
}

menu* getmenuDis(int size)
{
	menu* result = new menu;
	if (size == 0)
		result->Add("�������� ����������");
	else
	{
		result->Add("�������� ����������");
		result->Add("�������� ����������");
		result->Add("������� ����������");
		result->Add("���������� ������ ���������");
	}
	return result;
}

bool inputFileName(string& name)
{
	cout << "������� ��� �����: ";
	getline(cin, name);
	int size = name.size();
	int i = 0;
	while (i < size)
	{
		if ((name[i] == '/') || (name[i] == '\\') || (name[i] == ':') || (name[i] == '*') || (name[i] == '?') || (name[i] == '�') || (name[i] == '<') || (name[i] == '>') || (name[i] == '|'))
		{
			cout << endl << "������ ������������ ������ " << name[i] << endl;
			return false;
		}
		else
			i++;
	}
	return true;
}

Record InputKeyboard(disciplines& dis)
{
	Record result;
	cin >> result;
	dis.Add(result._discipline);
	return result;
}

Journal InputFile(disciplines& dis)
{
	Journal result;
	string fileName;
	bool ok;
	do
	{
		system("cls");
		while (!(ok = inputFileName(fileName)))
		{
			system("pause");
		}
		system("cls");
	} while (!ok);
	result.InputFile(fileName);
	int size = result.size();
	for (int i = 0; i < size; i++)
		dis.Add(result.getRecord(i)._discipline);
	return result;
}

void InputElement(disciplines& dis, Guide& list)
{
	menu* menu_input = new menu;
	menu_input->Add("������ ������ �� �����");
	menu_input->Add("������ ������ �� ��������� ������");
	menu_input->Print();
	int n = menu_input->Choice("�������� ��������:");
	system("cls");
	switch (n)
	{
	case 1:
		list.Add(InputFile(dis));
		break;
	case 2:
		list.Add(InputKeyboard(dis));
		break;
	}
	delete menu_input;
}

void PrintOnScreen(Guide list)
{
	list.Print();
	cout << endl;
	system("pause");
}

void PrintInFile(Guide list)
{
	string fileName;
	while (!inputFileName(fileName))
	{
		system("pause");
		system("cls");
	}
	list.PrintFile(fileName);
}

void Print(Guide list)
{
	menu* menu_choice = new menu;
	menu_choice->Add("������� ������ �� �����");
	menu_choice->Add("������� ������ � ����");
	cout << "�������� ��������:" << endl;
	menu_choice->Print();
	int choice = menu_choice->Choice("�������� ��������:");
	system("cls");
	switch (choice)
	{
	case 1:
		PrintOnScreen(list);
		break;
	case 2:
		PrintInFile(list);
		break;
	}
	system("cls");
	delete menu_choice;
}

int CheckChoise(string s, int borderBeg, int borderEnd)
{
	int num;
	if (s.empty())
	{
		cout << "������� ������ ������. ��������� ����" << endl;
		return -1;
	}
	else
	{
		num = 0;
		int len = s.size();
		int i = 0;
		int n;
		while (i < len)
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				n = s[i] - '0';
				num = num * 10 + n;
				i++;
			}
			else
			{
				cout << "������ ������������ ������: " << s[i] << " . ��������� ����" << endl;
				return -1;
			}
		if ((num < borderBeg) || (num > borderEnd))
		{
			cout << "��������� �������� �����������. �������� ������ ���� � ��������� �� " << borderBeg << " �� " << borderEnd << endl;
			return -1;
		}
		return num;
	}
}

Journal ChangeElement(Journal tmp)
{
	Journal result = tmp;
	menu* menu_choice = new menu;
	menu_choice->Add("��");
	menu_choice->Add("���");
	int enter;
	int choice;
	string n;
	int size = tmp.size();
	do
	{
		system("cls");
		do
		{
			result.Print();
			cout << endl << "�������� ����� ������: ";
			getline(cin, n);
			choice = CheckChoise(n, 1, size);
			if (choice == -1)
			{
				system("pause");
				system("cls");
			}
		} while (choice == -1);
		system("cls");
		Record e;
		cin >> e;
		if (result.Change(result.getRecord(choice - 1), e))
			cout << "������� ������� �������" << endl;
		else
			cout << "������� �� �������" << endl;
		cout << "����������? " << endl;
		menu_choice->Print();
		getline(cin, n);
		enter = menu_choice->Choice("����������?");
	} while (enter == 1);
	delete menu_choice;
	return result;
}

void Change(Guide& list)
{
	string n;
	int choice = 0;
	int size = list.size();
	do
	{
		list.Print();
		cout << endl << "�������� ����� ������: ";
		getline(cin, n);
		choice = CheckChoise(n, 1, size);
		if (choice == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	Journal tmp;
	Journal change;
	tmp = list[choice - 1];
	change = tmp;
	list.Change(tmp, ChangeElement(change));
	system("cls");
}

Journal DeleteElement(Journal tmp)
{
	Journal result = tmp;
	menu* menu_choice = new menu;
	menu_choice->Add("��");
	menu_choice->Add("���");
	int enter;
	int choice;
	string n;
	int size = tmp.size();
	do
	{
		system("cls");
		do
		{
			result.Print();
			cout << endl << "�������� ����� ������: ";
			getline(cin, n);
			choice = CheckChoise(n, 1, size);
			if (choice == -1)
			{
				system("pause");
				system("cls");
			}
		} while (choice == -1);
		system("cls");
		if (result.Remove(result.getRecord(choice - 1)))
			cout << "������� ������� �������" << endl;
		else
			cout << "������� �� �������" << endl;
		cout << "����������? " << endl;
		menu_choice->Print();
		enter = menu_choice->Choice("����������?");
	} while (enter == 1);
	delete menu_choice;
	return result;
}

void Delete(Guide& list)
{
	string n;
	int choice = 0;
	int size = list.size();
	do
	{
		list.Print();
		cout << endl << "�������� ����� ������: ";
		getline(cin, n);
		choice = CheckChoise(n, 1, size);
		if (choice == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	system("cls");
	menu* menu_choice = new menu;
	menu_choice->Add("��������� ������� ������ � ��������");
	menu_choice->Add("������� ������������ ������ � ��������");
	cout << "�������� ��������: " << endl;
	menu_choice->Print();
	int k = menu_choice->Choice("�������� ��������:");
	switch (k)
	{
	case 1:
		if (list.Remove(list[choice - 1]))
			cout << "������� ������� ������" << endl;
		else
			cout << "������� �� ��� ������" << endl;
		break;
	case 2:
		if (list.Remove(DeleteElement(list[choice - 1])))
			cout << "������� ������� ������" << endl;
		else
			cout << "������� �� ��� ������" << endl;
		break;
	}
	system("pause");
	system("cls");
}

Guide Sort_curs(Guide tmp, int sort)
{
	string field;
	int choice;
	do
	{
		cout << "������� ����: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 4)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	switch (sort)
	{
	case 1:
		return tmp.Search(CompareToCourse, choice);
	case 2:
	{
		Record check;
		check._course = choice;
		return tmp.Search_bin(CompareToCourse_jj, check, CompareToCourse_jr);
	}
	}
}

Guide Sort_group(Guide tmp, int sort)
{
	string field;
	int choice;
	do
	{
		cout << "������� ������: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 10)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	switch (sort)
	{
	case 1:
		return tmp.Search(CompareToGroup, choice);
	case 2:
	{
		Record check;
		check._group = choice;
		return tmp.Search_bin(CompareToGroup_jj, check, CompareToGroup_jr);
	}
	}
}

Guide Sort_dis(Guide tmp, int sort, disciplines dis)
{
	menu* list_dis = new menu;
	list_dis = dis.getList();
	cout << "�������� ����������:" << endl;
	list_dis->Print();
	int choice = list_dis->Choice("�������� ����������:");
	system("cls");
	delete list_dis;
	switch (sort)
	{
	case 1:
		return tmp.Search(CompareToDiscipline, dis[choice - 1]);
	case 2:
	{
		Record check;
		check._discipline = dis[choice - 1];
		return tmp.Search_bin(CompareToDiscipline_jj, check, CompareToDiscipline_jr);
	}
	}
}


void PrintResultSessions(Guide list, disciplines dis)
{
	int sort;
	menu* menu_sort = new menu;
	menu_sort->Add("������� �����");
	menu_sort->Add("�������� �����");
	cout << "�������� ������ ������:" << endl;
	menu_sort->Print();
	sort = menu_sort->Choice("�������� ������ ������:");
	system("cls");
	menu* menu_choice = new menu;
	menu_choice->Add("����");
	menu_choice->Add("������");
	menu_choice->Add("����������");
	cout << "�������� ��������:" << endl;
	menu_choice->Print();
	int choice = menu_choice->Choice("�������� ��������:");
	delete menu_sort;
	delete menu_choice;
	Guide result;
	system("cls");
	switch (choice)
	{
	case 1:
		result = Sort_curs(list, sort);
		break;
	case 2:
		result = Sort_group(list, sort);
		break;
	case 3:
		result = Sort_dis(list, sort, dis);
		break;
	}
	system("cls");
	Print(result);
}

Guide Sort_number(Guide list, int sort)
{
	string field;
	int choice;
	do
	{
		cout << "������� ����� �������: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 1000000)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	switch (sort)
	{
	case 1:
		return list.Search(CompareToNumber, choice);
	case 2:
	{
		Record check;
		check._number = choice;
		return list.Search_bin(CompareToNumber_jj, check, CompareToNumber_jr);
	}
	}
}

Guide Sort_mark(Guide list, int sort)
{
	string field;
	int choice;
	do
	{
		cout << "������� ������: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 5)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	switch (sort)
	{
	case 1:
		return list.Search(CompareToMark, choice);
	case 2:
	{
		Record check;
		check._mark = choice;
		return list.Search_bin(CompareToMark_jj, check, CompareToMark_jr);
	}
	}
}

Guide Sort_AverangeMark(Guide list)
{
	string field;
	int choice;
	do
	{
		cout << "������� ������: ";
		getline(cin, field);
		if ((choice = CheckChoise(field, 1, 5)) == -1)
		{
			system("pause");
			system("cls");
		}
	} while (choice == -1);
	return list.AverangeValue(choice);
}

void Print_With_Filter(Guide list, disciplines dis)
{
	menu* menu_choice = new menu;
	menu_choice->Add("����");
	menu_choice->Add("������");
	menu_choice->Add("����������");
	menu_choice->Add("����� �������");
	menu_choice->Add("������� ����");
	menu_choice->Add("������");
	cout << "�������� �������� ��� ����������:" << endl;
	menu_choice->Print();
	int choice = menu_choice->Choice("�������� �������� ��� ����������:");
	system("cls");
	delete menu_choice;
	menu* menu_sort = new menu;
	menu_sort->Add("�������");
	menu_sort->Add("��������");
	cout << "�������� ��� ����������:" << endl;
	menu_sort->Print();
	int sort = menu_sort->Choice("�������� ��� ����������:");
	system("cls");
	delete menu_sort;
	Guide result;
	switch (choice)
	{
	case 1:
		result = Sort_curs(list, sort);
		break;
	case 2:
		result = Sort_group(list, sort);
		break;
	case 3:
		result = Sort_dis(list, sort, dis);
		break;
	case 4:
		result = Sort_number(list, sort);
		break;
	case 5:
		Sort_AverangeMark(list);
		break;
	case 6:
		Sort_mark(list, sort);
		break;
	}
	system("cls");
	result.Print();
	cout << endl << endl;
	menu* menu_ = new menu;
	menu_->Add("��");
	menu_->Add("���");
	cout << "�������� ��� ���� ������?" << endl;
	menu_->Print();
	choice = menu_->Choice("�������� ��� ���� ������?");
	system("cls");
	delete menu_;
	if (choice == 1)
		Print_With_Filter(result, dis);
}