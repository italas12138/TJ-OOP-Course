#include "PicReader.h"
#include <iostream>
#include <stdio.h>
#include<cmath>
#include<bitset>
#include<map>
#include<fstream>
#include<time.h>

using namespace std;

#define Pi 3.14159

//定义的8*8结构体块
struct compress_block {
	double R[8][8], G[8][8], B[8][8];
	double Y[8][8], Cb[8][8], Cr[8][8];
	struct compress_block* next_block;
};

//PEG算法提供了两张标准化系数矩阵，分别处理亮度数据和色差数据
//表1
const int Qy[8][8] = {
	16, 11, 10, 16, 24, 40, 51, 61,
	12, 12, 14, 19, 26, 58, 60, 55,
	14, 13, 16, 24, 40, 57, 69, 56,
	14, 17, 22, 29, 51, 87, 80, 62,
	18, 22, 37, 56, 68, 109, 103, 77,
	24, 35, 55, 64, 81, 104, 113, 92,
	49, 64, 78, 87, 103, 121, 120, 101,
	72, 92, 95, 98, 112, 100, 103, 99
};

//表2
const int Qc[8][8] = {
	17, 18, 24, 47, 99, 99, 99, 99,
	18, 21, 26, 66, 99, 99, 99, 99,
	24, 26, 56, 99, 99, 99, 99, 99,
	47, 66, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99
};

//ZIGZAG排序数组
const char ZIGZAG[64] = {
	0, 1, 5, 6, 14, 15, 27, 28,
	2, 4, 7, 13, 16, 26, 29, 42,
	3, 8, 12, 17, 25, 30, 41, 43,
	9, 11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54,
	20, 22, 33, 38, 46, 51, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61,
	35, 36, 48, 49, 57, 58, 62, 63
};

//DC，AC编码数组
BYTE Standard_DC_Luminance_NRCodes[] = { 0, 0, 7, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
BYTE Standard_DC_Luminance_Values[] = { 4, 5, 3, 2, 6, 1, 0, 7, 8, 9, 10, 11 };
BYTE Standard_DC_Chrominance_NRCodes[] = { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
BYTE Standard_DC_Chrominance_Values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
BYTE Standard_AC_Luminance_NRCodes[] = { 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d };
BYTE Standard_AC_Luminance_Values[] = {
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
};
BYTE Standard_AC_Chrominance_NRCodes[] = { 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77 };
BYTE Standard_AC_Chrominance_Values[] = {
	0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
	0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
	0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
	0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
	0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
	0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
	0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
	0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
};

//Huffman编码表
map<unsigned char, string>Huffman_code[4];
string result; //答案字符串

//由于中间需要先转换为Huffman编码，再按8位转换为字符
//中间储存字符串
string tmp_str;
int lastDC[3];



//压缩图片函数
void Compress_pic(const char* filename);
//读图片函数
void Read_pic(const char* filename);
//将压缩过程中读到的数据data分块为8*8
int div_88(compress_block* head, BYTE*& data, int x, int y);
//为每一块进行计算，算出YCbCr
void RGB_cpu(compress_block* new_node);
//获得压缩结果字符串result的函数
void Get_result(int img_height, int img_width, compress_block* head);
//具体的压缩编码过程
void compress_process(compress_block* head);
//压缩编码结束后，需要将Huffman编码按照8位转换为新字符
void write_byte();

//下面详述压缩过程
//DCT过程
void DCT(double f[8][8], double F[8][8]);
//DCT中用到alpha函数
double alpha(int u);
//数据量化过程
void quantify(double YCbCr[8][8], const int Q[8][8], int* tmp);
//Zigzag排序过程
void Zigzag_sort(int tmp[64]);
//获得具体编码过程
void writeCode(int* tmp, int DC_AC_type, int num);

//初始化Huffman编码
void Init_Huffman_Code();
//根据DC，AC系数表获得Huffman编码
void Get_Huffman_Code(BYTE* NRCodes, BYTE* Values, int index);

int Get_BitLen(int bit);
//动态内存申请之后的释放函数
void delete_block(compress_block* head);



double alpha(int u) {
	if (u == 0)
		return 1.0 / sqrt(8);
	else
		return 1.0 / 2;
}

//离散余弦变换（DCT）
void DCT(double f[8][8], double F[8][8]) {

	//f[8][8]是DCT前的，F[8][8]是DCT后的
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; j++)
		{
			F[i][j] = 0;
		}
	}

	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++) {
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++) {
					F[x][y] += f[i][j]
						* cos((2 * i + 1) / 16.0 * x * Pi)
						* cos((2 * j + 1) / 16.0 * y * Pi);
				}
			}
			F[x][y] *= alpha(x) * alpha(y);
		}

	return;
}

