// ����ֱ���������࣬���캯���Ĳ���Ϊ�������꣬����ֱ�Ǳߵĳ��Ȳ�����ʵ��������8����ͬ��ɫ��ֱ�������λ���һ�����˱��Ρ�

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities

using namespace Graph_lib;

const double PI = acos(-1.0); //����Բ����

struct righttriangle : Closed_polyline
{
	righttriangle(Point xy, int _a, int _b, double _angle, Color color);
};