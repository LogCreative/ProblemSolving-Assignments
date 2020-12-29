//计算这两个地点一年中每个月的平均气温
//使用柱状图表示，同时将其实现在同一张图上
//横轴为月份，纵轴为温度，注意坐标轴、标签、颜色的使用。

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities

#define READING_YEAR 2016					// 读取年份
#define MAX_TEMP 32							// 平均最高

// 存储的数据结构
struct AvgTemp {
	int year, month, day;			// 日期
	double tempAvg;					// 平均温度
};

class CityAvgTemp {
	// 数据结构：year/month/day, tempAvg,\n
	friend istream& operator>>(istream& is, AvgTemp& a);
public:
	CityAvgTemp(string file_name);
	~CityAvgTemp();
	// 得到比例
	double proportion(int month);
private:
	double monthAvg[13] = { 0 };		// 十二个月的平均温度，第 0 个废弃
};
