// ����һ������a[1],a[2],a[3],a[4],......a[n],���������������С�

#include "std_lib_facilities.h"
#define MAXLINE 100000

class subsequence {
public:
	subsequence(int n);
	void getMaxSequence();
	~subsequence();
private:
	int n;						// 1<=n<=100000
	int* a;						// �洢����
	bool error = false;			// �쳣
};
