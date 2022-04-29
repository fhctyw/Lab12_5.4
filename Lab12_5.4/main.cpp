#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

enum class Zodiac { Ram, Bull, Twins, Crab, Lion, Virgin, Balance, Scorpion, Archer, Goat, Water_Bearer, Fish };
string strZodiac[] = { "Ram", "Bull", "Twins", "Crab", "Lion", "Virgin", "Balance", "Scorpion", "Archer", "Goat", "Water_Bearer", "Fish" };
struct Friend
{
	string name, sur_name;
	Zodiac zodiac;
	int date[3];
};

Friend InputFriend()
{
	Friend tmp;
	cout << "Введіть прізвище: ";
	cin.get();
	cin.sync();
	getline(cin, tmp.sur_name);
	cout << "Введіть ім\'я: "; getline(cin, tmp.name);
	int s;
	cout << "Введіть знак зодіаку\n(0 - Овен, 1 - Телець, 2 - Близнюки, 3 - Рак, 4 - Лев, 5 - Діва, 6 - Терези, 7 - Скорпіон, 8 - Стрілец, 9 - Козеріг, 10 - Водолій, 11 - Риби): "; cin >> s;
	tmp.zodiac = (Zodiac)s;
	cout << "Введіть день народежння: "; cin >> tmp.date[0];
	cout << "Введіть місяць народежння: "; cin >> tmp.date[1];
	cout << "Введіть рік народежння: "; cin >> tmp.date[2];
	return tmp;
}

void create_file(string path)
{
	fstream file(path, ios::binary | ios::out);

	if (file.is_open())
	{
		char choice;
		size_t i = 0;
		file.write((char*)&i, sizeof(size_t));
		do
		{
			Friend f = InputFriend();

			size_t l = f.sur_name.length() + 1;
			file.write((char*)&l, sizeof(l));
			file.write(f.sur_name.c_str(), l);
			l = f.name.length() + 1;
			file.write((char*)&l, sizeof(l));
			file.write(f.name.c_str(), l);
			file.write((char*)&f.zodiac, sizeof(f.zodiac));
			file.write((char*)&f.date, sizeof(f.date));
			i++;
			cout << "continue?(y/n): "; cin >> choice;
		} while (choice == 'y' || choice == 'Y');
		file.seekp(0);
		file.write((char*)&i, sizeof(i));
	}
	else
		cout << "Помилка create_file()" << endl;
	file.close();
}

Zodiac getSign(int day, int month)
{
	if (month == 1 && day >= 21 || month == 2 && day <= 19)
		return Zodiac::Water_Bearer;
	if (month == 2 && day >= 20 || month == 3 && day <= 20)
		return Zodiac::Fish;
	if (month == 3 && day >= 21 || month == 4 && day <= 20)
		return Zodiac::Ram;
	if (month == 4 && day >= 21 || month == 5 && day <= 21)
		return Zodiac::Bull;
	if (month == 5 && day >= 22 || month == 6 && day <= 21)
		return Zodiac::Twins;
	if (month == 6 && day >= 22 || month == 7 && day <= 23)
		return Zodiac::Crab;
	if (month == 7 && day >= 24 || month == 8 && day <= 23)
		return Zodiac::Lion;
	if (month == 8 && day >= 24 || month == 9 && day <= 23)
		return Zodiac::Virgin;
	if (month == 9 && day >= 24 || month == 10 && day <= 23)
		return Zodiac::Balance;
	if (month == 10 && day >= 24 || month == 11 && day <= 22)
		return Zodiac::Scorpion;
	if (month == 11 && day >= 23 || month == 12 && day <= 21)
		return Zodiac::Archer;
	if (month == 12 && day >= 22 || month == 1 && day <= 20)
		return Zodiac::Goat;
}

