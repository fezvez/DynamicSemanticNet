#include "gdl_nextsentence.h"

GDL_NextSentence::GDL_NextSentence(PConstant nh, PConstant h, QVector<PTerm> b, GDL_TYPE t):
    GDL_RelationalSentence(h,b,t),
    nextHead(nh)
{
    Q_ASSERT(t == GDL::NEXT);


}

PConstant GDL_NextSentence::getRelationConstant(){
    return nextHead;
}

PConstant GDL_NextSentence::getHead(){
    return getRelationConstant();
}


