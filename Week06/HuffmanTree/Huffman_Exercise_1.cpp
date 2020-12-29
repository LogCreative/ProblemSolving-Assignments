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

// ���ǿ�����һ������ķ����޸� BFS �����������
// 1. ���ȸ�Ԫ�����
// 2. �����в�Ϊ�յ�ʱ�� ��ǰ���еĳ��� s_is 
//	���δӶ�����ȡ s_i ��Ԫ�ؽ�����չ��Ȼ�������һ�ε���

int Huffman::getSize() {
	// ���ȼ���
	int length = 0;

	// �������û��Ԫ�أ�û�б��볤��
	if (qchar.empty()) return 0;

	// �������ֻ��һ��Ԫ�أ����ڵ㲻����ڵ㣬��ֻ��һ�����뼴��
	// ������ڵ�һ������ڵ㣬���ڵ㲻�������
	if (qchar.top()->ch) return qchar.top()->freq;

	// �������������Ҫ֪������
	// ��������ڵ㣬����
	queue<TreeNode*> tq;
	TreeNode* tf;
	int layer = 0;
	tq.push(qchar.top());	// �����
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