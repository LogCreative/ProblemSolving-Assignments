#include "Question_1.h"

boat::boat(int _w, int _n): w(_w), n(_n) {
	weights = new int[n];
	arrange = new bool[n];
	for (int i = 0; i < n; ++i) {
		int _weight;
		cin >> _weight;
		if (_weight <= 0) errorlevel = 2;							//小于等于0
		else if (_weight > w && errorlevel == 0) errorlevel = 1;
		weights[i] = _weight;
	}
}

int divide(int a[], int low, int high) {
	int k = a[low];
	do {
		while (low < high && a[high] >= k) --high;
		if (low < high) { a[low] = a[high]; ++low; }
		while (low < high && a[low] <= k) ++low;
		if (low < high) { a[high] = a[low]; --high; }
	} while (low != high);
	a[low] = k;
	return low;
}

void quickSort(int a[], int low, int high) {
	int mid;
	if (low >= high) return;
	mid = divide(a, low, high);
	quickSort(a, low, mid - 1);
	quickSort(a, mid + 1, high);
}

// 快速排序
void quickSort(int a[], int size) {
	quickSort(a, 0, size - 1);
}

void boat::getBoatNum() {
	// 若有乘客体重超出独木舟可承载的最大量则输出：out
	// 若输入体重中存在小于等于0的值则输出：error
	// 若同时存在体重小于等于0的输入与超出承载量的输入则输出 : error
	if (errorlevel > 0) {
		if (errorlevel == 1) cout << "out" << endl;
		else cout << "error" << endl;
		return;
	}

	// 快速排序
	quickSort(weights, n);

	// 存储是否已经安排
	for (int i = 0; i < n; ++i) arrange[i] = false;

	// 输出个数
	int boatNum = 0;

	// 一条独木舟最多只能乘坐两人，且乘客的总重量不能超过独木舟的最大承载量。
	for (int i = n - 1; i >= 0; --i) {			//从最大的开始安排
		if (arrange[i]) continue;				//安排过将继续寻找
		int remain = w - weights[i];
		arrange[i] = true;
		for (int j = i - 1; j >= 0; --j) {
			if (arrange[j]) continue;
			if (weights[j] <= remain) {
				arrange[j] = true;				//找到配对
				break;
			}
		}
		++boatNum;								// 不论有无配对，都要加一艘船
	}

	//for (int i = n - 1, j = 0; i >= j; --i) {
	//	if (i == j) { ++boatNum; break; }		//只剩一个人
	//	if (weights[i] + weights[j] <= w) ++j;
	//	++boatNum;
	//}

	cout << boatNum << endl;
}

boat::~boat() {
	delete[] weights;
	delete[] arrange;
}