#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
#include <conio.h>

using namespace std;
inline void wait_for_press()
{
    cout << endl << "�����������..." << endl;
    _getch();
}

class Book_Sale
{
protected:
    char* isbn; // ָ���鼮��ŵ�ָ��
                 // ����鼮��ŵĿռ��趯̬����
                 // �鼮����� 5 �� 13 λ������ɣ��� 978-7-121-15535-2
    int    sales_volume;   // ������
    double original_price; // ԭʼ�۸�
    double real_price;     // ʵ�ۼ۸�
    double discount;       // �ۿ�
    double gross_sales;    // �����ܶ�

public:
    Book_Sale(int, int, double, double);
    Book_Sale(Book_Sale&);
    Book_Sale();
    Book_Sale(istream&);
    ~Book_Sale();
    void set(int, int, double, double);
    void set(int, int, double);
    void Set(istream&);
    void calculate_isbn(int);
    void display();
    friend istream& operator>>(istream&, Book_Sale&);
    friend ostream& operator<<(ostream&, Book_Sale&);
    void operator+=(int);
    void operator-=(int);
    friend bool operator>(Book_Sale&, Book_Sale&);
    friend bool operator>=(Book_Sale&, Book_Sale&);
    friend bool operator<(Book_Sale&, Book_Sale&);
    friend bool operator<=(Book_Sale&, Book_Sale&);
    friend bool operator==(Book_Sale&, Book_Sale&);
    friend bool operator!=(Book_Sale&, Book_Sale&);

};

class Book_Sale_Limit :protected Book_Sale {
protected:
    int limitNum;
public:
    Book_Sale_Limit(int, int, double, double, int);
    Book_Sale_Limit(Book_Sale_Limit&);
    Book_Sale_Limit();
    Book_Sale_Limit(istream&);
    void set(int, int, double, double, int);
    void set(int, int, double, int);
    void Set(istream&);
    void display();
    friend istream& operator>>(istream&, Book_Sale_Limit&);
    friend ostream& operator<<(ostream&, Book_Sale_Limit&);
    void operator+=(int);
    void operator-=(int);
    friend bool operator>(Book_Sale_Limit&, Book_Sale_Limit&);
    friend bool operator>=(Book_Sale_Limit&, Book_Sale_Limit&);
    friend bool operator<(Book_Sale_Limit&, Book_Sale_Limit&);
    friend bool operator<=(Book_Sale_Limit&, Book_Sale_Limit&);
    friend bool operator==(Book_Sale_Limit&, Book_Sale_Limit&);
    friend bool operator!=(Book_Sale_Limit&, Book_Sale_Limit&);
};

