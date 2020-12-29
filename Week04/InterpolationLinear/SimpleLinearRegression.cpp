#include "SimpleLinearRegression.h"

string LinearRegression::cutDouble(double x) {
    //���Ϊ0����Ԥȡ���Ϊ0.0000
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
    //��������n��Ϊn�������꣬ÿ��Ϊ�������֣��м�ʹ�ÿո�������ֱ��ʾ�����x,yֵ��

    while (cin) {
        cin >> x[count] >> y[count];

        // �������������Ƿ��ַ��������error��- �ݲ����ǣ����п��ܻᵼ�����ݲ�ƽ�⣬ֱ��error
        // ������ƽ��ģ����ж��ǲ��� EOF��Ȼ��ʣ��������������Ƿ��ַ�
        if (!cin.eof() && !cin) {
            error = true; return;
        }

        ++count;
    }
    --count;    // ����Ϊ��ʼ�����ʱ�����һ��

    // ��������꼯������1��������ɣ�ÿ��һ�����ꡣ
    // ����һ���㲻�ܽ����������
    if (count < 2) { error = true; return; }

    calcFactors();
}

void LinearRegression::calcFactors() {
    // �ȼ����ֵ
    double x_sum = 0, y_sum = 0;
    for (int i = 0; i < count; ++i) {
        x_sum += x[i];
        y_sum += y[i];
    }
    x_mean = x_sum / count;
    y_mean = y_sum / count;

    // �ټ����������
    L_xx = 0; L_yy = 0; L_xy = 0;
    for (int i = 0; i < count; ++i) {
        L_xx += (x[i] - x_mean) * (x[i] - x_mean);
        L_yy += (y[i] - y_mean) * (y[i] - y_mean);
        L_xy += (x[i] - x_mean) * (y[i] - y_mean);
    }

    // ���������ϵ��
    b = L_xy / L_xx;
    a = y_mean - b * x_mean;
}

void LinearRegression::getCoeff() {
    // �����ϵ��r�ľ���ֵ���ڵ���0.75ʱ��Ϊ���������к�ǿ��������ع�ϵ��
    // �����ϵ��С��0.75���޷����һԪ������Ϸ��̣�
    // �ڶ������error��
    // ���������error��
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