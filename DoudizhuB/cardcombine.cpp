#include "cardcombine.h"
#include <algorithm>
#include <cstring>
using std::sort;
using std::memset;


CardCombine::CardCombine()
{

}

vector<Card*> CardCombine::getList()const
{
    return _list;
}


void CardCombine::setList(const vector<Card*> &list)
{
    _list=list;
}


void CardCombine::combineSort()
{
    for(int i=0;i<_list.size();i++){
        for(int j=0;j<_list.size()-1;j++){
            if(_list[j]->getPoint()>_list[j+1]->getPoint()){
                std::swap(_list[j],_list[j+1]);
            }
        }
    }
}


bool CardCombine::is_Guo()
{
    return _list.size()==0;
}


bool CardCombine::is_Single()
{
    return _list.size()==1;
}


bool CardCombine::is_Shunzi(bool notpairs)
{
    int n=static_cast<int>(_list.size());
    if(notpairs){
        if(n<5)
            return false;
    }
    combineSort();
    if(_list[n-1]->getPoint()>Point::Card_A)
        return false;
    for(int i=0;i<n-1;i++){
        if(_list[i+1]->getPoint()-_list[i]->getPoint()!=1)
            return false;
    }
    return true;
}







bool CardCombine::is_Pair()
{
    int n=static_cast<int>(_list.size());
    return n==2&&_list[0]->getPoint()==_list[1]->getPoint();
}


bool CardCombine::is_Pairs()
{
    int n=static_cast<int>(_list.size());
    if(n<6||n%2!=0)
        return false;
    combineSort();
    n=n/2;
    for(int i=0;i<n;i++){
        if(_list[2*i]->getPoint()!=_list[2*i+1]->getPoint())
            return false;
    }
    CardCombine cc;
    for(int i=0;i<n;i++)
        cc._list.push_back(_list[2*i]);
    return cc.is_Shunzi(false);
}


bool CardCombine::is_Three()
{
    int n=static_cast<int>(_list.size());
    return n==3&&_list[0]->getPoint()==_list[1]->getPoint()&&_list[0]->getPoint()==_list[2]->getPoint();
}


bool CardCombine::is_Three_One()
{
    int n=static_cast<unsigned int>(_list.size());
    if(n!=4)
        return false;
    combineSort();
    if(_list[0]->getPoint()==_list[1]->getPoint()&&_list[0]->getPoint()==_list[2]->getPoint()&&_list[0]->getPoint()!=_list[3]->getPoint())
        return true;
    if(_list[1]->getPoint()==_list[2]->getPoint()&&_list[1]->getPoint()==_list[3]->getPoint()&&_list[0]->getPoint()!=_list[1]->getPoint())
        return true;
    return false;
}


bool CardCombine::is_Three_Two()
{
    int n=static_cast<int>(_list.size());
    if(n!=5)
        return false;
    combineSort();
    if(_list[0]->getPoint()==_list[1]->getPoint()&&_list[0]->getPoint()==_list[2]->getPoint()&&_list[3]->getPoint()==_list[4]->getPoint()&&_list[0]->getPoint()!=_list[3]->getPoint())
        return true;
    if(_list[0]->getPoint()==_list[1]->getPoint()&&_list[2]->getPoint()==_list[3]->getPoint()&&_list[2]->getPoint()==_list[4]->getPoint()&&_list[0]->getPoint()!=_list[2]->getPoint())
        return true;
    return false;
}


