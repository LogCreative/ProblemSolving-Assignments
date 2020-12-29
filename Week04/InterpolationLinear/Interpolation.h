#pragma once

#include "std_lib_facilities.h"

#define MAXLINE 100		// 插值点个数大于等于2，不超过100。
#define EPSILON 1e-6	// 精度小量

// 浮点数类型默认为double。

// 使用牛顿插值法求解函数近似值。
class Interpolation {
	friend string cutDouble(double x);		// 截取函数
public:
	Interpolation();
	void solve(double);						// 求解
	~Interpolation();
private:
	bool error = false;						// 错误的插值输入
	int count = 0;							// 插值点个数
	double x[MAXLINE];						// 横坐标
	double y[MAXLINE];						// 纵坐标
	double diff[MAXLINE][MAXLINE];			// 插值表

	// 初始化插值表，主要对自变量排序与间距检测
	void initDiff();
	// 计算插值表
	void calcDiff();	
};