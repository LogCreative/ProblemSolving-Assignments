// 输入一段文本，根据字母符号的出现次数对文本进行Huffman编码，并输出编码后文本的位长。
// 本题中字母定义：大小写字母、空格、回车、数字及其它标点符号等。这里，我们仅仅包含ASCII码；大小写字母为不同字母。

#include "std_lib_facilities.h"

class Huffman {
public:
	Huffman(string);
	~Huffman();
	// 获取编码位长
	int getSize();
private:
	//编码
	void encode();

	// Huffman 树节点
	struct TreeNode
	{
		char ch;
		int freq;
		TreeNode* left, * right;

		// 默认构造函数
		TreeNode() : ch(0), freq(0), left(NULL), right(NULL) {}
		// 新节点
		TreeNode(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
		// Huffman 虚节点, NULL 赋予 ch 上会报错。
		TreeNode(TreeNode* l, TreeNode* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {}
		// 析构函数
		~TreeNode() {}
	};

	// 比较仿生函数
	struct cmp {
		bool operator()(TreeNode* left, TreeNode* right) {
			return left->freq > right->freq;
		}
	};

	// 树节点的优先队列，升序排列
	priority_queue<TreeNode*, vector<TreeNode*>, cmp> qchar;
};