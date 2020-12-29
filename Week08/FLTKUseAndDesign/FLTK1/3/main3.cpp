
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities
#include "Binary_tree.h"
#include "TriangleBinary_tree.h"
#include <iostream>
//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    int N;
    cin >> N;

    Point tl(100,100);           // to become top left  corner of window
    Point shift(20, 20);         // Æ«ÒÆÁ¿

    Simple_window win(tl, pow(2, N - 1) * w + shift.x, (N * h + shift.y) * 2, "Binary_tree");    // make a simple window

    Binary_tree bt(N, shift, Color::red);
    win.attach(bt);
    TriangleBinary_tree rbt(N, Point(shift.x, N * h + shift.y + 20), Color::green);
    win.attach(rbt);

    win.wait_for_button();       // give control to the display engine
}

//------------------------------------------------------------------------------
