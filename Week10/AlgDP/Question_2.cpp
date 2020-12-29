#include "Question_2.h"

subsequence::subsequence(int _n) : n(_n), a(new int[n]) {
	if (n > MAXLINE) { error = true; return; }
	int _a;
	int i = 0;
	// 若输入序列中的数值超出[-1000,1000]范围或序列长度不符合规范（n大于100000或n与序列长度不等），则输出error。
	while (cin >> _a) {
		if (i >= n || _a < -1000 || _a > 1000) { error = true; return; }
		a[i] = _a;
		++i;
	}
}

void subsequence::getMaxSequence() {
	if (error) { cout << "error" << endl; return; }
	// 考虑性质：如果一个子序列的和为负，不可能是最大连续子序列的一部分。
	// 设f[x]是以a[x]终止且包含a[x]的最大序列的和
	int* f = new int[n];
	int* b = new int[n];
	f[0] = a[0];
	b[0] = 0;
	for (int i = 1; i < n; ++i) {
		if (f[i - 1] > 0) {				// f[i-1] + a[i] > a[i]
			f[i] = f[i - 1] + a[i];
			b[i] = b[i - 1];
		}
		//若在序列中有两个最大和序列，则输出第一个最大和序列的起始位置和结束位置。
		else if (f[i - 1] == 0) {
			f[i] = f[i - 1] + a[i];
			b[i] = (i > b[i - 1]) ? b[i - 1] : i;
		}
		else {
			f[i] = a[i];
			b[i] = i;
		}
	}

	int maxf = f[0], maxptr = 0;
	for (int i = 1; i < n; ++i) {
		if (f[i] > maxf) {
			maxf = f[i];
			maxptr = i;
		}
	}

	// 输出为一行，包括三个数字，分别为子串的最大和、子串在序列中的起始位置、子串在序列中的终止位置.
	cout << maxf << ' ' << b[maxptr] + 1 << ' ' << maxptr + 1 << endl;

}

subsequence::~subsequence() {
	delete[] a;
}