Book_Sale::Book_Sale(int x, int y, double z, double dis) {
    isbn = new char[20];
    calculate_isbn(x);
    sales_volume = y;
    original_price = z;
    discount = dis;

    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
Book_Sale::Book_Sale(Book_Sale& bk) {
    isbn = new char[20];
    strcpy(isbn, bk.isbn);
    sales_volume = bk.sales_volume;
    original_price = bk.original_price;
    real_price = bk.real_price;
    discount = bk.discount;
    gross_sales = bk.gross_sales;
}
Book_Sale::Book_Sale() {
    isbn = new char[20];
    strcpy(isbn, "");
    sales_volume = 0;
    original_price = 0;
    real_price = 0;
    discount = 0;
    gross_sales = 0;
}
Book_Sale::Book_Sale(istream& in) {
    int ib;
    in >> ib;
    if (ib == -1)
        exit(0);
    in >> sales_volume >> original_price >> discount;

    isbn = new char[20];
    calculate_isbn(ib);
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
Book_Sale::~Book_Sale() {
    // delete(isbn);//��̬�����Ҫdelete໣�
}
void Book_Sale::set(int x, int y, double z, double dis) {
    if (x != -1) calculate_isbn(x);
    if (y != -1) sales_volume = y;
    if (z != -1) original_price = z;
    if (dis != -1) discount = dis;

    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
void Book_Sale::set(int x, int y, double z) {
    if (x != -1) calculate_isbn(x);
    if (y != -1) sales_volume = y;
    if (z != -1) original_price = z;
    discount = 1;

    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
void Book_Sale::Set(istream& in) {
    int ib;
    in >> ib;
    if (ib == -1)
        exit(0);
    in >> sales_volume >> original_price >> discount;

    calculate_isbn(ib);
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}

void Book_Sale::calculate_isbn(int x) {
    strcpy(isbn, "978-7-121-");

    int ind = 9;
    for (int i = 4;i >= 0;i--) {
        char ch = '0' + (int)(x / (pow(10, i)));
        x %= (int)(pow(10, i));
        isbn[++ind] = ch;
    }
    isbn[++ind] = '-';

    int outcome = 0, multi[2] = { 1,3 }, num = 0;
    for (int i = 0;i < 17;i++) {
        int t = isbn[i] - '0';
        if (t < 0 || t>9) continue;
        outcome = (outcome + t * multi[num]) % 10;
        num = (num + 1) % 2;
    }
    outcome = (10 - outcome) % 10;
    char ch = '0' + outcome;
    isbn[++ind] = ch;
    isbn[++ind] = '\0';
}
void Book_Sale::display() {
    cout << "�����ISBN��Ϊ:" << isbn;
    cout << "������Ϊ:" << sales_volume << "��";
    cout << "��ԭ��Ϊ:" << original_price << "Ԫ";
    cout << "���ۿ�Ϊ:" << discount;
    cout << "���ּ�Ϊ:" << real_price << "Ԫ";
    cout << "�������۶�Ϊ:" << gross_sales << "Ԫ";
    cout << endl;
}
void Book_Sale::operator+=(int x) {
    sales_volume += x;
    gross_sales = real_price * sales_volume;
}
void Book_Sale::operator-=(int x) {
    sales_volume -= x;
    gross_sales = real_price * sales_volume;
}
bool operator>(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales > bk2.gross_sales;
}
bool operator>=(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales >= bk2.gross_sales;
}
bool operator<(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales <= bk2.gross_sales;
}
bool operator<=(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales <= bk2.gross_sales;
}
bool operator==(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales == bk2.gross_sales;
}
bool operator!=(Book_Sale& bk1, Book_Sale& bk2) {
    return bk1.gross_sales != bk2.gross_sales;
}
istream& operator>>(istream& in, Book_Sale& bk) {
    int ib;
    in >> ib;
    if (ib == -1)
        exit(0);
    in >> bk.sales_volume >> bk.original_price >> bk.discount;

    bk.calculate_isbn(ib);
    bk.real_price = bk.original_price * bk.discount;
    bk.gross_sales = bk.real_price * bk.sales_volume;

    return in;
}
ostream& operator<<(ostream& os, Book_Sale& bk) {
    cout << "�����ISBN��Ϊ:" << bk.isbn;
    cout << "������Ϊ:" << bk.sales_volume << "��";
    cout << "��ԭ��Ϊ:" << bk.original_price << "Ԫ";
    cout << "���ۿ�Ϊ:" << bk.discount;
    cout << "���ּ�Ϊ:" << bk.real_price << "Ԫ";
    cout << "�������۶�Ϊ:" << bk.gross_sales << "Ԫ";
    cout << endl;
    return os;
}

Book_Sale_Limit::Book_Sale_Limit(int x, int y, double z, double dis, int lim) :Book_Sale(x, y, z, dis) {
    limitNum = lim;
    if (sales_volume > limitNum) {
        gross_sales = limitNum * real_price + (sales_volume - limitNum) * original_price;
    }
}

Book_Sale_Limit::Book_Sale_Limit(Book_Sale_Limit& bk) :Book_Sale(bk) {
    limitNum = bk.limitNum;
}

Book_Sale_Limit::Book_Sale_Limit() : Book_Sale() {
    limitNum = 0;
}

Book_Sale_Limit::Book_Sale_Limit(istream& in) : Book_Sale(in) {
    in >> limitNum;
    if (sales_volume > limitNum) {
        gross_sales = limitNum * real_price + (sales_volume - limitNum) * original_price;
    }
}

void Book_Sale_Limit::set(int x, int y, double z, double dis, int lim) {
    Book_Sale::set(x, y, z, dis);
    if (lim != -1)limitNum = lim;
    if (sales_volume > limitNum) {
        gross_sales = limitNum * real_price + (sales_volume - limitNum) * original_price;
    }
}

void Book_Sale_Limit::set(int x, int y, double z, int lim) {
    Book_Sale::set(x, y, z);
    limitNum = lim;
    if (sales_volume > limitNum) {
        gross_sales = limitNum * real_price + (sales_volume - limitNum) * original_price;
    }
}

void Book_Sale_Limit::Set(istream& in) {
    Book_Sale::Set(in);
    in >> limitNum;
    if (sales_volume > limitNum) {
        gross_sales = limitNum * real_price + (sales_volume - limitNum) * original_price;
    }
}

void Book_Sale_Limit::display() {
    cout << "�����ISBN��Ϊ:" << isbn;
    cout << "������Ϊ:" << sales_volume << "��";
    cout << "��ԭ��Ϊ:" << original_price << "Ԫ";
    cout << "���ۿ�Ϊ:" << discount;
    cout << "���ּ�Ϊ:" << real_price << "Ԫ";
    cout << "�������۶�Ϊ:" << gross_sales << "Ԫ";
    cout << "���ۿ���������Ϊ:" << limitNum << "��";
    cout << endl;
}
void Book_Sale_Limit::operator+=(int x) {
    sales_volume += x;
    gross_sales = real_price * sales_volume;
    if (sales_volume > limitNum) {
        gross_sales = limitNum * real_price + (sales_volume - limitNum) * original_price;
    }
}
void Book_Sale_Limit::operator-=(int x) {
    sales_volume -= x;
    gross_sales = real_price * sales_volume;
    if (sales_volume > limitNum) {
        gross_sales = limitNum * real_price + (sales_volume - limitNum) * original_price;
    }
}
bool operator>(Book_Sale_Limit& bk1, Book_Sale_Limit& bk2) {
    return bk1.gross_sales > bk2.gross_sales;
}
bool operator>=(Book_Sale_Limit& bk1, Book_Sale_Limit& bk2) {
    return bk1.gross_sales >= bk2.gross_sales;
}
bool operator<(Book_Sale_Limit& bk1, Book_Sale_Limit& bk2) {
    return bk1.gross_sales <= bk2.gross_sales;
}
bool operator<=(Book_Sale_Limit& bk1, Book_Sale_Limit& bk2) {
    return bk1.gross_sales <= bk2.gross_sales;
}
bool operator==(Book_Sale_Limit& bk1, Book_Sale_Limit& bk2) {
    return bk1.gross_sales == bk2.gross_sales;
}
bool operator!=(Book_Sale_Limit& bk1, Book_Sale_Limit& bk2) {
    return bk1.gross_sales != bk2.gross_sales;
}
istream& operator>>(istream& in, Book_Sale_Limit& bk) {
    int ib;
    in >> ib;
    if (ib == -1)
        exit(0);
    in >> bk.sales_volume >> bk.original_price >> bk.discount >> bk.limitNum;

    bk.calculate_isbn(ib);
    bk.real_price = bk.original_price * bk.discount;
    bk.gross_sales = bk.real_price * bk.sales_volume;

    if (bk.sales_volume > bk.limitNum) {
        bk.gross_sales = bk.limitNum * bk.real_price + (bk.sales_volume - bk.limitNum) * bk.original_price;
    }

    return in;
}
ostream& operator<<(ostream& os, Book_Sale_Limit& bk) {
    cout << "�����ISBN��Ϊ:" << bk.isbn;
    cout << "������Ϊ:" << bk.sales_volume << "��";
    cout << "��ԭ��Ϊ:" << bk.original_price << "Ԫ";
    cout << "���ۿ�Ϊ:" << bk.discount;
    cout << "���ּ�Ϊ:" << bk.real_price << "Ԫ";
    cout << "�������۶�Ϊ:" << bk.gross_sales << "Ԫ";
    cout << "���ۿ���������Ϊ:" << bk.limitNum << "��";
    cout << endl;
    return os;
}

int main()
{
    {
        Book_Sale_Limit b1(95995, 3418, 100, 0.9, 3000);
        Book_Sale_Limit b2 = b1;
        Book_Sale_Limit b3;
        b3 = b1;

        cout << "���Գ�ʼ����display��cin����" << endl;

        cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:311800Ԫ���ۿ���������Ϊ:3000��\nʵ��Ϊ��";
        b1.display();
        cout << "b2Ӧ����ͬ�ϣ�ʵ��Ϊ��";
        b2.display();
        cout << "b3Ӧ����ͬ�ϣ�ʵ��Ϊ��";
        b3.display();

        Book_Sale_Limit b4;
        cout << "������ĳ�鼮������Ϣ��" << endl; //95995 3418 100 0.9 3000
        cin >> b4;
        cout << "b4Ӧ���������������Ϣ��ʵ��Ϊ��";
        b4.display();

        wait_for_press();
    }

    {
        Book_Sale_Limit b1, b2, b3(95995, 3418, 100, 1, 3000);

        cout << "����set" << endl;

        b1.set(95995, 3418, 100, 0.9, 3000);
        b2.set(95995, 3418, 100, 3000);
        b3.set(-1, 3500, -1, 0.8, -1);

        cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:311800Ԫ���ۿ���������Ϊ:3000��\nʵ��Ϊ��";
        b1.display();
        cout << "b2Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:1���ּ�Ϊ:100Ԫ�������۶�Ϊ:341800Ԫ���ۿ���������Ϊ:3000��\nʵ��Ϊ��";
        b2.display();
        cout << "b3Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3500����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.8���ּ�Ϊ:80Ԫ�������۶�Ϊ:290000Ԫ���ۿ���������Ϊ:3000��\nʵ��Ϊ��";
        b3.display();

        wait_for_press();
    }

    {
        Book_Sale_Limit b1(95995, 3418, 100, 0.9, 3000);

        cout << "��������+=/-=" << endl;

        b1 += 10;
        cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3428����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:312800Ԫ���ۿ���������Ϊ:3000��\nʵ��Ϊ��";
        b1.display();

        b1 -= 10;
        cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:311800Ԫ���ۿ���������Ϊ:3000��\nʵ��Ϊ��";
        b1.display();


        wait_for_press();
    }

    {
        Book_Sale_Limit b1(95994, 3000, 100, 0.8, 3000);//240000
        Book_Sale_Limit b2(95996, 4800, 100, 0.5, 3000);//330000
        Book_Sale_Limit b3(95998, 2000, 100, 0.9, 3000);//180000

        cout << "���ԱȽ������" << endl;

        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b1 > b3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b2 >= b3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 < b3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b2 <= b3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 == b2) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 != b1) << endl;

        wait_for_press();
    }

    return 0;
}
