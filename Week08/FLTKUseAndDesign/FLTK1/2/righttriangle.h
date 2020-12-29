// 定义直角三角形类，构造函数的参数为顶点坐标，两条直角边的长度并创建实例，利用8个不同颜色的直角三角形绘制一个正八边形。

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities

using namespace Graph_lib;

const double PI = acos(-1.0); //定义圆周率

struct righttriangle : Closed_polyline
{
	righttriangle(Point xy, int _a, int _b, double _angle, Color color);
};