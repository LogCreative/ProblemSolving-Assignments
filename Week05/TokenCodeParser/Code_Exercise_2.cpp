#include "Token_Exercise_1.h"
#include "Code_Exercise_2.h"

bool Code::wisdigit(string str) {
	if (*str.begin() >= '0' && *str.begin() <= '9')
		return true;		//标识符区分大小写，且不以数字开头；
	for (auto c : str)
		if (!(c >= '0' && c <= '9'))
			return false;
	return true;
}

void Code::wsave(string word) {
	if (!word.empty() &&
		find(reservedWord.begin(), reservedWord.end(), word) == reservedWord.end() &&
		!wisdigit(word)) {
		code.push_back(word);
		reservedWord.push_back(word);		// 防止重复 也将被推入
	}
}

// 注释开始后没有存储之前的单词
// 字符串的非注释
// 标识符区分大小写
Code::Code(string str) {

	int comment = 0;
	bool stringing = false;
	char prev = '\0';					//上一个字符
	string word = "";					//单词
	for (auto c : str) {
		// 仅大小写不同 看作相同单词。
		// 统一转换为小写字母
		if ((c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z' && c != 'n') ||
			(c >= '0' && c <= '9'))
			word += c;
		else {
			switch (c)
			{
			case '_': //按序输出标识符,标识符之间以空格或标点（_除外）隔开。
				word += c;
				break;
			case '"':
				stringing = !stringing;
				break;
			case 'n':	//\n不计算在内。这也太坑了
				if (prev != '\\') word += c;
				break;
			case '/':
				if (prev == '/' && !stringing) {	// 注释开始，直至换行结束
					comment = 1;
					wsave(word);
					word = "";
				}
				else if (prev == '*')	// 注释结束
				{
					comment = 0;
					word = "";
				}
				else if (comment == 0) {
					wsave(word);
					word = "";
				}
				break;
			case '*':
				if (prev == '/') {	// 注释开始，换行不结束
					comment = 2;
					// 注释开始需要存储之前的单词
					wsave(word);
					word = "";
				}
				else if (comment == 0) {
					wsave(word);
					word = "";
				}
				break;
			case '\n':
				if (prev != '\\' && comment == 1) {		//只有双且没有强制换行才可以结束
					comment = 0;
					word = "";
					break;
				}
			default:
				// 空格或标点（除连字符 - 下划线_外）均作为单词间的分割标志
				if (comment) break;
				wsave(word);
				word = "";
				break;
			}
		}
		prev = c;
	}
}

void Code::print() {
	sort(code.begin(), code.end());
	for (auto it = code.begin(); it != code.end(); ++it)
		cout << *it << (it == code.end() ? "" : " ");
}