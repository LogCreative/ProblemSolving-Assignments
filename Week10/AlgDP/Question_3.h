
#include "std_lib_facilities.h"

class palindrome {
public:
	palindrome(string _str);
	
	// 字符串的最长回文子序列；如有多个长度相同的最长回文字符串，则以最后一个最长回文字符串作为输出。
	void getRes();

	// 得到数字（本题目不使用）
	void getResNum();
	
	~palindrome();
private:
	string str;
	int n;				//字符串长度
};
