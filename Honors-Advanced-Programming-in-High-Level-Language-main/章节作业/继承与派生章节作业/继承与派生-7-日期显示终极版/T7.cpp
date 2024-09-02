#define _CRT_SECURE_NO_WARNINGS
#define ll long long  //��������longlong �ĳ�int�Ͳ��������쳣�ˣ�
#include <iostream>
#include <ctime>
#include <conio.h>
#include<cstring>

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
protected:
    int year, month, day;
public:
    Date();
    Date(int, int, int);
    Date(int);
    void set(int, int, int);
    void set(int, int);
    void set(int);
    void setx(int);
    operator int();
    int calc();
    friend istream& operator >>(istream&, Date&);
    friend ostream& operator <<(ostream&, Date&);
    friend Date operator +(Date&, int);
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

class Time {
protected:
    int h, m, s;
public:
    Time();
    Time(int, int, int);
    Time(ll);
    void set(int, int, int);
    void set(ll);
    operator ll();
    ll calc();
    friend istream& operator >>(istream&, Time&);
    friend ostream& operator <<(ostream&, Time&);
    friend Time operator +(Time&, ll);
    friend Time operator +(ll, Time&);
    friend Time operator -(Time&, ll);
    friend ll operator -(Time&, Time&);
    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);
    friend bool operator>(Time&, Time&);
    friend bool operator<(Time&, Time&);
    friend bool operator>=(Time&, Time&);
    friend bool operator<=(Time&, Time&);
    friend bool operator==(Time&, Time&);
    friend bool operator!=(Time&, Time&);
};

class DateTime :protected Date, protected Time {
public:
    DateTime();
    DateTime(int, int, int, int, int, int);
    DateTime(int, int, int);
    explicit DateTime(ll);
    void set(int, int, int, int, int, int);
    void set(int, int, int);
    void set(ll);
    operator ll();
    friend istream& operator >>(istream&, DateTime&);
    friend ostream& operator <<(ostream&, DateTime&);
    friend DateTime operator +(DateTime&, ll);
    friend DateTime operator +(ll, DateTime&);
    friend DateTime operator -(DateTime&, ll);
    friend ll operator -(DateTime&, DateTime&);
    DateTime operator =(DateTime&);
    DateTime operator =(ll);
    DateTime& operator++();
    DateTime operator++(int);
    DateTime& operator--();
    DateTime operator--(int);
    friend bool operator>(DateTime&, DateTime&);
    friend bool operator<(DateTime&, DateTime&);
    friend bool operator>=(DateTime&, DateTime&);
    friend bool operator<=(DateTime&, DateTime&);
    friend bool operator==(DateTime&, DateTime&);
    friend bool operator!=(DateTime&, DateTime&);

};

