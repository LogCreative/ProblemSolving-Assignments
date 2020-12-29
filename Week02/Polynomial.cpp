#include "Polynomial.h"
#include "std_lib_facilities.h"

Polynomial::Polynomial(string str){
    error = false;
    
    //对输入字符串进行分析
    int sign = 1;
    int magnit = 10;
    double dilimit = 1;
    double tmp_coeff = 0.0;
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
                    else if (c == ' ') return;          //结束多项式输入
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
// 对double小数的截位，可以通过to_string将其转换为字符串并进行截位。请自行设计相应函数。
// setprecision 为四舍五入。
string cutDouble(double x) {
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

// 稀疏打印
void prt(double _coeff[MAXPOWER],bool error) {
    if (error) cout << "error" << endl;
    else {
        bool constOnly = true;
        bool first = true;
        for (int i = MAXPOWER - 1; i >= 0; --i)
            if (_coeff[i] != 0.0) {
                cout << (_coeff[i] > 0 ? (!first ? "+" : "") : "") << cutDouble(_coeff[i]) << (i == 0 ? "" : ("x" + (i > 1 ? "^" + to_string(i) : "")));
                constOnly = false;
                first = false;
            }
        if (constOnly) cout << "0.0000";
        cout << endl;
    }
}

void Polynomial::print() { prt(coeff, error); }

void Polynomial::printDerivitive() {
    double dcoeff[MAXPOWER] = { 0 };
    for (int i = MAXPOWER - 1; i >= 1; --i) 
        if (coeff[i] != 0.0)
            dcoeff[i - 1] = i * coeff[i];
    prt(dcoeff, error);
}

void Polynomial::getValue(double x) {
    if (error) cout << "error" << endl;
    else {
        double value = 0.0;
        double item = 1;
        for (int i = 0; i < MAXPOWER; ++i) {
            if (coeff[i] != 0) 
                value += coeff[i] * item;
            item *= x;
        }
        cout << cutDouble(value) << endl;
    }
}

int Polynomial::getPower() {
    for (int i = MAXPOWER - 1; i >= 0; --i)
        if (coeff[i] != 0)
            return i;
    return 0;                               // 返回常数级
}

void Divide(Polynomial poly1, Polynomial poly2) {
    double quotient_coeff[MAXPOWER] = { 0 },
        remain_coeff[MAXPOWER] = { 0 };

    // 得到两个多项式的最高幂次
    int power1 = poly1.getPower(),
        power2 = poly2.getPower();

    // 现在的余项是被除式
    for (int i = power1; i >= 0; --i)
        remain_coeff[i] = poly1.coeff[i];

    // 得到商多项式的最高幂次
    int powerQ = power1 - power2;

    // 除式是否为0
    if (poly2.coeff[power2] == 0) {
        cout << "error\n" << "error" << endl;
        return;
    }

    // 计算商和余
    for (int i = 0; i <= powerQ; ++i) {
        quotient_coeff[powerQ - i] = remain_coeff[power1 - i] / poly2.coeff[power2];
        for (int j = 0; j <= power2; ++j)
            remain_coeff[power1 - i - j] = remain_coeff[power1 - i - j] - quotient_coeff[powerQ - i] * poly2.coeff[power2 - j];
    }
    
    // 输出商和余
    prt(quotient_coeff, false);
    prt(remain_coeff, false);
}

Polynomial::~Polynomial(){}