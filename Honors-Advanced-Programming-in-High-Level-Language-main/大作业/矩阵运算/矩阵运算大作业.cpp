#include<iostream>
#include<conio.h>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const int N = 300;
int len1, wid1, len2, wid2;
int m1[N][N], m2[N][N], m3[N][N];

void wait_for_enter(){
	cout << endl << "���س�������";
	while (_getch() != '\r');
	cout << endl << endl;
	return;
}

void menu() {

	const int width = 15;

	for (int i = 1;i <= width*4-4;i++)cout << '*';
	cout << endl;

	cout << " *";
	for (int i = 1;i <= width - 7;i++)cout << ' ';
	cout << std::left << setw(width) << "1 ����ӷ�";
	cout << std::left << setw(width) << "2 ��������";
	cout << std::left << setw(width) << "3 ����ת��";
	cout << '*' << endl;

	cout << " *";
	for (int i = 1;i <= width - 7;i++)cout << ' ';
	cout << std::left << setw(width) << "4 ����˷�";
	cout << std::left << setw(width) << "5 Hadamard�˻�";
	cout << std::left << setw(width) << "6 ������";
	cout << '*' << endl;

	cout << " *";
	for (int i = 1;i <= width - 7;i++)cout << ' ';
	cout << std::left << setw(width) << "7 ���Ӧ��";
	cout << std::left << setw(width) << "8 OTSU�㷨";
	cout << std::left << setw(width) << "0 �˳�ϵͳ";
	cout << '*' << endl;

	for (int i = 1;i <= width*4-4;i++)cout << '*';
	cout << endl << "ѡ��˵���<0~8>:" << endl;
}

void matri_input() {
	cout << "����������������������" << endl;
	cin >> len1 >> wid1;
	cout << "���������" << endl;
	for (int i = 1;i <= len1;i++)
		for (int j = 1;j <= wid1;j++)
			cin >> m1[i][j];
}
void matri1_input() {
	cout << "�������һ�������������������" << endl;
	cin >> len1 >> wid1;
	cout << "�������һ������" << endl;
	for (int i = 1;i <= len1;i++)
		for (int j = 1;j <= wid1;j++)
			cin >> m1[i][j];
}
void matri2_input() {
	cout << "������ڶ������������������" << endl;
	cin >> len2 >> wid2;
	cout << "������ڶ�������" << endl;
	for (int i = 1;i <= len2;i++)
		for (int j = 1;j <= wid2;j++)
			cin >> m2[i][j];
}

void matri_output(int start, int len, int wid) { //����𰸾���

	int Width = 1; //��ȡ�������ʱ ���ʵ� ÿһ��������ռ���
	for (int i = start;i <= len;i++)
		for (int j = start;j <= wid;j++)
			while ((m3[i][j] / (int)pow(10, Width)) != 0)Width++;
	Width += 2;

	cout << endl << "������Ϊ��" << endl << endl;

	for (int i = start;i <= len;i++) {
		for (int j = start;j <= wid;j++) 
			cout << setw(Width) << m3[i][j];
		cout << endl;
	}

	wait_for_enter();

	return;
}

void matriplus() { //1������ӷ�

	matri1_input(); //������������
	matri2_input();

	if (len1 != len2 || wid1 != wid2) { //�����벻�Ϸ�
		cout << endl << "�������ֻ��ͬ�;���ļӷ�����������" << endl;
		cout << "������ѡ��˵���" << endl;
		wait_for_enter();
		return;
	}

	for (int i = 1;i <= len1;i++) 
		for (int j = 1;j <= wid1;j++) 
			m3[i][j] = m1[i][j] + m2[i][j];

	matri_output(1, len1, wid1);

	return;
}

void nummulti() { //2����������

	matri_input(); //�������

	int num; //��������
	cout << "�������������ϵ�����" << endl;
	cin >> num;

	for (int i = 1;i <= len1;i++) 
		for (int j = 1;j <= wid1;j++) 
			m3[i][j] = m1[i][j] * num;

	matri_output(1, len1, wid1);

	return;
}