void quantify(double YCbCr[8][8], const int Q[8][8], int* tmp) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			tmp[i * 8 + j] = int(round(YCbCr[i][j] / Q[i][j]));

		}
}

//对一个64位的数组进行ZigZag排序
void Zigzag_sort(int tmp[64])
{
	int ZigZag_tmp[64];
	for (int i = 0; i < 64; ++i)
	{
		ZigZag_tmp[ZIGZAG[i]] = tmp[i];
	}
	for (int i = 0; i < 64; ++i)
	{
		tmp[i] = ZigZag_tmp[i];
	}

	return;
}

//求整数bit的二进制长度
int Get_BitLen(int bit) {
	//如果是0直接返回0
	if (bit == 0)
		return 0;

	//如果为负数，需要转为正数
	if (bit < 0)
		bit = -bit;

	int length = 0;
	while (bit > 0) {
		length++;
		bit >>= 1;
	}
	return length;
}

void writeCode(int* tmp, int DC_AC_type, int num) {
	//对第一个值（DC）进行特殊处理：减去前一个小块该值的原值
	int tmp_1 = tmp[0];
	tmp[0] -= lastDC[num];
	lastDC[num] = tmp_1;

	//找到从后往前的最后一个0
	int last_zero = 0;
	for (int i = 63; i > 0; i--) {
		if (tmp[i] == 0)
			last_zero++;
		else
			break;
	}

	//前面需要统计0的个数
	int zero_num = 0;
	//第一个用DC处理，之后用AC进行处理
	int is_AC = 0;

	for (int i = 0; i < 64 - last_zero; i++) {
		//如果当前值不为0，或者满足16个单元时
		if (i == 0 || tmp[i] != 0 || zero_num == 15) {

			//正负标志位
			int flag = 0;
			if (tmp[i] < 0)
				flag = 1, tmp[i] *= -1;

			bitset<50>bit(tmp[i]);
			int bit_len = Get_BitLen(tmp[i]);
			//加入对应的huffman编码
			tmp_str = tmp_str + Huffman_code[DC_AC_type + is_AC][(zero_num << 4) | bit_len];

			for (int i = bit_len - 1; i >= 0; i--)
			{
				if (bit[i] ^ flag)
					tmp_str = tmp_str + '1';
				else
					tmp_str = tmp_str + '0';
			}
			zero_num = 0;
		}
		else
			zero_num++;
		//第一次处理之后就可以用AC处理了
		is_AC = 1;
	}

	//如果末尾有0，加入EOB
	if (last_zero)
		tmp_str = tmp_str + Huffman_code[DC_AC_type + 1][0];

	return;
}

void Get_Huffman_Code(BYTE* NRCodes, BYTE* Values, int index) {
	
	BYTE* values_ptr = Values;
	int code = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < int(NRCodes[i]); j++) {
			BYTE values_value = *values_ptr;
			string str;
			bitset<50>bit(code);
			for (int k = i; k >= 0; k--) {
				if (bit[k] == 0) 
					str = str + '0';
				else 
					str = str + '1';
			}
			Huffman_code[index][values_value] = str;

			values_ptr++;
			code++;
		}
		code <<= 1;
	}
}

