#include "AnalogClock.h"


Pointer::Pointer(int _length, double _angle, int _width) :
	length(_length), angle(_angle), width(_width)
{
	tip = converter(length, angle);
}

void Pointer::draw_lines() const {
	if (color().visibility()) {
		Point lt = converter(width, angle + 90);
		Point rt = converter(width, angle - 90);

		fl_begin_complex_polygon();

		fl_vertex(tip.x, tip.y);
		fl_vertex(lt.x, lt.y);
		fl_vertex(rt.x, rt.y);

		fl_end_complex_polygon();
	}
}

AnalogClock::AnalogClock() {
	set_color(Color::blue);
}

string AnalogClock::dualFiller(int _input) const {
	return _input < 10 ? "0" + to_string(_input) : to_string(_input);
}

string AnalogClock::getDate(tm *p) const {
	
	return to_string(p->tm_year + 1900) + " / " + 
		to_string(p->tm_mon + 1) + " / " + 
		to_string(p->tm_mday);
}

string AnalogClock::getTime(tm* p) const {
	
	return dualFiller(p->tm_hour) + " : " +
		dualFiller(p->tm_min) + " : " +
		dualFiller(p->tm_sec);
}

double AnalogClock::AngleMap(double _progress) const {
	return _progress * 360 - 90;
}

double AnalogClock::getHAngle(tm* p) const {
	double tmp = ((p->tm_hour > 12 ? p->tm_hour - 12 : p->tm_hour) + p->tm_min / 60.0) / 12.0;
	return AngleMap(tmp);
}

double AnalogClock::getMAngle(tm* p) const {
	return AngleMap(p->tm_min / 60.0);
}

double AnalogClock::getSAngle(tm* p) const {
	return AngleMap(p->tm_sec / 60.0);
}

Point converter(int length, double angle) {
	double arc_angle = angle * PI / 180;
	return Point(
		CENTER + length * cos(arc_angle), 
		CENTER + length * sin(arc_angle)
	);
}

void AnalogClock::draw_lines() const {
	for (;; Sleep(1000)) {
		//外边缘
		Graph_lib::Rectangle* rect;
		rect = new Graph_lib::Rectangle(Point(100, 100), 400, 400);
		rect->set_color(Color::dark_green);
		rect->set_fill_color(Color::white);
		rect->set_style(Line_style(Line_style::solid, 10));
		rect->draw();
		//内边缘
		rect = new Graph_lib::Rectangle(Point(105, 105), 390, 390);
		rect->set_color(Color::green);
		rect->set_style(Line_style(Line_style::solid, 5));
		rect->draw();

		//时钟的中心在（300，300），圆的半径设定为150
		//角度定义是顺时针为正
		Graph_lib::Text* tick;
		for (int i = 1, j = -60; i <= 12 && j < 300; ++i, j = j + 30) {
			Point tickp = converter(150, j);
			tick = new Graph_lib::Text(converter(170, j), to_string(i));
			tick->set_color(Color::black);
			tick->set_font_size(FONTSIZE);
			tick->move(i >= 10 ? -15 : -5, 5);
			tick->set_color(Color::blue);
			tick->draw();
			fl_pie(tickp.x, tickp.y, 5, 5, 0, 360);
		}

		time_t nowtime;		//当前时间
		time(&nowtime);
		tm* p = localtime(&nowtime);

		Graph_lib::Rectangle* bazel = new Graph_lib::Rectangle(
			Point(CENTER - FONTSIZE * 5 - 10, CENTER + 5), 110, 55);
		bazel->set_color(Color::red);
		bazel->draw();

		Graph_lib::Text* datetick = new Graph_lib::Text(
			Point(CENTER - FONTSIZE * 5, CENTER + FONTSIZE), 
			getDate(p)
		);
		datetick->set_color(Color::red);
		datetick->draw();
		Graph_lib::Text* timetick = new Graph_lib::Text(
			Point(CENTER - FONTSIZE * 4.75, CENTER + 2 * FONTSIZE), 
			getTime(p)
		);
		timetick->set_color(Color::red);
		timetick->draw();
		Pointer* sptr = new Pointer(150, getSAngle(p), 2);
		sptr->set_color(Color::black);
		sptr->draw();
		Pointer* mptr = new Pointer(130, getMAngle(p), 4);
		mptr->set_color(Color::black);
		mptr->draw();
		Pointer* hptr = new Pointer(100, getHAngle(p), 7);
		hptr->set_color(Color::black);
		hptr->draw();
	}
}

AnalogClock::~AnalogClock() = default;