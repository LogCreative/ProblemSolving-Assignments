// Week 1 - Problem 2:
// Solving zero of the function

// By using Newton's method

#include "../std_lib_facilities.h"
#include "polynomial.h"

// 迭代次数阈值
#define THERESHOLD 2000

// 定义函数 f
inline double f(double x){ return x*exp(x)-1; }

// 定义函数 f'
// 后面可以尝试直接近似计算
inline double fprime(double x){ return (x+1)*exp(x); }

// 超出迭代次数异常
class OutOfIterationTheresholdException {
public:
    OutOfIterationTheresholdException(): 
        message("Out of iteration thereshold") {}
    const char* what() const {return message;}
private:
    const char* message;
};

// Newton's method:
// x[k+1] = x[k] - f(x[k]) / fprime(x[k])
double NewtonZero(Polynomial *poly, double initialValue){
    double xprev, xfwd  = initialValue;
    int iteration = 0;
    do{
        xprev = xfwd;
        xfwd = xprev - poly->getValue(xprev) / poly->getDerivValue(xprev);
        if (++iteration>THERESHOLD)
            throw OutOfIterationTheresholdException();
    } while(abs(xfwd - xprev)>2e-5);
    return xfwd;
}

int main(){
    Polynomial *poly = new Polynomial();
    cout << "The zero of function(Newton's Method):" << NewtonZero(poly,0.5)<<endl;
    return 0;
}