
#include "std_lib_facilities.h"

class palindrome {
public:
	palindrome(string _str);
	
	// �ַ���������������У����ж��������ͬ��������ַ������������һ��������ַ�����Ϊ�����
	void getRes();

	// �õ����֣�����Ŀ��ʹ�ã�
	void getResNum();
	
	~palindrome();
private:
	string str;
	int n;				//�ַ�������
};
