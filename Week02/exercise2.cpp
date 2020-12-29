#include "std_lib_facilities.h"
#include "Polynomial.h"

int main()
{
    //请打开文件目录修改Polynomial.h，Polynomial.cpp，和exercise_2.cpp
    /********** Begin **********/
    
    bool exercise1=true;
    if(exercise1)    {
    //第一关执行代码
        string str;          
        getline(cin,str);
        double x;
        cin >> x;
        Polynomial poly(str+' ');
        poly.print();
        poly.printDerivitive();
        poly.getValue(x);
   
    }   else     {
    //第二关执行代码
        string str1, str2;
        getline(cin, str1);
        getline(cin, str2);
        Polynomial poly1(str1 + ' '), poly2(str2 + ' ');
        Divide(poly1, poly2);
        
    }
	/********** End **********/
  	return 0;
}

