#include "NodeRecognition.h"

NodeRecognition::NodeRecognition(string str) {
	// 一个测试用例中节点对与单个节点的个数和不超过100个，最少0个；
	// 节点可能不连通；

	int nidl = 0;					// 左节点标识符
	int nidr = 0;					// 右节点标识符

	// 输入状态
	// outside:		输入状态外
	// left:		左节点输入
	// right:		右节点输入
	enum inputStates { outside, left, right };
	
	// 输入状态
	enum inputStates inputState = outside;

	char prev = '\0';

	for (auto c : str) {
		switch (c) {
			case '<':				// 左起
				inputState = left;	
				break;
			case '>':				// 右终
				// 为了方便计算，每个节点使用唯一的自然数表示，该自然数同时代表节点的权重；
				// 所以大于等于 0，空节点使用 -1 标识
				if (inputState == left) nidr = -1;
				// 避免<>输入：最少0个
				if (prev != '<') {
					// 存储节点对
					nodePairs.insert(make_pair(nidl, nidr));
					// 存储包含的节点
					nodeContains.insert(nidl);
					if (nidr != -1) nodeContains.insert(nidr);
				}
				// 初始化变量
				nidl = 0; nidr = 0; inputState = outside;
				break;
			case ' ':				// 分隔
				if (inputState > 0) inputState = right;
				break;
			default:				// 数字
				if (c >= '0' && c <= '9') {
					if (inputState == left)
						nidl = nidl * 10 + c - '0';
					else if (inputState == right)
						nidr = nidr * 10 + c - '0';
				}
				break;
		}
		prev = c;
	}

	graphRecognite();
}

void NodeRecognition::graphRecognite() {
	// 单个节点：只有一个 <Node>，其余对中无法找到该节点
	// 二叉树：节点有至多两个儿子
	// 一般树：节点有不止两个儿子
	// 图：有环路
	// 访问后即被删除

	// 存储已经删除的节点
	vector<set<pair<int, int>>::iterator> deliters;

	for (auto i = nodePairs.begin(); i != nodePairs.end(); i++) {
		if (find(deliters.begin(), deliters.end(), i) != deliters.end()) continue;	//删除后的节点即跳过
		if (i->second == -1) { // 孤立节点，或根节点
			graph g;					// 临时存储的图
			g.weight += i->first; g.size += 1;

			// 该图的节点访问队列
			queue<int> nodeQ;
			nodeQ.push(i->first);

			deliters.push_back(i);

			while (!nodeQ.empty()) {
				int father = nodeQ.front(); nodeQ.pop();
				// 定义为访问过，即从包含的节点中删除
				nodeContains.erase(father);

				int sonNum = 0;	//儿子数

				for (auto j = nodePairs.begin(); j != nodePairs.end(); j++) {
					if (find(deliters.begin(), deliters.end(), j) != deliters.end()) continue;
					if (j->second == father) {		// j 中有 father 的儿子
						++sonNum;

						if (nodeContains.find(j->first) != nodeContains.end()) {
							nodeQ.push(j->first);	// 尚未访问过，推入访问队列
							g.weight += j->first; g.size += 1;
							nodeContains.erase(j->first);
						}
						else g.graphType = Graph;	// 儿子节点已经被访问过，形成回路，为一般图
						
						deliters.push_back(j);
					}
				}

				// 关于树，提升等级
				if (g.graphType < BinaryTree && (sonNum == 1 || sonNum == 2))  g.graphType = BinaryTree;
				else if (g.graphType < Tree && sonNum>2) g.graphType = Tree;
			}

			graphs.push(g);	// 推入图
		}
	}

	// 仍然剩余连接 都是成对出现 意味着为一般图 只需要考虑连通关系即可 需要进行第二轮循环
	// 如果该单个节点相连通的的节点集合被识别为一般图，则子图里根节点、父子关系等与树相关的概念将不成立，而是设置为一般的图节点与连通关系。
	// 这里采用广度优先搜索（BFS）
	for (auto i = nodePairs.begin(); i != nodePairs.end() && nodePairs.size() > deliters.size(); i++) {
		if (find(deliters.begin(), deliters.end(), i) != deliters.end()) continue;	//删除后的节点即跳过
		// 从当前的对开始构建图，父亲开始
		if (nodeContains.find(i->second) != nodeContains.end()) {
			graph g(Graph, i->second, 1);
			queue<int> nodeQ;
			nodeQ.push(i->second);
			nodeContains.erase(i->second);
			while (!nodeQ.empty()) {
				int father = nodeQ.front(); nodeQ.pop();
				for (auto j = nodePairs.begin(); j != nodePairs.end(); j++) {
					if (find(deliters.begin(), deliters.end(), j) != deliters.end()) continue;
					int son = -1;
					if (j->first == father) son = j->second;
					else if (j->second == father) son = j->first;
					if (son != -1 && nodeContains.find(son) != nodeContains.end()) {
						nodeQ.push(son);	// 尚未访问过，推入访问队列
						g.weight += son; g.size += 1;
						deliters.push_back(j);
						// 定义为访问过，即从包含的节点中删除
						nodeContains.erase(son);
					}
				}
			}
			graphs.push(g);	// 推入图
		}
	}
}

void NodeRecognition::prtStruct() {
	// 英文语法复数
	cout << "We have recognized " << graphs.size() << ((graphs.size() <= 1)?" graph.":" graphs.") << endl;
	while (!graphs.empty()) {
		auto g = graphs.top(); graphs.pop();
		cout << "--";
		switch (g.graphType) {
			case Node:			cout << "Node"; break;
			case BinaryTree:	cout << "Binary tree"; break;
			case Tree:			cout << "Tree"; break;
			default:			cout << "Graph"; break;
		}
		cout << ". Weight: " << g.weight << ". Size: " << g.size << "." << endl;
	}
}

NodeRecognition::~NodeRecognition() = default;