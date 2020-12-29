//�����������ص�һ����ÿ���µ�ƽ������
//ʹ����״ͼ��ʾ��ͬʱ����ʵ����ͬһ��ͼ��
//����Ϊ�·ݣ�����Ϊ�¶ȣ�ע�������ᡢ��ǩ����ɫ��ʹ�á�

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities

#define READING_YEAR 2016					// ��ȡ���
#define MAX_TEMP 32							// ƽ�����

// �洢�����ݽṹ
struct AvgTemp {
	int year, month, day;			// ����
	double tempAvg;					// ƽ���¶�
};

class CityAvgTemp {
	// ���ݽṹ��year/month/day, tempAvg,\n
	friend istream& operator>>(istream& is, AvgTemp& a);
public:
	CityAvgTemp(string file_name);
	~CityAvgTemp();
	// �õ�����
	double proportion(int month);
private:
	double monthAvg[13] = { 0 };		// ʮ�����µ�ƽ���¶ȣ��� 0 ������
};
