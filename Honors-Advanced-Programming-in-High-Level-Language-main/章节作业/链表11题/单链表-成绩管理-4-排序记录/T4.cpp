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

void print() {
	student* p = head, * q;
	const int width = 10;
	while (p != NULL) {
		cout << "ѧ�ţ�" << std::left << setw(width) << (p->no);
		cout << " ������" << std::left << setw(width) << (p->name);
		cout << " �ɼ���" << std::left << setw(width) << (p->score) << endl;

		q = p;
		p = p->next;
		delete q;
	}
}

void stu_swap(student* p1, student* p2, student* p3) {
	if (p2 == head)
		head = p3;
	else p1->next = p3;
	p2->next = p3->next;
	p3->next = p2;
}

void bubble_sort1(student* last, student* cur, int num, int done) {
	if (num >= n - done) 
		return;
	student* next = cur->next;
	if ((cur->score < next->score) || (cur->score == next->score && cur->no > next->no)) {
		stu_swap(last, cur, next);
		swap(cur, next); //�������������ز����٣���
	}
	bubble_sort1(cur, next, num + 1, done);
}

void bubble_sort() {
	int done = 0;
	while (done < n) {
		bubble_sort1(NULL, head, 1, done);
		done++;
	}
}

int main() {
	read();
	bubble_sort();
	print();

	return 0;
}
