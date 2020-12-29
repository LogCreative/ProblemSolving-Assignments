#include "Question_2.h"

subsequence::subsequence(int _n) : n(_n), a(new int[n]) {
	if (n > MAXLINE) { error = true; return; }
	int _a;
	int i = 0;
	// �����������е���ֵ����[-1000,1000]��Χ�����г��Ȳ����Ϲ淶��n����100000��n�����г��Ȳ��ȣ��������error��
	while (cin >> _a) {
		if (i >= n || _a < -1000 || _a > 1000) { error = true; return; }
		a[i] = _a;
		++i;
	}
}

void subsequence::getMaxSequence() {
	if (error) { cout << "error" << endl; return; }
	// �������ʣ����һ�������еĺ�Ϊ������������������������е�һ���֡�
	// ��f[x]����a[x]��ֹ�Ұ���a[x]��������еĺ�
	int* f = new int[n];
	int* b = new int[n];
	f[0] = a[0];
	b[0] = 0;
	for (int i = 1; i < n; ++i) {
		if (f[i - 1] > 0) {				// f[i-1] + a[i] > a[i]
			f[i] = f[i - 1] + a[i];
			b[i] = b[i - 1];
		}
		//�����������������������У��������һ���������е���ʼλ�úͽ���λ�á�
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

	// ���Ϊһ�У������������֣��ֱ�Ϊ�Ӵ������͡��Ӵ��������е���ʼλ�á��Ӵ��������е���ֹλ��.
	cout << maxf << ' ' << b[maxptr] + 1 << ' ' << maxptr + 1 << endl;

}

subsequence::~subsequence() {
	delete[] a;
}