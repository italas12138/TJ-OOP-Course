#include<iostream>
#include<fstream>
#include<cstring>
#include<queue>
#include<time.h>
#include<bitset>
#include<unordered_map>

using namespace std;

int node_num; //Huffman tree�Ľ������

struct Huffman_node { //����Huffman���
	char c = '\0';
	int freq = 0, num = 0;
	Huffman_node* left_child = NULL, * right_child = NULL;
	/*friend bool operator <(Huffman_node x, Huffman_node y) {    //����ýṹ��Ĵ�С�Ƚ�
		return x.freq < y.freq;	  //�������ڴ�������Ҫ�Ƚϵ���ָ��ýṹ���ָ�룬���Բ��������ַ�ʽ
	}*/
}*root;

struct cmp { 
	bool operator() (const Huffman_node* x, const Huffman_node* y) {
		return x->freq > y->freq; 
	}
};

unordered_map<char, int>cnt; //cnt[c]: �ַ�c�ڴ�ѹ���ļ��г��ֵĴ���
unordered_map<char, string>ans; //ans[c]: �ַ�c��Ӧ��01��
priority_queue<Huffman_node*, vector<Huffman_node*>, cmp>que; //����Huffmanʱ����ĶԽ����������ȶ���

long getFileSize(const char* strFileName) //�õ��ļ���С
{
	std::ifstream in(strFileName, ios::binary);
	if (!in.is_open()) return 0;

	in.seekg(0, std::ios_base::end);
	std::streampos sp = in.tellg();
	return sp;
}

bool is_leaf(Huffman_node* t) {
	return (t->left_child == NULL) && (t->right_child == NULL);
}

void output_tree(Huffman_node* t, char* fn) { //���Huffman tree��fn�ļ���
	ofstream fl;
	if (t == root) {
		fl.open(fn,ios::binary); //�����ƴ��ļ�
		if (!fl) { //����ļ��Ƿ�ɹ���
			cout << "Error opening file" << endl;
			exit(1);
		}

		fl.write((char*)&node_num, sizeof(int));
		fl.close();
	}

	if (t->left_child != NULL)
		output_tree(t->left_child, fn);
	if (t->right_child != NULL)
		output_tree(t->right_child, fn);

	//�ȱ��������������֤���һ�����ʱ�����������ӽ�㶼����������ڽ�ѹ��ʱ�ع�Huffman tree
	fl.open(fn, ios::binary | ios::app);
	if (!fl) {
		cout << "Error opening file" << endl;
		exit(1);
	}

	if (is_leaf(t)) { //Ҷ��㣺�������һ������Ҷ���� 1 , ������������Ҷ����Ӧ�ַ�
		bool leaf = 1;
		fl.write((char*)&leaf, sizeof(bool));
		fl.write((char*)&t->num, sizeof(int));
		fl.write((char*)&t->c, sizeof(char));
	}
	else { //��Ҷ��㣺�������һ����ʾ��Ҷ�ڵ�� 0, �������������������ӽ���ţ����ӽ�㼴��0��ʾ��
		bool leaf = 0; 
		int child = 0;

		fl.write((char*)&leaf, sizeof(bool));
		fl.write((char*)&t->num, sizeof(int));
		if (t->left_child == NULL)
			fl.write((char*)&child, sizeof(int));
		else
			fl.write((char*)&t->left_child->num, sizeof(int));
		if (t->right_child == NULL)
			fl.write((char*)&child, sizeof(int));
		else
			fl.write((char*)&t->right_child->num, sizeof(int));
	}

	fl.close(); //��ʱ�ر��ļ���
}

void traverse_tree(Huffman_node* t) { //����Huffman tree���ҵ�ÿ���ַ���Ҷ��㣩��Ӧ��01������� map ans��
	static string str;
	int len = str.length();
	if (t->left_child != NULL) {
		str = str + "0";
		traverse_tree(t->left_child);
		str.erase(len);
	}
	if (t->right_child != NULL) {
		str = str + "1";
		traverse_tree(t->right_child);
		str.erase(len);
	}
	if (is_leaf(t)) ans[t->c] = str;
}

void delete_tree(Huffman_node * t) {
	if (t->left_child != NULL)
		delete_tree(t->left_child);
	if (t->right_child != NULL)
		delete_tree(t->right_child);
	delete t;
}

