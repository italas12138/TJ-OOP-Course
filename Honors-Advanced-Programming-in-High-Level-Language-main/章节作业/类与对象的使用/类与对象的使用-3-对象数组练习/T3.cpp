#include<iostream>

using namespace std;

class student {
private:
	int num;
	int score;
public:
	void set(int, int);
	void reveal(int);
};
void student::set(int x, int y) {
	num = x, score = y;
}
void student::reveal(int x) {
	cout << "��" << x << "��ѧ����ѧ����" << num << "���ɼ�Ϊ" << score << endl;
}

int main() {
	student stu[5];
	student* p = &stu[0];
	for (int i = 0;i < 5;i++, p++) {
		cout << "�������" << i + 1 << "��ѧ���ĳɼ���" << endl;
		int num, score;
		cin >> num >> score;
		p->set(num, score);
	}
	p = &stu[0];
	for (int i = 0;i < 5;i++, p++) {
		if (i % 2 == 1) continue;
		p->reveal(i + 1);
	}
	//delete p;���Ƕ�̬����ģ�����delete�� 
	cout << "-*�������*-" << endl;
	return 0;
}