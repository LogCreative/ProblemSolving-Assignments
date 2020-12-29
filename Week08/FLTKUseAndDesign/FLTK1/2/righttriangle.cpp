#include "righttriangle.h"

righttriangle::righttriangle(Point xy, int _a, int _b, double _angle, Color color) {
	add(xy);
	add(Point(xy.x + _a * cos(_angle), xy.y + _a * sin(_angle)));
	add(Point(xy.x + _a * cos(_angle + PI / 2), xy.y + _a * sin(_angle + PI / 2)));//»¡¶ÈÖÆº¯Êý
	set_color(color);
	set_fill_color(color);
}