void Init_Huffman_Code() {
	Get_Huffman_Code(Standard_DC_Luminance_NRCodes, Standard_DC_Luminance_Values, 0);
	Get_Huffman_Code(Standard_AC_Luminance_NRCodes, Standard_AC_Luminance_Values, 1);
	Get_Huffman_Code(Standard_DC_Chrominance_NRCodes, Standard_DC_Chrominance_Values, 2);
	Get_Huffman_Code(Standard_AC_Chrominance_NRCodes, Standard_AC_Chrominance_Values, 3);
}

void compress_process(compress_block* head) {

	//初始化哈夫曼编码
	Init_Huffman_Code();

	compress_block* curnode;
	curnode = head;

	while (curnode->next_block) {
		//获得当前要处理的8*8块
		curnode = curnode->next_block;

		//用于储存DCT之后的数据
		double F[8][8];
		int tmp[64];

		//之后对8*8块的Y，Cb，Cr都要进行处理
		//对Y进行处理
		DCT(curnode->Y, F);
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; j++)
			{
				curnode->Y[i][j] = F[i][j];
			}
		}


		quantify(curnode->Y, Qy, tmp);
		Zigzag_sort(tmp);
		writeCode(tmp, 0, 0);




		//对Cb进行处理
		DCT(curnode->Cb, F);
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; j++)
			{
				curnode->Cb[i][j] = F[i][j];
			}
		}

		quantify(curnode->Cb, Qc, tmp);
		Zigzag_sort(tmp);
		writeCode(tmp, 2, 1);

		//对Cr进行处理
		DCT(curnode->Cr, F);
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; j++)
			{
				curnode->Cr[i][j] = F[i][j];
			}
		}

		quantify(curnode->Cr, Qc, tmp);
		Zigzag_sort(tmp);
		writeCode(tmp, 2, 2);

	}
	return;
}

//对之前获得的tmp_str分隔成字节，写入结果中
//如果不足8位，可以在末尾补0
void write_byte()
{
	int cur_bit = 0;

	while (tmp_str.length() >= cur_bit + 8) {
		bitset<8>bit(tmp_str.substr(cur_bit, 8));
		BYTE byte = BYTE(bit.to_ullong());
		result += char(byte);
		if (byte == 0xff)
			result += char(0x00);

		cur_bit += 8;
	}

	if (cur_bit == tmp_str.length())
		return;
	else
	{

		int number = 8 - (int(tmp_str.length()) - cur_bit);
		for (int i = 0; i < number; i++)
		{
			tmp_str += '0';
		}
		bitset<8>bit(tmp_str.substr(cur_bit, 8));
		BYTE byte = BYTE(bit.to_ullong());
		result += char(byte);
		if (byte == 0xff)
			result += char(0x00);
	}

	return;
}

