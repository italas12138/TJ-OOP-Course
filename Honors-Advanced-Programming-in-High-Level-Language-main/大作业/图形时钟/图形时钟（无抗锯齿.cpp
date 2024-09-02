#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <time.h>  
using namespace std;
const double Pi = 3.1415926;
struct tm t;
time_t now;
struct coordinate {
	int x, y;
};
void drawtxt(char* str, RECT r) {
	drawtext(*str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void init() {
	//���û�����ɫ��
	initgraph(640, 480);
	setbkcolor(RGB(253, 245, 230));
	cleardevice();

	//�����̣�
	setfillcolor(RGB(255, 235, 205));
	fillcircle(320, 240, 150);

	//��ʱ��ָ���м�СԲ��
	setfillcolor(RGB(235, 141, 76));
	fillcircle(320, 240, 5);

	//д�����ϵ����֣�
	settextcolor(RGB(235, 112, 76));
	drawtxt((char*)"1", { 310,95,320,105 });
	drawtxt((char*)"2", { 320,95,330,105 });
	drawtxt((char*)"6", { 310,385,330,375 });
	drawtxt((char*)"9", { 175,230,185,250 });
	drawtxt((char*)"3", { 465,230,455,250 });

	//���̶ȣ�
	setfillcolor(RGB(235, 112, 76));
	for (int i = 1;i <= 12;i++) {
		if (i % 3 == 0)continue;
		double x = 320 + 140 * sin(i / 6.0 * Pi);
		double y = 240 - 140 * cos(i / 6.0 * Pi);
		fillcircle((int)x, (int)y, 3);
	}
	for (int i = 1;i <= 60;i++) {
		if (i % 5 == 0)continue;
		double x = 320 + 141 * sin(i / 30.0 * Pi);
		double y = 240 - 141 * cos(i / 30.0 * Pi);
		fillcircle((int)x, (int)y, 2.2);
	}
}
int squdis(coordinate n1, coordinate n2) {
	return (n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y);
}

COLORREF mixcolor(COLORREF col1, COLORREF col2, double alpha) { //�����ɫ!
	int R, G, B;
	R = GetRValue(col1) * (1 - alpha) + GetRValue(col2) * alpha;
	G = GetGValue(col1) * (1 - alpha) + GetGValue(col2) * alpha;
	B = GetBValue(col1) * (1 - alpha) + GetBValue(col2) * alpha;
	return RGB(R, G, B);
}

//SDF�����
void SDF_line(coordinate n1, coordinate n2, double width, COLORREF line_col, COLORREF back_col)
{
	const int range = 10;
	int minx = min(n1.x, n2.x), maxx = max(n1.x, n2.x);
	int miny = min(n1.y, n2.y), maxy = max(n1.y, n2.y);
	for (int i = minx - range;i <= maxx + range;i++)
		for (int j = miny - range;j <= maxy + range;j++) {
			coordinate n0 = { i,j };
			double h = 1.0 * ((n1.x - i) * (n1.x - n2.x) + (n1.y - j) * (n1.y - n2.y)) / (squdis(n1, n2));
			if (h < 0 || h>1) {
				double d1 = sqrt(squdis(n0, n1)), d2 = sqrt(squdis(n0, n2));
				h = min(d1, d2);
			}
			double d = sqrt(squdis(n0, n1) - h * h * (squdis(n1, n2))) - width;
			if (h < 0 || h>1)d += width;
			double alpha = 0.5 - d;
			back_col = getpixel(i, j);
			if (d < 0) putpixel(i, j, line_col);
			else if (alpha >= 0 && alpha <= 1)
				putpixel(i, j, mixcolor(back_col, line_col, alpha));
		}
}
void draw() {

	static int lastsec = -1, lastmin = -1;
	if (t.tm_sec == lastsec)return; //��ֹ����Ҫ�ĸ���ָ�뵼����˸
	lastsec = t.tm_sec;

	//����һЩ��̬����������һ��ʱ��ָ���λ��
	static struct coordinate sec = { 320,240 }, min = { 320,240 }, hour = { 320,240 };

	//������
	setcolor(RGB(255, 235, 205));
	setlinestyle(PS_SOLID, 2);
	line(320, 240, sec.x, sec.y);//������һ������
	sec.x = 320 + 120 * sin(t.tm_sec / 60.0 * 2 * Pi);
	sec.y = 240 - 120 * cos(t.tm_sec / 60.0 * 2 * Pi);

	setlinestyle(PS_SOLID, 2);
	setcolor(RGB(235, 112, 76));
	//SDF_line({ 320,240 }, sec, 0.8, RGB(235, 112, 76), RGB(255, 235, 205));
	line(320, 240, sec.x, sec.y);//��������

	setfillcolor(RGB(235, 141, 76));//������Ϊ��ȥ��������ɵ��м�Բȱʧ
	fillcircle(320, 240, 5);

	if (t.tm_min == lastmin) {//������벻�ø��£����ٻ�һ����һ��������ʱ�롾��Ϊ�˷�ֹ���ȥ��������������ָ�벿��ȱʧ��
		setcolor(RGB(235, 112, 76));
		setlinestyle(PS_SOLID, 3);
		line(320, 240, min.x, min.y);

		setlinestyle(PS_SOLID, 4);
		setcolor(RGB(235, 112, 76));
		line(320, 240, hour.x, hour.y);
		return;
	}
	lastmin = t.tm_min;

	//���·��룺
	setcolor(RGB(255, 235, 205));
	setlinestyle(PS_SOLID, 3);
	line(320, 240, min.x, min.y);//��ȥ�ɷ���

	min.x = 320 + 100 * sin(1.0 * t.tm_min / 60.0 * 2 * Pi);
	min.y = 240 - 100 * cos(1.0 * t.tm_min / 60.0 * 2 * Pi);

	setlinestyle(PS_SOLID, 3);
	setcolor(RGB(235, 112, 76));
	line(320, 240, min.x, min.y);//���·���

	//��ʱ�루�����¾ɣ����˴��Ѿ���֤һ���Ӹ���һ�Σ���������˸����
	setcolor(RGB(255, 235, 205));
	setlinestyle(PS_SOLID, 4);
	line(320, 240, hour.x, hour.y);//��ȥ��ʱ��

	hour.x = 320 + 70 * sin(t.tm_hour % 12 / 12.0 * 2 * Pi + t.tm_min / 360.0 * Pi);
	hour.y = 240 - 70 * cos(t.tm_hour % 12 / 12.0 * 2 * Pi + t.tm_min / 360.0 * Pi);

	setlinestyle(PS_SOLID, 4);
	setcolor(RGB(235, 112, 76));
	line(320, 240, hour.x, hour.y);//����ʱ��

}
int main()
{
	//��ʼ������
	init();

	while (!_kbhit()) {
		//��ȡ��ǰʱ��
		time(&now);
		localtime_s(&t, &now);
		//���ݵ�ǰʱ�仭��ָ��
		draw();
	}
	closegraph();
	return 0;
}