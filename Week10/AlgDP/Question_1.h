// ����д���򣬶����ľ�۵������������ÿ���Ŀ��ÿλ�˿͵�������
// ���ݸ����Ĺ滮���㰲�������ÿͱ�������ٶ�ľ��������

#include "std_lib_facilities.h"

class boat {
public:
	boat(int _w, int _n);
	void getBoatNum();
	~boat();
private:
	int w;						// һ����ľ�۵���������		80<=w<=200
	int n;						// ��Ҫ�˴�������				1<=n<=300
	int* weights;				// n���ÿ͵�����
	bool* arrange;				//�Ƿ��Ѿ�����
	int errorlevel = 0;			// �쳣�ȼ��� 0-������� 1-out 2-error
};