void Display(string path)
{
	fstream f(path, ios::binary | ios::in);
	if (f.is_open())
	{
		cout << "----------------------------------------------------------------" << endl;
		cout << "| № |  Прізвище  |   Ім\'я   |Знак зодіака| день | місяць | рік |" << endl;
		cout << "----------------------------------------------------------------" << endl;
		cout << left;
		size_t cnt;
		f.read((char*)&cnt, sizeof(size_t));
		for (size_t i = 0; i < cnt; i++)
		{
			Friend fr;
			size_t l;
			f.read((char*)&l, sizeof(l));
			char* tmp = new char[l];
			f.read(tmp, l);
			fr.sur_name = tmp;
			delete[] tmp;
			f.read((char*)&l, sizeof(l));
			tmp = new char[l];
			f.read(tmp, l);
			fr.name = tmp;
			delete[] tmp;
			f.read((char*)&fr.zodiac, sizeof(fr.zodiac));
			f.read((char*)&fr.date, sizeof(fr.date));

			cout << '|' <<
				setw(3) << i + 1 << '|' <<
				setw(12) << fr.sur_name << '|' <<
				setw(10) << fr.name << '|' <<
				setw(12) << strZodiac[(int)fr.zodiac] << '|' <<
				setw(6) << fr.date[0] << '|' <<
				setw(8) << fr.date[1] << '|' <<
				setw(5) << fr.date[2] << '|' << endl;
		}
		cout << "----------------------------------------------------------------" << endl;
	}
	else
		cout << "Створіть масив" << endl;
	cout << endl;
}

void Sort(string path)
{
	fstream f(path, ios::binary | ios::out | ios::in);
	if (f.is_open())
	{
		size_t cnt = 0;
		f.read((char*)&cnt, sizeof(cnt));
		Friend* fr = new Friend[cnt];
		
		for (size_t i = 0; i < cnt; i++)
		{
			size_t l;
			f.read((char*)&l, sizeof(l));
			char* tmp = new char[l];
			f.read(tmp, l);
			fr[i].sur_name = tmp;
			delete[] tmp;
			f.read((char*)&l, sizeof(l));
			tmp = new char[l];
			f.read(tmp, l);
			fr[i].name = tmp;
			delete[] tmp;
			f.read((char*)&fr[i].zodiac, sizeof(fr[i].zodiac));
			f.read((char*)&fr[i].date, sizeof(fr[i].date));
		}
		
		f.clear();
		f.seekg(0);

		for (size_t i = 0; i < cnt; i++)
			for (size_t j = 0; j < cnt-i-1; j++)
				if (fr[j].sur_name > fr[j + 1].sur_name)
					swap(fr[j], fr[j + 1]);

		f.write((char*)&cnt, sizeof(cnt));
		for (size_t i = 0; i < cnt; i++)
		{
			size_t l = fr[i].sur_name.length() + 1;
			f.write((char*)&l, sizeof(l));
			f.write(fr[i].sur_name.c_str(), l);
			l = fr[i].name.length() + 1;
			f.write((char*)&l, sizeof(l));
			f.write(fr[i].name.c_str(), l);
			f.write((char*)&fr[i].zodiac, sizeof(fr[i].zodiac));
			f.write((char*)&fr[i].date, sizeof(fr[i].date));
		}
		
		delete[] fr;
	}
	else
		cout << "Sort()" << endl;
	f.close();
}

void Search(string path, Zodiac zodiac)
{
	fstream f(path, ios::binary | ios::in);
	if (f.is_open())
	{
		cout << "----------------------------------------------------------------" << endl;
		cout << "| № |  Прізвище  |   Ім\'я   |Знак зодіака| день | місяць | рік |" << endl;
		cout << "----------------------------------------------------------------" << endl;
		cout << left;

		size_t cnt = 0;
		f.read((char*)&cnt, sizeof(cnt));
		Friend ftmp;

		for (size_t i = 0; i < cnt; i++)
		{
			size_t l;
			f.read((char*)&l, sizeof(l));
			char* tmp = new char[l];
			f.read(tmp, l);
			ftmp.sur_name = tmp;
			delete[] tmp;
			f.read((char*)&l, sizeof(l));
			tmp = new char[l];
			f.read(tmp, l);
			ftmp.name = tmp;
			delete[] tmp;
			f.read((char*)&ftmp.zodiac, sizeof(ftmp.zodiac));
			f.read((char*)&ftmp.date, sizeof(ftmp.date));

			if (ftmp.zodiac == getSign(ftmp.date[0], ftmp.date[1]))
			{
				cout << '|' <<
					setw(3) << i + 1 << '|' <<
					setw(12) << ftmp.sur_name << '|' <<
					setw(10) << ftmp.name << '|' <<
					setw(12) << strZodiac[(int)ftmp.zodiac] << '|' <<
					setw(6) << ftmp.date[0] << '|' <<
					setw(8) << ftmp.date[1] << '|' <<
					setw(5) << ftmp.date[2] << '|' << endl;
			}
		}
		cout << "----------------------------------------------------------------" << endl;
	}
	else
		cout << "Search()" << endl;
	f.close();
}

