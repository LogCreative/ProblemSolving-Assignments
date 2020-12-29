// 修改前面的任务，这里，我们支持对连续的字母组合成单词，并利用哈夫曼编码压缩文本，输出编码后的文本长度。

#include "std_lib_facilities.h"

class Huffman2 {
public:
	Huffman2(string);
	~Huffman2();
	int getSize();
private:
	//编码
	void encode();

	// Huffman 树节点（单词状）
	struct TreeNode
	{
		string word;
		int freq;
		TreeNode* left, * right;

		// "" 是长度为 0 的字符串，在这里作为空。

		// 默认构造函数
		TreeNode() : word(""), freq(0), left(NULL), right(NULL) {}
		// 新节点
		TreeNode(string w, int f) : word(w), freq(f), left(NULL), right(NULL) {}
		// Huffman 虚节点, NULL 赋予 ch 上会报错。
		TreeNode(TreeNode* l, TreeNode* r) : word(""), freq(l->freq + r->freq), left(l), right(r) {}
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
	priority_queue<TreeNode*, vector<TreeNode*>, cmp> qword;

	// 非字母的单个字符，不参与 Huffman 编码
	map<char, int> cmap;
};
