#include<iostream>
#include<fstream>

using namespace std;

int main() {
	//���ļ�foo.bar
	ifstream  infile("foo.bar", ios::binary); //�ö����Ʒ�ʽ�򿪣�
	if (!infile.is_open()) {
		cout << "can't open file foo.bar\n";
		return -1;
	}

	//��������
	int rows=0;
	while (!infile.eof()) {
		while (infile.get() != '\n' && !infile.eof())
			continue;
		rows++;
	}

	//�ҵ�����λ��
	infile.clear(); //һ��Ҫ��clear��seekg
	infile.seekg(0, ios_base::end);
	streampos endpos = infile.tellg();
	//cout << "endpos=" << endpos << endl;

	//�������
	ofstream outfile("foo.bar", ios::binary|ios::app);
	if (!outfile.is_open()) {
		cout << "can't open file foo.bar\n";
		return -1;
	}
	outfile << endl << rows;

	//�ٴα����������ÿһ�е�ƫ����
	infile.clear(); //һ��Ҫ��clear��seekg
	infile.seekg(0, ios_base::beg);
	while (rows != 0) {
		outfile << ' ' << infile.tellg();
		while (infile.get() != '\n' && infile.tellg() < endpos)
			continue;
		rows--;
	}
	outfile << ' ' << endpos + 1ll;

	//�ر��ļ�
	infile.close();
	outfile.close();

	return 0;
}
