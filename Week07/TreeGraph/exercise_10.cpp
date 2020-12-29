#include "std_lib_facilities.h"
#include "NodeRecognition.h"
#include "TreeConstruct.h"

int main()
{
    bool exercise_1 = false;
    if (exercise_1) {
        //第一关执行代码
        //Please fix NodeRecognition.h and NodeRecognition.cpp
        string str;
        getline(cin, str);
        NodeRecognition nr(str);
        nr.prtStruct();
    }
    else {
        //第二关执行代码
        //Please fix TreeConstruct.h and TreeConstruct.cpp
        string str1, str2;
        getline(cin, str1);
        getline(cin, str2);
        TreeIsotope ti(str1, str2);
        ti.prtLayer();
        ti.prtTCode();
        ti.prtRes();
    }
    /********** End **********/
    return 0;
}