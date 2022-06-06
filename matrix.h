#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>
#include <vector>
#include <iostream>
using namespace std;

//如果使用3文件结构，成员函数的定义在另一文件中会有奇怪的报错，所以此处暂时成员函数的声明和定义放在一起
//使用了类模板
//将稀松矩阵和密集矩阵分为了两类
//具体的操作函数 可以是成员函数或者友元函数 或者常规的传入两个矩阵参数的函数
//同时，因为使用std::complex，所以没有额外写一个complex的class
//如果想要加上自定义类型，需要新定义一个类，并重写关于这个类的operator(+,-,*,/,<<)
//且暂时没有提供没有参数的构造器，必须要在初始化的时候确定矩阵的row和col
//如果后面需要一些复制矩阵之类的方法，可以添加，因为暂时不知道还不知道需要些什么方法所以还没写

//初始化矩阵必须确定矩阵的row和col
//不能出现matrix<int> c();这种无参数的情况

//稀松矩阵的三元组
template <class T>
struct triple
{
    //该元素在稀松矩阵的第几行和第几列
    int row_of_element;
    int column_of_element;
    T val;
};

template <class T>
class matrix
{
private:
    long long row;    //该矩阵有多少行
    long long column; //该矩阵有多少列

    //当一个矩阵过大，行数超过long long，我们需要分割矩阵
    // m_row表示当前矩阵在分割后的矩阵的第几行和第几列
    //最左上角的矩阵是第0行第0列
    //但是这样也仅支持long long*long long 长度的矩阵
    long long m_row; // start with index 0
    long long m_column;

    //二维动态数组
    //内存不够
    //long[10000][10000]就会爆掉
    vector<vector<T>> data;

public:
    matrix(long long row, long long col, long long m_row = 0, long long m_column = 0)
    {
        if (row <= 0 || col <= 0)
        {
            std::cout << "The value of col or row are not allowed" << endl;
        }
        else
        {
            this->row = row;
            this->column = col;
            this->m_row = m_row;
            this->m_column = m_column;
            vector<T> temp(col);
            this->data.resize(row, temp);
        }
    }
    matrix(vector<vector<T>> data, long long m_row = 0, long long m_column = 0)
    {        
            this->row = data.size();
            this->column = data[0].size();
            this->m_row = m_row;
            this->m_column = m_column;
            this->data = data;
    }

    T get_value(int row, int col) //访问最左上角的元素输入get_value(1,1)
    {
        if (row <= 0 || col <= 0 || row > this->data.size() || col > this->data[0].size())
        {
            std::cout << "The value of col or row are not allowed" << endl;
            exit(0);
        }
        return this->data[row - 1][col - 1];
    }
    void set_value(int row, int col, T val)
    {
        if (row <= 0 || col <= 0 || row > this->data.size() || col > this->data[0].size())
        {
            std::cout << "The value of col or row are not allowed" << endl;
            exit(0);
        }
        this->data[row - 1][col - 1] = val;
    }

    void display()
    {
        for (int i = 0; i < this->data.size(); i++)
        {
            for (int j = 0; j < this->data[0].size(); j++)
            {
                std::cout<<this->data[i][j]<<"  ";
            }
            std::cout<<endl;
        }
        cout<<endl;
    }
};

template <class T>
class sparse_matrix
{
private:
    long long row;
    long long column;
    long long m_row;
    long long m_column;
    vector<triple<T>> data;

public:
    sparse_matrix(long long row, long long col, long long m_row = 0, long long m_column = 0)
    {
        if (row <= 0 || col <= 0)
        {
            cout << "The value of col or row are not allowed" << endl;
        }
        else
        {
            this->row = row;
            this->column = col;
            this->m_row = m_row;
            this->m_column = m_column;
        }
    }
    
    
    /*
    因为vector<triple<T>> data中的元素的行数和列数可能超过矩阵本身的行数和列数，所以这种初始化方式暂时注释掉
    sparse_matrix(long long row, long long col, vector<triple<T>> data, long long m_row = 0, long long m_column = 0){
        if (row <= 0 || col <= 0)
        {
            cout << "The value of col or row are not allowed" << endl;
        }
        else
        {
            this->row = data.size();
            this->column = data.size();
            this->m_row = m_row;
            this->m_column = m_column;
            this->data = data;
        }
    }
    */

    T get_value(int row, int col)
    { //如果没有，则返回0，暂时是暴力遍历，最坏情况下O(n^2)复杂度，可能后面优化一下
        if (row <= 0 || col <= 0 || row > this->row || col > this->column)
        {
            std::cout << "The value of col or row are not allowed" << endl;
            exit(0);
        }
        for (int i = 0; i < this->data.size(); i++)
        {
            if (this->data[i].row_of_element == row && this->data[i].column_of_element == col)
            {
                return this->data[i].val;
            }
        }
        return 0;
    }
    void set_value(int row, int col, T val)
    { //如果没有，则插入0，暂时是暴力遍历，最坏情况下O(n^2)复杂度，可能后面优化一下
        if (row <= 0 || col <= 0 || row > this->row || col > this->column)
        {
            std::cout << "The value of col or row are not allowed" << endl;
            exit(0);
        }
        bool find = false;
        for (int i = 0; i < this->data.size(); i++)
        {
            if (this->data[i].row_of_element == row && this->data[i].column_of_element == col)
            {
                this->data[i].val = val;
                find = true;
                break;
            }
        }
        if (!find)
        {
            triple<T> temp={row, col, val};
            this->data.push_back(temp);
        }
    }
    void display()
    {
        for (int i = 0; i < this->data.size(); i++)
        {
            std::cout<<"row:"<<this->data[i].row_of_element<<"  "<<"col:"<<this->data[i].column_of_element<<"  "<<"val:"<<this->data[i].val<<endl;
            cout<<endl;
        }
    }
};


#endif