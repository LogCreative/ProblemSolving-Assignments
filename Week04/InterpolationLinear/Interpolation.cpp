#include "Interpolation.h"

string cutDouble(double x) {
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

Interpolation::Interpolation() {
	// 接下来的n行为n个插值点坐标，每行为两个数字，中间使用空格隔开，分别表示坐标的x,y值。
    while (cin) {
        cin >> x[count] >> y[count];

        // 输入中若包含非法字符，则输出error；- 暂不考虑，很有可能会导致数据不平衡，直接error
        // 看来是平衡的，先判断是不是 EOF，然后剩余的情况就是输入非法字符
        if (!cin.eof() && !cin) {
            cout << "error"; error = true; return;
        }

        ++count;
    }
    --count;    // 会因为开始输入的时候多算一次
	

    initDiff();
    calcDiff();
}

void Interpolation::initDiff() {
    if (error) return;

    // 考虑等距节点，若提供的为非等距点，则输出error。注意，插值点输入过程中，x不一定严格增长；
    // 使用直接选择排序，y数组做跟随处理，100 数量比较小。
    // 在这个过程中进行间距检测
    int minIndex;
    double dist;                    // 间距
    for (int i = 0; i < count; ++i) {
        minIndex = i;
        for (int j = i + 1; j < count; ++j)
            if (x[j] < x[minIndex])
                minIndex = j;
        // 更新 x 数组（排序中）
        double temp = x[i];
        x[i] = x[minIndex];
        x[minIndex] = temp;
        // y 数组更新
        temp = y[i];
        y[i] = y[minIndex];
        y[minIndex] = temp;
        // 间距检测
        if (i == 0);                // 不计算间距
        else if (i == 1) dist = x[i] - x[i - 1];
        else if (x[i] - x[i - 1] - dist > EPSILON)
        {
            cout << "error"; error = true; return;
        }
        // 将 y 数组的对应值放入差分数组中
        diff[i][0] = y[i];
    }
}

void Interpolation::calcDiff() {
    if (error) return;

    // 从第 1 列开始直到第 count-1 列计算差分
    for (int j = 1; j < count; ++j)
        for (int i = j; i < count; ++i)
            diff[i][j] = diff[i][j - 1] - diff[i - 1][j - 1];
}

void Interpolation::solve(double _x) {
    if (error) return;

    double t = (_x - x[0]) / (x[1] - x[0]);         // 因子

    double polyTerm = 1,                            // 多项式项
        factorial = 1,                              // 阶乘项
        result = 0;                                 // 结果
    
    for (int i = 0; i < count; ++i) {
        result += diff[i][i] / factorial * polyTerm;
        polyTerm *= t - i;
        factorial *= i + 1;
    }

    cout << cutDouble(result);
    
}

Interpolation::~Interpolation() {

}