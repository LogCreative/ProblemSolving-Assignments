// �޸�ǰ��������������֧�ֶ���������ĸ��ϳɵ��ʣ������ù���������ѹ���ı�������������ı����ȡ�

#include "std_lib_facilities.h"

class Huffman2 {
public:
	Huffman2(string);
	~Huffman2();
	int getSize();
private:
	//����
	void encode();

	// Huffman ���ڵ㣨����״��
	struct TreeNode
	{
		string word;
		int freq;
		TreeNode* left, * right;

		// "" �ǳ���Ϊ 0 ���ַ�������������Ϊ�ա�

		// Ĭ�Ϲ��캯��
		TreeNode() : word(""), freq(0), left(NULL), right(NULL) {}
		// �½ڵ�
		TreeNode(string w, int f) : word(w), freq(f), left(NULL), right(NULL) {}
		// Huffman ��ڵ�, NULL ���� ch �ϻᱨ��
		TreeNode(TreeNode* l, TreeNode* r) : word(""), freq(l->freq + r->freq), left(l), right(r) {}
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
	priority_queue<TreeNode*, vector<TreeNode*>, cmp> qword;

	// ����ĸ�ĵ����ַ��������� Huffman ����
	map<char, int> cmap;
};
