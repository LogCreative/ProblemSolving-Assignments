//����һ��Binary_tree�࣬��������Shape�ࡣ
// ������Ϊһ��������levels==0��ʾû�нڵ㣬levels==1��ʾ��һ���ڵ㣬levels==2��ʾ��һ������ڵ�������ӽڵ㣬levels==3��ʾ��һ������ڵ㡢�����ӽڵ��Լ��������ӽڵ�ĸ��������ӽڵ㣬�������ơ�ʹ��СԲȦ��ʾһ���ڵ㣬������������Щ�ڵ㡣
// ע�⣺ʹ���麯�����������Ľڵ㡣

#ifndef BT_GUARD
#define BT_GUARD 1

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities

using namespace Graph_lib;

const int w = 30;			// ������
const int h = 50;			// ���
const int r = 10;			// �ڵ�뾶

struct Binary_tree : public Shape {
	Binary_tree(int _N, Point _xy, Color color);
	// ע�⣺ʹ���麯�����������Ľڵ㡣
	virtual void draw_nodes() const;
	void draw_lines() const;
protected:
	int N;						// ����
private:
	Point xy;					// ƽ��ƫ����
	// ����ڵ�λ��
	void calc_nodes();
};

#endif // !BT_GUARD