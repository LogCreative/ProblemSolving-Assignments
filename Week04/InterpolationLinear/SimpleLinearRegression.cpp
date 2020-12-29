#include "SimpleLinearRegression.h"

string LinearRegression::cutDouble(double x) {
    //如解为0，则预取输出为0.0000
    if (abs(x - (int)x) < EPSILON) x = (int)x;
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

LinearRegression::LinearRegression() {
    //接下来的n行为n个点坐标，每行为两个数字，中间使用空格隔开，分别表示坐标的x,y值。

    while (cin) {
        cin >> x[count] >> y[count];

        // 输入中若包含非法字符，则输出error；- 暂不考虑，很有可能会导致数据不平衡，直接error
        // 看来是平衡的，先判断是不是 EOF，然后剩余的情况就是输入非法字符
        if (!cin.eof() && !cin) {
            error = true; return;
        }

        ++count;
    }
    --count;    // 会因为开始输入的时候多算一次

    // 输入的坐标集至少由1个坐标组成，每行一个坐标。
    // 但是一个点不能进行线性拟合
    if (count < 2) { error = true; return; }

    calcFactors();
}

void LinearRegression::calcFactors() {
    // 先计算均值
    double x_sum = 0, y_sum = 0;
    for (int i = 0; i < count; ++i) {
        x_sum += x[i];
        y_sum += y[i];
    }
    x_mean = x_sum / count;
    y_mean = y_sum / count;

    // 再计算求和因子
    L_xx = 0; L_yy = 0; L_xy = 0;
    for (int i = 0; i < count; ++i) {
        L_xx += (x[i] - x_mean) * (x[i] - x_mean);
        L_yy += (y[i] - y_mean) * (y[i] - y_mean);
        L_xy += (x[i] - x_mean) * (y[i] - y_mean);
    }

    // 最后求出拟合系数
    b = L_xy / L_xx;
    a = y_mean - b * x_mean;
}

void LinearRegression::getCoeff() {
    // 若相关系数r的绝对值大于等于0.75时认为两个变量有很强的线性相关关系，
    // 若相关系数小于0.75则无法求出一元线性拟合方程，
    // 第二行输出error，
    // 第三行输出error。
    if (error) { cout << "error" << endl; return; }
    double Coeff = L_xy / sqrt(L_xx * L_yy);
    cout << cutDouble(Coeff) << endl;
    if (abs(Coeff) < 0.75) error = true;
}

void LinearRegression::getFunction() {
    if (error) { cout << "error" << endl; return; }
    cout << "y=" << cutDouble(b) << "*x" << (a >= 0 ? "+" : "") << cutDouble(a) << endl;
}

void LinearRegression::getValue(double _x) {
    if (error) { cout << "error" << endl; return; }
    cout << cutDouble(b * _x + a) << endl;
}

LinearRegression::~LinearRegression() {

}