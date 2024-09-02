#include<iostream>
#include<streambuf>
#include<cstring>
#include<iterator>
#include<fstream>
#include<sstream>
#include<time.h>

using namespace std;

bool valid(string str) {
    if (str.length() != 11)
        return 0;
    if (str[0] != '1' || str[1] < '3' || str[1] >'9')
        return 0;
    for (int i = 2;i < str.length();i++)
        if (str[i] < '0' || str[i]>'9')
            return 0;
    return 1;
}
int main(int argc, char* argv[]) {
    time_t start, end;
    start = clock();

    if (argc != 3) {
        cerr << "������ļ�����ǰ��λ����" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "�޷��������ļ�" << endl;
        return -1;
    }
    string ans;
    while (!in.eof()) {
        string cur;
        getline(in, cur);
        if (!valid(cur))
            continue;
        if (argv[2] != cur.substr(0, 3))
            continue;
        if (ans < cur)
            ans = cur;
    }
    in.close();
    cout << ans << endl;

    end = clock();
    //cout << "��������ʱ�䣺" << (end - start) * 1.0 / CLOCKS_PER_SEC << "s\n";


    //���������ַ�����??????






    /* ͨ��argv[2]�������кϷ���Ϣ���������ƥ������ֵ */
    /* ��Ҫע��argv��Ϊ�ַ������ͣ��������Ҫ�Ըò�������ת�� */
    return 0;
}
/*
    �����д���򣬴ӵ绰���а��ж�����Ϣ����װ���� valid() ���м���ȡ������Ϣ�Ƿ�Ϊ�绰����
    ����ʹ���ַ���������
    ��Ҫ���Ǵ������룬�����㲻��Ҫ���������ʾ��������˵����Ϸ���Ϣ����
    ����Ϸ������ݽ�Ϊ 11λ(10���Ƴ���)���ͣ�ǰ��λ�ַ��Ϸ���Χ�� 13-19 (���Ϸ������� 13000000000~19999999999)��
    ʹ��longlong
*/
/* istreambuf_iterator<char> beg(fin),
      end; // ���������ļ�ָ�룬ָ��ʼ�ͽ������� char(һ�ֽ�) Ϊ����
  string content(beg, end); // ���ļ�ȫ������ string �ַ���
  fin.close(); // �������ļ���ر��ļ������һ����ϰ��*/