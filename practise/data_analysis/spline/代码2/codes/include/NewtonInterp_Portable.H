/**
 * @file NewtonInterp_Portable.H
 * @brief 一个精简版的广义Newton（即包括Hermite）插值的实现类，
 * 可以根据输入的插值条件计算差分表的前n列;
 * @author htli (3180102114@zju.edu.cn)
 * @version 1.0
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021  linhuo2020
 * 
 */
#ifndef _PROJECT3_NEWTONINTERPHT_M_H_
#define _PROJECT3_NEWTONINTERPHT_M_H_

#include <iostream>
#include <vector>


#include "InterpConditions.H"
#include "TriangleTable.H"
#include "Config.H"

class NewtonInterp
{
protected:
    TriangleTable<Real> tableOfDividedDiffs_;
    InterpConditions IntpConds_;

public:
    NewtonInterp(){};
    NewtonInterp(const InterpConditions &_IntpConds) { this->ResetIntpConds(_IntpConds); };
    ~NewtonInterp()=default;
    void ResetIntpConds(const InterpConditions &_IntpConds) { IntpConds_ = _IntpConds; };
    const InterpConditions getIntpConds() const { return IntpConds_; };
    ///根据插值条件输出差分表的前N列，不需要的部分用0补齐
    void QuickInterp(int N);
    ///格式化输出差分表与插值多项式
    const void Display() const;
    ///获得存储的差分表
    const TriangleTable<Real> getTableOfDividedDiffs()const{return tableOfDividedDiffs_;};
};

void NewtonInterp::QuickInterp(int N)
{
    tableOfDividedDiffs_.clearAll();

    const InterpConditions IntpConds = this->getIntpConds();

    const RealBox IntpInfo = IntpConds.getIntpInfo();

    const RealVect RowNames = IntpConds.getIntpSets();

    tableOfDividedDiffs_.setRowNames(RowNames);
    const int RowNum = RowNames.size();

    tableOfDividedDiffs_.addEle(IntpInfo[0][1]);
    int SameSiteFlag = 1;
    int SiteIndex = 0;

    for (int tempRow = 1; tempRow < RowNum; tempRow++)
    {
        if (RowNames[tempRow - 1] == RowNames[tempRow])
        {
            SameSiteFlag++;
        }
        else
        {
            SameSiteFlag = 1;
            SiteIndex++;
        };
        int j = 0;

	for (; j < SameSiteFlag && j < N; j++)
            tableOfDividedDiffs_.addEle(IntpInfo[SiteIndex][j + 1] / fac(j));

	for (; j < tempRow + 1 && j < N; j++)
            tableOfDividedDiffs_.addEle((tableOfDividedDiffs_.locate(tempRow, j - 1) - tableOfDividedDiffs_.locate(tempRow - 1, j - 1)) / (RowNames[tempRow] - RowNames[tempRow - j]));

	for(;j < tempRow + 1;j++)
            tableOfDividedDiffs_.addEle(0);
    }
}

const void NewtonInterp::Display() const
{
    std::cout << tableOfDividedDiffs_;
}

#else
//do nothing
#endif
