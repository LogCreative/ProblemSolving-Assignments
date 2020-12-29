#include "LinearEquations.h"
#include "std_lib_facilities.h"

LinearEquations::LinearEquations(string str) {
	// �û�����ĺϷ����ʽ������.��+��_��-���ź������Լ���ĸ��x��
	// ÿһ��֮���� + �� - ������ϵ��Ϊ������С����
	// ���С����������ΪС�����4λ
    
    //�������ַ������з���
    int sign = 1;
    int magnit = 10;
    double dilimit = 1;
    double tmp_coeff = 0.0;
    int index = 0;
    bool indexing = false;
    char prev = '\0';
    bool right = false; 

    for (auto c : str) {
        //�ظ������ַ�ɸ��
        if (((c == '.' || c == '_' || c == '+' || c == '-' || c == ' ')
            && (prev == '.' || prev == '_' || prev == '+' || prev == '-'))
            || (c == 'x' && (prev == 'x' || prev == '.' || prev == '_'))) {
            error = true; return;
        }

        if (c >= '0' && c <= '9') {
            if (indexing) index = index * 10 + c - '0';
            else {
                tmp_coeff = tmp_coeff * magnit + (c - '0') * dilimit;
                if (dilimit < 1) dilimit /= 10;
            }
        }
        else {
            switch (c) {
            case '.':
                if (indexing) { error = true; return; }     // ������С��ָ��
                magnit = 1; dilimit = 0.1; break;
            case 'x': tmp_coeff = sign * (tmp_coeff == 0.0 ? (prev == '0' ? tmp_coeff : 1.0) : tmp_coeff);
                //index = 1;                                // ������ʡ�� x_1
                break;
            case '_': index = 0; indexing = true; break;
            case '+':case '-': case '=': case '\n':
                if (tmp_coeff != 0.0) {   // �ضϷ�
                    if (indexing) {
                        A[line][index] += tmp_coeff;
                        validUnks[index] = true;
                    }
                    //else if (index == 1)                  // ������ʡ�� x_1
                    //    coeff[1] += tmp_coeff;
                    else // ������
                        b[line] += (right ? 1 : -1) * sign * tmp_coeff;     // �������Ϊ����
                }
                // ��ʼ������
                if (c == '+') sign = 1;
                else if (c == '-') sign = -1;
                index = 0;
                indexing = false;
                tmp_coeff = 0.0;
                magnit = 10;
                dilimit = 1;
                if (c == '\n') { ++line; sign = 1; right = false; } // ���к���š����ø�λ
                if (c == '=') { right = true; sign = 1; }           // ���ں���Ÿ�λ
                break;
            default: error = true; return;
            }
        }

        prev = c;
    }
}

// ��ȡλ������
// ��doubleС���Ľ�λ������ͨ��to_string����ת��Ϊ�ַ��������н�λ�������������Ӧ������
// setprecision Ϊ�������롣
// -0.0000 ������
string cutDouble(double x) {
    //���Ϊ0����Ԥȡ���Ϊ0.0000
    if (abs(x-(int)x) < EPSILON) x = (int)x;
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

//���ǲ���������ط�����
void LinearEquations::solve() {
    // ���ǵ���Щδ֪������û�б�ʹ�ã���Ҫ�ȼ�����Чδ֪���ĸ���
    vector<int> validIndices({ -1 });           // ��Чָ�꣬0 ����
    for (int i = 0; i < UNKNOWNS; ++i)
        if (validUnks[i])
            validIndices.push_back(i);
    int validUnkCnt = validIndices.size() - 1;

    // �����ʽ���в����ϵ�����
    // �ȿ����޽�����Σ�������δ֪�������ٱ�Ȼ�޽�
    if (error || line - 1 < validUnkCnt) {
        cout << "error" << endl; return;
    }

    // ����Ψһ�⣬���±�n������ʽ�����Ӧ�Ľ⣬�����֮����һ���ո������
    for (int k = 1; k <= validUnkCnt; ++k) {

        // ѡ��Ԫ
        int maxPtr = k;
        double maxEle = abs(A[k][validIndices[k]]);
        for (int r = k + 1; r <= line - 1; ++r)                 //�������п�������
            if (abs(A[r][validIndices[k]]) > abs(maxEle)) {
                maxPtr = r; maxEle = abs(A[r][validIndices[k]]);
            }

        //������Ԫ��
        //for (int j = k; j <= validUnkCnt; ++j) {
        double temp;
        for (vector<int>::iterator j = validIndices.begin(); j != validIndices.end(); ++j) {
            temp = A[maxPtr][*j];
            A[maxPtr][*j] = A[k][*j];
            A[k][*j] = temp;
        }
        temp = b[maxPtr];
        b[maxPtr] = b[k];
        b[k] = temp;

        if (!A[k][validIndices[k]]) {
            cout << "error" << endl; return;
        }

        for (int i = k + 1; i <= line - 1; ++i) {               //�������п�������
            temp = A[i][validIndices[k]] / A[k][validIndices[k]];
            for (vector<int>::iterator j = validIndices.begin() + k; j != validIndices.end(); ++j)
                A[i][*j] = A[i][*j] - temp * A[k][*j];
            b[i] = b[i] - temp * b[k];
        }
    }

    // �ش�����
    // end �õ���������һ����Ԫ+1��ָ��
    x[validIndices[validUnkCnt]] = b[validUnkCnt] / A[validUnkCnt][validIndices[validUnkCnt]];
    for (int k = validUnkCnt - 1; k >= 1; --k) {
        double S = b[k];
        //for (int j = k + 1; j <= validUnkCnt; ++j)
        for (vector<int>::iterator j = validIndices.begin() + k + 1; j != validIndices.end(); ++j) 
            S -= A[k][*j] * x[*j];
        x[validIndices[k]] = S / A[k][validIndices[k]];
        // Linux ƽ̨��Windows ƽ̨��ͬʱ����inf��nan
        if (isinf(x[validIndices[k]])||isnan(x[validIndices[k]])) {        
            cout << "error" << endl; return;        // �޽�
        }
    }

    for (int k = 1; k <= validUnkCnt; ++k)
        cout << cutDouble(x[validIndices[k]]) << ' ';

}

LinearEquations::~LinearEquations() {}