// �ָ���������������������Ĳ�����������������ͬ����
// ���ڵ�ı��루����AHU algorithm�����ж��Ƿ�ͬ����
// ��һ���Ƕ�����

#include"std_lib_facilities.h"

class TreeIsotope {
public:
	TreeIsotope(string, string);
	~TreeIsotope();

	// �����һ�����Ĳ�����ڶ������Ĳ�����
	void prtLayer();
	// �ֱ������һ�����������ĸ��ڵ�0/1������ڶ������������ĸ��ڵ�0/1���룻
	void prtTCode();
	// �ж��������Ƿ�ͬ����ͬ�����: Yes , �������: No ��
	void prtRes();

private:
	vector<pair<char, char>> treePairs1;		// ��һ�����Ľڵ�
	vector<pair<char, char>> treePairs2;		// �ڶ������Ľڵ�

	struct TreeNode
	{
		char val;								// ��ֵ
		vector<TreeNode*> children;				// ����

		// ���캯�����޸Ķ�����Ҫ�����޸�
		TreeNode(char c) :val(c) {}
		~TreeNode() {}
	};

	TreeNode* root1 = NULL;						// ��һ��������������Ҫ��ʼ������Ϊ�գ�����Ϊ���ֵ
	TreeNode* root2 = NULL;						// �ڶ���������������Ҫ��ʼ������Ϊ�գ�����Ϊ���ֵ

	int layer1;									// ��һ�����Ĳ���
	int layer2;									// �ڶ������Ĳ���

	string TCode1;								// ��һ����������
	string TCode2;								// �ڶ�����������

	// �������Դ洢
	void treeConstruct();

	// ��ȡ����
	int getLayer(TreeNode*);
	// ��ȡ����
	string getTCode(TreeNode*);
};