void Get_result(int img_height, int img_width, compress_block* head) {

	//SOI文件头
	result += char(0xff);
	result += char(0xd8);

	//APP0图像识别信息
	//图像识别信息头
	result += char(0xff);
	result += char(0xe0);
	//段长度
	result += char(0x00);
	result += char(0x10);
	//交换格式
	result += char(0x4A);
	result += char(0x46);
	result += char(0x49);
	result += char(0x46);
	result += char(0x00);
	//主版本号和次版本号
	result += char(0x01);
	result += char(0x02); //不一样
	//单位密度
	result += char(0x00); //不一样
	//X像素密度
	result += char(0x00); //不一样
	result += char(0x01);
	//Y像素密度
	result += char(0x00); //不一样
	result += char(0x01);
	//缩略图X像素
	result += char(0x00);
	//缩略图Y像素
	result += char(0x00);
	//RGB缩略图
	//这里是空的

	//DQT定义量化表
	//定义量化表的头
	result += char(0xff);
	result += char(0xdb);
	//段长度
	result += char(0x00);
	result += char(0x84);
	//QT信息
	result += char(0x00);
	//QT量化表 量化表0
	int Zigzag_1[64], Zigzag_2[64];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Zigzag_1[i * 8 + j] = Qy[i][j];
	for (int i = 0; i < 64; i++)
		Zigzag_2[ZIGZAG[i]] = Zigzag_1[i];
	for (int i = 0; i < 64; i++)
		result += char(Zigzag_2[i]);

	//QT信息
	result += char(0x01);
	//QT量化表 量化表1
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Zigzag_1[i * 8 + j] = Qc[i][j];
	for (int i = 0; i < 64; i++)
		Zigzag_2[ZIGZAG[i]] = Zigzag_1[i];
	for (int i = 0; i < 64; i++)
		result += char(Zigzag_2[i]);

	//SOF0图像基本信息
	//图像基本信息
	result += char(0xff);
	result += char(0xc0);
	//段长度
	result += char(0x00);
	result += char(0x11);
	//样本精度
	result += char(0x08);
	//样本高度
	result += char(img_height >> 8);
	result += char(img_height & 0b1111);
	//样本宽度
	result += char(img_width >> 8);
	result += char(img_width & 0b1111);
	//组件数量
	result += char(0x03);
	//Y组件
	result += char(0x01); //组件ID
	result += char(0x11); //采样系数
	result += char(0x00); //量化表号
	//Cb组件
	result += char(0x02);
	result += char(0x11);
	result += char(0x01);
	//Cr组件
	result += char(0x03);
	result += char(0x11);
	result += char(0x01);

	//DHT定义huffman表
	//Huffman表头
	result += char(0xff);
	result += char(0xc4);
	//段长度
	result += char(0x01);
	result += char(0xa2);
	//HT信息
	//DC HT为0
	result += char(0x00);
	for (int i = 0; i < 16; i++)
		result += char(Standard_DC_Luminance_NRCodes[i]);
	for (int i = 0; i < 12; i++)
		result += char(Standard_DC_Luminance_Values[i]);
	//AC HT为0
	result += char(0x10);
	for (int i = 0; i < 16; i++)
		result += char(Standard_AC_Luminance_NRCodes[i]);
	for (int i = 0; i < 162; i++)
		result += char(Standard_AC_Luminance_Values[i]);
	//DC HT为1
	result += char(0x01);
	for (int i = 0; i < 16; i++)
		result += char(Standard_DC_Chrominance_NRCodes[i]);
	for (int i = 0; i < 12; i++)
		result += char(Standard_DC_Chrominance_Values[i]);
	//AC HT为1
	result += char(0x11);
	for (int i = 0; i < 16; i++)
		result += char(Standard_AC_Chrominance_NRCodes[i]);
	for (int i = 0; i < 162; i++)
		result += char(Standard_AC_Chrominance_Values[i]);

	//SOS扫描行开始
	//扫描行开始的头
	result += char(0xff);
	result += char(0xda);
	//段长度
	result += char(0x00);
	result += char(0x0c);
	//扫描行内组件数量
	result += char(0x03);
	//Y分量
	//第一个字节是组件ID；第二个字节0-3位AC表号，4-7位DC表号，表号的值是0-3。
	result += char(0x01);
	result += char(0x00);
	//Cb分量
	result += char(0x02);
	result += char(0x11);
	//Cr分量
	result += char(0x03);
	result += char(0x11);
	//剩余3个字节,用途不明,忽略
	result += char(0x00);
	result += char(0x3f);
	result += char(0x00);



	compress_process(head);

	write_byte();

	//EOI文件尾
	result += char(0xff);
	result += char(0xd9);

	return;
}

