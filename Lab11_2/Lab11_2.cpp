// Lab11_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>


using namespace std;

enum Spec { COMP, IT, MATH, PHYSIC, WORK };
string strSpec[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student
{
    char surname[99];
    int curs;
    Spec spec;
    int math;
    int physics;
    int informatics;
};

double percentOfStudent(char* fname)
{

    ifstream f(fname, ios::binary);
    if (!f)
    {
        return 0;
    }

    Student p;
    int count = 0, countOfStudent = 0;
    while (f.read((char*)&p, sizeof(Student)))
    {
        countOfStudent++;
        if (((p.physics + p.math + p.informatics) / 3) < 4)
            count++;
    }

    double result = (1.0 * count / countOfStudent) * 100;

    return result;
}


double  CountStudent(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        return 0;
    }
    Student p;
    int count = 0;
    while (f.read((char*)&p, sizeof(Student)))
    {
        if (p.physics >= 4 || p.math >= 4 || p.informatics >= 4)
            count++;
    }

    return count;
}

void EnterSave(char* fname)
{
    ofstream f(fname, ios::binary);
    if (!f)
    {
        return;
    }

    Student p;

    int spec;
    char ch;
    int i = 0;
    do
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cout << " прізвище: "; cin >> p.surname;
        cout << " Курс : "; cin >> p.curs;
        cout << " Спеціальність (0 - КН, 1 - ІНФ, 2 - МЕ, 3 - ФІ, 4 - ТН): ";
        cin >> spec;
        p.spec = (Spec)spec;
        cout << "Оцінка з математики "; cin >> p.math;
        cout << "Оцінка з фізики "; cin >> p.physics;
        cout << "Оцінка з інформатики: "; cin >> p.informatics;
        cout << endl;
        if (!f.write((char*)&p, sizeof(Student)))
        {
            cerr << "." << endl;
        }
        cout << "Продовжити? (Y/N) "; cin >> ch;
        i++;
    } while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        return;
    }

    Student p;
    int i = 0;

    cout << "====================================================================================="
        << endl;
    cout << "| № | Прізвище | Курс |      Спеціальність      | Фізика | Математика | Інформатика |"
        << endl;
    cout << "-------------------------------------------------------------------------------------"
        << endl;
    while (f.read((char*)&p, sizeof(Student)))
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(9) << left << p.surname
            << "| " << setw(4) << left << p.curs << " "
            << "| " << setw(24) << left << strSpec[p.spec]
            << "| " << setw(6) << left << p.physics << " "
            << "| " << setw(10) << left << p.math << " "
            << "| " << setw(11) << left << p.informatics << " " << "|" << endl;
        cout << "-------------------------------------------------------------------------------------"
            << endl;
        ++i;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[61];
    char ch;


    int menuItem;
    do
    {
        cout << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - Кількість студентів, які вчаться без трійок" << endl;
        cout << " [4] - Відсоток студентів з cереднім балом меншим 4" << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        switch (menuItem)
        {
        case 1:
            cin.get();
            cin.sync();
            cout << "Запис інформації у файл "; cin.getline(fname, 61);
            EnterSave(fname);
            break;
        case 2:
            cin.get();
            cin.sync();
            cout << "Вивід вмісту файлу на екран "; cin.getline(fname, 61);
            LoadPrint(fname);
            break;
        case 3:
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу "; cin.getline(fname, 61);
            cout << CountStudent(fname);
            break;
        case 4:
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу "; cin.getline(fname, 61);
            cout << percentOfStudent(fname);
            break;
        }

    } while (menuItem != 0);
}


