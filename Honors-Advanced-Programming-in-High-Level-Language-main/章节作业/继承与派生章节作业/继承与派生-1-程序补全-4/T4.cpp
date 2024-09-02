#include <iostream>

using namespace std;

class Student
{
public:
    Student();
    ~Student();

protected:
    int num;
    char* name;
    char sex;
};

Student::Student() {
    name = new char[20];
    num = 0, sex = 'm';
}
Student:: ~Student() {
    delete name;
}

class Student1 : public Student
{
public:
    Student1();
    ~Student1();
    void get_value1();
    void display1();
private:
    int age;
    char* addr;
};

Student1::Student1() {
    addr = new char[20];
    //get_value1();
    age = 0;
}
Student1::~Student1() {
    delete addr;
}
void Student1::get_value1()
{
    cin >> num >> name >> sex;
    cin >> age >> addr;
}

void Student1::display1()
{
    cout << " name: " << name << endl;
    cout << " num: " << num << endl;
    cout << " sex: " << sex << endl;
    cout << " age: " << age << endl;
    cout << " address: " << addr << endl;
}


int main()
{
    Student1 stud1;
    stud1.get_value1();
    stud1.display1();
    return 0;
}
/*
* Analysis:
* ����һ��Student1���͵�stud1ʱ
    ��Student1�Ĺ��캯�������Զ�������ࣨStudent���Ĺ��캯��
    Ȼ��ִ��Student1�Ĺ��캯���е����

    ��stud1��������ʱ���Զ����������ࣨStudent1������������
    ִ����Ϻ��Զ����û��ࣨStudent������������

    ��֮�����캯���Ȼ����������࣬�����������������ٻ��ࡣ
*/
/*
* public��protected���ּ̳з�ʽ�ıȽϷ�����
* ���ù��ü̳з�ʽʱ��
* �����Ա���ʿ���Ϊpublic��protected�ĳ�Ա���������з��ʿ�����ͬ��privated�Ĳ��ɷ���
* ���ñ����̳з�ʽʱ��
* �����Ա���ʿ���Ϊpublic��protected�ĳ�Ա���������о�Ϊprotected,private�Ĳ��ɷ���
* 
* ���ߵĲ�֮ͬ�����ڣ������ԱΪpublicʱ���������з��ʿ��Ʒֱ�Ϊpublic��protected��
* 
* ��������¶��߲��ܻ�����棿
* ����public�Ļ����Ա����Ҫ������ܹ�������ʣ���ֻ�ܹ��ü̳ж����ܱ����̳У�
    ��Ҫ����벻�ܹ���������ʣ����ü̳в��ܴ��汣���̳С�
*/