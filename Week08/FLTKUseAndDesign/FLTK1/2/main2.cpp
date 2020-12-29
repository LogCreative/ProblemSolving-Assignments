
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities
#include "righttriangle.h"

//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl,600,400,"righttriangle");    // make a simple window

    const int LEG = 100;

    const double HYP = LEG * sqrt(2);

    righttriangle rt_1(Point(100 + HYP, 100 + HYP), 100, 100, 0, Color::red);
    righttriangle rt_2(Point(100 + HYP / 2, 100 + HYP / 2 + LEG), 100, 100, PI / 4, Color::yellow);
    righttriangle rt_3(Point(100, 100 + HYP), 100, 100, PI / 2, Color::green);
    righttriangle rt_4(Point(100 + HYP / 2 - LEG, 100 + HYP / 2), 100, 100, PI / 4 * 3, Color::cyan);
    righttriangle rt_5(Point(100, 100), 100, 100, PI, Color::blue);
    righttriangle rt_6(Point(100 + HYP / 2, 100 + HYP / 2 - LEG), 100, 100, PI / 4 * 5, Color::magenta);
    righttriangle rt_7(Point(100 + HYP, 100), 100, 100, PI / 2 * 3, Color::black);
    righttriangle rt_8(Point(100 + HYP / 2 + LEG, 100 + HYP / 2), 100, 100, PI / 4 * 7, Color::white);

    win.attach(rt_1);
    win.attach(rt_2);
    win.attach(rt_3);
    win.attach(rt_4);
    win.attach(rt_5);
    win.attach(rt_6);
    win.attach(rt_7);
    win.attach(rt_8);
    
    win.wait_for_button();       // give control to the display engine
}

//------------------------------------------------------------------------------
