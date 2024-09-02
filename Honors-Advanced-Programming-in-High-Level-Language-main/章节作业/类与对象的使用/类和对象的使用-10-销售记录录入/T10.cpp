#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>

using namespace std;

class Book_Sale
{
private:
    char* isbn; // ָ���鼮��ŵ�ָ��
                 // ����鼮��ŵĿռ��趯̬����
                 // �鼮����� 5 �� 13 λ������ɣ��� 978-7-121-15535-2
    int    sales_volume;   // ������
    double original_price; // ԭʼ�۸�
    double real_price;     // ʵ�ۼ۸�
    double discount;       // �ۿ�
    double gross_sales;    // �����ܶ�

public:
    /* ���Խ��� istream & �����ж�ȡ�鼮������Ϣ�Ĺ��캯��Book_Sale (istream &)�����������Լ�������Ҫ�ĳ�Ա���� */
    Book_Sale(istream &);
    ~Book_Sale();
    void Set(istream&);
    void calculate_isbn(int);
    void display();
};

Book_Sale::Book_Sale(istream &in) {
    int isbn;
    in >> isbn;
    if (isbn == -1)
        exit(0);
    in >> sales_volume >> original_price >> discount;

    calculate_isbn(isbn);
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}
Book_Sale::~Book_Sale() {
    delete(isbn);//��̬�����Ҫdelete໣�
}
void Book_Sale::Set(istream& in) {
    int isbn;
    in >> isbn;
    if (isbn == -1)
        exit(0);
    in >> sales_volume >> original_price >> discount;

    calculate_isbn(isbn);
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;
}

void Book_Sale::calculate_isbn(int x) {
    isbn = new char[20];
    strcpy(isbn, "978-7-121-");

    int ind = 9;
    for (int i = 4;i >= 0;i--) {
        //cout << (pow(10, i)) << endl;
        //cout << (int)(x / (pow(10, i))) << endl;
        char ch = '0' + (int)(x / (pow(10, i)));
        x %= (int)(pow(10, i));
        isbn[++ind] = ch;
    }
    isbn[++ind]= '-';

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
    cout << "�����ISBN��Ϊ" << isbn << endl;
    cout << "����Ϊ" << fixed << setprecision(5) << sales_volume << "��" << endl;
    cout << "ԭ��Ϊ" << fixed << setprecision(5) << original_price << "Ԫ" << endl;
    cout << "�ۿ�Ϊ" << fixed << setprecision(5) << discount << endl;
    cout << "�ּ�Ϊ" << fixed << setprecision(5) << real_price << "Ԫ" << endl;
    cout << "�����۶�Ϊ" << fixed << setprecision(5) << gross_sales <<  "Ԫ" << endl;
    cout << endl;
}
int main() {
    Book_Sale moon(cin);
    moon.display();
    while (1) {
        moon.Set(cin);
        moon.display();
    }
    return 0;
}