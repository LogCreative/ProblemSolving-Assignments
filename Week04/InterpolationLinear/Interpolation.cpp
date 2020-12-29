#include "Interpolation.h"

string cutDouble(double x) {
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

Interpolation::Interpolation() {
	// ��������n��Ϊn����ֵ�����꣬ÿ��Ϊ�������֣��м�ʹ�ÿո�������ֱ��ʾ�����x,yֵ��
    while (cin) {
        cin >> x[count] >> y[count];

        // �������������Ƿ��ַ��������error��- �ݲ����ǣ����п��ܻᵼ�����ݲ�ƽ�⣬ֱ��error
        // ������ƽ��ģ����ж��ǲ��� EOF��Ȼ��ʣ��������������Ƿ��ַ�
        if (!cin.eof() && !cin) {
            cout << "error"; error = true; return;
        }

        ++count;
    }
    --count;    // ����Ϊ��ʼ�����ʱ�����һ��
	

    initDiff();
    calcDiff();
}

void Interpolation::initDiff() {
    if (error) return;

    // ���ǵȾ�ڵ㣬���ṩ��Ϊ�ǵȾ�㣬�����error��ע�⣬��ֵ����������У�x��һ���ϸ�������
    // ʹ��ֱ��ѡ������y���������洦��100 �����Ƚ�С��
    // ����������н��м����
    int minIndex;
    double dist;                    // ���
    for (int i = 0; i < count; ++i) {
        minIndex = i;
        for (int j = i + 1; j < count; ++j)
            if (x[j] < x[minIndex])
                minIndex = j;
        // ���� x ���飨�����У�
        double temp = x[i];
        x[i] = x[minIndex];
        x[minIndex] = temp;
        // y �������
        temp = y[i];
        y[i] = y[minIndex];
        y[minIndex] = temp;
        // �����
        if (i == 0);                // ��������
        else if (i == 1) dist = x[i] - x[i - 1];
        else if (x[i] - x[i - 1] - dist > EPSILON)
        {
            cout << "error"; error = true; return;
        }
        // �� y ����Ķ�Ӧֵ������������
        diff[i][0] = y[i];
    }
}

void Interpolation::calcDiff() {
    if (error) return;

    // �ӵ� 1 �п�ʼֱ���� count-1 �м�����
    for (int j = 1; j < count; ++j)
        for (int i = j; i < count; ++i)
            diff[i][j] = diff[i][j - 1] - diff[i - 1][j - 1];
}

void Interpolation::solve(double _x) {
    if (error) return;

    double t = (_x - x[0]) / (x[1] - x[0]);         // ����

    double polyTerm = 1,                            // ����ʽ��
        factorial = 1,                              // �׳���
        result = 0;                                 // ���
    
    for (int i = 0; i < count; ++i) {
        result += diff[i][i] / factorial * polyTerm;
        polyTerm *= t - i;
        factorial *= i + 1;
    }

    cout << cutDouble(result);
    
}

Interpolation::~Interpolation() {

}