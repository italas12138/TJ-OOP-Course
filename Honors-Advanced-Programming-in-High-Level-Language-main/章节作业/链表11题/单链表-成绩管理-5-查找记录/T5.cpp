#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
}*head = NULL, * tail = NULL;

int n;

void read() {
	ifstream file("d:\\student.txt");
	file >> n;

	for (int i = 1;i <= n;i++) {
		student* p = new(nothrow) student;
		if (p == NULL) {
			cout << "�����ڴ�ʧ��";
			exit(0);
		}
		file >> (p->no) >> (p->name) >> (p->score);
		p->next = NULL;
		if (head == NULL)
			head = p, tail = p;
		else
			tail->next = p, tail = p;
	}

	file.close();
}

void destroy() {
	student* p = head, * q;
	while (p != NULL) {
		q = p;
		p = p->next;
		delete q;
	}
}

bool iscontinue() {
	char c;
	cout << "�Ƿ������ѯ��y or n" << endl;
	cin >> c;
	if (c == 'y' || c == 'Y')
		return 1;
	else return 0;
}

bool find(int num) {
	student* p = head;
	while (p != NULL) {
		if (p->no == num) {
			const int width = 10;
			cout << "ѧ�ţ�" << std::left << setw(width) << (p->no);
			cout << "������" << std::left << setw(width) << (p->name);
			cout << "�ɼ���" << std::left << setw(width) << (p->score) << endl;
			return 1;
		}
		else p = p->next;
	}
	return 0;
}

void query() {
	int num;
	while (1) {
		cin >> num;
		if (!find(num))
			cout << "Not Exist" << endl;
		if (!iscontinue())
			return;
	}
}

int main() {
	read();
	query();
	destroy();

	return 0;
}