#include<iostream>
using namespace std;
struct node {
	double val;
	int len;
	node* next;
}*head, * tail;
int get_len(int x) {
	if (x == 0) return 1;
	int ret = 0;
	if (x < 0)
		ret++, x = -x;
	while (x) {
		ret++;
		x /= 10;
	}
	return ret;
}
int main() {
	cout << "������һЩ����������q����:\n ";

	head = new(nothrow)node;
	if (head == NULL) {
		cout << "��̬�����ڴ�ʧ��" << endl;
		return 0;
	}
	head->next = NULL;
	tail = head;

	double x;
	int Len=0;
	while (cin >> x) {
		node* p = new(nothrow)node;
		if (p == NULL) {
			cout << "��̬�����ڴ�ʧ��" << endl;
			return 0;
		}
		p->val = x;
		p->len = get_len((int)x);
		p->next = NULL;
		tail->next = p;
		tail = p;

		Len = max(Len, p->len);
	}

	node* p = head;
	while (p->next != NULL) {
		p = p->next;
		x = p->val;
		cout.width(Len + 4);
		long long y = (long long)(1ll * 1000 * x); //�ضϵķ������������������룡
		x = y / 1000.0;
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout.precision(3);
		cout << x << endl;
	}

	p = head;
	while (p != NULL) {
		node* q = p->next;
		delete p;
		p = q;
	}

	cout << "------�������------";
	return 0;
}