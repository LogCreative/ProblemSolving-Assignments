#pragma once

#include "std_lib_facilities.h"

#define MAXLINE 100		// ��������������101�С�
#define EPSILON 1e-6	// ����С��

class LinearRegression {
public:
	LinearRegression();
	// �����������ϵ��
	void getCoeff();	
	// ����������Ϸ���
	void getFunction();
	// �����Ӧ���ֵ
	void getValue(double);
	~LinearRegression();
private:
	bool error = false;						// ��������Ե㼯
	int count = 0;							// �������
	double x[MAXLINE];						// ������
	double y[MAXLINE];						// ������

	double x_mean;							// �������ֵ
	double y_mean;							// �������ֵ
	double L_xx, L_yy, L_xy;				// �������

	double b, a;							// ���ϵ�����

	// ����ϵ��
	void calcFactors();
	// ��ȡ����
	string cutDouble(double x);		
};