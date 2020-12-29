#include "Token_Exercise_1.h"

Token::Token(string str) {
	// �ո����κε����ı�㲻Ϊ���ʣ�

	// ���ո�_���ո� ��  ���ո�-���ո񣩲�Ϊ���ʣ�
	// a_b����һ�����ʣ�
	// a-b����һ�����ʣ�
	// A_C��a_c����ͬһ�����ʡ�

	string word = "";					//����
	for (auto c : str) {
		// ����Сд��ͬ ������ͬ���ʡ�
		// ͳһת��ΪСд��ĸ
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
				// �ո���㣨�����ַ� - �»���_�⣩����Ϊ���ʼ�ķָ��־
				// a�����ո���a_���ո�Ϊ����a��
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