bool CardCombine::is_Four_Two()
{

    int n=static_cast<int>(_list.size());
    if(n!=6&&n!=8)
        return false;
    if(n==6){
        int count[16];
        memset(count,0,16*sizeof(int));
        for(int i=0;i<n;i++)
            count[_list[i]->getPoint()]++;
        for(int i=0;i<16;i++){
            if(count[i]==4)
                return true;
        }
        return false;
    }
    else if(n==8){
        combineSort();
        if(_list[0]->getPoint()==_list[1]->getPoint()&&_list[0]->getPoint()==_list[2]->getPoint()&&_list[0]->getPoint()==_list[3]->getPoint()){
            if(_list[4]->getPoint()==_list[5]->getPoint()&&_list[6]->getPoint()==_list[7]->getPoint()){
                return true;
            }
        }
        else if (_list[2]->getPoint()==_list[3]->getPoint()&&_list[2]->getPoint()==_list[4]->getPoint()&&_list[2]->getPoint()==_list[5]->getPoint()) {
            if(_list[0]->getPoint()==_list[1]->getPoint()&&_list[6]->getPoint()==_list[7]->getPoint()){
                return true;
            }
        }
        else if (_list[4]->getPoint()==_list[5]->getPoint()&&_list[4]->getPoint()==_list[6]->getPoint()&&_list[4]->getPoint()==_list[7]->getPoint()) {
            if(_list[0]->getPoint()==_list[1]->getPoint()&&_list[2]->getPoint()==_list[3]->getPoint()){
                return true;
            }
        }
        else{
            return false;
        }
    }
}


bool CardCombine::is_Plane()
{
    int n=static_cast<int>(_list.size());
    if(n<6||n%3!=0)
        return false;
    combineSort();
    n=n/3;
    for(int i=0;i<n;i++){
        if(_list[3*i]->getPoint()!=_list[3*i+1]->getPoint() || _list[3*i]->getPoint()!=_list[3*i+2]->getPoint())
            return false;
    }


    CardCombine cc;
    for(int i=0;i<n;i++)
        cc._list.push_back(_list[3*i]);
    return cc.is_Shunzi(false);
}


bool CardCombine::is_Plane_Single()
{

    int count[16];
    memset(count,0,16*sizeof(int));
    int n=static_cast<int>(_list.size());
    for(int i=0;i<n;i++)
        count[_list[i]->getPoint()]++;
    CardCombine cc1,cc2;
    for(int i=0;i<n;i++){
        if(count[_list[i]->getPoint()]==1)
            cc1._list.push_back(_list[i]);
        else
            cc2._list.push_back(_list[i]);
    }
    return cc2.getList().size()==3*cc1.getList().size()&&cc2.is_Plane();
}


bool CardCombine::is_Plane_Pair()
{
    int count[16];
    memset(count,0,16*sizeof(int));
    int n=static_cast<int>(_list.size());
    for(unsigned int i=0;i<n;i++)
        count[_list[i]->getPoint()]++;
    CardCombine cc1,cc2;
    for(int i=0;i<n;i++){
        if(count[_list[i]->getPoint()]==2)
            cc1._list.push_back(_list[i]);
        else
            cc2._list.push_back(_list[i]);
    }
    return 2*cc2.getList().size()==3*cc1.getList().size()&&cc2.is_Plane();
}


bool CardCombine::is_Boom()
{
    int n=static_cast<int>(_list.size());
    return n==4&&_list[0]->getPoint()==_list[1]->getPoint()&&_list[0]->getPoint()==_list[2]->getPoint()&&_list[0]->getPoint()==_list[3]->getPoint();
}


bool CardCombine::is_KingBoom()
{
    int n=static_cast<int>(_list.size());
    if(n!=2)
        return false;
    if(_list[0]->getPoint()==Point::Card_RK&&_list[1]->getPoint()==Point::Card_BK)
        return true;
    if(_list[0]->getPoint()==Point::Card_BK&&_list[1]->getPoint()==Point::Card_RK)
        return true;
    return false;
}


