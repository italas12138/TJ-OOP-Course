#include<iostream>
using namespace std;
istream& f(istream& in) {
    auto in_state = in.rdstate(); // �������뺯����״̬
    /* �������������ܾ��������� */
    while (!in.eof()) {
        int x;
        if (in >> x) {
            if (x == -1 || in.eof())
                break;
            else {
                cout << "��˵��:" << x << " ";
            }
        }
        else {
            if (in.eof())
                break;
            if (!in.fail()) {
                cout << "I cannot go on\n";
                exit(1);
            }
            cout << "����Ƿ������������� ";
            in.clear();
            while (!isspace(in.get()))
                continue;
        }
    }
    in.setstate(in_state);        // ��λ��
    return in;
}
int main() {
    cout << "������һЩ��������-1��Ctrl+Z������" << endl;
    f(cin);
    cout << "------�������------";
    return 0;
}

/*
    ����Ϊ��1�ָ�λ��ʽ���ã�
    ����λ������˼Ӧ����ʹ���ָ���do something֮ǰ��״̬��
    ��do something֮ǰ��״̬��һ���� failbit=eofbit=badbit=0
*/