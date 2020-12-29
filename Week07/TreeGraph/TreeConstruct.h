// 现给定两棵树，请输出该树的层数（两个树层数相同）；
// 根节点的编码（根据AHU algorithm）；判断是否同构。
// 不一定是二叉树

#include"std_lib_facilities.h"

class TreeIsotope {
public:
	TreeIsotope(string, string);
	~TreeIsotope();

	// 输出第一行树的层数与第二行树的层数；
	void prtLayer();
	// 分别输出第一行所构成树的根节点0/1编码与第二行所构成树的根节点0/1编码；
	void prtTCode();
	// 判断两个树是否同构，同构输出: Yes , 否则输出: No 。
	void prtRes();

private:
	vector<pair<char, char>> treePairs1;		// 第一棵树的节点
	vector<pair<char, char>> treePairs2;		// 第二棵树的节点

	struct TreeNode
	{
		char val;								// 数值
		vector<TreeNode*> children;				// 儿子

		// 构造函数，修改儿子需要访问修改
		TreeNode(char c) :val(c) {}
		~TreeNode() {}
	};

	TreeNode* root1 = NULL;						// 第一棵树的树根，需要初始化变量为空，否则为随机值
	TreeNode* root2 = NULL;						// 第二棵树的树根，需要初始化变量为空，否则为随机值

	int layer1;									// 第一棵树的层数
	int layer2;									// 第二棵树的层数

	string TCode1;								// 第一棵树的树码
	string TCode2;								// 第二棵树的树码

	// 构建树以存储
	void treeConstruct();

	// 获取层数
	int getLayer(TreeNode*);
	// 获取树码
	string getTCode(TreeNode*);
};