
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities
#include "hyperelliptic.h"
#include <iostream>

//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    int a, b, m, n, N;
    std::cin >> a >> b >> m >> n >> N;

    Point tl(100, 100);
    Point shift(100, 100);
    Simple_window win(tl, 2 * (shift.x + a), 2 * (shift.y + b),"hyperelliptic");    // make a simple window
    
    hyperelliptic hyptic(shift, a, b, m, n, N);               // ≥¨Õ÷‘≤
    hyptic.set_color(Color::red);
    win.attach(hyptic);

    win.wait_for_button();
}

//------------------------------------------------------------------------------