Date::Date() {
    year = 1900, month = 1, day = 1;
    /*tm t;
    time_t cur;
    time(&cur);
    localtime_s(&t, &cur);
    year = t.tm_year + 1900;
    month = t.tm_mon + 1;
    day = t.tm_mday;*/
}
Date::Date(int x, int y, int z) :year(x), month(y), day(z) {
};
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
void Date::setx(int x) {
    x = x + 1;
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
Date::operator int() {
    int ret = 0;
    ret += day;
    for (int i = 0;i < month - 1;++i)
        ret += i == 1 ? (m_sum[i] + is_leap(year)) : m_sum[i];
    for (int i = 1900;i < year;++i)
        ret += y_sum[is_leap(i)];
    return ret - 1;
}
int Date::calc() {
    return int(*this);
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
bool operator<(Date& d1, Date& d2) {
    return int(d1) < int(d2);
}
bool operator>=(Date& d1, Date& d2) {
    return int(d1) >= int(d2);
}
bool operator<=(Date& d1, Date& d2) {
    return int(d1) <= int(d2);
}
bool operator==(Date& d1, Date& d2) {
    return int(d1) == int(d2);
}
bool operator!=(Date& d1, Date& d2) {
    return int(d1) != int(d2);
}


Time::Time() {
    h = 0, m = 0, s = 0;
}
Time::Time(int x, int y, int z) {
    h = x, m = y, s = z;
}
Time::Time(ll x) {
    h = int(x / 3600), x %= 3600;
    m = int(x / 60), x %= 60;
    s = int(x);
}
void Time::set(int x, int y, int z) {
    h = x, m = y, s = z;
}
void Time::set(ll x) {
    h = int(x / 3600), x %= 3600;
    m = int(x / 60), x %= 60;
    s = int(x);
}
Time::operator ll() {
    return 1LL * h * 3600 + 1LL * m * 60 + s;
}
ll Time::calc() {
    return ll(*this);
}
istream& operator >>(istream& is, Time& t) {
    is >> t.h >> t.m >> t.s;
    return is;
}
ostream& operator <<(ostream& os, Time& t) {
    os << t.h << t.m << t.s;
    return os;
}
Time operator +(Time& t, ll x) {
    Time ret(ll(t) + x);
    return ret;
}
Time operator +(ll x, Time& t) {
    Time ret(ll(t) + x);
    return ret;
}
Time operator -(Time& t, ll x) {
    Time ret(ll(t) - x);
    return ret;
}
ll operator -(Time& t1, Time& t2) {
    return ll(t1) - ll(t2);
}
Time& Time::operator++() {
    ++s;
    m += s / 60, s %= 60;
    h += m / 60, m %= 60;
    return *this;
}
Time Time::operator++(int) {
    Time ret(ll(*this) + 1);
    return ret;
}
Time& Time::operator--() {
    --s;
    if (s < 0) {
        --m, s += 60;
    }
    if (m < 0) {
        --h, m += 60;
    }
    return *this;
}
Time Time::operator--(int) {
    Time ret(int(*this) - 1);
    return ret;
}
bool operator>(Time& t1, Time& t2) {
    return ll(t1) > ll(t2);
}
bool operator<(Time& t1, Time& t2) {
    return ll(t1) < ll(t2);
}
bool operator>=(Time& t1, Time& t2) {
    return ll(t1) >= ll(t2);
}
bool operator<=(Time& t1, Time& t2) {
    return ll(t1) <= ll(t2);
}
bool operator==(Time& t1, Time& t2) {
    return ll(t1) == ll(t2);
}
bool operator!=(Time& t1, Time& t2) {
    return ll(t1) != ll(t2);
}


DateTime::DateTime():Date(1900,1,1),Time() {
}
DateTime::DateTime(int y1, int m1, int d1, int h2, int m2, int s2):Date(y1, m1, d1), Time(h2, m2, s2) {
}
DateTime::DateTime(int h2, int m2, int s2) : Date(1900, 1, 1), Time(h2, m2, s2) {
}
DateTime::DateTime(ll x) {
    ll date = x / (60 * 60 * 24);
    x %= (60 * 60 * 24);
    Date::setx(int(date));
    Time::set(x);
}
void DateTime::set(int y1, int m1, int d1, int h2, int m2, int s2) {
    if (y1 != -1)year = y1;
    if (m1 != -1)month = m1;
    if (d1 != -1)day = d1;
    if (h2 != -1)h = h2;
    if (m2 != -1)m = m2;
    if (s2 != -1)s = s2;
}
void DateTime::set(int x, int y, int z) {
    year = x, month = y, day = z;
}
void DateTime::set(ll x) {
    ll date = x / (60 * 60 * 24);
    x %= (60 * 60 * 24);
    Date::setx(int(date));
    Time::set(x);
}
DateTime::operator ll() {
    return (Date::calc()) * 1LL * 60 * 60 * 24 + 1LL * h * 3600 + 1LL * m * 60 + s;
}
istream& operator >>(istream& is, DateTime& t) {
    is >> t.year >> t.month >> t.day >> t.h >> t.m >> t.s;
    return is;
}
ostream& operator <<(ostream& os, DateTime& t) {
    os << t.year << "��" << t.month << "��" << t.day << "�� ";
    if (t.h / 10 == 0)cout << "0";
    cout << t.h << ":";
    if (t.m / 10 == 0)cout << "0";
    cout << t.m << ":";
    if (t.s / 10 == 0)cout << "0";
    cout << t.s;
    return os;
}
DateTime operator +(DateTime& t, ll x) {
    DateTime ret(ll(t) + x);
    return ret;
}
DateTime operator +(ll x, DateTime& t) {
    DateTime ret(ll(t) + x);
    return ret;
}
DateTime operator -(DateTime& t, ll x) {
    DateTime ret(ll(t) - x);
    return ret;
}
ll operator -(DateTime& t1, DateTime& t2) {
    return ll(t1) - ll(t2);
}
DateTime DateTime::operator =(DateTime &t) {
    set(t.year, t.month, t.day, t.h, t.m, t.s);
    return *this;
}

DateTime DateTime::operator =(ll x) {
    set(x);
    return *this;
}
DateTime& DateTime::operator++() {
    DateTime::set(ll(*this) + 1);
    return *this;
}
DateTime DateTime::operator++(int) {
    DateTime ret(ll(*this));
    set(ll(*this) + 1);
    return ret;
}
DateTime& DateTime::operator--() {
    DateTime::set(ll(*this) - 1);
    return *this;
}
DateTime DateTime::operator--(int) {
    DateTime ret(ll(*this));
    set(ll(*this) - 1);
    return ret;
}
bool operator>(DateTime& t1, DateTime& t2) {
    return ll(t1) > ll(t2);
}
bool operator<(DateTime& t1, DateTime& t2) {
    return ll(t1) < ll(t2);
}
bool operator>=(DateTime& t1, DateTime& t2) {
    return ll(t1) >= ll(t2);
}
bool operator<=(DateTime& t1, DateTime& t2) {
    return ll(t1) <= ll(t2);
}
bool operator==(DateTime& t1, DateTime& t2) {
    return ll(t1) == ll(t2);
}
bool operator!=(DateTime& t1, DateTime& t2) {
    return ll(t1) != ll(t2);
}

int main()
{
    {
        DateTime t1;                           // 1900��1��1�� 00:00:00
        DateTime t2(1, 2, 3);                  // 1900��1��1�� 01:02:03
        DateTime t3(1980, 12, 31, 12, 23, 34); // 1980��12��31�� 12:23:34
        DateTime t4(123);                      // 1900��1��1�� 00:02:03

        cout << "���Գ�ʼ����cout����" << endl;

        cout << "d1Ӧ����1900��1��1�� 00:00:00�� ʵ��Ϊ��" << t1 << endl;
        cout << "d2Ӧ����1900��1��1�� 01:02:03��ʵ��Ϊ��" << t2 << endl;
        cout << "d2Ӧ����1980��12��31�� 12:23:34��ʵ��Ϊ��" << t3 << endl;
        cout << "d2Ӧ����1900��1��1�� 00:02:03��ʵ��Ϊ��" << t4 << endl;

        wait_for_press();
    }

    {
        DateTime t1;

        cout << "����set��cin����" << endl;
        t1.set(1980, 12, 31, 20, 14, 13);  // 1980��12��31�� 20:14:13
        cout << "t1Ӧ����1980��12��31�� 20:14:13��ʵ��Ϊ��" << t1 << endl;
        t1.set(2000, 2, 29);               // 2000��2��29�� 20:14:13
        cout << "t1Ӧ����2000��2��29�� 20:14:13��ʵ��Ϊ��" << t1 << endl;
        t1.set(-1, -1, -1, -1, 13, 14);    // 2000��2��29�� 20:13:14
        cout << "t1Ӧ����2000��2��29�� 20:13:14��ʵ��Ϊ��" << t1 << endl;
        t1.set(3768726214);                // 2019��6��5�� 12:23:34
        cout << "t1Ӧ����2019��6��5�� 12:23:34��ʵ��Ϊ��" << t1 << endl;

        DateTime t2;
        cout << "������ĳ�����ں�ʱ��" << endl;
        cin >> t2;
        cout << "t2Ӧ����������������ں�ʱ�䣬ʵ��Ϊ��" << t2 << endl;
        t2.set(-1, -1, -1, -1, -1, -1);
        cout << "t2Ӧ����������������ں�ʱ�䣬ʵ��Ϊ��" << t2 << endl;

        wait_for_press();
    }
     {
        DateTime t1(123);
        DateTime t2(3768726214);

        cout << "����ת�����캯����=����" << endl;

        cout << "t1Ӧ����1900��1��1�� 00:02:03��  ʵ��Ϊ��" << t1 << endl;
        cout << "t2Ӧ����2019��6��5�� 12:23:34��  ʵ��Ϊ��" << t2 << endl;

        DateTime t3, t4;
        t3 = (ll)123;
        cout << "t1Ӧ����1900��1��1�� 00:02:03��  ʵ��Ϊ��" << t3 << endl;

        t4 = (ll)3768726214;
        cout << "t2Ӧ����2019��6��5�� 12:23:34��  ʵ��Ϊ��" << t4 << endl;

        wait_for_press();
    }

     {
         DateTime d1(1900, 1, 1, 0, 2, 3);
         DateTime d2(2019, 6, 5, 12, 23, 34);

        cout << "��������ת������" << endl;

        cout << "d1Ӧ����123��   ʵ��Ϊ��" << ll(d1) << endl;
        cout << "d2Ӧ����3768726214��  ʵ��Ϊ��" << ll(d2) << endl;

        wait_for_press();
    }

      {
        DateTime d1(1907, 5, 20, 5, 20, 0);
        DateTime d2;

        cout << "��������+/-" << endl;

        d2 = d1 + (ll)60;
        cout << "d2Ӧ����1907��5��20�� 05:21:00��    ʵ��Ϊ��" << d2 << endl;

        d2 = (ll)520 + d1;
        cout << "d2Ӧ����1907��5��20�� 05:28:40��    ʵ��Ϊ��" << d2 << endl;

        d2 = d1 - (ll)3;
        cout << "d2Ӧ����1907��5��20�� 05:19:57��   ʵ��Ϊ��" << d2 << endl;

        d1.set(2016, 5, 20, 0, 0, 0);
        d2.set(2015, 5, 20, 0, 0, 0);
        cout << "d1-d2Ӧ����31622400��ʵ��Ϊ��" << d1 - d2 << endl;

        d1.set(2018, 5, 20, 0, 0, 0);
        d2.set(2017, 5, 20, 0, 0, 0);
        cout << "d1-d2Ӧ����31536000��ʵ��Ϊ��" << d1 - d2 << endl;

        wait_for_press();
    }
    
     {
        DateTime d1, d2;

        cout << "��������++/--" << endl;

        d1.set(1907, 5, 20, 12, 12, 58);
        d2 = d1++;
        cout << "d1Ӧ����1907��5��20�� 12:12:59��  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��20�� 12:12:58��  ʵ��Ϊ��" << d2 << endl;
        ++d1;
        cout << "d1Ӧ����1907��5��20�� 12:13:00��  ʵ��Ϊ��" << d1 << endl;

        d1.set(1907, 5, 20, 12, 12, 58);
        d2 = ++d1;
        cout << "d1Ӧ����1907��5��20�� 12:12:59��  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��20�� 12:12:59��  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 1, 1, 0, 0, 0);
        d2 = d1--;
        cout << "d1Ӧ����1906��12��31�� 23:59:59�� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��1��1�� 00:00:00��  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 1, 1, 0, 0, 0);
        d2 = --d1;
        cout << "d1Ӧ����1906��12��31�� 23:59:59�� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1906��12��31�� 23:59:59�� ʵ��Ϊ��" << d2 << endl;

        d1.set(2016, 2, 28, 23, 59, 59);
        d2 = d1++;
        cout << "d1Ӧ����2016��2��29�� 00:00:00�� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����2016��2��28�� 23:59:59�� ʵ��Ϊ��" << d2 << endl;

        d1.set(2018, 3, 1, 0, 0, 0);
        d2 = d1--;
        cout << "d1Ӧ����2018��2��28�� 23:59:59�� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����2018��3��1�� 00:00:00��  ʵ��Ϊ��" << d2 << endl;

        wait_for_press();
    }

    
    {
        DateTime d1(1907, 5, 20, 12, 30, 30);
        DateTime d2(1907, 5, 20, 12, 30, 30);
        DateTime d3(1907, 1, 1, 0, 0, 0);

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
