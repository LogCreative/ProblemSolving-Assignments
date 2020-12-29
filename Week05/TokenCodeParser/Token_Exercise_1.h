// 按格式要求输出给定单词的出现次数；

#include "std_lib_facilities.h"

struct wfreq
{
    string word;
    int freq;

    wfreq(string w,int f):word(w),freq(f){}
};

class Token {
    // 文本内容
    vector<string> text;
    vector<wfreq> fgroup;
public:
    // 构造函数
    // 第一行： 英文文本，单个测试用例的单词数不超过200个。
    Token(string str);

    // 寻找单词
    void find(string fstr);
    
    // 字符串比较并分类
    int strcmp_sort(string fstr);
    
    // 输出：给定单词的出现次数：
    // 输出之间以空格隔开。
    void print();

};
