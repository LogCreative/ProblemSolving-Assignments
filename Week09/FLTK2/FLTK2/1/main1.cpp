
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities
#include "BarChart.h"

//------------------------------------------------------------------------------

#define WIDTH 600							    // 窗口宽度
#define HEIGHT 400							    // 窗口高度
#define LEFT 50                                 // 横向偏移
#define BOTTOM 50                               // 纵向偏移
#define FONT_SIZE 10                            // 字号
#define TICK_NUM 10                             // 标签数量
#define MAX_TEMP 32							// 平均最高

//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl, WIDTH, HEIGHT, "City Temperature Monthly Average");    // make a simple window

    CityAvgTemp austin("austin.csv");
    CityAvgTemp newYork("NewYork.csv");

    const int GRAPH_WIDTH = WIDTH - LEFT * 2;         // 图宽度
    const int GRAPH_HEIGHT = HEIGHT - BOTTOM * 2;     // 图高度
    const double BANDWIDTH = GRAPH_WIDTH / 24;           // 带宽

    Axis x(Axis::x, Point(LEFT, HEIGHT - BOTTOM), GRAPH_WIDTH, 0, "Month");
    x.set_color(Color::black);
    x.label.set_font_size(FONT_SIZE);
    x.label.move(LEFT * 3, FONT_SIZE * 1.2);
    Axis y(Axis::y, Point(LEFT, HEIGHT - BOTTOM), GRAPH_HEIGHT, TICK_NUM, "Average Temperature C");
    y.set_color(Color::black);
    y.label.set_font_size(FONT_SIZE);
    win.attach(x);
    win.attach(y);

    // 柱形图主体
    Graph_lib::Rectangle* bar;

    // 写入循环的需要使用指针
    for (int i = 1; i <= 12; ++i) {
        bar = new Graph_lib::Rectangle(
            Point(LEFT + BANDWIDTH * (2.0 * i - 0.75), HEIGHT - BOTTOM - austin.proportion(i) * GRAPH_HEIGHT),
            Point(LEFT + BANDWIDTH * 2 * i, HEIGHT - BOTTOM)
        );
        bar->set_color(Color::dark_blue);
        bar->set_fill_color(Color::blue);
        win.attach(*bar);
        bar = new Graph_lib::Rectangle(
            Point(LEFT + BANDWIDTH * 2 * i, HEIGHT - BOTTOM - newYork.proportion(i) * GRAPH_HEIGHT),
            Point(LEFT + BANDWIDTH * (2.0 * i + 0.75), HEIGHT - BOTTOM)
        );
        bar->set_color(Color::dark_red);
        bar->set_fill_color(Color::red);
        win.attach(*bar);
    }
    
    // 刻度
    Graph_lib::Text* tick;

    // x 轴刻度
    for (int i = 1; i <= 12; ++i) {
        tick = new Graph_lib::Text(
            Point(LEFT + BANDWIDTH * 2 * i, HEIGHT - BOTTOM), 
            to_string(i)
        );
        tick->set_color(Color::black);
        tick->set_font_size(FONT_SIZE);
        tick->move(-FONT_SIZE / 2, FONT_SIZE);
        win.attach(*tick);
    }

    // y 轴刻度
    for (int i = 0; i <= TICK_NUM; ++i) {
        tick = new Graph_lib::Text(
            Point(LEFT, HEIGHT - BOTTOM - (double)i * GRAPH_HEIGHT / TICK_NUM), 
            to_string(MAX_TEMP * i / TICK_NUM)
        );
        tick->set_color(Color::black);
        tick->set_font_size(FONT_SIZE);
        tick->move(-FONT_SIZE * 2, FONT_SIZE / 2);
        win.attach(*tick);
    }

    // 图例矩形
    Graph_lib::Rectangle* rect;
    
    rect = new Graph_lib::Rectangle(Point(LEFT + 20, BOTTOM), GRAPH_WIDTH / 4, GRAPH_HEIGHT / 5);
    rect->set_color(Color::black);
    rect->set_fill_color(Color::white);
    win.attach(*rect);

    rect = new Graph_lib::Rectangle(Point(LEFT + 30, BOTTOM + 10), 30, 15);
    rect->set_color(Color::dark_blue);
    rect->set_fill_color(Color::blue);
    win.attach(*rect);

    rect = new Graph_lib::Rectangle(Point(LEFT + 30, BOTTOM + 30), 30, 15);
    rect->set_color(Color::dark_red);
    rect->set_fill_color(Color::red);
    win.attach(*rect);

    // 图例文字
    Graph_lib::Text* label;
    label = new Graph_lib::Text(Point(LEFT + 70, BOTTOM + 20), "Austin");
    label->set_font_size(FONT_SIZE);
    label->set_color(Color::black);
    win.attach(*label);
    label = new Graph_lib::Text(Point(LEFT + 70, BOTTOM + 40), "New York");
    label->set_font_size(FONT_SIZE);
    label->set_color(Color::black);
    win.attach(*label);

    win.wait_for_button();       // give control to the display engine
} 

//------------------------------------------------------------------------------
