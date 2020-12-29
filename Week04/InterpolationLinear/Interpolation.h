#pragma once

#include "std_lib_facilities.h"

#define MAXLINE 100		// ��ֵ��������ڵ���2��������100��
#define EPSILON 1e-6	// ����С��

// ����������Ĭ��Ϊdouble��

// ʹ��ţ�ٲ�ֵ����⺯������ֵ��
class Interpolation {
	friend string cutDouble(double x);		// ��ȡ����
public:
	Interpolation();
	void solve(double);						// ���
	~Interpolation();
private:
	bool error = false;						// ����Ĳ�ֵ����
	int count = 0;							// ��ֵ�����
	double x[MAXLINE];						// ������
	double y[MAXLINE];						// ������
	double diff[MAXLINE][MAXLINE];			// ��ֵ��

	// ��ʼ����ֵ����Ҫ���Ա�������������
	void initDiff();
	// �����ֵ��
	void calcDiff();	
};