CardCombine::Type CardCombine::getType()
{
    if(is_Guo())
        return Type::Guo;
    if(is_Single())
        return Type::Single;
    if(is_Shunzi(true))
        return Type::Shunzi;
    if(is_Pair())
        return Type::Pair;
    if(is_Pairs())
        return Type::Pairs;
    if(is_Three())
        return Type::Three;
    if(is_Three_One())
        return Type::Three_One;
    if(is_Three_Two())
        return Type::Three_Two;
    if(is_Four_Two())
        return Type::Four_Two;
    if(is_Plane())
        return Type::Plane;
    if(is_Plane_Single())
        return Type::Plane_Single;
    if(is_Plane_Pair())
        return Type::Plane_Pair;
    if(is_Boom())
        return Type::Boom;
    if(is_KingBoom())
        return Type::KingBoom;
    return Type::Unknown;
}


int CardCombine::priority(CardCombine::Type type)
{
    switch(type)
    {
    case Type::KingBoom:
        return 5;
    case Type::Boom:
        return 4;
    case Type::Guo:
        return 2;
    case Type::Unknown:
        return 1;
    default:
        return 3;
    }
    return 1;
}


Point CardCombine::representPoint(Type type)
{
    switch(type)
    {
    case Type::Guo:
        return Point::Card_Zero;
    case Type::Single:
        return _list[0]->getPoint();
    case Type::Shunzi:{
        combineSort();
        int n=static_cast<int>(_list.size());
        return _list[n-1]->getPoint();
    }
    case Type::Pair:
        return _list[0]->getPoint();
    case Type::Pairs:{
        combineSort();
        int n=static_cast<int>(_list.size());
        return _list[n-1]->getPoint();
    }
    case Type::Three:
        return _list[0]->getPoint();
    case Type::Three_One:{
        combineSort();
        if(_list[0]->getPoint()==_list[1]->getPoint())
            return _list[0]->getPoint();
        return _list[1]->getPoint();
    }
    case Type::Three_Two:{
        combineSort();
        if(_list[2]->getPoint()==_list[3]->getPoint())
            return _list[2]->getPoint();
        return _list[0]->getPoint();
    }
    case Type::Four_Two:{
        int count[16];
        memset(count,0,16*sizeof(int));
        int n=static_cast<int>(_list.size());
        for(int i=0;i<n;i++)
            count[_list[i]->getPoint()]++;
        for(int i=0;i<n;i++){
            if(count[_list[i]->getPoint()]==4)
                return _list[i]->getPoint();
        }

    }
    case Type::Plane:{
        combineSort();
        int n=static_cast<int>(_list.size());
        return _list[n-1]->getPoint();
    }
    case Type::Plane_Single:{
        int count[16];
        memset(count,0,16*sizeof(int));
        int n=static_cast<int>(_list.size());
        for(int i=0;i<n;i++)
            count[_list[i]->getPoint()]++;
        CardCombine temp;
        for(int i=0;i<n;i++){
            if(count[_list[i]->getPoint()]==3)
                temp._list.push_back(_list[i]);
        }
        return temp.representPoint(Type::Plane);
    }
    case Type::Plane_Pair:
        return this->representPoint(Type::Plane_Single);
    case Type::Boom:
        return _list[0]->getPoint();
    case Type::KingBoom:
        return Point::Card_BK;
    }
    return Point::Card_Zero;
}

CardCombine::CompareRes CardCombine::compareTo(CardCombine& combine)
{
    Type mine_type=getType();
    Type other_type=combine.getType();
    int mine_priority=priority(mine_type);
    int other_priority=priority(other_type);
    if(mine_priority<other_priority)
        return CompareRes::Smaller;
    if(mine_priority>other_priority)
        return CompareRes::Larger;
    if(mine_type==other_type){
        Point L_point=representPoint(mine_type);
        Point R_point=combine.representPoint(other_type);
        if(this->_list.size()!=combine._list.size()){
            return CompareRes::CannotCompare;
        }
        if(L_point<R_point)
            return CompareRes::Smaller;
        if(L_point>R_point)
            return CompareRes::Larger;
        return CompareRes::Equal;
    }
    return CompareRes::CannotCompare;
}

void CardCombine::clear()
{
    for(int i=0;i<_list.size();i++){
        _list[i]->setVisible(false);
    }
    _list.clear();
}
