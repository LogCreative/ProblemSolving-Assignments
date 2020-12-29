#include "hyperelliptic.h"

void hyperelliptic::calc_points() {
	// 计算点
	// x 的 取值范围为 [-a,a]
	double x = -a;
	double y;
	for (int i = 0; i <= N; ++i) {
		y = 1 - pow(x / a, m);
		if (y != 0) { 
			y = pow(y, 1.0 / n) * b;
			add(Point(x + xy.x, y + xy.y));
			add(Point(x + xy.x, -y + xy.y));			// 两个点
		}
		else { 
			//y = 0;
			add(Point(x + xy.x, y + xy.y));
		}
		x += 2.0 * a / N;
	}
}

void hyperelliptic::draw_lines() const {
	if (color().visibility() && 1 < number_of_points()) {
		for (unsigned int i = 0; i < number_of_points(); ++i)
			for (unsigned int j = i + 1; j < number_of_points(); ++j)
				fl_line(point(i).x, point(i).y, point(j).x, point(j).y);
	}
}

/*

hyptic_window::hyptic_window(Point xy, int w, int h, const string& title) :
	Simple_window(xy, w, h, title),
	ib(Point(100, 50), 400, 20, "Input"),
	generate_btn(Point(100, 80), 100, 20, "Submit", cb_generate)
{
	//attach(ib);
	//attach(generate_btn);
	//hyperelliptic hyptic(Point(300, 300), 1,2,3,4,5);               // 超椭圆
	//attach(hyptic);
}

void hyptic_window::cb_generate(Address, Address pw) {
	reference_to<hyptic_window>(pw).generate();
}

void hyptic_window::generate() {
	string input = ib.get_string() + ' ';	// 该函数没有定义，源代码已经修改 @ GUI.cpp
	int _a, _b, _m, _n, _N;
	int param_cnt = 0;
	int temp_param = 0;
	for (auto c : input) {
		if (isdigit(c)) temp_param = temp_param * 10 + (c - '0');
		else if (c == ' ') {
			switch (param_cnt)
			{
			case 0: _a = temp_param; break;
			case 1: _b = temp_param; break;
			case 2: _m = temp_param; break;
			case 3: _n = temp_param; break;
			case 4: _N = temp_param; break;
			}
			if (++param_cnt == 5) break;
			temp_param = 0;
		}
	}
	
}

*/