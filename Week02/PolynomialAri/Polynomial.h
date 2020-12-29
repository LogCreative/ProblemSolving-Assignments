#pragma once

#define MAXPOWER 101

class Polynomial {
public:
    // 1.根据用户输入的表达式初始化一个多项式并将其化简为标准形式，系数的精度设为小数点后4位（本题中，所有输出中的系数均为小数点后4位的形式）；
    Polynomial(string str);
    void print();
    // 2.对简化后的多项式进行求导，并按照多项式指数递降方式排列；
    // 3.对多项式进行计算（多项式计算过程中，小数计算需要按照系统默认浮点数精度先行计算，最后计算完成时才截取位数）。

    ~Polynomial();
private:
    bool        error;                     //是否为异常表达式
    double      coeff[MAXPOWER] = { 0 };   //多项式系数
};