void ZIP(char** argv) {
	ifstream infile(argv[1], ios::binary);
	if (!infile) { //����ļ��Ƿ�ɹ���
		cerr << "Error opening file" << endl;
		exit(1);
	}

	while (!infile.eof()) { //ͳ�������ַ����ֵĴ���
		char c;
		//infile >> c;  ע�⵽���ֶ������Կո��뻻�У�
		c = infile.get();
		if (infile.eof())break; //�˾�ı�Ҫ����eof()�������й� 
		if (cnt.find(c) == cnt.end()) cnt[c] = 1;
		else cnt[c]++;
	}

	infile.close();

	unordered_map<char, int>::iterator it; //����һ��unordered map<char,int>���͵ĵ������������� cnt
	for (it = cnt.begin();it != cnt.end();it++) { //���������ַ���Huffman��㲢�Ҽ������ȶ���
		char c = it->first;
		int freq = it->second;
		Huffman_node* nd = new Huffman_node;
		nd->c = c;
		nd->freq = freq;
		nd->num = ++node_num;
		que.push(nd);
	}

	while (que.size() > 1) {
		Huffman_node* n1, * n2; //ȡ�����ȶ��ж��׵�����Ԫ��
		n1 = que.top();
		que.pop();
		n2 = que.top();
		que.pop();

		Huffman_node* nd = new Huffman_node; //�����½�㣺n1 n2�ĸ����
		nd->freq = n1->freq + n2->freq;
		nd->left_child = n1;
		nd->right_child = n2;
		nd->num = ++node_num;

		que.push(nd);
	}

	root = que.top(); //���ʣ�µĽ���Ǹ����

	output_tree(root, argv[2]); //���Huffman tree
	traverse_tree(root); ////����Huffman tree���ҵ�ÿ���ַ���Ҷ��㣩��Ӧ��01������� map ans��

	long long tot_ansc = 0, left_num=0; //left_ansc: ���unsigned char ���͵�����-1 ; left_num:ԭ�ļ���Ӧ��01������8�õ�������
	infile.open(argv[1], ios::binary);
	ofstream outfile(argv[2], ios::binary | ios::app);

	while (!infile.eof()) {
		char c;
		//infile >> c;  ע�⵽���ֶ������Կո��뻻�У�
		c = infile.get();
		left_num += ans[c].length();
		tot_ansc += left_num / 8;
		left_num %= 8;
	}
	outfile.write((char*)&tot_ansc, sizeof(long long));
	outfile.write((char*)&left_num, sizeof(long long));
	infile.close();

	infile.open(argv[1], ios::binary);
	if (!infile) {
		cerr << "Can not open the input file!" << endl; // ���������Ϣ���˳�
		return;
	}
	string ans_str;
	while (!infile.eof()) {
		char c;
		c = infile.get();
		ans_str += ans[c];
		while (ans_str.length() >= 8) {
			unsigned char ansc = 0;
			for (int i = 0;i < 8;i++)
				ansc = ansc << 1 | (ans_str[i] - '0');
			outfile.write((char*)&ansc, sizeof(unsigned char));
			ans_str.erase(0, 8);
		}
	}
	if (ans_str.length()) {
		unsigned char ansc = 0;
		for (int i = 0;i < ans_str.length();i++)
			ansc = ansc << 1 | (ans_str[i] - '0');
		outfile.write((char*)&ansc, sizeof(unsigned char));
	}

	infile.close();
	outfile.close();
	delete_tree(root); //����̬������ڴ棡

	cerr << "�ļ�ѹ���ʣ�" << 1.0 * getFileSize(argv[2]) / getFileSize(argv[1]) * 100 << "%" << endl;
}

unordered_map<int, Huffman_node*>mp2; // mp2[num]: num��Ӧ��Huffman���

void UNZIP(char** argv) {
	ifstream infile(argv[1], ios::binary); // �Զ����Ʒ�ʽ���ļ�
	ofstream outfile(argv[2], ios::binary);
	if ((!infile) || (!outfile)) {
		cerr << "Can not open the input file!" << endl; // ���������Ϣ���˳�
		return;
	}

	infile.read((char*)&node_num, sizeof(int));  //��ʼ�ع�Huffman tree
	while (node_num--) {
		Huffman_node* nd = new Huffman_node;
		if (node_num == 0) { //���һ���Ǹ���㣡
			root = nd;
		}
		bool leaf;
		infile.read((char*)&leaf, sizeof(bool));
		infile.read((char*)&nd->num, sizeof(int));
		mp2[nd->num] = nd;
		if (leaf) {
			infile.read((char*)&nd->c, sizeof(char));
		}
		else {
			int n1 = 0, n2 = 0;
			infile.read((char*)&n1, sizeof(int));
			infile.read((char*)&n2, sizeof(int));
			if (n1 != 0)nd->left_child = mp2[n1];
			if (n2 != 0)nd->right_child = mp2[n2];
		}
	}

	long long tot_ansc, left_num; //��ʼ��ȡԭ�ı���Ӧ��ѹ������
	infile.read((char*)&tot_ansc, sizeof(long long));
	infile.read((char*)&left_num, sizeof(long long));

	Huffman_node* cur = root;
	while (tot_ansc--) {
		unsigned char c;
		infile.read((char*)&c, sizeof(unsigned char));
		bitset<8> bit(c);

		for (int i = 7;i >= 0;i--) {//����
			if (bit[i] == 0) //ע����0����'0'��
				cur = cur->left_child;
			else
				cur = cur->right_child;

			if (is_leaf(cur)) {
				outfile << cur->c;
				cur = root;
			}
		}

	}
	if (left_num != 0) { //���һ����������
		unsigned char c;
		infile.read((char*)&c, sizeof(unsigned char));
		bitset<8> bit(c);
		for (int i = 7 - left_num;i >= 0;i--) {
			if (bit[i] == 0)
				cur = cur->left_child;
			else 
				cur = cur->right_child;
			if (is_leaf(cur)) {
				outfile << cur->c;
				cur = root;
			}
		}

	}

	infile.close();
	outfile.close();
	delete_tree(root);//����̬������ڴ棡
}

int main(int argc, char** argv) {
	clock_t starttime, endtime;
	starttime = clock();

	if (argc != 4) {
		cerr << "Please make sure the number of parameters is correct." << endl;
		return -1;
	}
	if (strcmp(argv[3], "zip") == 0) {
		ZIP(argv);
	}
	else if (strcmp(argv[3], "unzip") == 0) {
		UNZIP(argv);
	}
	else {
		cerr << "Unknown parameter!\nCommand list:\nzip/unzip" << endl;
		return -1;
	}

	endtime = clock();
	cerr << "��������ʱ�䣺" << 1.00 * (endtime - starttime) / CLOCKS_PER_SEC << "��" << endl;
	return 0;
}
/*
g++ �ļ�ѹ��.cpp -o �ļ�ѹ��
�ļ�ѹ��.exe ser.log ser_compressed.log zip
�ļ�ѹ��.exe ser_compressed.log ser_decompressed.log unzip
*/