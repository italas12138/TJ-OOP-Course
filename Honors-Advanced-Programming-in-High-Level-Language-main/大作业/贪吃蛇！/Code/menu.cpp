#define _CRT_SECURE_NO_WARNINGS
#include"classes.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<fstream>

using namespace std;

int menu(); //��ҳ��
int menu1(); //���롾��ʼ��Ϸ����ѡ����Ϸģʽ
void menu2(); //���롾��ʷ��¼�������ʾ
int button_judge(int x, int y, int r[3][4]);

int button_judge(int x, int y, int r[3][4])
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3]) return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3]) return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3]) return 3;
	return 0;
}

int menu() {
	initgraph(1200, 800);
	for (int i = 0;i < 256;i += 5)
	{
		setbkcolor(RGB(i, i, i));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
		cleardevice();//������ȡ���ڱ���ɫ��
		Sleep(15);//��ʱ15ms
	}
	IMAGE title;
	loadimage(&title, _T("./image./1.jpg"), 700, 300);
	putimage(600 - 350, 0, &title);

	IMAGE pic;
	loadimage(&pic, _T("./image./dtt.jpg"), 140*1.2, 40*1.2);
	putimage(1000, 745, &pic);

	int butt[3][4] = { {380,280,820,430},{380,440,820,590},{380,600,820,750} };
	int r[3][4];
	for (int i = 0;i < 3;i++) {
		r[i][0] = butt[i][0] + 45;
		r[i][1] = butt[i][1] + 20;
		r[i][2] = butt[i][2] - 45;
		r[i][3] = butt[i][3] - 20;
	}
	RECT R1 = { butt[0][0],butt[0][1],butt[0][2],butt[0][3] }; //����ָ�� 
	RECT R2 = { butt[1][0],butt[1][1],butt[1][2],butt[1][3] };
	RECT R3 = { butt[2][0],butt[2][1],butt[2][2],butt[2][3] };
	LOGFONT f; //������ʽָ��
	gettextstyle(&f); //��ȡ������ʽ ����û̫��
	_tcscpy(f.lfFaceName, _T("����")); //��������Ϊ����
	//_tcscpy(f.lfFaceName, _T("bold"));
	f.lfHeight = 40, f.lfWeight = 133; //���������С
	f.lfQuality = ANTIALIASED_QUALITY; //�������Ч��Ϊ�����
	settextstyle(&f); //����������ʽ
	settextcolor(BLACK);
	drawtext(_T("��ʼ��Ϸ"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("������Ϸ"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("��ʷ��¼"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	MOUSEMSG m; //���ָ��
	int event = 0, jud = 0;
	while (1) {
		m = GetMouseMsg(); //��ȡһ�������Ϣ
		switch (m.uMsg) {
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//����ɫ
			setlinestyle(PS_SOLID, 3);
			setfillcolor(WHITE);
			jud = button_judge(m.x, m.y, r);
			if (jud != 0) {
				if (event != jud) {
					event = jud;
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);
				}
			}
			else if (event != 0) {//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
				event = 0;
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (int i = 0;i <= 10;i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}
			jud = button_judge(m.x, m.y, r);
			if (jud == 1) {
				cleardevice();
				return menu1();
			}
			else if (jud == 2) return 4;
			else if (jud == 3) {
				cleardevice();
				menu2(); 
				return 0;
			}
			break;
			FlushMouseMsgBuffer();//��������Ϣ������
		}
	}
	setrop2(R2_COPYPEN);
}
int menu1() {
	int butt[3][4] = { {0,0,400,250},{0,250,400,500},{0,500,400,750} };
	int r[3][4];
	for (int i = 0;i < 3;i++) {
		r[i][0] = butt[i][0] + 65;
		r[i][1] = butt[i][1] + 60;
		r[i][2] = butt[i][2] - 65;
		r[i][3] = butt[i][3] - 60;
	}
	RECT R1 = { butt[0][0],butt[0][1],butt[0][2],butt[0][3] }; //����ָ�� 
	RECT R2 = { butt[1][0],butt[1][1],butt[1][2],butt[1][3] };
	RECT R3 = { butt[2][0],butt[2][1],butt[2][2],butt[2][3] };
	LOGFONT f; //������ʽָ��
	gettextstyle(&f); //��ȡ������ʽ ����û̫��
	//wcscpy_s(f.lfFaceName, _T("����"));
	_tcscpy(f.lfFaceName, _T("����")); //��������Ϊ����
	//_tcscpy(f.lfFaceName, _T("bold"));
	f.lfHeight = 40, f.lfWeight = 133; //���������С
	f.lfQuality = ANTIALIASED_QUALITY; //�������Ч��Ϊ�����
	settextstyle(&f); //����������ʽ
	settextcolor(BLACK);
	drawtext(_T("���Ű�"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("���װ�"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("�߼���"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	IMAGE pic, pic1;
	loadimage(&pic, _T("./image./2.jpg"), 800, 250);
	putimage(400 - 32, 0, &pic);

	loadimage(&pic, _T("./image./3.jpg"), 800, 250);
	putimage(400 - 32, 245, &pic);

	loadimage(&pic, _T("./image./4.jpg"), 800, 250);
	putimage(400 - 32, 495, &pic);

	//loadimage(&pic1, _T("./image./Esc.jpg"), 700*0.4, 200*0.4);
	//putimage(900, 750, &pic1);



	MOUSEMSG m; //���ָ��
	int event = 0, jud = 0;
	while (1) {
		m = GetMouseMsg(); //��ȡһ�������Ϣ
		switch (m.uMsg) {
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//����ɫ
			setlinestyle(PS_SOLID, 3);
			setfillcolor(WHITE);
			jud = button_judge(m.x, m.y, r);
			if (jud != 0) {
				if (event != jud) {
					event = jud;
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);
				}
			}
			else if (event != 0) {//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
				event = 0;
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (int i = 0;i <= 10;i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}
			jud = button_judge(m.x, m.y, r);
			if (jud != 0) return jud;
			break;
			FlushMouseMsgBuffer();//��������Ϣ������
		}
	}
}
void menu2() {
	IMAGE pic1;
	loadimage(&pic1, _T("./image./Esc.jpg"), 700*0.4, 200*0.4);
	putimage(900, 750, &pic1);

	ifstream fl("./file./game_record.txt", ios::app);
	int ry[2] = { 0,50 }, rx[2] = { 0,100 };
	while (!fl.eof()) {
		int type, score;
		if (!(fl >> type >> score))break;
		LOGFONT f; //������ʽָ��
		gettextstyle(&f); //��ȡ������ʽ ����û̫��
		_tcscpy(f.lfFaceName, _T("����")); //��������Ϊ����
		//_tcscpy(f.lfFaceName, _T("bold"));
		//f.lfHeight = 40, f.lfWeight = 133; //���������С
		//f.lfQuality = ANTIALIASED_QUALITY; //�������Ч��Ϊ�����
		settextstyle(&f); //����������ʽ
		settextcolor(BLACK);
		char str[15] = "", number[15] = { '0','1','2','3','4','5','6','7','8','9','\0' };

		int cur = 9, tmp = score;
		while (cur != 0 && (int)(score / pow(10, cur)) == 0)cur--;
		for (int i = cur;i >= 0;i--) {
			strncat(str, number + (int)(tmp / (int)pow(10, i)), 1);
			tmp %= (int)pow(10, i);
		}

		int num = MultiByteToWideChar(0, 0, str, -1, NULL, 0);
		wchar_t* wide = new wchar_t[num];
		MultiByteToWideChar(0, 0, str, -1, wide, num);
		/*num ��ó��ֽ�����Ŀռ�
		MultiByteToWideChar()��ʾ��s�е��ַ����ݵ�psָ����ڴ��С�-1��ʾ������s�е�'\0'����num��ʾ���ݵ��ֽڸ�����*/

		RECT R1 = { rx[0], ry[0], rx[1], ry[1] };
		RECT R2 = { rx[0] + 100, ry[0], rx[1] + 200, ry[1] };
		RECT R3 = { rx[0] + 300, ry[0], rx[1] + 300, ry[1] };
		RECT R4 = { rx[0] + 400, ry[0], rx[1] + 400, ry[1] };
		drawtext(_T("�汾��"), &R1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (type == 1)drawtext(_T("���Ű�"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (type == 2)drawtext(_T("���װ�"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (type == 3)drawtext(_T("�߼���"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("�÷֣�"), &R3, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext((LPCTSTR)wide, &R4, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		ry[0] += 52  , ry[1] += 52;
	}

	while (Keyboard_monitor(0, 0) != 27); //��Esc�˳�ҳ��
}
