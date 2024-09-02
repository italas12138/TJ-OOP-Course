//����Ԫ�������������+
#include<iostream>
#include<iomanip> //������setw
using namespace std;
class Array {
private:
	int matrix[2][3];
public:
	void readFromKeyboard();
	friend Array operator+(const Array&, const Array&);
	void display();
};
void Array::readFromKeyboard() {
	for (int i = 0;i < 2;++i)
		for (int j = 0;j < 3;++j)
			cin >> matrix[i][j];
}
void Array::display() {
	for (int i = 0;i < 2;++i) {
		for (int j = 0;j < 3;++j)
			cout << setw(7) << matrix[i][j];
		cout << endl;
	}
}
Array operator + (const Array & a, const Array & b) { //operator������or��
	Array c;
	for (int i = 0;i < 2;++i)
		for (int j = 0;j < 3;++j)
			c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
	return c;
}
int main() {
	Array a, b, c;

	cout << "���������a:" << endl;
	a.readFromKeyboard();
	cout << "����aΪ:" << endl;
	a.display();

	cout << "���������b:" << endl;
	b.readFromKeyboard();
	cout << "����bΪ:" << endl;
	b.display();

	c = a + b;
	cout << "����c = a + bΪ:" << endl;
	c.display();

	return 0;
}