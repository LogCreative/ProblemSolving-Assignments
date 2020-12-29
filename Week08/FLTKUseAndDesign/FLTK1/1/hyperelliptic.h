// 超椭圆
// pow(abs(x/a),m) + pow(abs(y/b),n) = 1
// m, n > 0

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities

using namespace Graph_lib;

// 超椭圆
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
    Point xy;       // 偏移量
    int a;          // x 分母参数 a
    int b;          // y 分母参数 b
    int m;          // x 项的指数 m
    int n;          // y 项的指数 n
    int N;          // 样本点个数 N
};

/* UI 创建时线程访问冲突 暂不解决
// 超椭圆窗口
struct hyptic_window : Simple_window {
    hyptic_window(Point xy, int w, int h, const string& title);

private:
    Graph_lib::In_box ib;               // 输入框
    Graph_lib::Button generate_btn;     // 提交按钮

    // 生成回调函数
    static void cb_generate(Graph_lib::Address, Graph_lib::Address);
    // 生成函数
    void generate();            
};
*/