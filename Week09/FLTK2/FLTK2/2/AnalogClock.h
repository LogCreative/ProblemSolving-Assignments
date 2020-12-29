//编写一个模拟时钟，即一个带有转动指针的时钟。通过一个库函数调用从操作系统获取时间值。提示：clock()、sleep()
//要求：
//绘制的模拟时钟和现实时钟一致，具有时 / 分 / 秒针，12个小时的刻度及对应数字
//在时钟上显示日期（年 / 月 / 日）以及当前时间
#define _CRT_SECURE_NO_WARNINGS
#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities
#define CENTER 300							 // 中心点位置
#define FONTSIZE 25							 // 字号
const double PI = acos(-1);					 // 圆周率

using namespace Graph_lib;

// 获取极坐标点位
Point converter(int length, double angle);

// 指针
struct Pointer : Closed_polyline
{
	Pointer(int _length, double _angle, int _width);
private:
	void draw_lines() const;
	int			length;						// 长度
	double		angle;						// 角度制角度（顺时针定义）
	int			width;						// 指针宽度
	Point		tip;						// 尖端位置
};

// 模拟时钟
class AnalogClock: public Shape {
public:
	AnalogClock();
	~AnalogClock();
	// 获取日期
	string getDate(tm* p) const;
	// 获取时间
	string getTime(tm* p) const;
	// 获取时针角度
	double getHAngle(tm *p) const;
	// 获取分针角度
	double getMAngle(tm* p) const;
	// 获取秒针角度
	double getSAngle(tm* p) const;
private:
	// 角度映射
	double AngleMap(double _progress) const;
	// 双位补零
	string dualFiller(int _input) const;
	void draw_lines() const;
};