// ����ʽҪ������������ʵĳ��ִ�����

#include "std_lib_facilities.h"

struct wfreq
{
    string word;
    int freq;

    wfreq(string w,int f):word(w),freq(f){}
};

class Token {
    // �ı�����
    vector<string> text;
    vector<wfreq> fgroup;
public:
    // ���캯��
    // ��һ�У� Ӣ���ı����������������ĵ�����������200����
    Token(string str);

    // Ѱ�ҵ���
    void find(string fstr);
    
    // �ַ����Ƚϲ�����
    int strcmp_sort(string fstr);
    
    // ������������ʵĳ��ִ�����
    // ���֮���Կո������
    void print();

};
