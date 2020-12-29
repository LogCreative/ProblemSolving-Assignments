// 请编程写程序，读入独木舟的最大承载量、旅客数目与每位乘客的重量。
// 根据给出的规划计算安置所有旅客必须的最少独木舟条数。

#include "std_lib_facilities.h"

class boat {
public:
	boat(int _w, int _n);
	void getBoatNum();
	~boat();
private:
	int w;						// 一条独木舟的最大承载量		80<=w<=200
	int n;						// 将要乘船的人数				1<=n<=300
	int* weights;				// n个旅客的体重
	bool* arrange;				//是否已经安排
	int errorlevel = 0;			// 异常等级： 0-正常输出 1-out 2-error
};