void RGB_cpu(compress_block* new_node)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			new_node->Y[i][j] = 0.29871 * new_node->R[i][j] + 0.58661 * new_node->G[i][j] + 0.11448 * new_node->B[i][j] - 128;
			new_node->Cb[i][j] = -0.16874 * new_node->R[i][j] - 0.33126 * new_node->G[i][j] + 0.50000 * new_node->B[i][j];
			new_node->Cr[i][j] = 0.50000 * new_node->R[i][j] - 0.41869 * new_node->G[i][j] - 0.08131 * new_node->B[i][j];
		}
	}

	return;
}

//将所有的数据划分为8*8的块的链表
int div_88(compress_block* head, BYTE*& data, int x, int y)
{
	compress_block* curnode;

	//数据转换成8*8的整块
	for (int i = 0; i < x; i += 8)
	{
		for (int j = 0; j < y; j += 8)
		{
			compress_block* new_node = new compress_block();
			if (!new_node)
			{
				cout << "动态内存申请失败" << endl;
				return -1;
			}

			//将这一8*8块的RGB赋值进结构体中
			for (int p = i; p < i + 8; ++p)
			{
				for (int q = j; q < j + 8; ++q)
				{
					int index = p * y * 4 + q * 4;
					new_node->R[p - i][q - j] = data[index];
					new_node->G[p - i][q - j] = data[index + 1];
					new_node->B[p - i][q - j] = data[index + 2];
					
				}
			}
			RGB_cpu(new_node);

			curnode = head;

			//找到列表尾
			while (curnode->next_block)
			{
				curnode = curnode->next_block;
			}

			curnode->next_block = new_node;
		}
	}

	return 0;
}

void delete_block(compress_block* head) {
	compress_block* deletenode = head;
	compress_block* nextnode = head->next_block;
	while (nextnode)
	{
		deletenode->next_block = NULL;
		delete deletenode;
		deletenode = nextnode;
		nextnode = nextnode->next_block;
	}
	delete deletenode;

	return;
}

void Compress_pic(const char* filename) {

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	// 获取时钟频率
	QueryPerformanceFrequency(&frequency);

	// 获取开始时间
	QueryPerformanceCounter(&start);

	PicReader imread;
	BYTE* data = nullptr;
	UINT x, y;
	imread.readPic(filename);
	imread.getData(data, x, y);

	compress_block* head = new compress_block();
	if (head == NULL) {
		cout << "内存申请失败" << endl;
		exit(0);
	}
	head->next_block = NULL;

	//全部数据划分为8*8的块链表
	int a = div_88(head, data, x, y);

	delete[] data;
	data = nullptr;

	Get_result(x, y, head);

	//输出
	const char* outfile = "lena.jpg";
	ofstream fl(outfile, ios::binary);
	if (!fl) {
		cout << "文件打开失败" << endl;
		exit(0);
	}
	fl << result;
	fl.close();

	//释放动态申请的空间（链表）
	delete_block(head);

	// 获取结束时间
	QueryPerformanceCounter(&end);

	// 计算程序执行时间
	double duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	// 输出程序执行时间（以秒为单位）
	cout << "程序执行时间: " << duration << " 秒" << endl;

	return;
}

void Read_pic(const char* filename) {

	PicReader imread;
	BYTE* data = nullptr;
	UINT x, y;
	imread.readPic(filename);
	imread.getData(data, x, y);
	imread.showPic(data, x, y);

	delete[] data;
	data = nullptr;

	printf("Press enter to continue...");
	(void)getchar();
}

//主函数
int main(int argc, char** argv) {
	cout << "开始运行" << endl;

	if (argc != 3) {
		cerr << "请检查参数个数是否正确" << endl;
		return -1;
	}

	if (!strcmp(argv[1], "-compress") || !strcmp(argv[1], "-read")) {
		if (!strcmp(argv[1], "-compress"))
		{
			Compress_pic(argv[2]);
		}
		else if (!strcmp(argv[1], "-read"))
		{
			Read_pic(argv[2]);
		}
	}
	else {
		cerr << "Unknown parameter!\nCommand list:\n-compress\n-read" << endl;
		return -1;
	}

	cout << "Complete!" << endl;
	return 0;
}

