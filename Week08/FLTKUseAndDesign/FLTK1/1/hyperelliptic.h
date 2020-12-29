// ����Բ
// pow(abs(x/a),m) + pow(abs(y/b),n) = 1
// m, n > 0

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities

using namespace Graph_lib;

// ����Բ
struct hyperelliptic : Shape {
    hyperelliptic(Point _xy, int _a, int _b, int _m, int _n, int _N) : 
        xy(Point(_xy.x + _a, _xy.y + _b)),
        a(_a), b(_b), m(_m), n(_n), N(_N)
    {
        calc_points();
        if (m <= 0 || n <= 0) error("Bad hyperelliptic: non-positive index");
    };

    void calc_points();
    void draw_lines() const;

private:
    Point xy;       // ƫ����
    int a;          // x ��ĸ���� a
    int b;          // y ��ĸ���� b
    int m;          // x ���ָ�� m
    int n;          // y ���ָ�� n
    int N;          // ��������� N
};

/* UI ����ʱ�̷߳��ʳ�ͻ �ݲ����
// ����Բ����
struct hyptic_window : Simple_window {
    hyptic_window(Point xy, int w, int h, const string& title);

private:
    Graph_lib::In_box ib;               // �����
    Graph_lib::Button generate_btn;     // �ύ��ť

    // ���ɻص�����
    static void cb_generate(Graph_lib::Address, Graph_lib::Address);
    // ���ɺ���
    void generate();            
};
*/