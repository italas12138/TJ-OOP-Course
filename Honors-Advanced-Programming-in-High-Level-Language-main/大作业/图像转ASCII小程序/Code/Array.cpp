#pragma once
#include <iostream>
using namespace std;

class Array
{
public:
    template <typename... Args>
    Array(Args... args)
    {
        // ��ȡ��������С��ת��Ϊsize_t����
        auto num = sizeof...(args);
        size_t list[] = { args... };

        index = 0;
        axisNum = num;
        nowAxis = 1;
        for (int i = 1;i <= num;i++)
            shape[i] = list[i - 1];
        totNum[num] = 1;
        for (int i = num - 1;i >= 0;i--)
            totNum[i] = shape[i + 1] * totNum[i + 1];
        data = new int[totNum[0]];
    }
    Array(Array* arr) {
        axisNum = arr->axisNum;
        nowAxis = arr->nowAxis;
        index = arr->index;
        for (int i = 0;i <= axisNum;i++) {
            totNum[i] = arr->totNum[i];
            shape[i] = arr->shape[i];
        }
    }
    ~Array() {
    }

    template <typename... Args>
    Array at(Args... args)
    {
        // ��ȡ��������С��ת��Ϊsize_t����
        auto num = sizeof...(args);
        size_t list[] = { args... };
    }

    template <typename... Args>
    void reshape(Args... args)
    {
        // ��ȡ��������С��ת��Ϊsize_t����
        auto num = sizeof...(args);
        size_t list[] = { args... };

        index = 0;
        axisNum = num;
        nowAxis = 1;
        for (int i = 1;i <= num;i++)
            shape[i] = list[i - 1];
        totNum[num] = 1;
        for (int i = num - 1;i >= 0;i--)
            totNum[i] = shape[i + 1] * totNum[i + 1];

    }

    int* get_content() { return data; }

    void set(int value) {}

    void copyData(Array& arr) {
        for (int i = 0;i < totNum[0];i++)
            data[i] = arr.data[i];
    }

    void newData() {
        data = new int[totNum[0]];
    }

    void releaseData() {
        delete[] data;
    }

    Array operator[](int index)
    {
        // �������޸��Ӿ����nowAxis��ֵ�Լ������б�Ҫ��ֵ���Է���һ���Ӿ���
        Array subArr(this);
        ++subArr.nowAxis;
        subArr.index = this->index + totNum[nowAxis] * index;
        subArr.data = data;
        return subArr;
    }

    Array& operator=(int data)
    {
        //cout << "index=" << index << endl;
        this->data[index] = data;
        return *this;
    }

    operator int() {
        //cout << "index=" << index << endl;
        return data[index];
    }

    Array operator+(Array& arr) {
        Array ret(this);
        ret.newData();
        for (int i = 0;i < totNum[0];i++)
            ret.data[i] = data[i] + arr.data[i];
        return ret;
    }

    Array operator+(int Data) {
        Array ret(this);
        ret.newData();
        for (int i = 0;i < totNum[0];i++)
            ret.data[i] = data[i] + Data;
        return ret;
    }

    Array operator-(Array& arr) {
        Array ret(this);
        ret.newData();
        for (int i = 0;i < totNum[0];i++)
            ret.data[i] = data[i] - arr.data[i];
        return ret;
    }

    Array operator-(int Data) {
        Array ret(this);
        ret.newData();
        for (int i = 0;i < totNum[0];i++)
            ret.data[i] = data[i] - Data;
        return ret;
    }

    Array operator*(Array& arr) {
        Array ret(this);
        ret.newData();
        for (int i = 0;i < totNum[0];i++)
            ret.data[i] = data[i] * arr.data[i];
        return ret;
    }

    Array operator*(int Data) {
        Array ret(this);
        ret.newData();
        for (int i = 0;i < totNum[0];i++)
            ret.data[i] = data[i] * Data;
        return ret;
    }

    Array operator/(Array& arr) {
        Array ret(this);
        ret.newData();
        for (int i = 0;i < totNum[0];i++)
            if (arr.data[i] != 0) ret.data[i] = data[i] / arr.data[i];
        return ret;
    }

    Array operator/(int Data) {
        Array ret(this);
        ret.newData();
        for (int i = 0;i < totNum[0];i++)
            ret.data[i] = data[i] / Data;
        return ret;
    }


    int* data;
    int index; //��ǰ���ڵ��±�
    int shape[16];//ÿһά�Ĵ�С
    int totNum[16];
    int axisNum; //�ܹ��м�ά
    int nowAxis; //�����ڵڼ�ά
};