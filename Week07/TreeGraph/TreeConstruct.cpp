#include"TreeConstruct.h"

TreeIsotope::TreeIsotope(string str1, string str2) {
	// 数的节点由字母表示，
	// 且已知所有节点输入都能构成树（测试中树的层数不超过10层）

	char nidl = '\0';			// 左节点标识符
	char nidr = '\0';			// 右节点标识符

	for (int o = 1; o <= 2; ++o) {
		string rstr = (o == 1) ? str1 : str2;
		char prev = '\0';			// 上一个读取
		for (auto c : rstr) {
			if (isalpha(c)) {
				if (prev == '<')		nidl = c;
				else if (prev == ' ')	nidr = c;
			}
			else if (c == '>' && prev != '<') {	// 结束该节点的读取，空节点跳过读入
				if (o == 1) treePairs1.push_back(make_pair(nidl, nidr));
				else treePairs2.push_back(make_pair(nidl, nidr));
				nidl = '\0'; nidr = '\0';			// 复位
			}
			prev = c;
		}
	}

	treeConstruct();
}

void TreeIsotope::treeConstruct() {
	for (int o = 1; o <= 2; ++o) {
		// 处理中的树对变量
		vector<pair<char, char>> treePairs = o == 1 ? treePairs1 : treePairs2;
		// 延迟删除
		vector<vector<pair<char, char>>::iterator> delPairs;
		// 寻找树根
		TreeNode*& root = o == 1 ? root1 : root2;
		for (auto i = treePairs.begin(); i != treePairs.end(); ++i) {
			if (i->second == '\0') {
				root = new TreeNode(i->first);
				delPairs.push_back(i);
				break;
			}
		}
		// 输入中非必须出现根节点
		// 如果为空根 需要手动寻找
		// cout << int(root->val) << endl;
		// if (root->val==-24) {
		if (root == NULL) {
			set<char> fathers;
			for (auto i = treePairs.begin(); i != treePairs.end(); ++i)
				fathers.insert(i->second);
			for (auto j = fathers.begin(); j != fathers.end(); ++j) {
				bool flag = false;
				for (auto i = treePairs.begin(); i != treePairs.end(); ++i)
					if (i->first == *j) { flag = true; break; }
				if (!flag) {
					root = new TreeNode(*j);
					break;
				}
			}
		}
		// 层序遍历 BFS
		// 访问队列
		queue<TreeNode*> visitQ;
		visitQ.push(root);
		TreeNode* tn, * nc;
		while (!visitQ.empty()) {
			tn = visitQ.front(); visitQ.pop();
			for (auto i = treePairs.begin(); i != treePairs.end(); ++i) {
				if (find(delPairs.begin(), delPairs.end(), i) != delPairs.end()) continue;		//已经被删除的树对
				if (i->second == tn->val) {
					nc = new TreeNode(i->first);
					tn->children.push_back(nc);
					visitQ.push(nc);
					delPairs.push_back(i);
				}
			}
		}
	}
}

int TreeIsotope::getLayer(TreeNode* t) {
	if (t == NULL) return 0;
	if (t->children.empty()) return 1;
	int layer = 0;
	for (auto i = t->children.begin(); i != t->children.end(); ++i)
		layer = max(getLayer(*i), layer);
	return layer + 1;
}

void TreeIsotope::prtLayer() {
	layer1 = getLayer(root1);
	layer2 = getLayer(root2);
	cout << layer1 << ' ' << layer2 << endl;
}

// 比较函数的降序排列
bool TCodeCmp(string left, string right) {
	if (left.size() == right.size()) return stoi(left) > stoi(right);
	return left.size() > right.size();
}

string TreeIsotope::getTCode(TreeNode* t) {
	if (t == NULL) return "";
	if (t->children.empty()) return "10";
	vector<string> ahuNames;
	for (auto i = t->children.begin(); i != t->children.end(); ++i)
		ahuNames.push_back(getTCode(*i));
	sort(ahuNames.begin(), ahuNames.end(), TCodeCmp);
	string TCode = "";
	for (auto i = ahuNames.begin(); i != ahuNames.end(); ++i)
		TCode = TCode + *i;
	return "1" + TCode + "0";
}

void TreeIsotope::prtTCode() {
	TCode1 = getTCode(root1);
	TCode2 = getTCode(root2);
	cout << TCode1 << ' ' << TCode2 << endl;
}

void TreeIsotope::prtRes() {
	if (layer1 == layer2 && TCode1 == TCode2) cout << "Yes" << endl;
	else cout << "No" << endl;
}

TreeIsotope::~TreeIsotope() = default;