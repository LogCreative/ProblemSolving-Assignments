#include "Polynomial.h"
#include "std_lib_facilities.h"

Polynomial::Polynomial(string str){
    error = false;
    
    //对输入字符串进行分析
    int sign = 1;
    int magnit = 10;
    float dilimit = 1;
    float tmp_coeff = 0.0;
    int index = 0;
    bool indexing = false;
    char prev = '\0';

    for(auto c : str){
        //重复特殊字符筛除
        if (((c == '.' || c == '^' || c == '+' || c == '-' || c == ' ')
            && (prev == '.' || prev == '^' || prev == '+' || prev == '-'))
            || (c == 'x' && (prev == 'x' || prev == '.' || prev == '^'))) {
            error = true; return;
        }

        if(c>='0' && c<='9'){
            if(indexing) index = index * 10 + c - '0';
            else {
                tmp_coeff = tmp_coeff * magnit + (c - '0') * dilimit;
                if(dilimit<1) dilimit /= 10;
            }
        } else {
            switch(c){
                case '.':
                    if (indexing) { error = true; return; }     // 不允许小数指数
                    magnit = 1; dilimit = 0.1; break;
                case 'x': tmp_coeff = sign * (tmp_coeff == 0.0 ? (prev == '0'? tmp_coeff : 1.0) : tmp_coeff); index = 1; break;
                case '^': index = 0; indexing = true; break;
                case '+':case '-': case ' ':
                    if (tmp_coeff != 0.0)    // 截断符
                        if (indexing) 
                            coeff[index] += tmp_coeff;
                        else if (index == 1)
                            coeff[1] += tmp_coeff;
                        else // 常数项
                            coeff[0] += sign * tmp_coeff;
                    // 初始化参数
                    if (c == '+') sign = 1;
                    else if (c == '-') sign = -1;
                    else if (c == ' ') {
                        calcDerivCoeff();       // 初始化导数多项式系数 
                        return;                 //结束多项式输入
                    }
                    index = 0; 
                    indexing = false; 
                    tmp_coeff = 0.0; 
                    magnit = 10; 
                    dilimit = 1;
                    break;
                default: error = true; return;
            }
        }
    
        prev = c;
    }

}

// 截取位数问题
// 对float小数的截位，可以通过to_string将其转换为字符串并进行截位。请自行设计相应函数。
// setprecision 为四舍五入。
string cutFloat(float x) {
    string s = to_string(x);
    string o = "";
    int count = -1;
    for (auto c : s) {
        if (c == '.') count = 4;
        else {
            if (count == 0) return o;
            if (count > 0) --count;
        }
        o += c;
    }
}

void Polynomial::calcDerivCoeff() {
    for (int i = MAXPOWER - 1; i >= 1; --i)
        if (coeff[i] != 0.0)
            dcoeff[i - 1] = i * coeff[i];
}

float Polynomial::getDerivValue(float x) {
    float value = 0.0;
    float item = 1;
    for (int i = 0; i < MAXPOWER; ++i) {
        if (dcoeff[i] != 0)
            value += dcoeff[i] * item;
        item *= x;
    }
    return value;
}

float Polynomial::getValue(float x) {
    float value = 0.0;
    float item = 1;
    for (int i = 0; i < MAXPOWER; ++i) {
        if (coeff[i] != 0) 
            value += coeff[i] * item;
        item *= x;
    }
    return value;
}

// 判定符号
inline int sign(float x) { return (x > 0 ? 1 : (x == 0 ? 0 : -1)); }

bool Polynomial::newtonVerify(float a, float b) {
    // 0. f(x) 在区间 [a,b] 内存在二阶连续导数 - 不验证
    
    // 1. f(a)f(b)<0
    float fa = getValue(a);
    float fb = getValue(b);
    float fpa = getDerivValue(a);
    float fpb = getDerivValue(b);
    if (fa * fb >= 0) return false;

    // 2. x in [a,b], f'(x) neq 0
    if (fpa == 0 || fpb == 0) return false;

    // 3. x in [a,b], f'(x) 不变号
    int derivSign = sign(fpa);
    float interval = (b - a) / SAMPLES;
    float verfi = a;
    for (int i = 0; i < SAMPLES; ++i, verfi += interval) 
        if(sign(getDerivValue(verfi))!=derivSign) 
            return false;

    // 4. a - f(a) / f'(a) <= b, b - f(b) / f'(b) >= a
    if (a - fa / fpa > b || b - fb / fpb < a) return false;

    return true;
}

// 超出迭代次数上限
class OutOfIterationLimitException {};

void Polynomial::newtonSolver(float a, float b) {
    // 1. 若输入的表达式不合法或左右区间不合法，输出为error。
    if (error || !newtonVerify(a,b)) {
        cout << "error" << endl; return; 
    }

    // 2. 若方程在区间内无解则输出error，否则输出近似解。
    float initialValue = a;
    float xprev, xfwd = initialValue;
    int iteration = 0;
    try {
        do {
            xprev = xfwd;
            xfwd = xprev - getValue(xprev) / getDerivValue(xprev);
            if (++iteration > ITER_THES)
                throw OutOfIterationLimitException();
        } while (abs(xfwd - xprev) > ACCURACY);
        cout << cutFloat(xfwd) << endl;
    }
    catch (OutOfIterationLimitException) {
        cout << "error" << endl; return;
    }
}

Polynomial::~Polynomial(){}