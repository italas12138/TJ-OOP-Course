#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

/**********************************************
*
*    TO-DO:
*        �벹ȫ������Ĵ��룬��ֻ�ύ���������Ĵ��롣
*
***********************************************/
class Teacher;
class Student;

class Teacher {
private:
    int id, age, gender;
    char name[100];
public:
    Teacher();
    explicit Teacher(Student&);
    void show_info();
};

class Student {
private:
    int id, age, gender;
    char name[100];
public:
    friend class Teacher;
    Student(int, int, int, char*);
    void show_info();
};

Teacher::Teacher() :id(0), age(0), gender(0) { 
    strcpy(name, ""); 
}
Teacher::Teacher(Student& stu) {
    id = stu.id;
    age = stu.age;
    gender = stu.gender;
    strcpy(name, stu.name);
}
void Teacher::show_info() {
    cout << "��ʦ��:" << id << " ";
    cout << "��ʦ����:" << age << "�� ";
    if (gender == 0)
        cout << "��ʦ�Ա�:Ů ";
    else
        cout << "��ʦ�Ա�:�� ";
    cout << "��ʦ����:" << name << endl;
}
Student::Student(int x, int y, int z, char* s) :id(x), age(y), gender(z) {
    strcpy(name, s);
}
void Student::show_info() {
    cout << "ѧ��ѧ��:" << id << " ";
    cout << "ѧ������:" << age << "�� ";
    if (gender == 0)
        cout << "ѧ���Ա�:Ů ";
    else
        cout << "ѧ���Ա�:�� ";
    cout << "ѧ������:" << name << endl;
}

/**********************************************
*
*    TO-DO END
*
***********************************************/

int main() {
    int id, age, gender;
    char name[16];

    cin >> id >> age >> gender >> name;
    Student stu(id, age, gender, name);
    stu.show_info();

    Teacher teac;
    teac = (Teacher)stu;
    teac.show_info();
    return 0;
}