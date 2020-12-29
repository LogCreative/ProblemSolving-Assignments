// ����һ���ı���������ĸ���ŵĳ��ִ������ı�����Huffman���룬�����������ı���λ����
// ��������ĸ���壺��Сд��ĸ���ո񡢻س������ּ����������ŵȡ�������ǽ�������ASCII�룻��Сд��ĸΪ��ͬ��ĸ��

#include "std_lib_facilities.h"

class Huffman {
public:
	Huffman(string);
	~Huffman();
	// ��ȡ����λ��
	int getSize();
private:
	//����
	void encode();

	// Huffman ���ڵ�
	struct TreeNode
	{
		char ch;
		int freq;
		TreeNode* left, * right;

		// Ĭ�Ϲ��캯��
		TreeNode() : ch(0), freq(0), left(NULL), right(NULL) {}
		// �½ڵ�
		TreeNode(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
		// Huffman ��ڵ�, NULL ���� ch �ϻᱨ��
		TreeNode(TreeNode* l, TreeNode* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {}
		// ��������
		~TreeNode() {}
	};

	// �ȽϷ�������
	struct cmp {
		bool operator()(TreeNode* left, TreeNode* right) {
			return left->freq > right->freq;
		}
	};

	// ���ڵ�����ȶ��У���������
	priority_queue<TreeNode*, vector<TreeNode*>, cmp> qchar;
};