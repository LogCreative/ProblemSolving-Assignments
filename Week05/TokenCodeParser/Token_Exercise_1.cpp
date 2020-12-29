#include "Token_Exercise_1.h"

Token::Token(string str) {
	// 空格与任何单独的标点不为单词；

	// （空格）_（空格） 与  （空格）-（空格）不为单词；
	// a_b记作一个单词；
	// a-b记作一个单词；
	// A_C与a_c记作同一个单词。

	string word = "";					//单词
	for (auto c : str) {
		// 仅大小写不同 看作相同单词。
		// 统一转换为小写字母
		if (c >= 'A' && c <= 'Z')
			word += tolower(c);
		else if ((c >= 'a' && c <= 'z') || (c>='0' && c<='9'))
			word += c;
		else {
			switch (c)
			{
			case '-': case '_':
				word += c;
				break;
			case ' ': default:
				// 空格或标点（除连字符 - 下划线_外）均作为单词间的分割标志
				// a—（空格）与a_（空格）为单词a。
				if (!word.empty() && (*(word.end() - 1) == '-' || *(word.end() - 1) == '_')) 
					word.pop_back();
				if (!word.empty()) 
					text.push_back(word);
				word = "";
				break;
			}
		}
	}

};

void Token::find(string fstr) {
	string word = "";
	string fword = "";
	for (auto c : fstr) {
		if (c == ' ') {
			fgroup.push_back(wfreq(word, strcmp_sort(fword)));
			word = "";
			fword = "";
		}
		else {
			word += c;
			fword += tolower(c);
		}
	}
}

int Token::strcmp_sort(string fword) {
	int cnt = 0;
	for (auto w : text) 
		if (w == fword) 
			++cnt;
	return cnt;
}

void Token::print() {
	for (auto it = fgroup.begin(); it != fgroup.end(); ++it)
		cout << '(' << it->word << ',' << it->freq << ")" <<
			(it == fgroup.end() - 1 ? "" : " ");
}