/**
 * @file InterpConditions.H
 * @brief 一个记录实数插值点列及对应函数值导数值的类
 * @author htli (3180102114@zju.edu.cn)
 * @version 1.0
 * @date 2021-10-22
 * 
 * @copyright Copyright (c) 2021  linhuo2020
 * 
 */
#ifndef _PROJECT3_INTERPCONDITIONS_H_
#define _PROJECT3_INTERPCONDITIONS_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Config.H"

class InterpConditions
{
protected:
    ///由若干插值向量组成的向量，称为插值箱
    ///规定每个插值向量首项是互不相同的插值点，后续依次存储的是该点处的函数值，一次导数值，二次导数值，……
    RealBox IntpInfo_;
    ///精度（两数之差小于精度时会被认为一个数）
    Real tolerance_ = 1e-7;

public:
    InterpConditions(){};
    ///创建一个以给定插值点列及对应的函数值导数值为内容的插值条件
    InterpConditions(const RealBox &_IntpInfo);
    ~InterpConditions()=default;

  ///清空插值箱中所有插值信息，并增加插值点列及对应的函数值导数值
    void ResetIntpInfo(const RealBox &_IntpInfo);

  ///增加一个插值点及对应的函数值导数值;如果已有这个插值点，则清空旧数据并用新数据覆盖
    void ResetIntpSite(const RealVect &_SiteInfo);

  ///检验是否为只提供函数值的牛顿型插值;若是则真
    const bool is_PrimaryIntp() const;

  ///搜索插值箱中第几个插值向量对应该插值点;若未含有该点则返回-1
    const int where_has_Site(const Real &_x) const;

  ///检验插值点信息合法性;合法则真
    const bool SiteLegality(const RealVect &_SiteInfo) const{ return (_SiteInfo.size() > 1); };

  ///检验插值点列信息合法性(首先每个插值长度不小于2,其次插值点互不相同);合法则真
    const bool InfoLegality(const RealBox &_IntpInfo) const;

  ///获得差分表型的插值列
    const RealVect getIntpSets() const;

  ///获得插值箱中全部信息
    const RealBox getIntpInfo() const { return IntpInfo_; };

  ///格式化输出插值条件
    friend std::ostream &operator<<(std::ostream &os, const InterpConditions &_IntpConds);
};


InterpConditions::InterpConditions(const RealBox &_IntpInfo)
{
    this->ResetIntpInfo(_IntpInfo);
}


void InterpConditions::ResetIntpInfo(const RealBox &_IntpInfo)
{
    if (this->InfoLegality(_IntpInfo))
        {IntpInfo_ = _IntpInfo;}
    else
    {
        std::cout << "Warning: illegal input." << std::endl;
    };
}

void InterpConditions::ResetIntpSite(const RealVect &_SiteInfo)
{
    if (this->SiteLegality(_SiteInfo))
    {
        const int cord = this->where_has_Site(_SiteInfo[0]);
        if (cord < 0)
            IntpInfo_.push_back(_SiteInfo);
        else
        {
            IntpInfo_[cord] = _SiteInfo;
        };
    }
    else
    {
        std::cout << "Warning: illegal input." << std::endl;
    };
};

const bool InterpConditions::is_PrimaryIntp() const
{
    bool flag = true;
    RealVect SitesSeq = this ->getIntpSets();
    RealVect::iterator it = adjacent_find(SitesSeq.begin(), SitesSeq.end());
    if (it != SitesSeq.end())
    {
        flag = false;
    }
    return flag;
}

const bool InterpConditions::InfoLegality(const RealBox &_IntpInfo) const
{
    bool flag = true;
    const int IntpInfoSize = _IntpInfo.size();
    RealVect SitesSeq;
    for (int i = 0; i < IntpInfoSize; i++)
    {
        flag *= this->SiteLegality(_IntpInfo[i]);
        SitesSeq.push_back(_IntpInfo[i][0]);
    }
    RealVect::iterator it = adjacent_find(SitesSeq.begin(), SitesSeq.end());
    if (it != SitesSeq.end())
    {
        flag = false;
    };
    return flag;
}

const int InterpConditions::where_has_Site(const Real &_x) const
{
    const int IntpInfoSize = this->getIntpInfo().size();
    for (int i = 0; i < IntpInfoSize; i++)
    {
        if (fabs(this->getIntpInfo()[i][0] - _x) < tolerance_)
            return i;
    }
    return -1;
}

const RealVect InterpConditions::getIntpSets() const
{
    const RealBox IntpInfo = this->getIntpInfo();
    const int IntpInfoSize = IntpInfo.size();
    RealVect IntpSets;
    for (int i = 0; i < IntpInfoSize; i++)
    {
        int SiteInfoSize = IntpInfo[i].size();
        for (int j = 1; j < SiteInfoSize; j++)
            IntpSets.push_back(IntpInfo[i][0]);
    }
    return IntpSets;
}

std::ostream &operator<<(std::ostream &os, const InterpConditions &_IntpConds)
{
    const RealBox IntpInfo = _IntpConds.getIntpInfo();
    const int IntpInfoSize = IntpInfo.size();
    for (int i = 0; i < IntpInfoSize; i++)
    {
        const Real xi = IntpInfo[i][0];
        const int SiteInfoSize = IntpInfo[i].size();
        os << "f(" << xi << ") = " << IntpInfo[i][1];
        for (int j = 2; j < SiteInfoSize; j++)
            os << " ,d^" << (j - 1) << "f(" << xi << ") = " << IntpInfo[i][j];
        os << std::endl;
    }
    return os;
}

#else
//do nothing
#endif
