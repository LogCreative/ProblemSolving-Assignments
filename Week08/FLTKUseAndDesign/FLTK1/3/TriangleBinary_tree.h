//从Binary_tree派生一个新类，对节点使用一个三角形的表示来覆盖此虚函数。

#include "Binary_tree.h"

struct TriangleBinary_tree : public Binary_tree
{
public:
	TriangleBinary_tree(int N, Point xy, Color color);
	virtual void draw_nodes() const;
};