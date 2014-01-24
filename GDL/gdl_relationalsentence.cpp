#include "gdl_relationalsentence.h"

GDL_RelationalSentence::GDL_RelationalSentence(PConstant h, QVector<PTerm> b):
    head(h),
    body(b)
{
}

bool GDL_RelationalSentence::isGround() const{
    return false;
}
