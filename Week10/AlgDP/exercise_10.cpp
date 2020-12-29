#include "std_lib_facilities.h"
#include "Question_1.h"
#include "Question_2.h"
#include "Question_3.h"
int main()
{
    /********** Begin **********/
    //int exercise = 1;
    //int exercise = 2;
    int exercise = 3;

    if (exercise == 1) {
        //第一关执行代码
        //Please fix Question_1.h and Question_1.cpp
        int w, n;
        cin >> w >> n;
        boat b(w, n);
        b.getBoatNum();
    }
    else if (exercise == 2) {
        //Please fix Question_2.h and Question_2.cpp  
        int n;
        cin >> n;
        subsequence sq(n);
        sq.getMaxSequence();
    }
    else if (exercise == 3) {
        //Please fix Question_3.h and Question_3.cpp
        string str;                 // 输入字符串中不仅可能存在字母，还可能存在符号空格数字等，输入为一行。
        getline(cin, str);
        palindrome pd(str);
        pd.getRes();
    }
    else
        cout << "error";

    /********** End **********/
    return 0;
}

