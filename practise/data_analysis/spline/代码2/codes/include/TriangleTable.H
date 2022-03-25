/**
 * @file TriangleTable.H
 * @brief 一个三角型二维存储空间的模板类。
 * @author htli (3180102114@zju.edu.cn)
 * @version 1.0
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021  linhuo2020
 * 
 */
#ifndef _PROJECT3_TRIANGLETABLE_H_
#define _PROJECT3_TRIANGLETABLE_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Config.H"

#define TriTab TriangleTable<T>
template <class T>
class TriangleTable;

template <class T>
std::ostream &operator<<(std::ostream &os, const TriangleTable<T> &_TriTab);

template <class T>
class TriangleTable
{
protected:
    std::vector<Real> RowNames_;
    std::vector<T> elements_;

public:
    TriangleTable(){};
    TriangleTable(const std::vector<T> &_elements) { this->setEles(_elements); };
    ~TriangleTable()=default;
    void setRowNames(const std::vector<Real> &_RowNames) { RowNames_ = _RowNames; };

  ///按三角表的格式存储元素
    void setEles(const std::vector<T> &_elements) { elements_ = _elements; };

  ///清空元素与行名
    void clearAll();

  ///往现有的三角表中末尾填充一个元素
    void addEle(const T &_newele);

  ///根据二维坐标定位元素
    const T locate(const int &_x, const int &_y) const;

  ///获得所有元素
    const std::vector<T> getEles() const { return elements_; };

  ///获得每行的行名
    const std::vector<Real> getRowNames() const { return RowNames_; };

  ///获得对角线上所有元素
    const std::vector<T> getDiag() const;

  ///获得第N列上的所有元素(N从1开始计数)
    const std::vector<T> getNthCol(const int N) const;

  ///获得元素总数
    const int getNumEle() const { return this->getEles().size(); };

  ///获得已按三角阵形式填满的行数
    const int getNumRow() const;

  ///判断三角表的每一行是否被填满
    const bool is_Full() const;

  ///输出当前已填满的所有行
    friend std::ostream & operator<< <>(std::ostream &os, const TriangleTable<T> &_TriTab);
};

template <class T>
const int TriangleTable<T>::getNumRow() const
{
    const int eleSize = this->getNumEle();
    const int validRow = floor(sqrt(2 * eleSize + 0.25) - 0.5);
    return validRow;
}

template <class T>
const std::vector<T> TriangleTable<T>::getNthCol(const int N) const
{
    const int RowNum = this->getNumRow();
    std::vector<T> eleNCol;
    for (int i = N-1; i < RowNum; i++)
        eleNCol.push_back(this->locate(i, N-1));
    return eleNCol;
}

template <class T>
const std::vector<T> TriangleTable<T>::getDiag() const
{
    const int RowNum = this->getNumRow();
    std::vector<T> eleDiag;
    for (int i = 0; i < RowNum; i++)
        eleDiag.push_back(this->locate(i, i));
    return eleDiag;
}

template <class T>
const T TriangleTable<T>::locate(const int &_x, const int &_y) const
{
    if (_x >= _y)
    {
        return this->getEles()[(_x + 1) * _x / 2 + _y];
    }
    else
    {
        return this->getEles()[(_y + 1) * _y / 2 + _x];
    };
};

template <class T>
const bool TriangleTable<T>::is_Full() const
{
    const int NumRow = this->getNumRow();
    return (NumRow * (NumRow + 1) == (2 * (this->getNumEle)));
}

template <class T>
void TriangleTable<T>::clearAll()
{
    elements_.clear();
    RowNames_.clear();
}

template <class T>
void TriangleTable<T>::addEle(const T &_newele)
{
    elements_.push_back(_newele);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const TriangleTable<T> &_TriTab)
{
    const std::vector<T> ele = _TriTab.getEles();
    const std::vector<Real> rowNames = _TriTab.getRowNames();
    const int rowSize = _TriTab.getNumRow();
    for (int i = 0; i < rowSize; i++)
    {
        os << " Row" << i << " " << rowNames[i] << " :";
        for (int j = 0; j <= i; j++)
        {
            os << " " << _TriTab.locate(i, j);
        }
        os << std::endl;
    }
    return os;
}
#else
//do nothing
#endif
