#include "Question_3.h"

palindrome::palindrome(string _str): str(_str), n(_str.length()) {}

void palindrome::getResNum() {
	// f[i][j]表示str的第i个字符至第j个字符组成的子串，最长的回文序列长度为多少。
	int** f = new int* [n];
	for (int i = 0; i < n; ++i) {
		f[i] = new int[n];
		for (int j = 0; j < n; ++j)
			f[i][j] = 0;					// 初始化置零，左下角必定为0
	}

	//注意遍历顺序，i 从最后一个字符开始往前遍历，j 从 i + 1 开始往后遍历，这样可以保证每个子问题都已经算好了。左下右方向的位置已经被计算出来，只能斜着遍历或者反着遍历.
	for (int i = n - 1; i >= 0; --i) {
		f[i][i] = 1;						//单字符回文
		for (int j = i + 1; j < n; ++j) {
			if (str[j] == str[i])							//如果i和j相同，
				f[i][j] = f[i + 1][j - 1] + 2;				//在内值的基础上加2；
			else											//如果i和j不同，
				f[i][j] = max(f[i + 1][j], f[i][j - 1]);	//取左子串和右子串中的最大值。
		}
	}

	cout << f[0][n - 1] << endl;
	
	for (int i = 0; i < n; ++i)
		delete[] f[i];
	delete[] f;
}

void palindrome::getRes() {
	// 所有长度为1的字符串都是回文
	if (n == 1) { cout << str << endl; return; }
	
	vector<vector<string>> fstr(n, vector<string>(n, ""));	//初始化
	
	for (int i = n - 1; i >= 0; --i) {
		//由于字符串的对称中心可能不止存在一个字符，例如 abcdba，cd为abba的对称中心，因此仅输出字符串中回文部分字符。这里将自身设定为空，由于之前已经初始化，所以这里可以不用再次赋值。
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