// 代码中‘标识符’的统计与输出：

#include "std_lib_facilities.h"

class Code {
	vector<string> reservedWord = {
	"alignas","alignof","and","and_eq",
	"asm","atomic_cancel","atomic_commit","atomic_noexcept"
	"auto","bitand","bitor","bool",
	"break","case","catch","char",
	"char8_t","char16_t","char32_t","class",
	"compl","concept","const","consteval",
	"constexpr","constinit","const_cast","continue",
	"co_await","co_return","co_yield","decltype",
	"default","define","defined","delete",
	"do","double","dynamic_cast","elif",
	"else","error","endif","enum",
	"explicit","export","extern","false",
	"final","float","for","friend",
	"goto","if","ifdef","ifndef",
	"import","include","inline","int",
	"line","long","module","mutable",
	"namespace","new","noexcept","not",
	"not_eq","nullptr","operator","or",
	"or_eq","override","pragma","private",
	"protected","public","reflexpr","register",
	"reinterpret_cast","requires","return","short",
	"signed","sizeof","static","static_assert",
	"static_cast","struct","switch","synchronized",
	"template","this","thread_local","throw",
	"xor_eq","true","try","typedef",
	"typeid","typename","undef","union",
	"unsigned","using","virtual","void",
	"volatile","wchar_t","while","xor"
	};

	// 预处理的单词
	vector<string> code;

	// 数字性判定
	bool wisdigit(string str);

	// 选择存储之前的单词
	void wsave(string str);
public:
	// 输入代码程序文本。不超过200行
	Code(string str);

	//给定一段代码，输出该段代码中除关键词、数字以外 从小到大输出所有‘标识符’
	void print();
};
