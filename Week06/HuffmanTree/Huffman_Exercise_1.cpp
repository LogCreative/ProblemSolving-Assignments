#include "Huffman_Exercise_1.h"

Huffman::Huffman(string str) {
	map<char, int> qmap;
	for (auto c : str) ++qmap[c];
	for (auto p : qmap) qchar.push(new TreeNode(p.first, p.second));
	encode();
}

void Huffman::encode() {
	while (qchar.size() > 1) {
		TreeNode* l = qchar.top(); qchar.pop();
		TreeNode* r = qchar.top(); qchar.pop();
		qchar.push(new TreeNode(l, r));
	}
}

// 我们可以用一种巧妙的方法修改 BFS 来层序遍历：
// 1. 首先根元素入队
// 2. 当队列不为空的时候 求当前队列的长度 s_is 
//	依次从队列中取 s_i 个元素进行拓展，然后进入下一次迭代

int Huffman::getSize() {
	// 长度计数
	int length = 0;

	// 如果队列没有元素，没有编码长度
	if (qchar.empty()) return 0;

	// 如果队列只有一个元素，根节点不是虚节点，则只有一个编码即可
	// 否则根节点一定是虚节点，根节点不计入编码
	if (qchar.top()->ch) return qchar.top()->freq;

	// 层序遍历树，需要知道层数
	// 读到非虚节点，计数
	queue<TreeNode*> tq;
	TreeNode* tf;
	int layer = 0;
	tq.push(qchar.top());	// 根入队
	while (!tq.empty()) {
		int currentLevelSize = tq.size();
		for (int i = 0; i < currentLevelSize; ++i) {
			tf = tq.front(); tq.pop();
			if (tf->ch) length += tf->freq * layer;
			if (tf->left) tq.push(tf->left);
			if (tf->right) tq.push(tf->right);
		}
		++layer;
	}
	return length;
}

Huffman::~Huffman() = default;