#include "Binary_tree.h"

Binary_tree::Binary_tree(int _N, Point _xy, Color color):
	N(_N),xy(_xy) {
	set_color(color);
	calc_nodes();
}

void Binary_tree::calc_nodes() {
	if (N == 0) return;
	add(xy);						//�ϳ��� 0 ���ڵ�
	int layer_num = 1;
	double interval = pow(2, N - 1) * w;
	Point bottom_left = Point(xy.x + interval / 2, xy.y);							// ������
	for (int i = 0; i < N; ++i) {
		int j = layer_num;
		Point cur = bottom_left;
		while (j--) {
			add(cur);
			cur = Point(cur.x + interval, cur.y);									// �����ƶ� interval
		}
		layer_num *= 2;																// �ò�ڵ�������2
		interval /= 2;																// ������2
		bottom_left = Point(bottom_left.x - interval / 2, bottom_left.y + h);		// �ƶ����½ڵ�����
	}
}

void Binary_tree::draw_nodes() const {
	if (color().visibility())
		for (int i = 1; i < pow(2, N); ++i)
			fl_pie(point(i).x - r, point(i).y - r, r + r, r + r, 0, 360);
}

void Binary_tree::draw_lines() const {
	// �� i �� 2^(i-1) ~ 2^i - 1
	int layer_start = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = layer_start; j < 2 * layer_start; ++j) {
			fl_line(point(j).x, point(j).y, point(2 * j).x, point(2 * j).y);
			fl_line(point(j).x, point(j).y, point(2 * j + 1).x, point(2 * j + 1).y);
		}
		layer_start *= 2;
	}
	draw_nodes();
}