#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

int y_sum[2] = { 365,366 };
int m_sum[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

inline void wait_for_press()
{
	cout << endl << "�����������..." << endl;
	_getch();
}

bool is_leap(int x) {
    if (x % 100 == 0)
        return x % 400 == 0;
    return x % 4 == 0;
}

class Date {
private:
	int year, month, day;
public:
	Date();
	Date(int, int, int);
	Date(int);
    void set(int, int, int);
	void set(int, int);
	void set(int);
	operator int();
	friend istream& operator >>(istream&, Date&);
	friend ostream& operator <<(ostream&, Date&);
	friend Date operator +(Date&,int);
    friend Date operator +(int, Date&);
    friend Date operator -(Date&, int);
    friend int operator -(Date&, Date&);
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    friend bool operator>(Date&, Date&);
    friend bool operator<(Date&, Date&);
    friend bool operator>=(Date&, Date&);
    friend bool operator<=(Date&, Date&);
    friend bool operator==(Date&, Date&);
    friend bool operator!=(Date&, Date&);
};

Date::Date() {
    tm t;
    time_t cur;
    time(&cur);
    localtime_s(&t, &cur);
    year = t.tm_year + 1900;
    month = t.tm_mon + 1;
    day = t.tm_mday;
}
Date::Date(int x, int y, int z) :year(x), month(y), day(z) {};
Date::Date(int x) { //���Ǹ�����
    year = 1900, month = 1, day = 1;
    bool leap = is_leap(year);
    while (x > y_sum[leap]) {
        x -= y_sum[leap];
        ++year;
        leap = is_leap(year);
    }
    while ((month != 2 && x > m_sum[month - 1]) || (x > m_sum[month - 1] + leap)) {
        if (month != 2) x -= m_sum[month - 1];
        else x -= (m_sum[month - 1] + leap);
        ++month;
    }
    day = x;
}
void Date::set(int x, int y, int z) {
    if (x != 0)year = x;
    if (y != 0) month = y;
    if (z != 0)day = z;
}
void Date::set(int x, int y) {
    year = x;
    month = y;
    day = 1;
}
void Date::set(int x) {
    year = x;
    month = 1;
    day = 1;
}
Date::operator int() {
    int ret = 0;
    ret += day;
    for (int i = 0;i < month - 1;++i)
        ret += i == 1 ? (m_sum[i] + is_leap(year)) : m_sum[i];
    for (int i = 1900;i < year;++i)
        ret += y_sum[is_leap(i)];
    return ret;
}
istream& operator>>(istream& is, Date& d) {
    is >> d.year >> d.month >> d.day;
    return is;
}
ostream& operator <<(ostream& os, Date& d) {
    os << d.year << "��" << d.month << "��" << d.day << "��";
    return os;
}
/*
* ��ʵ������������+-Ҳ�ܵó���
* ��Ϊ�Ѿ�ʵ����Date��int���໥ת��
* ��1900.1.1Ϊ��ת������
*/
Date operator +(Date& d, int x) {
    int tmp = int(d) + x;
    return Date(tmp);
}
Date operator +(int x, Date& d) {
    int tmp = int(d) + x;
    return Date(tmp);
}
Date operator -(Date& d, int x) {
    int tmp = int(d) - x;
    return Date(tmp);
}
int operator -(Date& d1, Date& d2) {
    int tmp = int(d1) - int(d2);
    return tmp;
}
Date& Date::operator++() {
    ++day;
    if (day > (month == 2 ? (m_sum[month - 1] + is_leap(year)) : m_sum[month - 1]))
        ++month, day = 1;
    if (month > 12)
        ++year, month = 1;
    return *this;
}
Date Date::operator++(int) {
    Date ret(year, month, day);
    ++day;
    if (day > (month == 2 ? (m_sum[month - 1] + is_leap(year)) : m_sum[month - 1]))
        ++month, day = 1;
    if (month > 12)
        ++year, month = 1;
    return ret;
}
Date& Date::operator--() {
    --day;
    if (day == 0) {
        if (month == 1)
            --year, month = 12, day = 31;
        else
            --month, day = (month == 2 ? (m_sum[month - 1] + is_leap(year)) : m_sum[month - 1]);
    }
    return *this;
}
Date Date::operator--(int) {
    Date ret(year, month, day);
    --day;
    if (day == 0) {
        if (month == 1)
            --year, month = 12, day = 31;
        else
            --month, day = (month == 2 ? (m_sum[month - 1] + is_leap(year)) : m_sum[month - 1]);
    }
    return ret;
}
bool operator>(Date& d1, Date& d2) {
    return int(d1) > int(d2);
}
bool operator<(Date& d1, Date& d2){
    return int(d1) < int(d2);
}
bool operator>=(Date& d1, Date& d2) {
    return int(d1) >= int(d2);
}
bool operator<=(Date& d1, Date& d2){
    return int(d1) <= int(d2);
}
bool operator==(Date& d1, Date& d2) {
    return int(d1) == int(d2);
}
bool operator!=(Date& d1, Date& d2) {
    return int(d1) != int(d2);
}
int main()
{
     {
        Date d1;
        Date d2(1907, 5, 20);

        cout << "���Գ�ʼ����cout����" << endl;

        cout << "d1Ӧ���ǽ��죬 ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��20�գ�ʵ��Ϊ��" << d2 << endl;

        wait_for_press();
    }

    {
        Date d1, d2, d3, d4;

        cout << "����set��cin����" << endl;
        d1.set(1907, 5, 20);
        d2.set(1907, 5);
        d3.set(1907);

        cout << "d1Ӧ����1907��5��20�գ�ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��1�գ� ʵ��Ϊ��" << d2 << endl;
        cout << "d3Ӧ����1907��1��1�գ� ʵ��Ϊ��" << d3 << endl;

        cout << "������ĳ����" << endl;
        cin >> d4;
        d4.set(0, 0, 0);
        cout << "d4Ӧ����������������ڣ�ʵ��Ϊ��" << d4 << endl;

        wait_for_press();
    }
     {
        Date d1(10);
        Date d2(250);
        Date d3(1314);
        Date d4(13145);

        cout << "����ת�����캯��" << endl;

        cout << "d1Ӧ����1900��1��10�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1900��9��7�գ�ʵ��Ϊ��" << d2 << endl;
        cout << "d3Ӧ����1903��8��7�գ�  ʵ��Ϊ��" << d3 << endl;
        cout << "d4Ӧ����1935��12��28�գ�ʵ��Ϊ��" << d4 << endl;

        Date d5, d6;
        d5 = 30041;
        cout << "d5Ӧ����1982��4��1�գ� ʵ��Ϊ��" << d5 << endl;

        d6 = 42301;
        cout << "d6Ӧ����2015��10��25�գ� ʵ��Ϊ��" << d6 << endl;

        wait_for_press();
    }
    
    {
        Date d1(1900, 1, 1);
        Date d2(1907, 5, 20);
        Date d3(1982, 4, 1);
        Date d4(2015, 10, 25);

        cout << "��������ת������" << endl;

        cout << "d1Ӧ����1��     ʵ��Ϊ��" << int(d1) << endl;
        cout << "d2Ӧ����2696�� ʵ��Ϊ��" << int(d2) << endl;
        cout << "d3Ӧ����30041�� ʵ��Ϊ��" << int(d3) << endl;
        cout << "d4Ӧ����42301�� ʵ��Ϊ��" << int(d4) << endl;

        wait_for_press();
    }
    
    {
        Date d1(1907, 5, 20);
        Date d2;

        cout << "��������+/-" << endl;

        d2 = d1 + 520;
        cout << "d2Ӧ����1908��10��21�գ�    ʵ��Ϊ��" << d2 << endl;

        d2 = 520 + d1;
        cout << "d2Ӧ����1908��10��21�գ�    ʵ��Ϊ��" << d2 << endl;

        d2 = d1 - 3;
        cout << "d2Ӧ����1907��5��17�գ�   ʵ��Ϊ��" << d2 << endl;

        d1.set(2016, 5, 20);
        d2.set(2015, 5, 20);
        cout << "d1-d2Ӧ����366��ʵ��Ϊ��" << d1 - d2 << endl;

        d1.set(2018, 5, 20);
        d2.set(2017, 5, 20);
        cout << "d1-d2Ӧ����365��ʵ��Ϊ��" << d1 - d2 << endl;

        wait_for_press();
    }
    
    {
        Date d1, d2;

        cout << "��������++/--" << endl;

        d1.set(1907, 5, 20);
        d2 = d1++;
        cout << "d1Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��20�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 5, 20);
        d2 = ++d1;
        cout << "d1Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 1, 1);
        d2 = d1--;
        cout << "d1Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��1��1�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 1, 1);
        d2 = --d1;
        cout << "d1Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d2 << endl;

        d1.set(2016, 2, 28);
        d2 = d1++;
        cout << "d1Ӧ����2016��2��29�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����2016��2��28�գ� ʵ��Ϊ��" << d2 << endl;

        d1.set(2018, 3, 1);
        d2 = d1--;
        cout << "d1Ӧ����2018��2��28�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����2018��3��1�գ�  ʵ��Ϊ��" << d2 << endl;

        wait_for_press();
    }
    
    
    {
        Date d1(1907, 5, 20);
        Date d2(1907, 5, 20);
        Date d3(1907, 1, 1);

        cout << "���ԱȽ������" << endl;

        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d1 > d3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d2 >= d3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d1 < d3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d2 <= d3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d1 == d2) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d1 != d1) << endl;

        wait_for_press();
    }
    
    return 0;
}
