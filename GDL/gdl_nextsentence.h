#ifndef GDL_NEXTSENTENCE_H
#define GDL_NEXTSENTENCE_H

#include "gdl_constant.h"
#include "gdl_relationalsentence.h"

class GDL_NextSentence;
typedef QSharedPointer<GDL_NextSentence> PNextSentence;

class GDL_NextSentence : public GDL_RelationalSentence
{
public:
    GDL_NextSentence(PConstant nh, PConstant h, QVector<PTerm> b, GDL::GDL_TYPE t = GDL::NONE);

    PConstant getHead();
    PConstant getRelationConstant();

protected:
    PConstant nextHead;
};

#endif // GDL_NEXTSENTENCE_H
