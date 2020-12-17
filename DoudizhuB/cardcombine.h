#ifndef CARDCOMBINE
#define CARDCOMBINE

#include <vector>
using std::vector;
#include "card.h"
#include <QString>
#include <QtAlgorithms>

class CardCombine
{

public:
    vector<Card*> _list;
    bool is_Guo();               //过
    bool is_Single();            //单牌
    bool is_Shunzi(bool notpairs);                 //顺子
    bool is_Pair();             //对子
    bool is_Pairs();                //连对
    bool is_Three();             //三张
    bool is_Three_One();              //三带一
    bool is_Three_Two();              //三带二
    bool is_Four_Two();          //四带二
    bool is_Plane();                  //无翅飞机
    bool is_Plane_Single();      //飞机带单牌
    bool is_Plane_Pair();         //飞机带对子
    bool is_Boom();              //普通炸弹
    bool is_KingBoom();          //王炸
    void combineSort();

    enum Type
    {
        Unknown,                      //非法牌型
        Guo,                          //过
        Single,                       //单张
        Shunzi,                       //顺子
        Pair,                        //对子
        Pairs,                      //连对
        Three,                        //三张
        Three_One,                    //三带一
        Three_Two,                    //三带二
        Four_Two,                     //四带二
        Plane,                        //无翅飞机
        Plane_Single,                 //飞机带同数量的单张
        Plane_Pair,                    //飞机带同数量的对子
        Boom,                         //炸弹
        KingBoom,                     //王炸
    };
    enum CompareRes
    {
        Smaller,                      //比不过
        Equal,                        //一样大
        Larger,                       //比得过
        CannotCompare,                //无法比较
    };
    CardCombine();
    vector<Card*> getList()const;                //get the list of cards
    void setList(const vector<Card*>& list); //set the list of cards
    Type getType();                             //返回牌型
    static int priority(Type type);             //计算某牌型的优先级(5,4,3,2,1,值越大越优先级越高)
    Point representPoint(Type type);            //计算代表点数
    CompareRes compareTo(CardCombine& combine); //牌组权值比较
    void clear();

};

#endif
