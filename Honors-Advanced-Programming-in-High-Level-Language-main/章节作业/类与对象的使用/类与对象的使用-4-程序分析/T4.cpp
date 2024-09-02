#include <iostream>

using namespace std;

class Student
{
public:
    Student(int n, float s) :num(n), score(s) {}
    void change(int n, float s) { num = n; score = s; }
    void display() { cout << num << " " << score << endl; }
private:
    int num;
    float score;
};

int main()
{
    Student stud(101, 78.5);
    stud.display();
    stud.change(101, 80.5);
    stud.display();
    return 0;
}
/*
-*Result-*
output:
101 78.5
101 80.5
-*end*-
Analysis:
����stud����ʱ�����˹��캯����
Student(int n, float s) :num(n), score(s) {}
����display����ʱ�����101 78.5
����change����ʱ��ѧ����ɼ��޸�Ϊ��101 80.5
�ٴε���display���������101 80.5
*/