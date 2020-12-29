#include "std_lib_facilities.h"
#include "Interpolation.h"
#include "SimpleLinearRegression.h"

//定义main函数
int main()
{
    /********** Begin **********/
    bool exercisel = false;

    // 第一行为待计算的x值，
    double _x;
    cin >> _x;

    if (exercisel) {
        //第一关执行代码 完成 Interpolation.cpp与 Interpolation.h文件
        //是第一行输入了非法字符
        if (!cin) {
            cout << "error"; return 1;
        }
        Interpolation inter;
        inter.solve(_x);
    }
    else {
        //第二执行代码 完成 SimpleLinearRegression.cpp与 SimpleLinearRegression.h文件
        if (!cin){
            for (int i = 0; i < 3; ++i)
                cout << "error" << endl;
            return 1;
        }
        LinearRegression lr;
        lr.getCoeff();
        lr.getFunction();
        lr.getValue(_x);
    }

    /********** End **********/
    return 0;
}

