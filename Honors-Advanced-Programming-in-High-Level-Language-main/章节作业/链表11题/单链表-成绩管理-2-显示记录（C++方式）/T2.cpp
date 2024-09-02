#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
};

int main() {

	ifstream file("d:\\student.txt");
	int n;
	file >> n;

	student* head = NULL, * tail = NULL;

	for (int i = 1;i <= n;i++) {
		student* p=new(nothrow) student;
		if (p == NULL) {
			cout << "�����ڴ�ʧ��";
			return 0;
		}
		file >> (p->no) >> (p->name) >> (p->score);
		p->next = NULL;
		if (head == NULL)
			head = p, tail = p;
		else
			tail->next = p, tail = p;
	}

	file.close();//�ǵù��ļ���

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

	return 0;

}