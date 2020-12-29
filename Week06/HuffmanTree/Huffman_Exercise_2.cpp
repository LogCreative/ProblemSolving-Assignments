#include "Huffman_Exercise_2.h"

Huffman2::Huffman2(string str) {
	// ���룺 Ӣ���ı���������������������������500����
	//��1�������У����Ե��ʽ��й��������룻

	map<string, int> wmap;				// ���ʴʵ�

	string word = "";					// ����
	for (auto c : str) {
		// ����Сд��ͬ <��>������ͬ���ʡ�
		if (isalpha(c))
			word += c;					// �������֧�ֶ���������ĸ��ϳɵ���
		else {
			// �ָ�����洢�ǿյ���
			if (!word.empty()) ++wmap[word];
			++cmap[c];					// �洢�ָ���
			word.clear();				// ��յ���
		}
	}
	if (!word.empty()) ++wmap[word];	// �������ʣ��ĵ�����Ҫ��¼

	for (auto p : wmap) qword.push(new TreeNode(p.first, p.second));
	encode();
}

// Huffman ����
void Huffman2::encode() {
	while (qword.size() > 1) {
		TreeNode* l = qword.top(); qword.pop();
		TreeNode* r = qword.top(); qword.pop();
		qword.push(new TreeNode(l, r));
	}
}

int Huffman2::getSize() {
	// ����� ����ö��ı��ı��볤�ȡ�
	//��2�������ı��ı��볤�ȣ����У��ı��еķ���ĸ�ĵ����ַ��ı��볤�ȹ̶�Ϊ8 bit��

	// ���ȼ���
	int length = 0;

	// ��ʼ�����ȼ���Ϊ����ĸ�����ַ��ı��볤�Ⱥ�
	for (auto p : cmap)
		length += p.second;
	length *= 8;

	// �������û��Ԫ�أ����ش�����볤��
	if (qword.empty()) return length;

	// �������ֻ��һ��Ԫ�أ����ڵ㲻����ڵ㣬��ֻ��һ�����뼴��
	// ������ڵ�һ������ڵ㣬���ڵ㲻�������
	if (!qword.top()->word.empty()) return qword.top()->freq + length;

	// �������������Ҫ֪������
	// ��������ڵ㣬����
	queue<TreeNode*> tq;
	TreeNode* tf;
	int layer = 0;
	tq.push(qword.top());	// �����
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