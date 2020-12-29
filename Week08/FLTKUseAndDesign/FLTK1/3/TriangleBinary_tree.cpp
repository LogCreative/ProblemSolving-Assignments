#include "TriangleBinary_tree.h"

TriangleBinary_tree::TriangleBinary_tree(int _N, Point _xy, Color _color) : Binary_tree(_N, _xy, _color) {}

void TriangleBinary_tree::draw_nodes() const {
	if (color().visibility())
		for (int i = 1; i < pow(2, N); ++i) {
			Point center = point(i);
            
			fl_begin_complex_polygon();

            fl_vertex(center.x, center.y - r);
			fl_vertex(center.x - r, center.y + r);
			fl_vertex(center.x + r, center.y + r);
            
			fl_end_complex_polygon();
		}
}