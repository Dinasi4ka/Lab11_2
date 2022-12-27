// Lab11_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>


using namespace std;

enum Spec { COMP, IT, MATH, PHYSIC, WORK };
string strSpec[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

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
        cout << "������� � " << i + 1 << ":" << endl;

        cout << " �������: "; cin >> p.surname;
        cout << " ���� : "; cin >> p.curs;
        cout << " ������������ (0 - ��, 1 - ���, 2 - ��, 3 - Բ, 4 - ��): ";
        cin >> spec;
        p.spec = (Spec)spec;
        cout << "������ � ���������� "; cin >> p.math;
        cout << "������ � ������ "; cin >> p.physics;
        cout << "������ � �����������: "; cin >> p.informatics;
        cout << endl;
        if (!f.write((char*)&p, sizeof(Student)))
        {
            cerr << "." << endl;
        }
        cout << "����������? (Y/N) "; cin >> ch;
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
    cout << "| � | ������� | ���� |      ������������      | Գ���� | ���������� | ����������� |"
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
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ʳ������ ��������, �� ������� ��� �����" << endl;
        cout << " [4] - ³������ �������� � c������ ����� ������ 4" << endl;
        cout << "������ ��������: "; cin >> menuItem;
        switch (menuItem)
        {
        case 1:
            cin.get();
            cin.sync();
            cout << "����� ���������� � ���� "; cin.getline(fname, 61);
            EnterSave(fname);
            break;
        case 2:
            cin.get();
            cin.sync();
            cout << "���� ����� ����� �� ����� "; cin.getline(fname, 61);
            LoadPrint(fname);
            break;
        case 3:
            cin.get();
            cin.sync();
            cout << "������ ����� ����� "; cin.getline(fname, 61);
            cout << CountStudent(fname);
            break;
        case 4:
            cin.get();
            cin.sync();
            cout << "������ ����� ����� "; cin.getline(fname, 61);
            cout << percentOfStudent(fname);
            break;
        }

    } while (menuItem != 0);
}


