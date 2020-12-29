//定义一个Binary_tree类，它派生自Shape类。
// 层数作为一个参数（levels==0表示没有节点，levels==1表示有一个节点，levels==2表示有一个顶层节点和两个子节点，levels==3表示有一个顶层节点、两个子节点以及这两个子节点的各自两个子节点，依此类推。使用小圆圈表示一个节点，并用线连接这些节点。
// 注意：使用虚函数来绘制它的节点。

#ifndef BT_GUARD
#define BT_GUARD 1

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities

using namespace Graph_lib;

const int w = 30;			// 中轴间距
const int h = 50;			// 层高
const int r = 10;			// 节点半径

struct Binary_tree : public Shape {
	Binary_tree(int _N, Point _xy, Color color);
	// 注意：使用虚函数来绘制它的节点。
	virtual void draw_nodes() const;
	void draw_lines() const;
protected:
	int N;						// 层数
private:
	Point xy;					// 平移偏移量
	// 计算节点位置
	void calc_nodes();
};

#endif // !BT_GUARD