void matritrans() { //3������ת��

	matri_input();

	for (int i = 1;i <= wid1;i++) 
		for (int j = 1;j <= len1;j++) 
			m3[i][j] = m1[j][i];

	matri_output(1, wid1, len1);

	return;
}
void matrimulti() { //4������˷�

	matri1_input();
	matri2_input();

	if (len2 != wid1) {
		cout << endl << "������󣬵�һ�������������ڶ��������������������������" << endl;
		cout << "������ѡ��˵���" << endl;
		wait_for_enter();
		return;
	}

	for (int i = 1;i <= len1;i++) 
		for (int j = 1;j <= wid2;j++) 
			for (int k = 1;k <= len2;k++)
				m3[i][j] += m1[i][k] * m2[k][j];

	matri_output(1, len1, wid2);

	return;
}

void hadamulti() { //5��Hadamard�˻�

	matri1_input();
	matri2_input();

	if (len1 != len2 || wid1 != wid2) {
		cout << endl << "�������ֻ��ͬ�;����Hadamard�˻���������" << endl;
		cout << "������ѡ��˵���" << endl;
		wait_for_enter();
		return;
	}

	for (int i = 1;i <= len1;i++) 
		for (int j = 1;j <= wid1;j++) 
			m3[i][j] = m1[i][j] * m2[i][j];

	matri_output(1, len1, wid1);

	return;
}

void conv() { //6��������

	matri1_input();
	matri2_input();

	len1++, wid1++; //����padding(�)=1;

	if (len2 != 3 || wid2 != 3) {
		cout << endl << "�������������3*3��kernel����" << endl;
		cout << "������ѡ��˵���" << endl;
		wait_for_enter();
		return;
	}

	for (int i = 0;i <= len1 - 2;i++)//ö�پ��������������
		for (int j = 0;j <= wid1 - 2;j++) {
			for (int lk = 0;lk < 3;lk++)//����������ֵ
				for (int rk = 0;rk < 3;rk++)
					m3[i][j] += m1[i + lk][j + rk] * m2[lk + 1][rk + 1];
		}

	matri_output(0, len1 - 2, wid1 - 2);

	return;
}

Mat demo_conv(Mat m, int B[3][3]) {

	cvtColor(m, m, CV_BGR2GRAY); //��������ͼ��תΪ�Ҷ�ͼ
	len1 = m.rows, wid1 = m.cols;//�õ�������ͼ�ε�����������

	for (int i = 0;i < len1;i++) //��Matת���ɶ�ά�����Խ�������
		for (int j = 0;j < wid1;j++) {
			m1[i][j] = m.at<uchar>(i, j);
		}

	int sum=0; //�������˵��ܺ�sum
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 3;j++)
			sum += B[i][j];

	memset(m3, 0, sizeof(m3)); //���ڶ�ε��ô˺�������Ҫ��ʼ��m3���𰸾���

	//��ʼ��������
	for (int i = 0;i < len1 - 2;i++) { //ö�پ���𰸾��������
		for (int j = 0;j < wid1 - 2;j++) {

			for (int lk = 0;lk < 3;lk++) //����������ֵ
				for (int rk = 0;rk < 3;rk++)
					m3[i][j] += m1[i + lk][j + rk] * B[lk][rk];

			if (sum)m3[i][j] /= sum;

			if (m3[i][j] < 0)m3[i][j] = 0; //ע�⵽�Ҷ�ֵ��ȡֵ��Χ��0~255������
			if (m3[i][j] > 255)m3[i][j] = 255;
		
		}
	}

	for (int i = 0;i < len1;i++) //�����������Ƹ�Mat���͵�m������
		for (int j = 0;j < wid1;j++) {
			m.at<uchar>(i,j) = m3[i][j];
		}

	return m;
}

