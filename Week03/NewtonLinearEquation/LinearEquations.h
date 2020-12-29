#pragma once
#include "std_lib_facilities.h"
#define UNKNOWNS 101					// ���δ֪��������x_0���գ��������� n ����Ҫ���������Ƕ�С��100��
#define EPSILON 1e-6					// 0��ֵ������-0.0000

class LinearEquations {
	friend string cutDouble(double x);          // ��λ����
public:
	// ��������빲��N�У�ÿһ��Ϊһ�����Է��̣�δ֪����x_n��ʽ��ʾδ֪����
	LinearEquations(string str);
	// ������Ԫ��˹��ȥ�������
	void solve();

	~LinearEquations();
private:
	bool error = false;							// ��������Է�����
	int line = 1;								// ����
	bool validUnks[UNKNOWNS] = { false };		// ��Ч��δ֪��
	double A[UNKNOWNS][UNKNOWNS] = { 0 };		// �������	[1~maxvalidUnk][1~maxvalidUnk]
	double b[UNKNOWNS] = { 0 };					// ������	[1~maxvalidUnk]
	double x[UNKNOWNS];							// �⼯		[1~maxvalidUnk]
};