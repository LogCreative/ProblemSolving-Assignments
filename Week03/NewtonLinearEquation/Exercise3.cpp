#include "std_lib_facilities.h"
#include "Polynomial.h"
#include "LinearEquations.h"

int main()
{
    /********** Begin **********/

    bool exercise1 = false;
    if (exercise1) {
        //第一关执行代码
            //Please fix Polynomial.h and Polynomial.cpp
        string str;
        getline(cin, str);
        Polynomial poly(str + ' ');
        float a, b;
        cin >> a >> b;
        poly.newtonSolver(a, b);
    }
    else {
        //第二关执行代码
        //Please fix LinearEquations.h and LinearEquations.cpp
        string str;
        char ch;
        while (cin.get(ch))           // 以 EOF 作为结尾
            str.push_back(ch);
        LinearEquations les(str);            // Windows 平台
        //LinearEquations les(str+'\n');     // 在 linux 评测平台需要添加换行符，可能由于get(ch)的定义是不一样的
        //les.solve();
        les.solve();
    }
    /********** End **********/
    return 0;
}

