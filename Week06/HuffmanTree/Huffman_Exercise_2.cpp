#include "Huffman_Exercise_2.h"

Huffman2::Huffman2(string str) {
	// 输入： 英文文本，单个测试用例单词数不超过500个。
	//（1）本题中，仅对单词进行哈夫曼编码；

	map<string, int> wmap;				// 单词词典

	string word = "";					// 单词
	for (auto c : str) {
		// 仅大小写不同 <不>看作相同单词。
		if (isalpha(c))
			word += c;					// 这里，我们支持对连续的字母组合成单词
		else {
			// 分割符，存储非空单词
			if (!word.empty()) ++wmap[word];
			++cmap[c];					// 存储分隔符
			word.clear();				// 清空单词
		}
	}
	if (!word.empty()) ++wmap[word];	// 如果还有剩余的单词需要记录

	for (auto p : wmap) qword.push(new TreeNode(p.first, p.second));
	encode();
}

// Huffman 编码
void Huffman2::encode() {
	while (qword.size() > 1) {
		TreeNode* l = qword.top(); qword.pop();
		TreeNode* r = qword.top(); qword.pop();
		qword.push(new TreeNode(l, r));
	}
}

int Huffman2::getSize() {
	// 输出： 输出该段文本的编码长度。
	//（2）计算文本的编码长度，其中，文本中的非字母的单个字符的编码长度固定为8 bit。

	// 长度计数
	int length = 0;

	// 初始化长度计数为非字母单个字符的编码长度和
	for (auto p : cmap)
		length += p.second;
	length *= 8;

	// 如果队列没有元素，返回纯粹编码长度
	if (qword.empty()) return length;

	// 如果队列只有一个元素，根节点不是虚节点，则只有一个编码即可
	// 否则根节点一定是虚节点，根节点不计入编码
	if (!qword.top()->word.empty()) return qword.top()->freq + length;

	// 层序遍历树，需要知道层数
	// 读到非虚节点，计数
	queue<TreeNode*> tq;
	TreeNode* tf;
	int layer = 0;
	tq.push(qword.top());	// 根入队
	while (!tq.empty()) {
		int currentLevelSize = tq.size();
		for (int i = 0; i < currentLevelSize; ++i) {
			tf = tq.front(); tq.pop();
			if (!tf->word.empty()) length += tf->freq * layer;
			if (tf->left) tq.push(tf->left);
			if (tf->right) tq.push(tf->right);
		}
		++layer;
	}
	return length;
}

Huffman2::~Huffman2() = default;