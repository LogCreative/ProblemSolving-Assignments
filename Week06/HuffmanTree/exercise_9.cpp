#include "std_lib_facilities.h"
#include "Huffman_Exercise_1.h"
#include "Huffman_Exercise_2.h"
int main()
{
    /********** Begin **********/
    bool exercise_1 = false;
    if (exercise_1) {
        //第一关执行代码
        //Please fix Huffman_Exercise_1.h and Huffman_Exercise_1.cpp
        string str;
        // 本题中字母定义：大小写字母、空格、回车、数字及其它标点符号等。这里，我们仅仅包含ASCII码；大小写字母为不同字母。
        char ch;
        while (cin.get(ch))
            str.push_back(ch);
        Huffman h(str);
        cout << h.getSize() << endl;
    }
    else {
        //Please fix Huffman_Exercise_2.h and Huffman_Exercise_2.cpp  
        string str;
        char ch;
        while (cin.get(ch))
            str.push_back(ch);
        Huffman2 h(str);
        cout << h.getSize() << endl;
    }
    /********** End **********/
    return 0;
}

