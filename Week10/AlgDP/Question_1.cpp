#include "Question_1.h"

boat::boat(int _w, int _n): w(_w), n(_n) {
	weights = new int[n];
	arrange = new bool[n];
	for (int i = 0; i < n; ++i) {
		int _weight;
		cin >> _weight;
		if (_weight <= 0) errorlevel = 2;							//С�ڵ���0
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

// ��������
void quickSort(int a[], int size) {
	quickSort(a, 0, size - 1);
}

void boat::getBoatNum() {
	// ���г˿����س�����ľ�ۿɳ��ص�������������out
	// �����������д���С�ڵ���0��ֵ�������error
	// ��ͬʱ��������С�ڵ���0�������볬������������������� : error
	if (errorlevel > 0) {
		if (errorlevel == 1) cout << "out" << endl;
		else cout << "error" << endl;
		return;
	}

	// ��������
	quickSort(weights, n);

	// �洢�Ƿ��Ѿ�����
	for (int i = 0; i < n; ++i) arrange[i] = false;

	// �������
	int boatNum = 0;

	// һ����ľ�����ֻ�ܳ������ˣ��ҳ˿͵����������ܳ�����ľ�۵�����������
	for (int i = n - 1; i >= 0; --i) {			//�����Ŀ�ʼ����
		if (arrange[i]) continue;				//���Ź�������Ѱ��
		int remain = w - weights[i];
		arrange[i] = true;
		for (int j = i - 1; j >= 0; --j) {
			if (arrange[j]) continue;
			if (weights[j] <= remain) {
				arrange[j] = true;				//�ҵ����
				break;
			}
		}
		++boatNum;								// ����������ԣ���Ҫ��һ�Ҵ�
	}

	//for (int i = n - 1, j = 0; i >= j; --i) {
	//	if (i == j) { ++boatNum; break; }		//ֻʣһ����
	//	if (weights[i] + weights[j] <= w) ++j;
	//	++boatNum;
	//}

	cout << boatNum << endl;
}

boat::~boat() {
	delete[] weights;
	delete[] arrange;
}