void demo() { //7�����Ӧ��

	Mat image = imread("demolena.jpg"); //��ȡlenaԭͼ 
	
	int B1[3][3] = { {1,1,1},{1,1,1},{1,1,1} }; //����������
	int B2[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	int B3[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int B4[3][3] = { {-1,-1,-1},{-1,9,-1},{-1,-1,-1} };
	int B5[3][3] = { {-1,-1,0},{-1,0,1},{0,1,1} };
	int B6[3][3] = { {1,2,1},{2,4,2},{1,2,1} };

	Mat image1=demo_conv(image, B1); //���ú����õ���ͬ���������lena
	Mat image2 = demo_conv(image, B2);
	Mat image3 = demo_conv(image, B3);
	Mat image4 = demo_conv(image, B4);
	Mat image5 = demo_conv(image, B5);
	Mat image6 = demo_conv(image, B6);

	imshow("original_Image", image);//��ʾ���е�lena��
	imshow("B1���Image", image1); 
	imshow("B2���Image", image2);
	imshow("B3���Image", image3);
	imshow("B4���Image", image4);
	imshow("B5���Image", image5);
	imshow("B6���Image", image6);
	waitKey(0);
	
	wait_for_enter();

	return;
}

void otsu() { //8:OTSU�㷨
	Mat origin_image = imread("demolena.jpg"); //��ȡlenaԭͼ 
	Mat result_image = origin_image;

	cvtColor(origin_image, origin_image, CV_BGR2GRAY); //��������ͼ��תΪ�Ҷ�ͼ
	cvtColor(result_image, result_image, CV_BGR2GRAY); 

	len1 = origin_image.rows, wid1 = origin_image.cols;//�õ�������ͼ�ε�����������

	int maxG = 0, ansT;

	for (int T = 0;T <= 255;T++) { //��otsu�㷨�ҵ���ֵ��

		int N0 = 0, N1 = 0;
		double w0=0, w1=0, u0=0, u1=0;

		for (int i = 0;i < len1;i++)
			for (int j = 0;j < wid1;j++) {
				int val = origin_image.at<uchar>(i, j);
				if (val < T)
					N0++, u0 += (double)val;
				else 
					N1++, u1 += (double)val;
			}

		w0 = 1.0 * N0 / (N0 + N1), w1 = 1.0 * N1 / (N0 + N1);
		u0 /= N0, u1 /= N1;

		int G = w0 * w1 * pow(u0 - u1, 2);
		if (G > maxG)maxG = G, ansT = T;
	}

	for (int i = 0;i < len1;i++)
		for (int j = 0;j < wid1;j++){
			int val = origin_image.at<uchar>(i, j);
			if(val>ansT) result_image.at<uchar>(i, j)=255;
			else result_image.at<uchar>(i, j)=0;
		}

	imshow("Origin", origin_image);
	imshow("Result", result_image);
	waitKey(0);

	wait_for_enter();

	return;
}

int main() {

	wait_for_enter();

	while (1) {

		system("cls");//��������ʾ�˵�
		menu();

		char choice = _getch();//����ѡ��Ĳ˵���

		if (choice == '0') {//�˳�ϵͳ
			cout << endl << "ȷ���˳����˳�������y������������n" << endl;
			char ch;
			cin >> ch;
			if (ch == 'y')break;
			else continue;
		}

		memset(m1, 0, sizeof(m1));//��ʼ���������飡
		memset(m2, 0, sizeof(m2));
		memset(m3, 0, sizeof(m3));

		switch (choice) {
		case'1':
			matriplus(); //1������ӷ�
			break;
		case'2':
			nummulti(); //2����������
			break;
		case'3':
			matritrans(); //3������ת��
			break;
		case'4':
			matrimulti(); //4������˷�
			break;
		case'5':
			hadamulti(); //5��Hadamard�˻�
			break;
		case'6':
			conv(); //6��������
			break;
		case'7':
			demo(); //7�����Ӧ��
			break;
		case'8':
			otsu();
			break;
		default:
			cout << endl << "�����������������" << endl;
			wait_for_enter();
		}
	}

	return 0;
}