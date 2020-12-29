// ���н��������ɶԸ��ӽڵ����ݣ�����ݸ����ĸ��ӽڵ��ϵȷ����Щ���ݶ����
// �����չ����������

#include "std_lib_facilities.h"

class NodeRecognition {
public:
	NodeRecognition(string);
	~NodeRecognition();

	// ������죬��С��������
	void prtStruct();
private:
	// �ڵ�ԵĴ洢����
	// ����������ظ�����һ����ֵ�ڵ㣬����Щ�ڵ㽫���ϲ���
	// ����Ϊ���ڵ� right -> left
	set<pair<int, int>> nodePairs;

	// ���нڵ�ļ���
	set<int> nodeContains;
	
	// ͼ����
	// Node:		�ڵ�
	// BinaryTree:	������
	// Tree:		��
	// Graph:		ͼ
	enum graphTypes {Node, BinaryTree, Tree, Graph};

	// ͼ����
	struct graph
	{
		enum graphTypes graphType;			// ͼ������
		int weight;							// ͼ��Ȩ��
		int size;							// ͼ�Ľڵ�����

		graph() :graphType(Node), weight(0), size(0) {}
		graph(graphTypes gt, int w, int s) : graphType(gt), weight(w), size(s) {}
		~graph() {}
	};

	// �ȽϷ����������������У�>��
	// ��������ȴ���Ϊ�������ڵ㡢��������һ������һ��ͼ
	// ���Ȩ��һ�£����սڵ�����С�������м���
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

	// ͼ�Ĵ洢���������ȶ��еķ�ʽ
	priority_queue<graph, vector<graph>, cmp> graphs;

	// ʶ��ͼ
	void graphRecognite();
};