string names[]{
	"Лад",
	"Георгій",
	"Шаміль",
	"Радим",
	"Зиновій",
	"Всеслав",
	"Милодух",
	"Честислав",
	"П\'єр",
	"Щедрогост",

	"Щедра",
	"Леля",
	"Інга",
	"Улита",
	"Наталка",
	"Февросія",
	"Олімпія",
	"Харитя",
	"Филікитата",
	"Галина"
};
string sur_names[]{
	"Коцовська",
	"Вітченко",
	"Дмитриченко",
	"Богачевська",
	"Галайчук",
	"Науменко",
	"Рибак",
	"Лебеденко",
	"Лавренко",
	"Лучкевич",

	"Котик",
	"Загнітко",
	"Стецько",
	"Горняткевич",
	"Леонтовичі",
	"Медуниця",
	"Николишин",
	"Зеров",
	"Нестеренко",
	"Мартинович"
};


void gen(string path, size_t cnt)
{
	fstream file(path, ios::binary | ios::out);

	if (file.is_open())
	{
		file.write((char*)&cnt, sizeof(cnt));
		for(size_t i = 0; i < cnt; i++)
		{
			Friend f;
			f.date[0] = 1 + rand() % 28;
			f.date[1] = 1 + rand() % 12;
			f.date[2] = 1900 + rand() % 123;
			f.name = names[rand() % 20];
			f.sur_name = sur_names[rand() % 20];
			f.zodiac = getSign(f.date[0], f.date[1]);

			size_t l = f.sur_name.length() + 1;
			file.write((char*)&l, sizeof(l));
			file.write(f.sur_name.c_str(), l);
			l = f.name.length() + 1;
			file.write((char*)&l, sizeof(l));
			file.write(f.name.c_str(), l);
			file.write((char*)&f.zodiac, sizeof(f.zodiac));
			file.write((char*)&f.date, sizeof(f.date));		
		};
	}
	else
		cout << "Помилка create_file()" << endl;
	file.close();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice;
	do
	{
		cout << "1 Створити список" << endl;
		cout << "2 Переглянути список" << endl;
		cout << "3 Пошук за зодіаком список" << endl;
		cout << "4 впорядкування за прізвищем" << endl;
		cout << "5 Згенерувати" << endl;
		cout << "choise: "; cin >> choice;

		switch (choice)
		{
		case 1: {
			string path;
			cin.get();
			cout << "Введіть файл: "; getline(cin, path);
			create_file(path);
			break;
		}
		case 2: {
			string path;
			cin.get();
			cout << "Введіть файл: "; getline(cin, path);
			Display(path);
			break;
		}
		case 3: {
			string path;
			cin.get();
			cout << "Введіть файл: "; getline(cin, path);
			size_t cnt;
			int z;
			cout << "Введіть зодіак: "; cin >> z;
			Search(path, (Zodiac)z);
			break;
		}
		case 4:
		{
			string path;
			cin.get();
			cout << "Введіть файл: "; getline(cin, path);
			Sort(path);
			break;
		}
		case 5:
		{
			string path;
			cin.get();
			cout << "Введіть файл: "; getline(cin, path);
			size_t cnt;
			cout << "Введіть кількість: "; cin >> cnt;
			gen(path, cnt);
			break;
		}
		}

	} while (choice != 0);

	return 0;
}