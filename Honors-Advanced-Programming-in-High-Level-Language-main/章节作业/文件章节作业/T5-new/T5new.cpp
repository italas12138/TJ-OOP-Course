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
    //time_t start, end;
    //start = clock();

    if (argc != 3) {
        cerr << "������ļ�����ǰ��λ����" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "�޷��������ļ�" << endl;
        return -1;
    }
    
    long long ans = 0;

    while (!in.eof()) {
        string cur;
        getline(in, cur);
        if (!valid(cur))
            continue;
        if (argv[2] != cur.substr(0, 3))
            continue;
        stringstream tmp(cur); //����stringstream��stringתΪlong long
        long long cur_tele;
        tmp >> cur_tele;
        if (ans < cur_tele)
            ans = cur_tele;
    }
    in.close();
    cout << ans << endl;

    //end = clock();
    //cout << "��������ʱ�䣺" << (end - start) * 1.0 / CLOCKS_PER_SEC << "s\n";
    return 0;
}