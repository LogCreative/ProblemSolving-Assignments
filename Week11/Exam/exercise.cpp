#include "std_lib_facilities.h"
#include "Exercise_1.h"
#include "Exercise_2.h"
#include "Exercise_3.h"
int main()
{
    /********** Begin **********/
    int exercise_1 = 1;
    //int exercise_1 = 2;
    //int exercise_1 = 3;
    if (exercise_1 == 1) {
        //第一关执行代码
        //Please fix Exercise_1.h and Exercise_1.cpp
        string rl;
        X x;
        while (getline(cin, rl)) 
            x.inputProgram(rl);
        x.outputQueue();
    }
    else if (exercise_1 == 2) {
        //第二关执行代码
        //Please fix Exercise_2.h and Exercise_2.cpp  
        string str;
        getline(cin, str);


    }
    else if (exercise_1 == 3) {
        //第二关执行代码
         //Please fix Exercise_3.h and Exercise_3.cpp  
        string str;
        getline(cin, str);




    }
    else {
        cout << "error";

    }

    /********** End **********/
    return 0;
}

