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

void stu_swap(student* p1, student* p2, student* p3) {
	p1->next = p3;
	p2->next = p3->next;
	p3->next = p2;
}

void sort1(student* last, student* cur, int num, int done) {
	if (num >= n - done)
		return;
	student* next = cur->next;
	if ((cur->score < next->score) || (cur->score == next->score && cur->no > next->no)) {
		stu_swap(last, cur, next);
		swap(cur, next); //�������������ز����٣���
	}
	sort1(cur, next, num + 1, done);
}

void sort() {
	int done = 0;
	while (done < n) {
		sort1(head, head->next, 1, done);
		done++;
	}
}

bool iscontinue() {
	char c;
	cout << "�Ƿ������ӣ�y or n" << endl;
	cin >> c;
	if (c == 'y' || c == 'Y')
		return 1;
	else return 0;
}

student* searchbyID(int num) {
	student* p = head->next;
	while (p != NULL) {
		if (p->no == num)
			return p;
		else
			p = p->next;
	}
	return NULL;
}

void addnode(int num) {
	student* p = new(nothrow) student;
	if (p == NULL) {
		cout << "�����ڴ�ʧ��";
		exit(0);
	}
	p->no = num;
	cin >> (p->name) >> (p->score);
	p->next = NULL;
	tail->next = p, tail = p;
	n++;
}

void sol() {
	int num;
	while (1) {
		cin >> num;
		student* p = searchbyID(num);
		if (p != NULL)
			cout << "Existed" << endl;
		else
			addnode(num);
		if (!iscontinue())
			return;
	}
}

int main() {
	read();
	sol();
	sort();
	print();

	return 0;
}