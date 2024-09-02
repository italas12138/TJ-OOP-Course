#include<iostream>
#include<fstream>
#include<iomanip>
#include<utility>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
}*head, * tail;

int n;

void read() {
	head = new(nothrow) student; //������ͷ���
	if (head == NULL) {
		cout << "�����ڴ�ʧ��";
		exit(0);
	}
	head->next = NULL;
	tail = head;

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
		tail->next = p, tail = p;
	}

	file.close();
}

void print() {
	student* p = head->next, * q;
	const int width = 10;
	while (p != NULL) {
		cout << "ѧ�ţ�" << std::left << setw(width) << (p->no);
		cout << " ������" << std::left << setw(width) << (p->name);
		cout << " �ɼ���" << std::left << setw(width) << (p->score) << endl;

		q = p;
		p = p->next;
		delete q;
	}
	delete head;
}

bool iscontinue() {
	char c;
	cout << "�Ƿ����ɾ����y or n" << endl;
	cin >> c;
	if (c == 'y' || c == 'Y')
		return 1;
	else return 0;
}

pair<student*, student*> searchbyID(int num) {
	student* p = head->next, * last = head;
	while (p != NULL) {
		if (p->no == num)
			return { last,p };
		else
			last = p, p = p->next;
	}
	return { NULL,NULL };
}

void deleteptr(student* last, student* p) {
	last->next = p->next;
	delete p;
}

void sol() {
	int num;
	while (1) {
		cin >> num;
		pair<student*, student*> ot = searchbyID(num);

		if (ot.second == NULL)
			cout << "Not Exist" << endl;
		else deleteptr(ot.first, ot.second);

		if (!iscontinue())
			return;
	}
}

int main() {
	read();
	sol();
	print();

	return 0;
}