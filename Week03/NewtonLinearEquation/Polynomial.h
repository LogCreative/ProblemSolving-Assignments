#include "std_lib_facilities.h"
#define MAXPOWER 101
#define ITER_THES 2000      // 迭代次数阈值
#define ACCURACY 1e-5       // 精确度，将计算结果按照小数点后4位直接截断，这里多计算两位再进行截断
#define SAMPLES 20          // 采样数，用于验证牛顿条件

// Week 03  浮点数数据类型为float

class Polynomial {
    friend string cutFloat(float x);                        // 截位函数
    //friend void prt(float _coeff[MAXPOWER], bool error);    // 打印任意多项式函数
public:
    bool        error;                                      //是否为异常表达式
    float       coeff[MAXPOWER] = { 0 };                    //多项式系数
    float       dcoeff[MAXPOWER] = { 0 };                   //导数多项式系数
    // 1.根据用户输入的表达式初始化一个多项式并将其化简为标准形式，系数的精度设为小数点后4位（本题中，所有输出中的系数均为小数点后4位的形式）；
    Polynomial(string str);
    //void print();
    // 2.对简化后的多项式进行求导，并按照多项式指数递降方式排列；
    //void printDerivitive();
    // 3.对多项式进行计算（多项式计算过程中，小数计算需要按照系统默认浮点数精度先行计算，最后计算完成时才截取位数）。
    //void printValue(float x);

    // 牛顿法求解
    void newtonSolver(float a, float b);
    
    ~Polynomial();
private:
    // 得到多项式次数
    //int getPower();
    // 得到表达式的值
    float getValue(float x);
    // 计算导数系数
    void calcDerivCoeff();
    // 得到表达式的导数值，需要先调用 calcDerivCoeff() 方法计算导数多项式系数
    float getDerivValue(float x);
    // 验证左右区间的合法性
    bool newtonVerify(float a, float b);
};