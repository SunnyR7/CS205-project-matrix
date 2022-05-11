#include <iostream>
#include "matrix.h"
#include "complex"
using namespace std;

/*
只是简单测试了下面几种

matrix的两种初始化方式
matrix的复数类型
matrix get
matrix set

sparse_matrix的初始化方式
sparse_matrix get
sparse_matrix set

然后在linux系统上跑一下
*/


int main()
{
    cout<<"---------------test1--------------"<<endl;
    matrix<complex<int>> a(4,5);
    a.display();
    complex<double> z1 {2, 5};
    a.set_value(1,1,z1);
    a.display();
    a.set_value(1,1,4);
    a.set_value(1,2,5);
    a.display();
    cout<<a.get_value(1,1)<<endl;

    cout<<"---------------test2--------------"<<endl;
    //下面这两种初始化动态二维数组的方式都可以

    // vector<vector<int>> temp_data(5); //定义二维动态数组大小5行   
    // for(int i =0; i< temp_data.size(); i++)//动态二维数组为5行4列，值全为0 
    // { 
    //     temp_data[i].resize(4); 
    // }
    // temp_data[3][3]=2;

    vector<int> temp(7);
    vector<vector<int>> temp_data2;
    temp_data2.resize(6, temp); //动态二维数组为6行7列，值全为0

    matrix<int> test2(temp_data2);
    test2.display();
    test2.set_value(1,1,4);
    test2.set_value(1,2,5);
    test2.display();

    cout<<"---------------test3--------------"<<endl;
    sparse_matrix<complex<int>> b(4,4);
    b.display();//没有元素，不打印
    complex<double> z2 {2, 5};
    b.set_value(1,1,z2);
    b.display();
    b.set_value(1,1,5);
    b.set_value(1,2,7);
    b.display();
    cout<<b.get_value(1,2)<<endl;
    
    return 0;
}
