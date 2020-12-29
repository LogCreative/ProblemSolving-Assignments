#include "Question_3.h"

palindrome::palindrome(string _str): str(_str), n(_str.length()) {}

void palindrome::getResNum() {
	// f[i][j]��ʾstr�ĵ�i���ַ�����j���ַ���ɵ��Ӵ�����Ļ������г���Ϊ���١�
	int** f = new int* [n];
	for (int i = 0; i < n; ++i) {
		f[i] = new int[n];
		for (int j = 0; j < n; ++j)
			f[i][j] = 0;					// ��ʼ�����㣬���½Ǳض�Ϊ0
	}

	//ע�����˳��i �����һ���ַ���ʼ��ǰ������j �� i + 1 ��ʼ����������������Ա�֤ÿ�������ⶼ�Ѿ�����ˡ������ҷ����λ���Ѿ������������ֻ��б�ű������߷��ű���.
	for (int i = n - 1; i >= 0; --i) {
		f[i][i] = 1;						//���ַ�����
		for (int j = i + 1; j < n; ++j) {
			if (str[j] == str[i])							//���i��j��ͬ��
				f[i][j] = f[i + 1][j - 1] + 2;				//����ֵ�Ļ����ϼ�2��
			else											//���i��j��ͬ��
				f[i][j] = max(f[i + 1][j], f[i][j - 1]);	//ȡ���Ӵ������Ӵ��е����ֵ��
		}
	}

	cout << f[0][n - 1] << endl;
	
	for (int i = 0; i < n; ++i)
		delete[] f[i];
	delete[] f;
}

void palindrome::getRes() {
	// ���г���Ϊ1���ַ������ǻ���
	if (n == 1) { cout << str << endl; return; }
	
	vector<vector<string>> fstr(n, vector<string>(n, ""));	//��ʼ��
	
	for (int i = n - 1; i >= 0; --i) {
		//�����ַ����ĶԳ����Ŀ��ܲ�ֹ����һ���ַ������� abcdba��cdΪabba�ĶԳ����ģ���˽�����ַ����л��Ĳ����ַ������ｫ�����趨Ϊ�գ�����֮ǰ�Ѿ���ʼ��������������Բ����ٴθ�ֵ��
		// fstr[i][i] = "";
		for (int j = i + 1; j < n; ++j) {
			if (str[j] == str[i])
				fstr[i][j] = str[i] + fstr[i + 1][j - 1] + str[j];
			else {
				if (fstr[i + 1][j].length() >= fstr[i][j - 1].length())
					fstr[i][j] = fstr[i + 1][j];
				else fstr[i][j] = fstr[i][j - 1];
			}
		}
	}

	cout << fstr[0][n - 1] << endl;
}

palindrome::~palindrome() = default;