//��Binary_tree����һ�����࣬�Խڵ�ʹ��һ�������εı�ʾ�����Ǵ��麯����

#include "Binary_tree.h"

struct TriangleBinary_tree : public Binary_tree
{
public:
	TriangleBinary_tree(int N, Point xy, Color color);
	virtual void draw_nodes() const;
};