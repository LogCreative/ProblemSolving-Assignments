#include "Token_Exercise_1.h"
#include "Code_Exercise_2.h"

bool Code::wisdigit(string str) {
	if (*str.begin() >= '0' && *str.begin() <= '9')
		return true;		//��ʶ�����ִ�Сд���Ҳ������ֿ�ͷ��
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
		reservedWord.push_back(word);		// ��ֹ�ظ� Ҳ��������
	}
}

// ע�Ϳ�ʼ��û�д洢֮ǰ�ĵ���
// �ַ����ķ�ע��
// ��ʶ�����ִ�Сд
Code::Code(string str) {

	int comment = 0;
	bool stringing = false;
	char prev = '\0';					//��һ���ַ�
	string word = "";					//����
	for (auto c : str) {
		// ����Сд��ͬ ������ͬ���ʡ�
		// ͳһת��ΪСд��ĸ
		if ((c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z' && c != 'n') ||
			(c >= '0' && c <= '9'))
			word += c;
		else {
			switch (c)
			{
			case '_': //���������ʶ��,��ʶ��֮���Կո���㣨_���⣩������
				word += c;
				break;
			case '"':
				stringing = !stringing;
				break;
			case 'n':	//\n���������ڡ���Ҳ̫����
				if (prev != '\\') word += c;
				break;
			case '/':
				if (prev == '/' && !stringing) {	// ע�Ϳ�ʼ��ֱ�����н���
					comment = 1;
					wsave(word);
					word = "";
				}
				else if (prev == '*')	// ע�ͽ���
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
				if (prev == '/') {	// ע�Ϳ�ʼ�����в�����
					comment = 2;
					// ע�Ϳ�ʼ��Ҫ�洢֮ǰ�ĵ���
					wsave(word);
					word = "";
				}
				else if (comment == 0) {
					wsave(word);
					word = "";
				}
				break;
			case '\n':
				if (prev != '\\' && comment == 1) {		//ֻ��˫��û��ǿ�ƻ��вſ��Խ���
					comment = 0;
					word = "";
					break;
				}
			default:
				// �ո���㣨�����ַ� - �»���_�⣩����Ϊ���ʼ�ķָ��־
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