#include "NodeRecognition.h"

NodeRecognition::NodeRecognition(string str) {
	// һ�����������нڵ���뵥���ڵ�ĸ����Ͳ�����100��������0����
	// �ڵ���ܲ���ͨ��

	int nidl = 0;					// ��ڵ��ʶ��
	int nidr = 0;					// �ҽڵ��ʶ��

	// ����״̬
	// outside:		����״̬��
	// left:		��ڵ�����
	// right:		�ҽڵ�����
	enum inputStates { outside, left, right };
	
	// ����״̬
	enum inputStates inputState = outside;

	char prev = '\0';

	for (auto c : str) {
		switch (c) {
			case '<':				// ����
				inputState = left;	
				break;
			case '>':				// ����
				// Ϊ�˷�����㣬ÿ���ڵ�ʹ��Ψһ����Ȼ����ʾ������Ȼ��ͬʱ����ڵ��Ȩ�أ�
				// ���Դ��ڵ��� 0���սڵ�ʹ�� -1 ��ʶ
				if (inputState == left) nidr = -1;
				// ����<>���룺����0��
				if (prev != '<') {
					// �洢�ڵ��
					nodePairs.insert(make_pair(nidl, nidr));
					// �洢�����Ľڵ�
					nodeContains.insert(nidl);
					if (nidr != -1) nodeContains.insert(nidr);
				}
				// ��ʼ������
				nidl = 0; nidr = 0; inputState = outside;
				break;
			case ' ':				// �ָ�
				if (inputState > 0) inputState = right;
				break;
			default:				// ����
				if (c >= '0' && c <= '9') {
					if (inputState == left)
						nidl = nidl * 10 + c - '0';
					else if (inputState == right)
						nidr = nidr * 10 + c - '0';
				}
				break;
		}
		prev = c;
	}

	graphRecognite();
}

void NodeRecognition::graphRecognite() {
	// �����ڵ㣺ֻ��һ�� <Node>����������޷��ҵ��ýڵ�
	// ���������ڵ���������������
	// һ�������ڵ��в�ֹ��������
	// ͼ���л�·
	// ���ʺ󼴱�ɾ��

	// �洢�Ѿ�ɾ���Ľڵ�
	vector<set<pair<int, int>>::iterator> deliters;

	for (auto i = nodePairs.begin(); i != nodePairs.end(); i++) {
		if (find(deliters.begin(), deliters.end(), i) != deliters.end()) continue;	//ɾ����Ľڵ㼴����
		if (i->second == -1) { // �����ڵ㣬����ڵ�
			graph g;					// ��ʱ�洢��ͼ
			g.weight += i->first; g.size += 1;

			// ��ͼ�Ľڵ���ʶ���
			queue<int> nodeQ;
			nodeQ.push(i->first);

			deliters.push_back(i);

			while (!nodeQ.empty()) {
				int father = nodeQ.front(); nodeQ.pop();
				// ����Ϊ���ʹ������Ӱ����Ľڵ���ɾ��
				nodeContains.erase(father);

				int sonNum = 0;	//������

				for (auto j = nodePairs.begin(); j != nodePairs.end(); j++) {
					if (find(deliters.begin(), deliters.end(), j) != deliters.end()) continue;
					if (j->second == father) {		// j ���� father �Ķ���
						++sonNum;

						if (nodeContains.find(j->first) != nodeContains.end()) {
							nodeQ.push(j->first);	// ��δ���ʹ���������ʶ���
							g.weight += j->first; g.size += 1;
							nodeContains.erase(j->first);
						}
						else g.graphType = Graph;	// ���ӽڵ��Ѿ������ʹ����γɻ�·��Ϊһ��ͼ
						
						deliters.push_back(j);
					}
				}

				// �������������ȼ�
				if (g.graphType < BinaryTree && (sonNum == 1 || sonNum == 2))  g.graphType = BinaryTree;
				else if (g.graphType < Tree && sonNum>2) g.graphType = Tree;
			}

			graphs.push(g);	// ����ͼ
		}
	}

	// ��Ȼʣ������ ���ǳɶԳ��� ��ζ��Ϊһ��ͼ ֻ��Ҫ������ͨ��ϵ���� ��Ҫ���еڶ���ѭ��
	// ����õ����ڵ�����ͨ�ĵĽڵ㼯�ϱ�ʶ��Ϊһ��ͼ������ͼ����ڵ㡢���ӹ�ϵ��������صĸ������������������Ϊһ���ͼ�ڵ�����ͨ��ϵ��
	// ������ù������������BFS��
	for (auto i = nodePairs.begin(); i != nodePairs.end() && nodePairs.size() > deliters.size(); i++) {
		if (find(deliters.begin(), deliters.end(), i) != deliters.end()) continue;	//ɾ����Ľڵ㼴����
		// �ӵ�ǰ�ĶԿ�ʼ����ͼ�����׿�ʼ
		if (nodeContains.find(i->second) != nodeContains.end()) {
			graph g(Graph, i->second, 1);
			queue<int> nodeQ;
			nodeQ.push(i->second);
			nodeContains.erase(i->second);
			while (!nodeQ.empty()) {
				int father = nodeQ.front(); nodeQ.pop();
				for (auto j = nodePairs.begin(); j != nodePairs.end(); j++) {
					if (find(deliters.begin(), deliters.end(), j) != deliters.end()) continue;
					int son = -1;
					if (j->first == father) son = j->second;
					else if (j->second == father) son = j->first;
					if (son != -1 && nodeContains.find(son) != nodeContains.end()) {
						nodeQ.push(son);	// ��δ���ʹ���������ʶ���
						g.weight += son; g.size += 1;
						deliters.push_back(j);
						// ����Ϊ���ʹ������Ӱ����Ľڵ���ɾ��
						nodeContains.erase(son);
					}
				}
			}
			graphs.push(g);	// ����ͼ
		}
	}
}

void NodeRecognition::prtStruct() {
	// Ӣ���﷨����
	cout << "We have recognized " << graphs.size() << ((graphs.size() <= 1)?" graph.":" graphs.") << endl;
	while (!graphs.empty()) {
		auto g = graphs.top(); graphs.pop();
		cout << "--";
		switch (g.graphType) {
			case Node:			cout << "Node"; break;
			case BinaryTree:	cout << "Binary tree"; break;
			case Tree:			cout << "Tree"; break;
			default:			cout << "Graph"; break;
		}
		cout << ". Weight: " << g.weight << ". Size: " << g.size << "." << endl;
	}
}

NodeRecognition::~NodeRecognition() = default;