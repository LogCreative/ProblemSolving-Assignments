#pragma once

#include "std_lib_facilities.h"

#define MAXLINE 100		// 输入行数不超过101行。
#define EPSILON 1e-6	// 精度小量

class LinearRegression {
public:
	LinearRegression();
	// 计算线性相关系数
	void getCoeff();	
	// 计算线性拟合方程
	void getFunction();
	// 求出对应点的值
	void getValue(double);
	~LinearRegression();
private:
	bool error = false;						// 错误的线性点集
	int count = 0;							// 坐标个数
	double x[MAXLINE];						// 横坐标
	double y[MAXLINE];						// 纵坐标

	double x_mean;							// 横坐标均值
	double y_mean;							// 纵坐标均值
	double L_xx, L_yy, L_xy;				// 求和因子

	double b, a;							// 拟合系数结果

	// 计算系数
	void calcFactors();
	// 截取函数
	string cutDouble(double x);		
};