// 题中将给出若干对父子节点数据，请根据给出的父子节点关系确定这些数据对组成
// 并按照规则依次输出

#include "std_lib_facilities.h"

class NodeRecognition {
public:
	NodeRecognition(string);
	~NodeRecognition();

	// 输出构造，从小到大排列
	void prtStruct();
private:
	// 节点对的存储集合
	// 如果输入中重复出现一个数值节点，则这些节点将被合并；
	// 后者为父节点 right -> left
	set<pair<int, int>> nodePairs;

	// 已有节点的集合
	set<int> nodeContains;
	
	// 图类型
	// Node:		节点
	// BinaryTree:	二叉树
	// Tree:		树
	// Graph:		图
	enum graphTypes {Node, BinaryTree, Tree, Graph};

	// 图构造
	struct graph
	{
		enum graphTypes graphType;			// 图的类型
		int weight;							// 图的权重
		int size;							// 图的节点总数

		graph() :graphType(Node), weight(0), size(0) {}
		graph(graphTypes gt, int w, int s) : graphType(gt), weight(w), size(s) {}
		~graph() {}
	};

	// 比较仿生函数，升序排列（>）
	// 输出的优先次序为：单个节点、二叉树、一般树、一般图
	// 如果权重一致，则按照节点数从小到大排列即可
	struct cmp {
		bool operator()(graph left, graph right) {
			if (left.graphType == right.graphType) {
				if (left.weight == right.weight)
					return left.size > right.size;
				return left.weight > right.weight;
			}
			return left.graphType > right.graphType;
		}
	};

	// 图的存储，采用优先队列的方式
	priority_queue<graph, vector<graph>, cmp> graphs;

	// 识别图
	void graphRecognite();
};