#include <iostream>

using namespace std;

class Student
{
public:
    Student(int n, float s) :num(n), score(s) {}
    void change(int n, float s) { num = n; score = s; }
    void display() { cout << num << " " << score << endl; }
    void fun(Student&);
private:
    int num;
    float score;
};

void Student::fun(Student& stu) {
    display();
    change(stu.num, stu.score);
    display();
}

int main()
{
    Student stud(101, 78.5), stud_change(101, 80.5);
    stud.fun(stud_change);
    return 0;
}
/*
-*Result-*
output:
101 78.5
101 80.5
-*end*-
Analysis:
����stud��stud_change����ʱ�����˹��캯����
Student(int n, float s) :num(n), score(s) {}
����fun������change��display����������fun�����У���
�����stud��ѧ����ɼ�
������stud_change��ֵ�ı�stud��ֵ
�������ı���stud��ѧ����ɼ�
*/