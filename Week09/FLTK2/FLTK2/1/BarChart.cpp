#include "BarChart.h"

istream& operator>>(istream& is, AvgTemp& a) {
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	char ch4 = 0;
	AvgTemp at;

	if (is >> at.year >> ch1 >> at.month >> ch2 >> at.day >> ch3 >> at.tempAvg >> ch4) {
		if (ch1 != '/' || ch2 != '/' || ch3 != ',' || ch4 != ',') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else return is;
	a = at;
	return is;
}

CityAvgTemp::CityAvgTemp(string file_name) {
	// Visual Studio 的调试运行目录与 sln 文件同级
	ifstream ifs(file_name, ifstream::in);
	if (!ifs) error("can't open ", file_name);
	else ifs.seekg(15);   // 略读第一行[15]：Date,TempAvg,\r\n

	double monthTemp[13] = { 0 };			// 十二个月的温度数据
	int cnt_days[13] = { 0 };				// 十二个月每月的计算天数

	AvgTemp a;
	while (ifs >> a) {							// 读取中
		if (a.year != READING_YEAR) error("not the reading year.");
		monthTemp[a.month] += a.tempAvg;		// 温度累积
		cnt_days[a.month]++;					// 记录天数 + 1
	}

	// 读取完毕后的统计
	for (int i = 1; i < 13; ++i)
		monthAvg[i] = monthTemp[i] / cnt_days[i];
}

double CityAvgTemp::proportion(int month) {
	return monthAvg[month] / MAX_TEMP;
}

CityAvgTemp::~CityAvgTemp() = default;