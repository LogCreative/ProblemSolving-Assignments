// 给出一个序列a[1],a[2],a[3],a[4],......a[n],计算其最大和子序列。

#include "std_lib_facilities.h"
#define MAXLINE 100000

class subsequence {
public:
	subsequence(int n);
	void getMaxSequence();
	~subsequence();
private:
	int n;						// 1<=n<=100000
	int* a;						// 存储序列
	bool error = false;			// 异常
};
